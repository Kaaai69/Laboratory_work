CREATE OR REPLACE PROCEDURE createOrder(
  p_user_id INT,
  p_items_json JSONB,
  OUT p_order_id INT
)
LANGUAGE plpgsql
AS $$
DECLARE
  v_order_id INT;
  v_total NUMERIC(12,2) := 0;
  v_item JSONB;
  v_pid INT;
  v_qty INT;
  v_price NUMERIC(12,2);
  v_stock INT;
BEGIN
  INSERT INTO orders(user_id, status, total_price, order_date)
  VALUES (p_user_id, 'pending', 0, NOW())
  RETURNING order_id INTO v_order_id;

  FOR v_item IN SELECT * FROM jsonb_array_elements(p_items_json)
  LOOP
    v_pid := (v_item->>'product_id')::INT;
    v_qty := (v_item->>'quantity')::INT;

    SELECT price, stock_quantity INTO v_price, v_stock
    FROM products WHERE product_id = v_pid FOR UPDATE;

    IF NOT FOUND THEN
      RAISE EXCEPTION 'Product % not found', v_pid;
    END IF;

    IF v_stock < v_qty THEN
      RAISE EXCEPTION 'Not enough stock for product % (have %, need %)', v_pid, v_stock, v_qty;
    END IF;

    UPDATE products SET stock_quantity = stock_quantity - v_qty
    WHERE product_id = v_pid;

    INSERT INTO order_items(order_id, product_id, quantity, price)
    VALUES (v_order_id, v_pid, v_qty, v_price);

    v_total := v_total + (v_price * v_qty);
  END LOOP;

  UPDATE orders SET total_price = v_total WHERE order_id = v_order_id;

  p_order_id := v_order_id;

  INSERT INTO audit_log(entity_type, entity_id, operation, performed_by, details)
  VALUES ('order', v_order_id, 'insert', p_user_id, 'Order created via procedure createOrder');

EXCEPTION WHEN OTHERS THEN
  INSERT INTO audit_log(entity_type, entity_id, operation, performed_by, details)
  VALUES ('order', COALESCE(v_order_id, -1), 'error', p_user_id, SQLERRM);
  RAISE;
END;
$$;

CREATE OR REPLACE PROCEDURE updateOrderStatus(
  p_order_id INT,
  p_new_status VARCHAR,
  p_changed_by INT
)
LANGUAGE plpgsql
AS $$
DECLARE
  v_old_status VARCHAR;
BEGIN
  SELECT status INTO v_old_status FROM orders WHERE order_id = p_order_id FOR UPDATE;
  IF NOT FOUND THEN
    RAISE EXCEPTION 'Order % not found', p_order_id;
  END IF;

  IF p_new_status = 'returned' AND NOT canReturnOrder(p_order_id) THEN
    RAISE EXCEPTION 'Order % cannot be returned (rules failed)', p_order_id;
  END IF;

  UPDATE orders SET status = p_new_status WHERE order_id = p_order_id;

  INSERT INTO order_status_history(order_id, old_status, new_status, changed_at, changed_by)
  VALUES (p_order_id, v_old_status, p_new_status, NOW(), p_changed_by);

  INSERT INTO audit_log(entity_type, entity_id, operation, performed_by, details)
  VALUES ('order', p_order_id, 'update', p_changed_by,
          'Status changed: ' || v_old_status || ' -> ' || p_new_status);

EXCEPTION WHEN OTHERS THEN
  INSERT INTO audit_log(entity_type, entity_id, operation, performed_by, details)
  VALUES ('order', p_order_id, 'error', p_changed_by, SQLERRM);
  RAISE;
END;
$$;
