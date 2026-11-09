-- Assignment 2: SQL Joins
-- MySQL 8.0+

CREATE DATABASE IF NOT EXISTS dbms_assignment2_mock;
USE dbms_assignment2_mock;

DROP VIEW IF EXISTS pune_instructor_student_count;
DROP TABLE IF EXISTS students;
DROP TABLE IF EXISTS instructors;

--symply just do create database college; itna karne ki jarurat nahi 

CREATE TABLE instructors (
    instructor_id INT PRIMARY KEY,
    instructor_name VARCHAR(100) NOT NULL,
    instructor_city VARCHAR(100) NOT NULL,
    specialization VARCHAR(100) NOT NULL
);

CREATE TABLE students (
    student_id INT PRIMARY KEY,
    student_name VARCHAR(100) NOT NULL,
    instructor_id INT NULL,
    student_city VARCHAR(100) NOT NULL,
    FOREIGN KEY (instructor_id) REFERENCES instructors (instructor_id)
);

INSERT INTO instructors
    (instructor_id, instructor_name, instructor_city, specialization)
VALUES
    (101, 'Dr. Sharma', 'Mumbai', 'Mathematics'),
    (102, 'Dr. Iyer', 'Bengaluru', 'Physics'),
    (103, 'Dr. Gupta', 'Delhi', 'Chemistry'),
    (104, 'Dr. Patel', 'Mumbai', 'Computer'),
    (105, 'Dr. Rao', 'Pune', 'Computer'),
    (106, 'Dr. Das', 'Kolkata', 'English'),
    (107, 'Dr. Mehta', 'Bengaluru', 'History'),
    (108, 'Dr. Nair', 'Delhi', 'Economics');

INSERT INTO students
    (student_id, student_name, instructor_id, student_city)
VALUES
    (1, 'Rahul', 101, 'Mumbai'),
    (2, 'Ananya', 102, 'Bengaluru'),
    (3, 'Arjun', 101, 'Mumbai'),
    (4, 'Kavita', 103, 'Delhi'),
    (5, 'Rohan', 104, 'Mumbai'),
    (6, 'Divya', 102, 'Bengaluru'),
    (7, 'Manish', 105, 'Pune'),
    (8, 'Sneha', 101, 'Mumbai'),
    (9, 'Vikram', NULL, 'Kolkata'),
    (10, 'Priya', 106, 'Delhi');

-- 1. Find the instructor of each student, including students without an instructor.
-- Outcome: Rahul/Dr. Sharma, Ananya/Dr. Iyer, Arjun/Dr. Sharma,
-- Kavita/Dr. Gupta, Rohan/Dr. Patel, Divya/Dr. Iyer, Manish/Dr. Rao,
-- Sneha/Dr. Sharma, Vikram/NULL, Priya/Dr. Das (10 rows).
SELECT s.student_id, s.student_name, i.instructor_id, i.instructor_name
FROM students AS s
LEFT JOIN instructors AS i
    ON i.instructor_id = s.instructor_id;

-- 2. Find students who do not have an instructor.
-- Outcome: Vikram (student_id 9, Kolkata; 1 row).
SELECT s.student_id, s.student_name, s.student_city
FROM students AS s
LEFT JOIN instructors AS i
    ON i.instructor_id = s.instructor_id
WHERE i.instructor_id IS NULL;

-- 3. Find students without an instructor and instructors without any student.
-- MySQL does not support FULL OUTER JOIN; combine both unmatched sides.
-- Outcome: Vikram with NULL instructor fields, plus Dr. Mehta (107) and
-- Dr. Nair (108) with NULL student fields (3 rows).
SELECT s.student_id, s.student_name, i.instructor_id, i.instructor_name
FROM students AS s
LEFT JOIN instructors AS i
    ON i.instructor_id = s.instructor_id
WHERE i.instructor_id IS NULL
UNION ALL
SELECT s.student_id, s.student_name, i.instructor_id, i.instructor_name
FROM instructors AS i
LEFT JOIN students AS s
    ON s.instructor_id = i.instructor_id
WHERE s.student_id IS NULL;

-- 4. Find students whose instructor's specialization is Computer.
-- Outcome: Rohan/Dr. Patel and Manish/Dr. Rao (2 rows).
SELECT s.student_id, s.student_name, i.instructor_name, i.specialization
FROM students AS s
INNER JOIN instructors AS i
    ON i.instructor_id = s.instructor_id
WHERE LOWER(i.specialization) = 'computer';

-- 5. Create a view with the number of students whose instructor belongs to Pune.
-- Outcome: The view contains total_students = 1 (Manish is assigned to Dr. Rao).
CREATE VIEW pune_instructor_student_count AS
SELECT COUNT(s.student_id) AS total_students
FROM instructors AS i
LEFT JOIN students AS s
    ON s.instructor_id = i.instructor_id
WHERE i.instructor_city = 'Pune';

-- Display the view result.
SELECT * FROM pune_instructor_student_count;
