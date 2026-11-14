-- ============================================================================
-- Problem Statement 04: University Management System
-- Dialect: MySQL 8.0+
-- 
-- Description:
-- A university wants to manage information about its students, courses,
-- instructors, and departments.
-- - Each student can enroll in multiple courses, and each course can have many students (M:N).
-- - Each course is taught by an instructor (1:N from Instructor to Course).
-- - Each instructor belongs to a single department, but a department can have multiple instructors (N:1).
-- - For each enrollment, the university records the grade obtained by the student.
--
-- Tasks Implemented:
-- 1. Entity sets, attributes, and primary/foreign keys.
-- 2. Relationships (Enrolls, Teaches, BelongsTo) and cardinalities.
-- 3. Normalized 3NF relational tables.
-- 4. Sample dataset and verification queries.
-- ============================================================================

CREATE DATABASE IF NOT EXISTS dbms_assignment4_mock;
USE dbms_assignment4_mock;

-- ----------------------------------------------------------------------------
-- STEP 1: Drop tables in reverse-dependency order for safe re-runs
-- ----------------------------------------------------------------------------
DROP TABLE IF EXISTS enrollments;
DROP TABLE IF EXISTS courses;
DROP TABLE IF EXISTS instructors;
DROP TABLE IF EXISTS students;
DROP TABLE IF EXISTS departments;

-- ----------------------------------------------------------------------------
-- STEP 2: Create Entities (3NF Normalized Relations)
-- ----------------------------------------------------------------------------

-- Entity 1: Department
-- FD: dept_id -> dept_name, building, budget, contact_phone
CREATE TABLE departments (
    dept_id INT PRIMARY KEY,
    dept_name VARCHAR(100) NOT NULL UNIQUE,
    building VARCHAR(100) NOT NULL,
    budget DECIMAL(12, 2) NOT NULL CHECK (budget >= 0),
    contact_phone VARCHAR(15) NOT NULL
);

-- Entity 2: Instructor
-- Represents Instructor entity + "BelongsTo" Many-to-One relationship to Department
-- FD: instructor_id -> instructor_name, email, phone_no, salary, dept_id
CREATE TABLE instructors (
    instructor_id INT PRIMARY KEY,
    instructor_name VARCHAR(100) NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    phone_no VARCHAR(15) NOT NULL,
    salary DECIMAL(10, 2) NOT NULL CHECK (salary > 0),
    dept_id INT NOT NULL,
    FOREIGN KEY (dept_id) REFERENCES departments(dept_id)
        ON UPDATE CASCADE
        ON DELETE RESTRICT
);

-- Entity 3: Course
-- Represents Course entity + "Teaches" One-to-Many relationship from Instructor
-- FD: course_id -> course_title, credits, instructor_id
CREATE TABLE courses (
    course_id VARCHAR(10) PRIMARY KEY,
    course_title VARCHAR(100) NOT NULL,
    credits INT NOT NULL CHECK (credits > 0),
    instructor_id INT NOT NULL,
    FOREIGN KEY (instructor_id) REFERENCES instructors(instructor_id)
        ON UPDATE CASCADE
        ON DELETE RESTRICT
);

-- Entity 4: Student
-- FD: student_id -> student_name, dob, email, contact_no, admission_year
CREATE TABLE students (
    student_id INT PRIMARY KEY,
    student_name VARCHAR(100) NOT NULL,
    dob DATE NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    contact_no VARCHAR(15) NOT NULL,
    admission_year INT NOT NULL CHECK (admission_year >= 2000)
);

-- ----------------------------------------------------------------------------
-- STEP 3: Create Relationship Junction Table (M:N Relationship)
-- ----------------------------------------------------------------------------

-- Relationship: "Enrolls" (M:N between Student and Course with grade)
-- Composite PK: (student_id, course_id)
-- FD: (student_id, course_id) -> grade, enrollment_date
CREATE TABLE enrollments (
    student_id INT NOT NULL,
    course_id VARCHAR(10) NOT NULL,
    grade VARCHAR(2) NOT NULL CHECK (grade IN ('A+', 'A', 'B+', 'B', 'C+', 'C', 'D', 'F', 'P')),
    enrollment_date DATE NOT NULL,
    PRIMARY KEY (student_id, course_id),
    FOREIGN KEY (student_id) REFERENCES students(student_id)
        ON UPDATE CASCADE
        ON DELETE CASCADE,
    FOREIGN KEY (course_id) REFERENCES courses(course_id)
        ON UPDATE CASCADE
        ON DELETE CASCADE
);

-- ----------------------------------------------------------------------------
-- STEP 4: Insert Sample Records
-- ----------------------------------------------------------------------------

-- Insert Departments
INSERT INTO departments (dept_id, dept_name, building, budget, contact_phone) VALUES
(10, 'Computer Engineering', 'Turing Block - A', 1500000.00, '020-25601111'),
(20, 'Information Technology', 'Babbage Block - B', 1200000.00, '020-25602222'),
(30, 'Electronics & Telecommunication', 'Tesla Block - C', 1350000.00, '020-25603333'),
(40, 'Applied Mathematics', 'Ramanujan Block - D', 800000.00, '020-25604444');

-- Insert Instructors (BelongsTo relationship)
INSERT INTO instructors (instructor_id, instructor_name, email, phone_no, salary, dept_id) VALUES
(101, 'Dr. Arvind Sharma', 'arvind.sharma@univ.edu', '9823011111', 110000.00, 10),
(102, 'Dr. Meera Kulkarni', 'meera.kulkarni@univ.edu', '9823022222', 105000.00, 10),
(103, 'Prof. Rajesh Nair', 'rajesh.nair@univ.edu', '9823033333', 95000.00, 20),
(104, 'Dr. Sunita Deshmukh', 'sunita.deshmukh@univ.edu', '9823044444', 115000.00, 30),
(105, 'Prof. Anand Joshi', 'anand.joshi@univ.edu', '9823055555', 90000.00, 40),
(106, 'Dr. Pooja Patil', 'pooja.patil@univ.edu', '9823066666', 102000.00, 20);

-- Insert Courses (Teaches relationship)
INSERT INTO courses (course_id, course_title, credits, instructor_id) VALUES
('CS301', 'Database Management Systems', 4, 101),
('CS302', 'Data Structures & Algorithms', 4, 102),
('IT301', 'Web Application Development', 3, 103),
('IT302', 'Cloud Computing Architecture', 3, 106),
('ET301', 'Signals and Digital Systems', 4, 104),
('ET302', 'Embedded Microcontrollers', 3, 104),
('MA201', 'Discrete Mathematics & Graph Theory', 4, 105),
('CS303', 'Operating Systems Concepts', 4, 101);

-- Insert Students
INSERT INTO students (student_id, student_name, dob, email, contact_no, admission_year) VALUES
(1, 'Rohan Verma', '2004-05-14', 'rohan.verma@student.univ.edu', '9123400001', 2022),
(2, 'Sneha Kulkarni', '2004-09-22', 'sneha.kulkarni@student.univ.edu', '9123400002', 2022),
(3, 'Aarav Gupta', '2003-11-05', 'aarav.gupta@student.univ.edu', '9123400003', 2021),
(4, 'Tanya Sen', '2004-03-30', 'tanya.sen@student.univ.edu', '9123400004', 2022),
(5, 'Vikram Shinde', '2003-07-19', 'vikram.shinde@student.univ.edu', '9123400005', 2021),
(6, 'Ananya Joshi', '2004-12-11', 'ananya.joshi@student.univ.edu', '9123400006', 2022);

-- Insert Enrollments (Enrolls relationship with grade)
INSERT INTO enrollments (student_id, course_id, grade, enrollment_date) VALUES
(1, 'CS301', 'A+', '2026-07-15'),
(1, 'CS302', 'A',  '2026-07-15'),
(1, 'MA201', 'B+', '2026-07-16'),
(2, 'CS301', 'A',  '2026-07-15'),
(2, 'IT301', 'A+', '2026-07-16'),
(2, 'CS303', 'B+', '2026-07-17'),
(3, 'CS301', 'B',  '2026-07-15'),
(3, 'IT302', 'A',  '2026-07-16'),
(3, 'ET301', 'B+', '2026-07-18'),
(4, 'CS302', 'A+', '2026-07-15'),
(4, 'MA201', 'A',  '2026-07-16'),
(4, 'IT301', 'A',  '2026-07-17'),
(5, 'ET301', 'A',  '2026-07-16'),
(5, 'ET302', 'A+', '2026-07-16'),
(6, 'CS301', 'A',  '2026-07-15'),
(6, 'CS303', 'A+', '2026-07-17');

-- ----------------------------------------------------------------------------
-- STEP 5: Verification Queries
-- ----------------------------------------------------------------------------

-- Query 1: BelongsTo verification
-- Display each instructor with their affiliated department and building location
SELECT 
    i.instructor_id,
    i.instructor_name,
    i.email,
    d.dept_name,
    d.building
FROM instructors i
JOIN departments d ON i.dept_id = d.dept_id
ORDER BY d.dept_name, i.instructor_name;

-- Query 2: Teaches verification
-- Display courses taught by each instructor along with course credits
SELECT 
    c.course_id,
    c.course_title,
    c.credits,
    i.instructor_name,
    d.dept_name
FROM courses c
JOIN instructors i ON c.instructor_id = i.instructor_id
JOIN departments d ON i.dept_id = d.dept_id
ORDER BY c.course_id;

-- Query 3: Enrolls verification
-- Display student course enrollments and the grades obtained by each student
SELECT 
    s.student_id,
    s.student_name,
    c.course_id,
    c.course_title,
    e.grade,
    i.instructor_name
FROM enrollments e
JOIN students s ON e.student_id = s.student_id
JOIN courses c ON e.course_id = c.course_id
JOIN instructors i ON c.instructor_id = i.instructor_id
ORDER BY s.student_id, c.course_id;

-- Query 4: Course-wise Enrollment Statistics and Grade Count
SELECT 
    c.course_id,
    c.course_title,
    i.instructor_name,
    COUNT(e.student_id) AS total_enrolled_students
FROM courses c
JOIN instructors i ON c.instructor_id = i.instructor_id
LEFT JOIN enrollments e ON c.course_id = e.course_id
GROUP BY c.course_id, c.course_title, i.instructor_name
ORDER BY total_enrolled_students DESC;

-- Query 5: Department Workload Summary
-- Count of instructors, courses offered, and total enrollments per department
SELECT 
    d.dept_name,
    COUNT(DISTINCT i.instructor_id) AS total_instructors,
    COUNT(DISTINCT c.course_id) AS total_courses_offered,
    COUNT(e.student_id) AS total_enrollments
FROM departments d
LEFT JOIN instructors i ON d.dept_id = i.dept_id
LEFT JOIN courses c ON i.instructor_id = c.instructor_id
LEFT JOIN enrollments e ON c.course_id = e.course_id
GROUP BY d.dept_id, d.dept_name
ORDER BY total_enrollments DESC;

