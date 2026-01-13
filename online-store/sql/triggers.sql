CREATE OR REPLACE FUNCTION trg_set_order_date_on_status_change()
RETURNS TRIGGER AS $$
BEGIN
  IF NEW.status IS DISTINCT FROM OLD.status THEN
    NEW.order_date := NOW();
  END IF;
  RETURN NEW;
END;
$$ LANGUAGE plpgsql;

DROP TRIGGER IF EXISTS set_order_date_on_status_change ON orders;
CREATE TRIGGER set_order_date_on_status_change
BEFORE UPDATE OF status ON orders
FOR EACH ROW
EXECUTE FUNCTION trg_set_order_date_on_status_change();


CREATE OR REPLACE FUNCTION trg_update_orders_on_product_price_change()
RETURNS TRIGGER AS $$
BEGIN
  IF NEW.price IS DISTINCT FROM OLD.price THEN
    UPDATE order_items oi
    SET price = NEW.price
    FROM orders o
    WHERE oi.order_id = o.order_id
      AND oi.product_id = NEW.product_id
      AND o.status = 'pending';

    UPDATE orders o
    SET total_price = sub.sum_price
    FROM (
      SELECT oi.order_id, SUM(oi.price * oi.quantity) AS sum_price
      FROM order_items oi
      WHERE oi.product_id = NEW.product_id
      GROUP BY oi.order_id
    ) sub
    WHERE o.order_id = sub.order_id;
  END IF;

  RETURN NEW;
END;
$$ LANGUAGE plpgsql;

DROP TRIGGER IF EXISTS update_orders_on_product_price_change ON products;
CREATE TRIGGER update_orders_on_product_price_change
AFTER UPDATE OF price ON products
FOR EACH ROW
EXECUTE FUNCTION trg_update_orders_on_product_price_change();


CREATE OR REPLACE FUNCTION trg_audit_products()
RETURNS TRIGGER AS $$
DECLARE
  v_user INT;
BEGIN
  BEGIN
    v_user := current_setting('app.user_id', true)::INT;
  EXCEPTION WHEN OTHERS THEN
    v_user := NULL;
  END;

  IF TG_OP = 'INSERT' THEN
    INSERT INTO audit_log(entity_type, entity_id, operation, performed_by, details)
    VALUES ('product', NEW.product_id, 'insert', v_user, 'Product inserted');
    RETURN NEW;
  ELSIF TG_OP = 'UPDATE' THEN
    INSERT INTO audit_log(entity_type, entity_id, operation, performed_by, details)
    VALUES ('product', NEW.product_id, 'update', v_user, 'Product updated');
    RETURN NEW;
  ELSIF TG_OP = 'DELETE' THEN
    INSERT INTO audit_log(entity_type, entity_id, operation, performed_by, details)
    VALUES ('product', OLD.product_id, 'delete', v_user, 'Product deleted');
    RETURN OLD;
  END IF;

  RETURN NULL;
END;
$$ LANGUAGE plpgsql;

DROP TRIGGER IF EXISTS audit_products ON products;
CREATE TRIGGER audit_products
AFTER INSERT OR UPDATE OR DELETE ON products
FOR EACH ROW
EXECUTE FUNCTION trg_audit_products();

-- =========================
-- AUDIT TRIGGER FOR USERS
-- =========================
CREATE OR REPLACE FUNCTION trg_audit_users()
RETURNS TRIGGER AS $$
DECLARE
  v_user INT;
BEGIN
  BEGIN
    v_user := current_setting('app.user_id', true)::INT;
  EXCEPTION WHEN OTHERS THEN
    v_user := NULL;
  END;

  IF TG_OP = 'INSERT' THEN
    INSERT INTO audit_log(entity_type, entity_id, operation, performed_by, details)
    VALUES ('user', NEW.user_id, 'insert', v_user, 'User inserted');
    RETURN NEW;
  ELSIF TG_OP = 'UPDATE' THEN
    INSERT INTO audit_log(entity_type, entity_id, operation, performed_by, details)
    VALUES ('user', NEW.user_id, 'update', v_user, 'User updated');
    RETURN NEW;
  ELSIF TG_OP = 'DELETE' THEN
    INSERT INTO audit_log(entity_type, entity_id, operation, performed_by, details)
    VALUES ('user', OLD.user_id, 'delete', v_user, 'User deleted');
    RETURN OLD;
  END IF;

  RETURN NULL;
END;
$$ LANGUAGE plpgsql;

DROP TRIGGER IF EXISTS audit_users ON users;
CREATE TRIGGER audit_users
AFTER INSERT OR UPDATE OR DELETE ON users
FOR EACH ROW
EXECUTE FUNCTION trg_audit_users();


-- =========================
-- BASIC AUDIT FOR ORDERS
-- =========================
CREATE OR REPLACE FUNCTION trg_audit_orders_basic()
RETURNS TRIGGER AS $$
DECLARE
  v_user INT;
BEGIN
  BEGIN
    v_user := current_setting('app.user_id', true)::INT;
  EXCEPTION WHEN OTHERS THEN
    v_user := NULL;
  END;

  IF TG_OP = 'INSERT' THEN
    INSERT INTO audit_log(entity_type, entity_id, operation, performed_by, details)
    VALUES ('order', NEW.order_id, 'insert', v_user, 'Order inserted (trigger)');
    RETURN NEW;
  ELSIF TG_OP = 'DELETE' THEN
    INSERT INTO audit_log(entity_type, entity_id, operation, performed_by, details)
    VALUES ('order', OLD.order_id, 'delete', v_user, 'Order deleted (trigger)');
    RETURN OLD;
  END IF;

  RETURN NULL;
END;
$$ LANGUAGE plpgsql;

DROP TRIGGER IF EXISTS audit_orders_basic ON orders;
CREATE TRIGGER audit_orders_basic
AFTER INSERT OR DELETE ON orders
FOR EACH ROW
EXECUTE FUNCTION trg_audit_orders_basic();

