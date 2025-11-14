SELECT
	main_table.order_item_id,
	main_table.order_id,
	secondary_table.name,
	main_table.quantity
FROM order_items main_table
JOIN products secondary_table ON main_table.product_id = secondary_table.id
WHERE main_table.order_id = 3;
	
	

