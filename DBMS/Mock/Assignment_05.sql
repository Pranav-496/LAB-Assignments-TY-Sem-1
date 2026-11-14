-- ============================================================================
-- Problem Statement 05: Hospital Management System
-- Dialect: MySQL 8.0+
-- 
-- Description:
-- A hospital wants to track patients, doctors, wards, and treatments.
-- - Each patient is admitted to a ward, and a ward can have multiple patients (N:1).
-- - Doctors can be assigned to multiple patients, and a patient can have multiple doctors (M:N).
-- - Each patient can undergo multiple treatments, and the hospital stores the treatment date (M:N).
--
-- Tasks Implemented:
-- 1. Entity sets, attributes, and primary/foreign keys.
-- 2. Relationships (AdmittedTo, Assigned, Undergoes) and cardinalities.
-- 3. Normalized 3NF relational tables.
-- 4. Sample dataset and verification queries.
-- ============================================================================

CREATE DATABASE IF NOT EXISTS dbms_assignment5_mock;
USE dbms_assignment5_mock;

-- ----------------------------------------------------------------------------
-- STEP 1: Drop tables in reverse-dependency order for safe re-runs
-- ----------------------------------------------------------------------------
DROP TABLE IF EXISTS patient_treatment;
DROP TABLE IF EXISTS doctor_patient;
DROP TABLE IF EXISTS patients;
DROP TABLE IF EXISTS treatments;
DROP TABLE IF EXISTS doctors;
DROP TABLE IF EXISTS wards;

-- ----------------------------------------------------------------------------
-- STEP 2: Create Entities (3NF Normalized Relations)
-- ----------------------------------------------------------------------------

-- Entity 1: Ward
-- FD: ward_id -> ward_name, ward_type, capacity
CREATE TABLE wards (
    ward_id INT PRIMARY KEY,
    ward_name VARCHAR(100) NOT NULL,
    ward_type VARCHAR(50) NOT NULL,
    capacity INT NOT NULL CHECK (capacity > 0)
);

-- Entity 2: Doctor
-- FD: doctor_id -> doctor_name, specialization, phone_no, email
CREATE TABLE doctors (
    doctor_id INT PRIMARY KEY,
    doctor_name VARCHAR(100) NOT NULL,
    specialization VARCHAR(100) NOT NULL,
    phone_no VARCHAR(15) NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL
);

-- Entity 3: Treatment
-- FD: treatment_id -> treatment_name, description, cost
CREATE TABLE treatments (
    treatment_id INT PRIMARY KEY,
    treatment_name VARCHAR(100) NOT NULL,
    description TEXT,
    cost DECIMAL(10, 2) NOT NULL CHECK (cost >= 0)
);

-- Entity 4: Patient
-- Represents Patient entity + "AdmittedTo" Many-to-One relationship to Ward
-- FD: patient_id -> patient_name, dob, gender, contact_no, address, admission_date, ward_id
CREATE TABLE patients (
    patient_id INT PRIMARY KEY,
    patient_name VARCHAR(100) NOT NULL,
    dob DATE NOT NULL,
    gender CHAR(1) NOT NULL CHECK (gender IN ('M', 'F', 'O')),
    contact_no VARCHAR(15) NOT NULL,
    address VARCHAR(255) NOT NULL,
    admission_date DATE NOT NULL,
    ward_id INT NOT NULL,
    FOREIGN KEY (ward_id) REFERENCES wards(ward_id)
        ON UPDATE CASCADE
        ON DELETE RESTRICT
);

-- ----------------------------------------------------------------------------
-- STEP 3: Create Relationship Junction Tables (M:N Relationships)
-- ----------------------------------------------------------------------------

-- Relationship: "Assigned" (M:N between Doctor and Patient)
-- Composite PK: (doctor_id, patient_id)
-- FD: (doctor_id, patient_id) -> assignment_date
CREATE TABLE doctor_patient (
    doctor_id INT NOT NULL,
    patient_id INT NOT NULL,
    assignment_date DATE NOT NULL,
    PRIMARY KEY (doctor_id, patient_id),
    FOREIGN KEY (doctor_id) REFERENCES doctors(doctor_id)
        ON UPDATE CASCADE
        ON DELETE CASCADE,
    FOREIGN KEY (patient_id) REFERENCES patients(patient_id)
        ON UPDATE CASCADE
        ON DELETE CASCADE
);

-- Relationship: "Undergoes" (M:N between Patient and Treatment with treatment_date)
-- Composite PK: (patient_id, treatment_id, treatment_date)
-- FD: (patient_id, treatment_id, treatment_date) -> remarks
CREATE TABLE patient_treatment (
    patient_id INT NOT NULL,
    treatment_id INT NOT NULL,
    treatment_date DATE NOT NULL,
    remarks VARCHAR(255),
    PRIMARY KEY (patient_id, treatment_id, treatment_date),
    FOREIGN KEY (patient_id) REFERENCES patients(patient_id)
        ON UPDATE CASCADE
        ON DELETE CASCADE,
    FOREIGN KEY (treatment_id) REFERENCES treatments(treatment_id)
        ON UPDATE CASCADE
        ON DELETE RESTRICT
);

-- ----------------------------------------------------------------------------
-- STEP 4: Insert Sample Records
-- ----------------------------------------------------------------------------

-- Insert Wards
INSERT INTO wards (ward_id, ward_name, ward_type, capacity) VALUES
(1, 'General Ward - Ground Floor', 'General', 20),
(2, 'Cardiology Ward', 'Specialized', 10),
(3, 'Intensive Care Unit (ICU)', 'ICU', 5),
(4, 'Pediatric Ward', 'Specialized', 15);

-- Insert Doctors
INSERT INTO doctors (doctor_id, doctor_name, specialization, phone_no, email) VALUES
(101, 'Dr. Rajesh Sharma', 'Cardiology', '9822011111', 'rajesh.sharma@hospital.org'),
(102, 'Dr. Priya Mehta', 'Neurology', '9822022222', 'priya.mehta@hospital.org'),
(103, 'Dr. Amit Patil', 'Orthopedics', '9822033333', 'amit.patil@hospital.org'),
(104, 'Dr. Sunita Deshmukh', 'Pediatrics', '9822044444', 'sunita.d@hospital.org'),
(105, 'Dr. Anand Joshi', 'General Medicine', '9822055555', 'anand.joshi@hospital.org');

-- Insert Treatments
INSERT INTO treatments (treatment_id, treatment_name, description, cost) VALUES
(501, 'Electrocardiogram (ECG)', 'Records electrical signals of the heart', 500.00),
(502, 'Echocardiogram (Echo)', 'Ultrasound of the heart', 2500.00),
(503, 'MRI Brain Scan', 'Detailed imaging of brain tissue', 7000.00),
(504, 'Fracture Cast Application', 'Plaster cast for immobilized limb fracture', 3500.00),
(505, 'Pediatric Nebulization', 'Inhalation therapy for respiratory relief', 400.00),
(506, 'Blood Chemistry Panel', 'Comprehensive metabolic blood test panel', 1200.00);

-- Insert Patients (AdmittedTo relationship)
INSERT INTO patients (patient_id, patient_name, dob, gender, contact_no, address, admission_date, ward_id) VALUES
(1, 'Rohan Verma', '1985-04-12', 'M', '9123456780', 'FC Road, Pune', '2026-11-01', 2),
(2, 'Sneha Kulkarni', '1992-09-23', 'F', '9123456781', 'Kothrud, Pune', '2026-11-03', 1),
(3, 'Aarav Gupta', '2018-06-15', 'M', '9123456782', 'Baner, Pune', '2026-11-05', 4),
(4, 'Vikram Shinde', '1960-12-01', 'M', '9123456783', 'Hadapsar, Pune', '2026-11-06', 3),
(5, 'Ananya Joshi', '2001-08-19', 'F', '9123456784', 'Viman Nagar, Pune', '2026-11-07', 1);

-- Insert Doctor-Patient Assignments (Assigned relationship - M:N)
-- Note: A doctor can have multiple patients, and a patient can have multiple doctors
INSERT INTO doctor_patient (doctor_id, patient_id, assignment_date) VALUES
(101, 1, '2026-11-01'), -- Dr. Sharma assigned to Rohan
(105, 1, '2026-11-02'), -- Dr. Joshi (General) also assigned to Rohan
(103, 2, '2026-11-03'), -- Dr. Patil assigned to Sneha
(104, 3, '2026-11-05'), -- Dr. Deshmukh assigned to Aarav
(101, 4, '2026-11-06'), -- Dr. Sharma assigned to Vikram (ICU)
(102, 4, '2026-11-06'), -- Dr. Mehta (Neuro) also assigned to Vikram
(105, 4, '2026-11-06'), -- Dr. Joshi also assigned to Vikram
(105, 5, '2026-11-07'); -- Dr. Joshi assigned to Ananya

-- Insert Patient Treatments (Undergoes relationship - M:N with treatment_date)
-- Note: A patient can undergo multiple treatments on different or same dates
INSERT INTO patient_treatment (patient_id, treatment_id, treatment_date, remarks) VALUES
(1, 501, '2026-11-01', 'ECG showed mild arrhythmia'),
(1, 502, '2026-11-02', 'Echo completed, normal ejection fraction'),
(2, 504, '2026-11-03', 'Radial fracture cast applied successfully'),
(3, 505, '2026-11-05', 'First session of nebulization'),
(3, 505, '2026-11-06', 'Follow-up nebulization, patient breathing stable'),
(4, 501, '2026-11-06', 'Urgent ICU ECG monitoring'),
(4, 503, '2026-11-07', 'Brain MRI clear of acute ischemic infarct'),
(4, 506, '2026-11-07', 'Routine metabolic panel'),
(5, 506, '2026-11-07', 'Fever profile blood panel');

-- ----------------------------------------------------------------------------
-- STEP 5: Verification Queries
-- ----------------------------------------------------------------------------

-- Query 1: AdmittedTo verification
-- Display each patient along with the ward they are admitted to and ward type
SELECT 
    p.patient_id,
    p.patient_name,
    p.gender,
    p.admission_date,
    w.ward_id,
    w.ward_name,
    w.ward_type
FROM patients p
JOIN wards w ON p.ward_id = w.ward_id
ORDER BY p.patient_id;

-- Query 2: Assigned verification
-- Display all patients, showing the multiple doctors assigned to each
SELECT 
    p.patient_id,
    p.patient_name,
    d.doctor_id,
    d.doctor_name,
    d.specialization,
    dp.assignment_date
FROM patients p
JOIN doctor_patient dp ON p.patient_id = dp.patient_id
JOIN doctors d ON dp.doctor_id = d.doctor_id
ORDER BY p.patient_id, d.doctor_name;

-- Query 3: Undergoes verification
-- Display all treatments undergone by each patient, including the treatment date and cost
SELECT 
    p.patient_id,
    p.patient_name,
    t.treatment_name,
    pt.treatment_date,
    t.cost,
    pt.remarks
FROM patients p
JOIN patient_treatment pt ON p.patient_id = pt.patient_id
JOIN treatments t ON pt.treatment_id = t.treatment_id
ORDER BY p.patient_id, pt.treatment_date;

-- Query 4: Total treatment cost incurred by each patient
SELECT 
    p.patient_id,
    p.patient_name,
    COUNT(pt.treatment_id) AS total_treatments_count,
    COALESCE(SUM(t.cost), 0.00) AS total_treatment_cost
FROM patients p
LEFT JOIN patient_treatment pt ON p.patient_id = pt.patient_id
LEFT JOIN treatments t ON pt.treatment_id = t.treatment_id
GROUP BY p.patient_id, p.patient_name
ORDER BY total_treatment_cost DESC;

-- Query 5: Ward Occupancy Summary
SELECT 
    w.ward_id,
    w.ward_name,
    w.ward_type,
    w.capacity AS total_capacity,
    COUNT(p.patient_id) AS currently_admitted_patients,
    (w.capacity - COUNT(p.patient_id)) AS available_beds
FROM wards w
LEFT JOIN patients p ON w.ward_id = p.ward_id
GROUP BY w.ward_id, w.ward_name, w.ward_type, w.capacity
ORDER BY w.ward_id;

