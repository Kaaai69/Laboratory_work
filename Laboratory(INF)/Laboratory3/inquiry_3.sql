SELECT
	main_table.order_id,
	SUM(secondary_table.total_price) AS order_amount
FROM orders main_table
JOIN order_items secondary_table ON main_table.order_id = secondary_table.order_id
WHERE main_table.order_id = 1
GROUP BY main_table.order_id;
	

