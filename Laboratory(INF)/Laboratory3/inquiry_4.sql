SELECT
	main_table.order_id,
	main_table.order_date,
	SUM(secondary_table.total_price) AS order_amount
FROM orders main_table
JOIN order_items secondary_table ON main_table.order_id = secondary_table.order_id
WHERE main_table.order_date BETWEEN '2024-01-14' AND '2024-04-10'
GROUP BY main_table.order_id, main_table.order_date;
	

