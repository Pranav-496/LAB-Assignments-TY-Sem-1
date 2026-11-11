--Instructions to run this shit are in Assignment_7
-- ==========================================
-- PROBLEM STATEMENT 09
-- LIBRARY DATABASE AUDIT SYSTEM
-- PostgreSQL / PLpgSQL
-- ==========================================

-- STEP 1: Create Pustak table

CREATE TABLE Pustak (
    Pustak_No INT PRIMARY KEY,
    Title VARCHAR(50),
    Author VARCHAR(50),
    Publisher VARCHAR(50),
    Count INT
);


-- STEP 2: Insert given records

INSERT INTO Pustak VALUES
(101, 'C Programming', 'Dennis Ritchie', 'PHI', 10),
(102, 'Data Structures', 'Seymour Lipschutz', 'McGraw Hill', 8),
(103, 'Database Systems', 'Korth', 'TMH', 5),
(104, 'Operating Systems', 'Silberschatz', 'Wiley', 7),
(105, 'Python Programming', 'Mark Lutz', 'O''Reilly', 12);


-- STEP 3: Create Lib_Audit table

CREATE TABLE Lib_Audit (
    Pustak_No INT,
    Title VARCHAR(50),
    Author VARCHAR(50),
    Publisher VARCHAR(50),
    Count INT,
    Audit_Date TIMESTAMP,
    Status VARCHAR(20)
);


-- STEP 4: Create BEFORE DELETE trigger function

CREATE OR REPLACE FUNCTION audit_delete()
RETURNS TRIGGER
LANGUAGE plpgsql
AS $$
BEGIN

    INSERT INTO Lib_Audit
    VALUES (
        OLD.Pustak_No,
        OLD.Title,
        OLD.Author,
        OLD.Publisher,
        OLD.Count,
        CURRENT_TIMESTAMP,
        'Deleted'
    );

    RETURN OLD;

END;
$$;


-- STEP 5: Create BEFORE DELETE trigger

CREATE TRIGGER trg_before_delete
BEFORE DELETE ON Pustak
FOR EACH ROW
EXECUTE FUNCTION audit_delete();


-- STEP 6: Create AFTER UPDATE trigger function

CREATE OR REPLACE FUNCTION audit_update()
RETURNS TRIGGER
LANGUAGE plpgsql
AS $$
BEGIN

    INSERT INTO Lib_Audit
    VALUES (
        NEW.Pustak_No,
        NEW.Title,
        NEW.Author,
        NEW.Publisher,
        NEW.Count,
        CURRENT_TIMESTAMP,
        'Updated'
    );

    RETURN NEW;

END;
$$;


-- STEP 7: Create AFTER UPDATE trigger

CREATE TRIGGER trg_after_update
AFTER UPDATE ON Pustak
FOR EACH ROW
EXECUTE FUNCTION audit_update();


-- STEP 8: Display original records

SELECT * FROM Pustak;


-- STEP 9: Test UPDATE trigger

UPDATE Pustak
SET Count = 20
WHERE Pustak_No = 102;


-- STEP 10: Test DELETE trigger

DELETE FROM Pustak
WHERE Pustak_No = 101;


-- STEP 11: Display audit records

SELECT * FROM Lib_Audit;
