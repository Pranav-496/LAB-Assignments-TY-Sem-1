--Instructions to run this shit are in Assignment_7

-- as we created tables in assignment 7 toh firse karne ki koi jarurat nahi

/*CREATE TABLE Borrow (
  Roll INT PRIMARY KEY,
  Name VARCHAR(30),
  Issue_Date DATE,
  Book_Name VARCHAR(50),
  Status CHAR(1)
);

CREATE TABLE Lib_Fine (
  Roll_no INT,
  Curr_Date DATE,
  AmT NUMERIC(10,2)
);*/

INSERT INTO Borrow VALUES
(107, 'Siddharth', '2025-10-05', 'Algorithms', 'I'),
(108, 'Meera', '2025-09-15', 'Computer Networks', 'I'),
(109, 'Akash', '2025-10-12', 'Software Engineering', 'I'),
(110, 'Tanya', '2025-09-20', 'Database Systems', 'I');

CREATE OR REPLACE PROCEDURE Calculate_Fine(p_roll INT)
LANGUAGE plpgsql
AS $$
DECLARE
  v_issue_date DATE;
  v_days INT;
  v_fine NUMERIC(10,2);
BEGIN
  SELECT Issue_Date
  INTO v_issue_date
  FROM Borrow
  WHERE Roll = p_roll
  AND Status = 'I'
  FOR UPDATE;

  IF NOT FOUND THEN
    RAISE NOTICE 'No issued book found for roll number %',p_roll;
    RETURN;
  END IF;

  v_days := CURRENT_DATE - v_issue_date;

  IF v_days > 30 THEN
    v_fine := v_days * 50;
  
  ELSIF v_days > 0 THEN
    v_fine := v_days * 5;
  
  ELSE 
    v_fine := 0;
  
  END IF;

  UPDATE Borrow
  SET Status = 'R'
  WHERE Roll = p_roll;

  IF v_fine > 0 THEN
    Insert into Lib_Fine
    values(p_roll, CURRENT_DATE, v_fine);
  END if;

  RAISE NOTICE 'Roll Number: %', p_roll;
  RAISE NOTICE 'Days: %', v_days;
  RAISE NOTICE 'Fine Amount: Rs. %', v_fine;
  RAISE NOTICE 'Book Returned Successfully';

END;
$$;

SELECT * FROM Borrow;

CALL Calculate_Fine(107);

SELECT * FROM Lib_Fine;