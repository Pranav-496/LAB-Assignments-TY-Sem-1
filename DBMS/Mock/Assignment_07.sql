/*
Instructions to run this shit in practical exam
sudo service postgresql start

sudo -u postgres psql
CREATE DATABASE dbms_practical;
\c dbms_practical
\i '/mnt/d/LAB-Assignments-TY-Sem-1/DBMS/Mock/Assignment_7.sql'

Alternative:
sudo -u postgres psql -d dbms_practical -f "/mnt/d/LAB-Assignments-TY-Sem-1/DBMS/Mock/Assignment_7.sql"
*/
-- ==========================================
-- PROBLEM STATEMENT 07
-- LIBRARY FINE MANAGEMENT SYSTEM
-- PostgreSQL / PLpgSQL
-- ==========================================

-- STEP 1: Create Borrow table

CREATE TABLE Borrow (
    Roll INT PRIMARY KEY,
    Name VARCHAR(30),
    Issue_Date DATE,
    Book_Name VARCHAR(50),
    Status CHAR(1)
);


-- STEP 2: Create Lib_Fine table

CREATE TABLE Lib_Fine (
    Roll_no INT,
    Curr_Date DATE,
    Amt NUMERIC(10,2)
);


-- STEP 3: Insert given records

INSERT INTO Borrow VALUES
(101, 'Rahul', '2025-10-15', 'C Programming', 'I'),
(102, 'Ananya', '2025-10-01', 'Data Structures', 'I'),
(103, 'Arjun', '2025-09-20', 'DBMS Concepts', 'I'),
(104, 'Kavita', '2025-10-10', 'Operating Systems', 'I'),
(105, 'Priya', '2025-09-25', 'Python Programming', 'I');


-- STEP 4: Accept user input and insert record
-- This below code block to take user input of these values
/*
\prompt 'Enter Roll Number (1/5): ' p_roll1
\prompt 'Enter Name (1/5): ' p_name1
\prompt 'Enter Issue Date (YYYY-MM-DD) (1/5): ' p_date1
\prompt 'Enter Book Name (1/5): ' p_book1
\prompt 'Enter Status (I/R) (1/5): ' p_status1

\prompt 'Enter Roll Number (2/5): ' p_roll2
\prompt 'Enter Name (2/5): ' p_name2
\prompt 'Enter Issue Date (YYYY-MM-DD) (2/5): ' p_date2
\prompt 'Enter Book Name (2/5): ' p_book2
\prompt 'Enter Status (I/R) (2/5): ' p_status2

\prompt 'Enter Roll Number (3/5): ' p_roll3
\prompt 'Enter Name (3/5): ' p_name3
\prompt 'Enter Issue Date (YYYY-MM-DD) (3/5): ' p_date3
\prompt 'Enter Book Name (3/5): ' p_book3
\prompt 'Enter Status (I/R) (3/5): ' p_status3

\prompt 'Enter Roll Number (4/5): ' p_roll4
\prompt 'Enter Name (4/5): ' p_name4
\prompt 'Enter Issue Date (YYYY-MM-DD) (4/5): ' p_date4
\prompt 'Enter Book Name (4/5): ' p_book4
\prompt 'Enter Status (I/R) (4/5): ' p_status4

\prompt 'Enter Roll Number (5/5): ' p_roll5
\prompt 'Enter Name (5/5): ' p_name5
\prompt 'Enter Issue Date (YYYY-MM-DD) (5/5): ' p_date5
\prompt 'Enter Book Name (5/5): ' p_book5
\prompt 'Enter Status (I/R) (5/5): ' p_status5

INSERT INTO Borrow
VALUES
(:p_roll1, :'p_name1', TO_DATE(:'p_date1', 'YYYY-MM-DD'), :'p_book1', :'p_status1'),
(:p_roll2, :'p_name2', TO_DATE(:'p_date2', 'YYYY-MM-DD'), :'p_book2', :'p_status2'),
(:p_roll3, :'p_name3', TO_DATE(:'p_date3', 'YYYY-MM-DD'), :'p_book3', :'p_status3'),
(:p_roll4, :'p_name4', TO_DATE(:'p_date4', 'YYYY-MM-DD'), :'p_book4', :'p_status4'),
(:p_roll5, :'p_name5', TO_DATE(:'p_date5', 'YYYY-MM-DD'), :'p_book5', :'p_status5');
*/


-- STEP 5: Create procedure to calculate fine

CREATE OR REPLACE PROCEDURE Calculate_Fine(p_roll INT)
LANGUAGE plpgsql
AS $$
DECLARE
    v_issue_date DATE;
    v_days INT;
    v_fine NUMERIC(10,2);

BEGIN

    -- Get issue date of the book

    SELECT Issue_Date
    INTO v_issue_date
    FROM Borrow
    WHERE Roll = p_roll
    AND Status = 'I'
    FOR UPDATE;

    -- Check whether record exists

    IF NOT FOUND THEN
        RAISE NOTICE 'No issued book found for Roll Number %', p_roll;
        RETURN;
    END IF;

    -- Calculate number of days

    v_days := CURRENT_DATE - v_issue_date;

    -- Calculate fine using conditions

    IF v_days > 30 THEN
        v_fine := v_days * 50;

    ELSIF v_days > 0 THEN
        v_fine := v_days * 5;

    ELSE
        v_fine := 0;

    END IF;

    -- Update book status

    UPDATE Borrow
    SET Status = 'R'
    WHERE Roll = p_roll;

    -- Insert fine details if fine is applicable

    IF v_fine > 0 THEN

        INSERT INTO Lib_Fine
        VALUES (p_roll, CURRENT_DATE, v_fine);

    END IF;

    -- Display result

    RAISE NOTICE 'Roll Number: %', p_roll;
    RAISE NOTICE 'Days: %', v_days;
    RAISE NOTICE 'Fine Amount: Rs. %', v_fine;
    RAISE NOTICE 'Book Returned Successfully';

END;
$$;


-- STEP 6: Display Borrow table

SELECT * FROM Borrow;

-- STEP 7: Execute procedure
-- Change roll number as required

CALL Calculate_Fine(101);


-- STEP 8: Display fine details

SELECT * FROM Lib_Fine;
