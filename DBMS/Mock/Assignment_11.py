# Assignment 11: Python and MySQL Book Management
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
# 3. Create a MySQL user for this assignment:
#    sudo mysql
#    Then, at the mysql> prompt, run the following SQL. Replace
#    your_password_here with a password you choose and remember.
#
#    CREATE USER IF NOT EXISTS 'books_user'@'localhost'
#        IDENTIFIED BY 'your_password_here';
#    ALTER USER 'books_user'@'localhost'
#        IDENTIFIED BY 'your_password_here';
#    GRANT CREATE ON *.* TO 'books_user'@'localhost';
#    GRANT ALL PRIVILEGES ON dbms_assignment11.* TO 'books_user'@'localhost';
#    FLUSH PRIVILEGES;
#    EXIT;
#
#    Use the same password in the PASSWORD setting below. The program creates
#    the dbms_assignment11 database and Books table automatically.
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
#    python DBMS/Mock/Assignment_11.py
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

        cursor.execute("CREATE DATABASE IF NOT EXISTS dbms_assignment11")
        cursor.execute("USE dbms_assignment11")
        cursor.execute(
            """
            CREATE TABLE IF NOT EXISTS Books (
                Book_ID INT PRIMARY KEY,
                Title VARCHAR(100) NOT NULL,
                Author VARCHAR(100) NOT NULL,
                Publisher VARCHAR(100) NOT NULL,
                `Count` INT NOT NULL
            )
            """
        )

        while True:
            print(
                "\n1. Add a new book\n"
                "2. Delete a book\n"
                "3. Edit book details\n"
                "4. View all books\n"
                "5. Search a book by Book_ID\n"
                "6. Exit"
            )
            choice = input("Choose an option: ").strip()

            if choice == "1":
                book_id = int(input("Book ID: "))
                title = input("Title: ").strip()
                author = input("Author: ").strip()
                publisher = input("Publisher: ").strip()
                count = int(input("Number of copies: "))

                if book_id <= 0 or count < 0:
                    print("Book ID must be positive and copies cannot be negative.")
                    continue
                if not title or not author or not publisher:
                    print("Title, author, and publisher cannot be empty.")
                    continue

                cursor.execute(
                    "INSERT INTO Books (Book_ID, Title, Author, Publisher, `Count`) "
                    "VALUES (%s, %s, %s, %s, %s)",
                    (book_id, title, author, publisher, count),
                )
                connection.commit()
                print("Book added.")

            elif choice == "2":
                book_id = int(input("Book ID to delete: "))
                cursor.execute("DELETE FROM Books WHERE Book_ID = %s", (book_id,))
                connection.commit()
                if cursor.rowcount:
                    print("Book deleted.")
                else:
                    print("No book found with that ID.")

            elif choice == "3":
                book_id = int(input("Book ID to edit: "))
                title = input("New title: ").strip()
                author = input("New author: ").strip()
                publisher = input("New publisher: ").strip()
                count = int(input("New number of copies: "))

                if count < 0:
                    print("Number of copies cannot be negative.")
                    continue
                if not title or not author or not publisher:
                    print("Title, author, and publisher cannot be empty.")
                    continue

                cursor.execute(
                    "UPDATE Books SET Title = %s, Author = %s, "
                    "Publisher = %s, `Count` = %s WHERE Book_ID = %s",
                    (title, author, publisher, count, book_id),
                )
                connection.commit()
                if cursor.rowcount:
                    print("Book details updated.")
                else:
                    print("No book found with that ID.")

            elif choice == "4":
                cursor.execute(
                    "SELECT Book_ID, Title, Author, Publisher, `Count` "
                    "FROM Books ORDER BY Book_ID"
                )
                books = cursor.fetchall()
                if not books:
                    print("No books found.")
                else:
                    for book in books:
                        print(
                            f"ID: {book[0]} | Title: {book[1]} | "
                            f"Author: {book[2]} | Publisher: {book[3]} | "
                            f"Copies: {book[4]}"
                        )

            elif choice == "5":
                book_id = int(input("Book ID to search: "))
                cursor.execute(
                    "SELECT Book_ID, Title, Author, Publisher, `Count` "
                    "FROM Books WHERE Book_ID = %s",
                    (book_id,),
                )
                book = cursor.fetchone()
                if book:
                    print(
                        f"ID: {book[0]} | Title: {book[1]} | "
                        f"Author: {book[2]} | Publisher: {book[3]} | "
                        f"Copies: {book[4]}"
                    )
                else:
                    print("No book found with that ID.")

            elif choice == "6":
                print("Goodbye.")
                break

            else:
                print("Invalid option. Choose a number from 1 to 6.")

    except ValueError:
        print("Book ID and number of copies must be whole numbers.")
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
