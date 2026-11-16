
# Assignment 11: Book Management using Python and MySQL
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
# 3. Create MySQL user:
#    sudo mysql
#
#    Run these commands inside MySQL:
#    CREATE USER IF NOT EXISTS 'books_user'@'localhost'
#    IDENTIFIED BY '12345';
#
#    ALTER USER 'books_user'@'localhost'
#    IDENTIFIED BY '12345';
#
#    GRANT CREATE ON *.* TO 'books_user'@'localhost';
#    GRANT ALL PRIVILEGES ON dbms_assignment11.*
#    TO 'books_user'@'localhost';
#    FLUSH PRIVILEGES;
#    EXIT;
#
# 4. Install MySQL connector:
#    python3 -m venv ~/dbms-env
#    source ~/dbms-env/bin/activate
#    python -m pip install mysql-connector-python
#
# 5. Run the program:
#    python Assignment_11.py
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
cur.execute("CREATE DATABASE IF NOT EXISTS dbms_assignment11")
cur.execute("USE dbms_assignment11")

cur.execute("""
CREATE TABLE IF NOT EXISTS Books (
    Book_ID INT PRIMARY KEY,
    Title VARCHAR(100),
    Author VARCHAR(100),
    Publisher VARCHAR(100),
    `Count` INT
)
""")

# Menu-driven program
while True:
    print("\n1. Add Book")
    print("2. Delete Book")
    print("3. Edit Book Details")
    print("4. View All Books")
    print("5. Search Book by ID")
    print("6. Exit")

    ch = int(input("Enter your choice: "))

    if ch == 1:
        id = int(input("Enter Book ID: "))
        title = input("Enter Title: ")
        author = input("Enter Author: ")
        publisher = input("Enter Publisher: ")
        count = int(input("Enter Count: "))

        cur.execute(
            "INSERT INTO Books VALUES (%s,%s,%s,%s,%s)",
            (id, title, author, publisher, count)
        )
        con.commit()
        print("Book Added Successfully")

    elif ch == 2:
        id = int(input("Enter Book ID: "))

        cur.execute("DELETE FROM Books WHERE Book_ID=%s", (id,))
        con.commit()

        if cur.rowcount > 0:
            print("Book Deleted Successfully")
        else:
            print("Book Not Found")

    elif ch == 3:
        id = int(input("Enter Book ID: "))

        cur.execute("SELECT * FROM Books WHERE Book_ID=%s", (id,))

        if cur.fetchone():
            title = input("Enter New Title: ")
            author = input("Enter New Author: ")
            publisher = input("Enter New Publisher: ")
            count = int(input("Enter New Count: "))

            cur.execute(
                "UPDATE Books SET Title=%s, Author=%s, Publisher=%s, `Count`=%s WHERE Book_ID=%s",
                (title, author, publisher, count, id)
            )
            con.commit()
            print("Book Updated Successfully")
        else:
            print("Book Not Found")

    elif ch == 4:
        cur.execute("SELECT * FROM Books")

        for row in cur.fetchall():
            print(row)

    elif ch == 5:
        id = int(input("Enter Book ID: "))

        cur.execute("SELECT * FROM Books WHERE Book_ID=%s", (id,))
        row = cur.fetchone()

        if row:
            print(row)
        else:
            print("Book Not Found")

    elif ch == 6:
        print("Program Exited")
        break

    else:
        print("Invalid Choice")

# Close database connection
cur.close()
con.close()
