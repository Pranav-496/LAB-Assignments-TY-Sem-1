-- Assignment 3: SQL Joins
-- MySQL 8.0+

CREATE DATABASE IF NOT EXISTS dbms_assignment3_mock;
USE dbms_assignment3_mock;

DROP VIEW IF EXISTS pune_instructor_student_count;
DROP TABLE IF EXISTS students;
DROP TABLE IF EXISTS instructors;

--symply just do create ddatabase college; itna karne ki jarurat nahi 

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
    (201, 'Dr. Kapoor', 'Mumbai', 'Mathematics'),
    (202, 'Dr. Menon', 'Bengaluru', 'Physics'),
    (203, 'Dr. Sharma', 'Delhi', 'Chemistry'),
    (204, 'Dr. Verma', 'Chennai', 'Computer'),
    (205, 'Dr. Das', 'Mumbai', 'Computer'),
    (206, 'Dr. Iyer', 'Kolkata', 'English'),
    (207, 'Dr. Gupta', 'Hyderabad', 'Biology'),
    (208, 'Dr. Nair', 'Pune', 'History');

INSERT INTO students
    (student_id, student_name, instructor_id, student_city)
VALUES
    (11, 'Neha', 201, 'Mumbai'),
    (12, 'Siddharth', 202, 'Bengaluru'),
    (13, 'Meera', 201, 'Pune'),
    (14, 'Akash', 203, 'Delhi'),
    (15, 'Tanya', 204, 'Chennai'),
    (16, 'Rahul', 205, 'Mumbai'),
    (17, 'Simran', NULL, 'Bengaluru'),
    (18, 'Karan', 206, 'Kolkata'),
    (19, 'Ankit', 207, 'Hyderabad'),
    (20, 'Prisha', 204, 'Chennai');

-- 1. Find the instructor of each student, including students without an instructor.
-- Outcome: Neha/Dr. Kapoor, Siddharth/Dr. Menon, Meera/Dr. Kapoor,
-- Akash/Dr. Sharma, Tanya/Dr. Verma, Rahul/Dr. Das, Simran/NULL,
-- Karan/Dr. Iyer, Ankit/Dr. Gupta, Prisha/Dr. Verma (10 rows).
SELECT s.student_id, s.student_name, i.instructor_id, i.instructor_name
FROM students AS s
LEFT JOIN instructors AS i
    ON i.instructor_id = s.instructor_id;

-- 2. Find students who do not have an instructor.
-- Outcome: Simran (student_id 17, Bengaluru; 1 row).
SELECT s.student_id, s.student_name, s.student_city
FROM students AS s
LEFT JOIN instructors AS i
    ON i.instructor_id = s.instructor_id
WHERE i.instructor_id IS NULL;

-- 3. Find students without an instructor and instructors without any student.
-- MySQL does not support FULL OUTER JOIN; combine both unmatched sides.
-- Outcome: Simran with NULL instructor fields, plus Dr. Nair (208) with
-- NULL student fields (2 rows).
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
-- Outcome: Tanya/Dr. Verma, Prisha/Dr. Verma, Rahul/Dr. Das (3 rows).
SELECT s.student_id, s.student_name, i.instructor_name, i.specialization
FROM students AS s
INNER JOIN instructors AS i
    ON i.instructor_id = s.instructor_id
WHERE LOWER(i.specialization) = 'computer';

-- 5. Create a view with the number of students whose instructor belongs to Pune.
-- Outcome: The view contains total_students = 0 (Dr. Nair has no students).
CREATE VIEW pune_instructor_student_count AS
SELECT COUNT(s.student_id) AS total_students
FROM instructors AS i
LEFT JOIN students AS s
    ON s.instructor_id = i.instructor_id
WHERE i.instructor_city = 'Pune';

-- Display the view result.
SELECT * FROM pune_instructor_student_count;
