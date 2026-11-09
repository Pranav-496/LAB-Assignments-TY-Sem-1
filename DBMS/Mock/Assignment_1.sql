-- Assignment 1: SQL Queries
-- MySQL 8.0+

CREATE DATABASE IF NOT EXISTS dbms_assignment1_mock;
USE dbms_assignment1_mock;

-- Reset only the assignment tables so this script can be rerun safely.
DROP TABLE IF EXISTS manages;
DROP TABLE IF EXISTS placed;
DROP TABLE IF EXISTS comp;
DROP TABLE IF EXISTS officers;

CREATE TABLE officers (
    off_name VARCHAR(100) PRIMARY KEY,
    street VARCHAR(100) NOT NULL,
    city VARCHAR(100) NOT NULL
);

CREATE TABLE comp (
    company_name VARCHAR(100) NOT NULL,
    city VARCHAR(100) NOT NULL,
    PRIMARY KEY (company_name, city)
);

CREATE TABLE placed (
    off_name VARCHAR(100) PRIMARY KEY,
    company_name VARCHAR(100) NOT NULL,
    salary DECIMAL(12, 2) NOT NULL,
    FOREIGN KEY (off_name) REFERENCES officers (off_name)
);

CREATE TABLE manages (
    off_name VARCHAR(100) PRIMARY KEY,
    manager_name VARCHAR(100) NOT NULL,
    FOREIGN KEY (off_name) REFERENCES officers (off_name),
    FOREIGN KEY (manager_name) REFERENCES officers (off_name)
);

INSERT INTO officers (off_name, street, city) VALUES
    ('Rahul Singh', 'MG Road', 'Mumbai'),
    ('Priya Mehta', 'Park Street', 'Bengaluru'),
    ('Arjun Rao', 'MG Road', 'Mumbai'),
    ('Kavita Shah', 'Civil Lines', 'Delhi'),
    ('Rohan Patel', 'MG Road', 'Mumbai'),
    ('Ananya Iyer', 'Brigade Road', 'Bengaluru'),
    ('Manish Gupta', 'Residency Road', 'Pune'),
    ('Sneha Nair', 'MG Road', 'Mumbai'),
    ('Vikram Das', 'Sector 5', 'Kolkata'),
    ('Divya Kumar', 'Jubilee Hills', 'Hyderabad');

INSERT INTO comp (company_name, city) VALUES
    ('TCS', 'Mumbai'),
    ('TCS', 'Bengaluru'),
    ('Infosys', 'Mumbai'),
    ('Infosys', 'Bengaluru'),
    ('Infosys', 'Hyderabad'),
    ('Amazon', 'Pune'),
    ('Google', 'Kolkata'),
    ('Microsoft', 'Hyderabad');

INSERT INTO placed (off_name, company_name, salary) VALUES
    ('Rahul Singh', 'TCS', 50000),
    ('Priya Mehta', 'TCS', 60000),
    ('Arjun Rao', 'TCS', 12000),
    ('Kavita Shah', 'Infosys', 20000),
    ('Rohan Patel', 'Infosys', 15000),
    ('Ananya Iyer', 'Infosys', 8000),
    ('Manish Gupta', 'Amazon', 40000),
    ('Sneha Nair', 'Amazon', 45000),
    ('Vikram Das', 'Google', 70000),
    ('Divya Kumar', 'Microsoft', 30000);

INSERT INTO manages (off_name, manager_name) VALUES
    ('Rahul Singh', 'Arjun Rao'),
    ('Priya Mehta', 'Ananya Iyer'),
    ('Arjun Rao', 'Rohan Patel'),
    ('Kavita Shah', 'Manish Gupta'),
    ('Rohan Patel', 'Rahul Singh'),
    ('Ananya Iyer', 'Priya Mehta'),
    ('Manish Gupta', 'Sneha Nair'),
    ('Sneha Nair', 'Rahul Singh'),
    ('Vikram Das', 'Divya Kumar'),
    ('Divya Kumar', 'Vikram Das');

-- 1. Find the names of all officers who work for TCS.
-- Expected: Rahul Singh, Priya Mehta, Arjun Rao (3 rows).
SELECT DISTINCT off_name
FROM placed
WHERE company_name = 'TCS';

-- 2. Find the names and cities of residence of all officers who work for TCS.
-- Expected: Rahul Singh/Mumbai, Priya Mehta/Bengaluru, Arjun Rao/Mumbai (3 rows).
SELECT o.off_name, o.city
FROM officers AS o
JOIN placed AS p ON p.off_name = o.off_name
WHERE p.company_name = 'TCS';

-- 3. Find TCS officers earning more than Rs. 10,000, with their addresses.
-- Expected: Rahul Singh/MG Road/Mumbai, Priya Mehta/Park Street/Bengaluru,
-- Arjun Rao/MG Road/Mumbai (3 rows).
SELECT o.off_name, o.street, o.city
FROM officers AS o
JOIN placed AS p ON p.off_name = o.off_name
WHERE p.company_name = 'TCS'
  AND p.salary > 10000;

-- 4. Find officers who live in a city where their company is located.
-- Expected: Rahul Singh, Priya Mehta, Arjun Rao, Rohan Patel, Ananya Iyer,
-- Manish Gupta, Vikram Das, Divya Kumar (8 rows).
SELECT DISTINCT o.*
FROM officers AS o
JOIN placed AS p ON p.off_name = o.off_name
JOIN comp AS c ON c.company_name = p.company_name
WHERE o.city = c.city;

-- 5. Find officers who share both street and city with their manager.
-- Expected pairs: Rahul Singh/Arjun Rao, Arjun Rao/Rohan Patel,
-- Rohan Patel/Rahul Singh, Sneha Nair/Rahul Singh (4 rows).
SELECT o.off_name, m.manager_name
FROM officers AS o
JOIN manages AS m ON m.off_name = o.off_name
JOIN officers AS manager ON manager.off_name = m.manager_name
WHERE o.street = manager.street
  AND o.city = manager.city;

-- 6. Find officers who do not work for TCS.
-- Expected: Kavita Shah, Rohan Patel, Ananya Iyer, Manish Gupta,
-- Sneha Nair, Vikram Das, Divya Kumar (7 rows).
SELECT o.*
FROM officers AS o
WHERE NOT EXISTS (
    SELECT 1
    FROM placed AS p
    WHERE p.off_name = o.off_name
      AND p.company_name = 'TCS'
);

-- 7. Find officers who earn more than each officer of Infosys.
-- Expected: Rahul Singh, Priya Mehta, Manish Gupta, Sneha Nair,
-- Vikram Das, Divya Kumar (6 rows).
SELECT p.off_name
FROM placed AS p
WHERE p.salary > ALL (
    SELECT infosys.salary
    FROM placed AS infosys
    WHERE infosys.company_name = 'Infosys'
);

-- 8. Find companies located in every city where Infosys is located.
-- Expected: Infosys (1 row).
select company_name from comp where city in (select city from comp where company_name like 'Infosys');

-- 9. Find officers earning more than the average salary at their company.
-- Expected: Rahul Singh/TCS/50000, Priya Mehta/TCS/60000,
-- Kavita Shah/Infosys/20000, Rohan Patel/Infosys/15000,
-- Sneha Nair/Amazon/45000 (5 rows).
SELECT p.off_name, p.company_name, p.salary
FROM placed AS p
WHERE p.salary > (
    SELECT AVG(other.salary)
    FROM placed AS other
    WHERE other.company_name = p.company_name
);

-- 10. Find the company or companies with the most officers (including ties).
-- Expected: TCS and Infosys (3 officers each; 2 rows).
SELECT company_name
FROM placed
GROUP BY company_name
HAVING COUNT(*) >= ALL (
    SELECT COUNT(*)
    FROM placed
    GROUP BY company_name
);

-- 11. Find the company or companies with the smallest payroll (including ties).
-- Expected: Microsoft (payroll 30000; 1 row).
SELECT company_name
FROM placed
GROUP BY company_name
HAVING SUM(salary) <= ALL (
    SELECT SUM(salary)
    FROM placed
    GROUP BY company_name
);

-- 12. Find companies whose average salary is higher than TCS's average salary.
-- Expected: Amazon (average 42500) and Google (average 70000; 2 rows).
SELECT company_name
FROM placed
GROUP BY company_name
HAVING AVG(salary) > (
    SELECT AVG(salary)
    FROM placed
    WHERE company_name = 'TCS'
);
