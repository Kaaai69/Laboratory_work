CREATE OR REPLACE FUNCTION getOrderStatus(p_order_id INT)
RETURNS VARCHAR AS $$
  SELECT status FROM orders WHERE order_id = p_order_id;
$$ LANGUAGE sql;

CREATE OR REPLACE FUNCTION getUserOrderCount()
RETURNS TABLE(user_id INT, order_count BIGINT) AS $$
  SELECT u.user_id, COUNT(o.order_id)
  FROM users u
  LEFT JOIN orders o ON o.user_id = u.user_id
  GROUP BY u.user_id
  ORDER BY u.user_id;
$$ LANGUAGE sql;

CREATE OR REPLACE FUNCTION getTotalSpentByUser(p_user_id INT)
RETURNS NUMERIC AS $$
  SELECT COALESCE(SUM(total_price), 0)
  FROM orders
  WHERE user_id = p_user_id AND status = 'completed';
$$ LANGUAGE sql;

CREATE OR REPLACE FUNCTION canReturnOrder(p_order_id INT)
RETURNS BOOLEAN AS $$
  SELECT
    (status = 'completed')
    AND (NOW() - order_date <= INTERVAL '30 days')
  FROM orders
  WHERE order_id = p_order_id;
$$ LANGUAGE sql;

CREATE OR REPLACE FUNCTION getOrderStatusHistory(p_order_id INT)
RETURNS TABLE(old_status VARCHAR, new_status VARCHAR, changed_at TIMESTAMP, changed_by INT) AS $$
  SELECT old_status, new_status, changed_at, changed_by
  FROM order_status_history
  WHERE order_id = p_order_id
  ORDER BY changed_at;
$$ LANGUAGE sql;

CREATE OR REPLACE FUNCTION getAuditLogByUser(p_user_id INT)
RETURNS TABLE(entity_type VARCHAR, entity_id INT, operation VARCHAR, performed_at TIMESTAMP, details TEXT) AS $$
  SELECT entity_type, entity_id, operation, performed_at, details
  FROM audit_log
  WHERE performed_by = p_user_id
  ORDER BY performed_at DESC;
$$ LANGUAGE sql;

CREATE OR REPLACE FUNCTION getAuditOrderReport()
RETURNS TABLE(
  order_id INT,
  order_user_id INT,
  order_status VARCHAR,
  total_price NUMERIC,
  order_date TIMESTAMP,
  status_old VARCHAR,
  status_new VARCHAR,
  status_changed_at TIMESTAMP,
  status_changed_by INT,
  audit_entity_type VARCHAR,
  audit_operation VARCHAR,
  audit_by INT,
  audit_at TIMESTAMP,
  audit_details TEXT
) AS $$
  SELECT
    o.order_id,
    o.user_id,
    o.status,
    o.total_price,
    o.order_date,
    h.old_status,
    h.new_status,
    h.changed_at,
    h.changed_by,
    a.entity_type,
    a.operation,
    a.performed_by,
    a.performed_at,
    a.details
  FROM orders o
  LEFT JOIN order_status_history h ON h.order_id = o.order_id
  LEFT JOIN audit_log a
    ON (a.entity_type='order' AND a.entity_id=o.order_id)
  ORDER BY o.order_id, h.changed_at, a.performed_at;
$$ LANGUAGE sql;
