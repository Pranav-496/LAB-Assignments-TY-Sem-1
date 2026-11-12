# Assignment 12: Python and MySQL Student Management
#
# Setup and run this program from the Ubuntu (WSL) terminal, not PowerShell.
#
# 1. Install MySQL and Python tools if they are not already installed:
#    sudo apt update
#    sudo apt install mysql-server python3-pip python3-venv
#
# 2. Start MySQL:
#    sudo service mysql start
#
# 3. Give the MySQL user permission to create and use this assignment database.
#    If you already created books_user for Assignment 11, open MySQL:
#    sudo mysql
#    Then run this SQL at the mysql> prompt:
#
#    GRANT CREATE ON *.* TO 'books_user'@'localhost';
#    GRANT ALL PRIVILEGES ON dbms_assignment12.* TO 'books_user'@'localhost';
#    FLUSH PRIVILEGES;
#    EXIT;
#
#    If you have not created books_user yet, run these commands in MySQL
#    instead, replacing your_password_here with a password you choose:
#
#    CREATE USER IF NOT EXISTS 'books_user'@'localhost'
#        IDENTIFIED BY 'your_password_here';
#    ALTER USER 'books_user'@'localhost'
#        IDENTIFIED BY 'your_password_here';
#    GRANT CREATE ON *.* TO 'books_user'@'localhost';
#    GRANT ALL PRIVILEGES ON dbms_assignment12.* TO 'books_user'@'localhost';
#    FLUSH PRIVILEGES;
#    EXIT;
#
#    Set PASSWORD below to the same password. The program creates the
#    dbms_assignment12 database and Students table automatically.
#
# 4. Go to the project folder in Ubuntu:
#    cd /mnt/d/LAB-Assignments-TY-Sem-1
#
# 5. Create a Python environment and install the MySQL connector.
#    These setup commands only need to be done once:
#    python3 -m venv ~/dbms-env
#    source ~/dbms-env/bin/activate
#    python -m pip install mysql-connector-python
#
# 6. Run the program from the project folder with the environment activated:
#    python DBMS/Mock/Assignment_12.py
#
#    To run it later, start MySQL, go to the project folder, and activate the
#    environment again with: source ~/dbms-env/bin/activate
#
# Troubleshooting:
# - Access denied: make sure the MySQL username and password below match.
# - Can't connect: start MySQL with sudo service mysql start.
# - No module named 'mysql': activate dbms-env and install the connector.
#
import mysql.connector
from mysql.connector import Error


HOST = "localhost"
USER = "books_user"
PASSWORD = "ChooseANewPassword"


def main():
    connection = None
    cursor = None

    try:
        connection = mysql.connector.connect(
            host=HOST,
            user=USER,
            password=PASSWORD,
        )
        cursor = connection.cursor()

        cursor.execute("CREATE DATABASE IF NOT EXISTS dbms_assignment12")
        cursor.execute("USE dbms_assignment12")
        cursor.execute(
            """
            CREATE TABLE IF NOT EXISTS Students (
                Student_ID INT PRIMARY KEY,
                Name VARCHAR(100) NOT NULL,
                City VARCHAR(100) NOT NULL,
                Age INT NOT NULL,
                Department VARCHAR(100) NOT NULL
            )
            """
        )

        while True:
            print(
                "\n1. Add a new student\n"
                "2. Delete a student\n"
                "3. Edit student details\n"
                "4. View all students\n"
                "5. Search a student by Student_ID\n"
                "6. Exit"
            )
            choice = input("Choose an option: ").strip()

            if choice == "1":
                student_id = int(input("Student ID: "))
                name = input("Name: ").strip()
                city = input("City: ").strip()
                age = int(input("Age: "))
                department = input("Department: ").strip()

                if student_id <= 0 or age < 0:
                    print("Student ID must be positive and age cannot be negative.")
                    continue
                if not name or not city or not department:
                    print("Name, city, and department cannot be empty.")
                    continue

                cursor.execute(
                    "INSERT INTO Students "
                    "(Student_ID, Name, City, Age, Department) "
                    "VALUES (%s, %s, %s, %s, %s)",
                    (student_id, name, city, age, department),
                )
                connection.commit()
                print("Student added.")

            elif choice == "2":
                student_id = int(input("Student ID to delete: "))
                cursor.execute(
                    "DELETE FROM Students WHERE Student_ID = %s",
                    (student_id,),
                )
                connection.commit()
                if cursor.rowcount:
                    print("Student deleted.")
                else:
                    print("No student found with that ID.")

            elif choice == "3":
                student_id = int(input("Student ID to edit: "))
                name = input("New name: ").strip()
                city = input("New city: ").strip()
                age = int(input("New age: "))
                department = input("New department: ").strip()

                if age < 0:
                    print("Age cannot be negative.")
                    continue
                if not name or not city or not department:
                    print("Name, city, and department cannot be empty.")
                    continue

                cursor.execute(
                    "UPDATE Students SET Name = %s, City = %s, Age = %s, "
                    "Department = %s WHERE Student_ID = %s",
                    (name, city, age, department, student_id),
                )
                connection.commit()
                if cursor.rowcount:
                    print("Student details updated.")
                else:
                    print("No student found with that ID.")

            elif choice == "4":
                cursor.execute(
                    "SELECT Student_ID, Name, City, Age, Department "
                    "FROM Students ORDER BY Student_ID"
                )
                students = cursor.fetchall()
                if not students:
                    print("No students found.")
                else:
                    for student in students:
                        print(
                            f"ID: {student[0]} | Name: {student[1]} | "
                            f"City: {student[2]} | Age: {student[3]} | "
                            f"Department: {student[4]}"
                        )

            elif choice == "5":
                student_id = int(input("Student ID to search: "))
                cursor.execute(
                    "SELECT Student_ID, Name, City, Age, Department "
                    "FROM Students WHERE Student_ID = %s",
                    (student_id,),
                )
                student = cursor.fetchone()
                if student:
                    print(
                        f"ID: {student[0]} | Name: {student[1]} | "
                        f"City: {student[2]} | Age: {student[3]} | "
                        f"Department: {student[4]}"
                    )
                else:
                    print("No student found with that ID.")

            elif choice == "6":
                print("Goodbye.")
                break

            else:
                print("Invalid option. Choose a number from 1 to 6.")

    except ValueError:
        print("Student ID and age must be whole numbers.")
    except Error as error:
        if connection is not None:
            connection.rollback()
        print(f"MySQL error: {error}")
    finally:
        if cursor is not None:
            cursor.close()
        if connection is not None:
            connection.close()


if __name__ == "__main__":
    main()
