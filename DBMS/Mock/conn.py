import mysql.connector

con = mysql.connector.connect(
    host="localhost",
    user="Pranav",
    password="12345"
)

cur = con.cursor()

cur.execute("create database if not exists conn2")
cur.execute("use conn2")

cur.execute("""
create table if not exists stu(
    roll int primary key,
    name varchar(10),
    age int
)
""")

while True:
    print("\n1. Add Student")
    print("2. Delete Student")
    print("3. Edit Student")
    print("4. View all Students")
    print("5. View one Students")
    print("6. Exit")

    ch = int(input("Enter your choice: "))

    if ch == 1:
        roll = int(input("Enter roll no : "))
        name = input("Enter name : ")
        age = int(input("Enter age : "))

        cur.execute(
            "insert into stu values (%s, %s, %s)",
            (roll,name,age)
        )
        con.commit()
        print("student added successfully")

    elif ch == 2:
        roll = int(input("Enter roll : "))
        cur.execute("delete from stu where roll = %s", (roll,))
        con.commit()

        if cur.rowcount > 0:
            print("student deleted successfully")
        else:
            print("roll no not found")


    elif ch == 3:
        roll = int(input("Enter roll : "))
        cur.execute("select * from stu where roll = %s",(roll,))
        if cur.fetchone():
            name = input("Enter name : ")
            age = int(input("Enter age : "))    

            cur.execute("update stu set name = %s, age = %s where roll = %s", (name,age,roll))
            con.commit()
            print("student updated successfully")

        else: 
            print("student not found")

    elif ch == 4:
        cur.execute("SELECT * FROM stu")

        for row in cur.fetchall():
            print(row)

    elif ch == 5:
        roll = int(input("Enter roll: "))

        cur.execute("SELECT * FROM stu WHERE roll=%s", (roll,))
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

cur.close()
con.close()