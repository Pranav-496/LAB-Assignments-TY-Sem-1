-- ============================================================================
-- Problem Statement 06: Online Shopping System
-- Dialect: MySQL 8.0+
-- 
-- Description:
-- An online shopping platform wants to manage customers, products, orders,
-- and product categories.
-- - Each customer can place multiple orders (1:N).
-- - Each order can contain multiple products, and each product can appear in multiple orders (M:N).
-- - Each product belongs to a category (N:1).
-- - For each product in an order, store the quantity and price at the time of order.
--
-- Tasks Implemented:
-- 1. Entity sets, attributes, and primary/foreign keys.
-- 2. Relationships (Places, Contains, BelongsTo) and cardinalities.
-- 3. Normalized 3NF relational tables.
-- 4. Sample dataset and verification queries.
-- ============================================================================

CREATE DATABASE IF NOT EXISTS dbms_assignment6_mock;
USE dbms_assignment6_mock;

-- ----------------------------------------------------------------------------
-- STEP 1: Drop tables in reverse-dependency order for safe re-runs
-- ----------------------------------------------------------------------------
DROP TABLE IF EXISTS order_items;
DROP TABLE IF EXISTS orders;
DROP TABLE IF EXISTS products;
DROP TABLE IF EXISTS categories;
DROP TABLE IF EXISTS customers;

-- ----------------------------------------------------------------------------
-- STEP 2: Create Entities (3NF Normalized Relations)
-- ----------------------------------------------------------------------------

-- Entity 1: Category
-- FD: category_id -> category_name, description
CREATE TABLE categories (
    category_id INT PRIMARY KEY,
    category_name VARCHAR(100) NOT NULL UNIQUE,
    description TEXT
);

-- Entity 2: Product
-- Represents Product entity + "BelongsTo" Many-to-One relationship to Category
-- FD: product_id -> product_name, description, current_price, stock_quantity, category_id
CREATE TABLE products (
    product_id INT PRIMARY KEY,
    product_name VARCHAR(100) NOT NULL,
    description TEXT,
    current_price DECIMAL(10, 2) NOT NULL CHECK (current_price >= 0),
    stock_quantity INT NOT NULL CHECK (stock_quantity >= 0),
    category_id INT NOT NULL,
    FOREIGN KEY (category_id) REFERENCES categories(category_id)
        ON UPDATE CASCADE
        ON DELETE RESTRICT
);

-- Entity 3: Customer
-- FD: customer_id -> customer_name, email, phone_no, shipping_address, registration_date
CREATE TABLE customers (
    customer_id INT PRIMARY KEY,
    customer_name VARCHAR(100) NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    phone_no VARCHAR(15) NOT NULL,
    shipping_address VARCHAR(255) NOT NULL,
    registration_date DATE NOT NULL
);

-- Entity 4: Orders
-- Represents Order entity + "Places" One-to-Many relationship from Customer
-- FD: order_id -> order_date, total_amount, order_status, customer_id
CREATE TABLE orders (
    order_id INT PRIMARY KEY,
    order_date DATETIME NOT NULL,
    total_amount DECIMAL(10, 2) NOT NULL CHECK (total_amount >= 0),
    order_status VARCHAR(20) NOT NULL CHECK (order_status IN ('Pending', 'Processing', 'Shipped', 'Delivered', 'Cancelled')),
    customer_id INT NOT NULL,
    FOREIGN KEY (customer_id) REFERENCES customers(customer_id)
        ON UPDATE CASCADE
        ON DELETE RESTRICT
);

-- ----------------------------------------------------------------------------
-- STEP 3: Create Relationship Junction Table (M:N Relationship)
-- ----------------------------------------------------------------------------

-- Relationship: "Contains" (M:N between Order and Product with quantity and order_price)
-- Composite PK: (order_id, product_id)
-- FD: (order_id, product_id) -> quantity, order_price
CREATE TABLE order_items (
    order_id INT NOT NULL,
    product_id INT NOT NULL,
    quantity INT NOT NULL CHECK (quantity > 0),
    order_price DECIMAL(10, 2) NOT NULL CHECK (order_price >= 0),
    PRIMARY KEY (order_id, product_id),
    FOREIGN KEY (order_id) REFERENCES orders(order_id)
        ON UPDATE CASCADE
        ON DELETE CASCADE,
    FOREIGN KEY (product_id) REFERENCES products(product_id)
        ON UPDATE CASCADE
        ON DELETE RESTRICT
);

-- ----------------------------------------------------------------------------
-- STEP 4: Insert Sample Records
-- ----------------------------------------------------------------------------

-- Insert Categories
INSERT INTO categories (category_id, category_name, description) VALUES
(1, 'Electronics', 'Smartphones, laptops, audio devices, and computer accessories'),
(2, 'Fashion & Apparel', 'Men and women clothing, footwear, and accessories'),
(3, 'Home & Kitchen', 'Home appliances, cookware, and kitchen tools'),
(4, 'Books & Stationery', 'Fiction, academic textbooks, notebooks, and writing materials');

-- Insert Products (BelongsTo relationship)
INSERT INTO products (product_id, product_name, description, current_price, stock_quantity, category_id) VALUES
(101, 'Dell Inspiron 15 Laptop', '15.6 inch FHD, Intel i5 12th Gen, 16GB RAM, 512GB SSD', 55000.00, 25, 1),
(102, 'Sony WH-1000XM4 Headphones', 'Wireless noise cancelling over-ear headphones', 19999.00, 40, 1),
(103, 'Logitech MX Master 3S Mouse', 'Wireless performance ergonomic mouse with quiet clicks', 7995.00, 50, 1),
(104, 'Levi''s Slim Fit Jeans', 'Stretchable dark blue denim jeans for men', 2499.00, 100, 2),
(105, 'Nike Air Zoom Pegasus', 'High performance lightweight running shoes', 8495.00, 35, 2),
(106, 'Philips Air Fryer XL', 'Rapid air technology 4.1L capacity digital fryer', 6999.00, 20, 3),
(107, 'Database System Concepts', 'Classic textbook by Silberschatz, Korth, and Sudarshan', 950.00, 60, 4),
(108, 'Clean Code by Robert Martin', 'A handbook of agile software craftsmanship', 650.00, 80, 4);

-- Insert Customers
INSERT INTO customers (customer_id, customer_name, email, phone_no, shipping_address, registration_date) VALUES
(1, 'Rohan Verma', 'rohan.verma@gmail.com', '9822011111', 'Flat 402, Green Acre, FC Road, Pune - 411004', '2026-01-10'),
(2, 'Sneha Kulkarni', 'sneha.k@yahoo.com', '9822022222', 'B-12, Sagar Society, Kothrud, Pune - 411038', '2026-02-15'),
(3, 'Aarav Gupta', 'aarav.gupta@outlook.com', '9822033333', '15 Park Street, Bandra West, Mumbai - 400050', '2026-03-01'),
(4, 'Tanya Sen', 'tanya.sen@gmail.com', '9822044444', 'Tower 3, Clover Park, Viman Nagar, Pune - 411014', '2026-04-12'),
(5, 'Vikram Shinde', 'vikram.shinde@rediffmail.com', '9822055555', 'Plot 22, Shivaji Nagar, Kolhapur - 416001', '2026-05-20');

-- Insert Orders (Places relationship)
INSERT INTO orders (order_id, order_date, total_amount, order_status, customer_id) VALUES
(1001, '2026-10-01 10:30:00', 74999.00, 'Delivered', 1),
(1002, '2026-10-05 14:15:00', 10994.00, 'Delivered', 2),
(1003, '2026-10-12 18:45:00', 55000.00, 'Shipped',   3),
(1004, '2026-10-20 09:20:00', 8599.00,  'Delivered', 1),
(1005, '2026-11-02 16:00:00', 1600.00,  'Processing', 4),
(1006, '2026-11-10 11:10:00', 19999.00, 'Pending',   5);

-- Insert Order Items (Contains relationship with quantity and snapshot order_price)
INSERT INTO order_items (order_id, product_id, quantity, order_price) VALUES
-- Order 1001 (Rohan): Laptop + Headphones
(1001, 101, 1, 55000.00),
(1001, 102, 1, 19999.00),

-- Order 1002 (Sneha): Slim Jeans + Running Shoes
(1002, 104, 1, 2499.00),
(1002, 105, 1, 8495.00),

-- Order 1003 (Aarav): Laptop
(1003, 101, 1, 55000.00),

-- Order 1004 (Rohan): Mouse + Clean Code Book
(1004, 103, 1, 7949.00), -- Purchased on slight discount (catalog was 7995.00)
(1004, 108, 1, 650.00),

-- Order 1005 (Tanya): Both Books
(1005, 107, 1, 950.00),
(1005, 108, 1, 650.00),

-- Order 1006 (Vikram): Headphones
(1006, 102, 1, 19999.00);

-- ----------------------------------------------------------------------------
-- STEP 5: Verification Queries
-- ----------------------------------------------------------------------------

-- Query 1: Places verification
-- Display each customer and their placed orders, including order status
SELECT 
    c.customer_id,
    c.customer_name,
    c.email,
    o.order_id,
    o.order_date,
    o.total_amount,
    o.order_status
FROM customers c
JOIN orders o ON c.customer_id = o.customer_id
ORDER BY c.customer_id, o.order_date;

-- Query 2: BelongsTo verification
-- Display all products along with their category name and stock
SELECT 
    p.product_id,
    p.product_name,
    c.category_name,
    p.current_price,
    p.stock_quantity
FROM products p
JOIN categories c ON p.category_id = c.category_id
ORDER BY c.category_name, p.product_name;

-- Query 3: Contains verification
-- Display itemized order breakdown showing product, snapshot order price, quantity, and line total
SELECT 
    o.order_id,
    c.customer_name,
    p.product_name,
    oi.quantity,
    oi.order_price AS price_at_order,
    (oi.quantity * oi.order_price) AS line_subtotal
FROM orders o
JOIN customers c ON o.customer_id = c.customer_id
JOIN order_items oi ON o.order_id = oi.order_id
JOIN products p ON oi.product_id = p.product_id
ORDER BY o.order_id, p.product_name;

-- Query 4: Top-Selling Products by Revenue and Units Sold
SELECT 
    p.product_id,
    p.product_name,
    cat.category_name,
    SUM(oi.quantity) AS total_units_sold,
    SUM(oi.quantity * oi.order_price) AS total_sales_revenue
FROM order_items oi
JOIN products p ON oi.product_id = p.product_id
JOIN categories cat ON p.category_id = cat.category_id
GROUP BY p.product_id, p.product_name, cat.category_name
ORDER BY total_sales_revenue DESC;

-- Query 5: Category-Wise Sales and Performance Summary
SELECT 
    cat.category_id,
    cat.category_name,
    COUNT(DISTINCT p.product_id) AS total_products_in_catalog,
    COALESCE(SUM(oi.quantity), 0) AS total_items_purchased,
    COALESCE(SUM(oi.quantity * oi.order_price), 0.00) AS total_category_revenue
FROM categories cat
LEFT JOIN products p ON cat.category_id = p.category_id
LEFT JOIN order_items oi ON p.product_id = oi.product_id
GROUP BY cat.category_id, cat.category_name
ORDER BY total_category_revenue DESC;

