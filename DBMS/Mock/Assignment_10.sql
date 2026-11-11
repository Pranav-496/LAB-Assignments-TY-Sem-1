--Instructions to run this shit are in Assignment_7

create table Kitab (
  Kitab_no int PRIMARY key,
  Title varchar(50),
  Author varchar(50),
  Publisher varchar(50),
  Count int
);

INSERT INTO Pustak VALUES
(106, 'Java Programming', 'James Gosling', 'Oracle Press',9),
(107, 'Algos', 'Robert Sedgewick', 'Addison-Wesley', 6),
(108, 'Computer Networks', 'Andrew Tanenbaum', 'Pearson', 7),
(109, 'Software engineering', 'Ian Sommerville', 'Pearson', 5),
(110, 'Artificial Intelligence', 'Stuart Russell', 'Pearson', 4);

CREATE TABLE Lib_Audit (
    Kitab_no INT,
    Title VARCHAR(50),
    Author VARCHAR(50),
    Publisher VARCHAR(50),
    Count INT,
    Audit_Date TIMESTAMP,
    Status VARCHAR(20)
);

CREATE OR REPLACE FUNCTION audit_delete()
RETURNS TRIGGER
LANGUAGE plpgsql
AS $$
BEGIN

    INSERT INTO Lib_Audit
    VALUES (
        OLD.Kitab_no,
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


CREATE TRIGGER trg_before_delete
BEFORE DELETE ON Kitab
FOR EACH ROW
EXECUTE FUNCTION audit_delete();

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

CREATE TRIGGER trg_after_update
AFTER UPDATE ON Kitab
FOR EACH ROW
EXECUTE FUNCTION audit_update();

SELECT * FROM Kitab;

Update Kitab
set Count = 20
where Kitab_no = 107;

delete from Kitab
where Kitab_no = 109;

SELECT * from Lib_Audit;