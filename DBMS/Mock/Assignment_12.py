
# Assignment 12: Student Management using Python and MySQL
#
# SETUP INSTRUCTIONS (Run in Ubuntu / WSL terminal):
#
# 1. Install MySQL and Python tools:
#    sudo apt update
#    sudo apt install mysql-server python3-pip python3-venv
#
# 2. Start MySQL:
#    sudo service mysql start
#
# 3. Give database permissions:
#    sudo mysql
#
#    Run these commands inside MySQL:
#    GRANT CREATE ON *.* TO 'books_user'@'localhost';
#    GRANT ALL PRIVILEGES ON dbms_assignment12.*
#    TO 'books_user'@'localhost';
#    FLUSH PRIVILEGES;
#    EXIT;
#
#    If books_user does not exist, create it first:
#    CREATE USER 'books_user'@'localhost' IDENTIFIED BY '12345';

#    CREATE USER IF NOT EXISTS 'books_user'@'localhost'
#        IDENTIFIED BY 'your_password_here';
#    ALTER USER 'books_user'@'localhost'
#        IDENTIFIED BY 'your_password_here';
#    GRANT CREATE ON *.* TO 'books_user'@'localhost';
#    GRANT ALL PRIVILEGES ON dbms_assignment12.* TO 'books_user'@'localhost';
#    FLUSH PRIVILEGES;
#    EXIT;
#
# 4. Go to the project folder:
#    cd /mnt/d/LAB-Assignments-TY-Sem-1
#
# 5. Create environment and install connector (one time only):
#    python3 -m venv ~/dbms-env
#    source ~/dbms-env/bin/activate
#    python -m pip install mysql-connector-python
#
# 6. Run the program:
#    python DBMS/Mock/Assignment_12.py
#
# NOTE: Use the same MySQL password in the PASSWORD variable.

import mysql.connector

# Connect to MySQL
con = mysql.connector.connect(
    host="localhost",
    user="books_user",
    password="12345"
)

cur = con.cursor()

# Create database and table
cur.execute("CREATE DATABASE IF NOT EXISTS dbms_assignment12")
cur.execute("USE dbms_assignment12")

cur.execute("""
CREATE TABLE IF NOT EXISTS Students (
    Student_ID INT PRIMARY KEY,
    Name VARCHAR(100),
    City VARCHAR(100),
    Age INT,
    Department VARCHAR(100)
)
""")

# Menu-driven program
while True:
    print("\n1. Add Student")
    print("2. Delete Student")
    print("3. Edit Student Details")
    print("4. View All Students")
    print("5. Search Student by ID")
    print("6. Exit")

    ch = int(input("Enter your choice: "))

    if ch == 1:
        id = int(input("Enter Student ID: "))
        name = input("Enter Name: ")
        city = input("Enter City: ")
        age = int(input("Enter Age: "))
        dept = input("Enter Department: ")

        cur.execute(
            "INSERT INTO Students VALUES (%s,%s,%s,%s,%s)",
            (id, name, city, age, dept)
        )
        con.commit()
        print("Student Added Successfully")

    elif ch == 2:
        id = int(input("Enter Student ID: "))

        cur.execute("DELETE FROM Students WHERE Student_ID=%s", (id,))
        con.commit()

        if cur.rowcount > 0:
            print("Student Deleted Successfully")
        else:
            print("Student Not Found")

    elif ch == 3:
        id = int(input("Enter Student ID: "))

        cur.execute("SELECT * FROM Students WHERE Student_ID=%s", (id,))

        if cur.fetchone():
            name = input("Enter New Name: ")
            city = input("Enter New City: ")
            age = int(input("Enter New Age: "))
            dept = input("Enter New Department: ")

            cur.execute(
                "UPDATE Students SET Name=%s, City=%s, Age=%s, Department=%s WHERE Student_ID=%s",
                (name, city, age, dept, id)
            )
            con.commit()
            print("Student Updated Successfully")
        else:
            print("Student Not Found")

    elif ch == 4:
        cur.execute("SELECT * FROM Students")
        students = cur.fetchall()

        if students:
            for row in students:
                print(row)
        else:
            print("No Students Found")

    elif ch == 5:
        id = int(input("Enter Student ID: "))

        cur.execute("SELECT * FROM Students WHERE Student_ID=%s", (id,))
        row = cur.fetchone()

        if row:
            print(row)
        else:
            print("Student Not Found")

    elif ch == 6:
        print("Program Exited")
        break

    else:
        print("Invalid Choice")

# Close database connection
cur.close()
con.close()
