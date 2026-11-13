# TY Semester 1 Lab Assignments

This repository contains lab assignments, practice programs, and mock practical solutions for **Data Structures and Algorithms (DSA)** and **Database Management Systems (DBMS)** for Third Year (TY) Semester 1.


---


## 📁 Repository Overview


```text
LAB-Assignments-TY-Sem-1/
├── DSA/
│   ├── TY_A_42/          # Course assignment solutions
│   ├── Mock/             # Practical exam mock problem solutions
│   └── *.cpp             # General ADT implementations & algorithms
└── DBMS/
    ├── Mock/             # Practical exam mock SQL, PL/pgSQL, Python, & MongoDB solutions
    └── *.txt             # Course assignment problem statements & solutions
```


---

## 📚 Data Structures and Algorithms (DSA)

The [`DSA`](./DSA) folder contains C++ implementations covering graph algorithms, trees, greedy strategies, dynamic programming, heaps, and branch & bound.

### Course Assignment Solutions (`DSA/TY_A_42`)

| Assignment | Topic                                        | Source file                                                                                                |
| ---------- | -------------------------------------------- | ---------------------------------------------------------------------------------------------------------- |
| 1          | Flight connections using an adjacency list   | [Assignment_01_Flight_List.cpp](./DSA/TY_A_42/Assignment_01_Flight_List.cpp)                               |
| 1          | Flight connections using an adjacency matrix | [Assignment_01_Flight_Matrix.cpp](./DSA/TY_A_42/Assignment_01_Flight_Matrix.cpp)                           |
| 2          | Binary Search Tree ADT                       | [Assignment_02_BST_ADT.cpp](./DSA/TY_A_42/Assignment_02_BST_ADT.cpp)                                       |
| 3          | Expression Tree                              | [Assignment_03_Expression_Tree.cpp](./DSA/TY_A_42/Assignment_03_Expression_Tree.cpp)                       |
| 4          | Dictionary using AVL Tree                    | [Assignment_04_Dictionary_AVL.cpp](./DSA/TY_A_42/Assignment_04_Dictionary_AVL.cpp)                         |
| 5          | Fractional Knapsack using Greedy Method      | [Assignment_05_Fractional_Knapsack_Greedy.cpp](./DSA/TY_A_42/Assignment_05_Fractional_Knapsack_Greedy.cpp) |
| 6          | 0/1 Knapsack using Branch and Bound          | [Assignment_06_Knapsack_Branch_Bound.cpp](./DSA/TY_A_42/Assignment_06_Knapsack_Branch_Bound.cpp)           |
| 6          | 0/1 Knapsack using Dynamic Programming       | [Assignment_06_Knapsack_DP.cpp](./DSA/TY_A_42/Assignment_06_Knapsack_DP.cpp)                               |


### Core Implementations and Lab Practice (`DSA`)

| Topic                                            | Source file                                                  |
| ------------------------------------------------ | ------------------------------------------------------------ |
| Flight connections using an adjacency list       | [ass1_list.cpp](./DSA/ass1_list.cpp)                         |
| Flight connections using an adjacency matrix     | [ass1_matrix.cpp](./DSA/ass1_matrix.cpp)                     |
| Expression Tree construction and traversal       | [ass3_expression_tree.cpp](./DSA/ass3_expression_tree.cpp)   |
| Graph flight connections representation          | [Assignment-01.cpp](./DSA/Assignment-01.cpp)                 |
| AVL Tree ADT (self-balancing BST)                | [AVL_ADT.cpp](./DSA/AVL_ADT.cpp)                             |
| Breadth-First Search (BFS)                       | [BFS.cpp](./DSA/BFS.cpp)                                     |
| Depth-First (DFS) and Breadth-First Search (BFS) | [DFS_BFS.cpp](./DSA/DFS_BFS.cpp)                             |
| Binary Tree ADT                                  | [BinaryTreeADT.cpp](./DSA/BinaryTreeADT.cpp)                 |
| Binary Search Tree ADT                           | [BST_ADT.cpp](./DSA/BST_ADT.cpp)                             |
| Binary Search Tree lab program                   | [BST_ADT_LAB.cpp](./DSA/BST_ADT_LAB.cpp)                     |
| Min/Max Heap operations and heapify              | [Heap.cpp](./DSA/Heap.cpp)                                   |
| Heap ADT (Min & Max Heap)                        | [Heap_ADT.cpp](./DSA/Heap_ADT.cpp)                           |
| 0/1 Knapsack using Branch and Bound              | [Knapsack_Branch_Bound.cpp](./DSA/Knapsack_Branch_Bound.cpp) |
| 0/1 Knapsack using Dynamic Programming           | [Knapsack_DP.cpp](./DSA/Knapsack_DP.cpp)                     |
| Fractional Knapsack using Greedy Method          | [Knapsack_greedy.cpp](./DSA/Knapsack_greedy.cpp)             |


### Practical & Mock Solutions (`DSA/Mock`)

| Problem / Domain | Topic | Source file |
|---|---|---|
| Ad Campaign Budget Optimization | 0/1 Knapsack (DP / Branch & Bound) | [0-1_Knapsack_Q1.cpp](./DSA/Mock/0-1_Knapsack_Q1.cpp) |
| Cloud Storage Backup Selection | 0/1 Knapsack (DP / Branch & Bound) | [0-1_Knapsack_Q2.cpp](./DSA/Mock/0-1_Knapsack_Q2.cpp) |
| Employee Directory Management | AVL Tree (Insert, Search, Delete, Height, Comparisons) | [AVL_Tree.cpp](./DSA/Mock/AVL_Tree.cpp) |
| Hospital Patient Records System | Binary Search Tree (Insert, Search, Min/Max ID, Metrics) | [BST_Q1.cpp](./DSA/Mock/BST_Q1.cpp) |
| Prefix Boolean Expression Tree | Expression Tree (Traversals, Logical Laws, Subtree Swap) | [Expression_Tree_Q1.cpp](./DSA/Mock/Expression_Tree_Q1.cpp) |
| Postfix Arithmetic/Boolean Expression | Expression Tree (Traversals, Evaluation, Conversions, Height) | [Expression_Tree_Q2.cpp](./DSA/Mock/Expression_Tree_Q2.cpp) |
| Food Relief Package Distribution | Fractional Knapsack (Greedy Approach) | [Fractional_Knapsack_Q1.cpp](./DSA/Mock/Fractional_Knapsack_Q1.cpp) |
| Server Processing Task Scheduling | Fractional Knapsack (Greedy Approach) | [Fractional_Knapsack_Q2.cpp](./DSA/Mock/Fractional_Knapsack_Q2.cpp) |
| Social Network Friendship Connections | Graph ADT (Adjacency Matrix & List, 1-Hop Connectivity) | [Graph_Q1.cpp](./DSA/Mock/Graph_Q1.cpp) |
| Airline Route Partnerships | Graph ADT (Adjacency Matrix & List, 1-Hop Connectivity) | [Graph_Q2.cpp](./DSA/Mock/Graph_Q2.cpp) |
| Job Priority Scheduling | Min/Max Heap (Complexity Analysis, Priority Ordering) | [Heap_Q1.cpp](./DSA/Mock/Heap_Q1.cpp) |
| Online Gaming Tournament Scores | Min/Max Heap (Highest/Lowest Scores, Extraction) | [Heap_Q2.cpp](./DSA/Mock/Heap_Q2.cpp) |
| Stock Price Tracker & Analysis | Min/Max Heap (Min/Max Tracking, Sorting, Complexity Analysis) | [Heap_Q3.cpp](./DSA/Mock/Heap_Q3.cpp) |

---

## 🗄️ Database Management Systems (DBMS)

The [`DBMS`](./DBMS) folder contains SQL, PL/pgSQL, Python/MySQL connectivity, and MongoDB solutions.

### Course Assignments (`DBMS`)

| Assignment | Topic                                  | File                                                  |
| ---------- | -------------------------------------- | ----------------------------------------------------- |
| 1          | SQL Queries (DDL & DML)                | [Assignment_1.txt](./DBMS/Assignment_1.txt)           |
| 2          | SQL Joins and Views                    | [Assignment_2.txt](./DBMS/Assignment_2.txt)           |
| 4          | PL/SQL Block and Fine Calculation      | [Assignment_4.txt](./DBMS/Assignment_4.txt)           |
| 5          | Database Triggers and Audit Table      | [Assignment_5.txt](./DBMS/Assignment_5.txt)           |
| 6          | Python and MySQL Database Connectivity | [Assignment_6.txt](./DBMS/Assignment_6.txt)           |
| 7          | MongoDB Queries (CRUD operations)      | [Assignment_7.txt](./DBMS/Assignment_7.txt)           |
| 8          | MongoDB Aggregation and Indexing       | [Assignment_8.txt](./DBMS/Assignment_8.txt)           |

### Practical & Mock Solutions (`DBMS/Mock`)

| Assignment | Technology / Topic   | Description                                                       | File                                               |
| ---------- | -------------------- | ----------------------------------------------------------------- | -------------------------------------------------- |
| 1          | MySQL                | Company Database Queries (DDL, DML, Subqueries, Joins)            | [Assignment_01.sql](./DBMS/Mock/Assignment_01.sql) |
| 2          | MySQL                | College Database Joins (Inner, Left, Right Joins & Views - Set A) | [Assignment_02.sql](./DBMS/Mock/Assignment_02.sql) |
| 3          | MySQL                | College Database Joins (Inner, Left, Right Joins & Views - Set B) | [Assignment_03.sql](./DBMS/Mock/Assignment_03.sql) |
| 7          | PostgreSQL / PLpgSQL | Library Fine Calculation Stored Procedure                         | [Assignment_07.sql](./DBMS/Mock/Assignment_07.sql) |
| 8          | PostgreSQL / PLpgSQL | Library Fine Management with Exception Handling                   | [Assignment_08.sql](./DBMS/Mock/Assignment_08.sql) |
| 9          | PostgreSQL / PLpgSQL | Library Audit System with `BEFORE DELETE` / `UPDATE` Triggers     | [Assignment_09.sql](./DBMS/Mock/Assignment_09.sql) |
| 10         | PostgreSQL / PLpgSQL | Library Audit Logging Trigger System (`Kitab` table)              | [Assignment_10.sql](./DBMS/Mock/Assignment_10.sql) |
| 11         | Python & MySQL       | Menu-driven Book Management System (CRUD Operations)              | [Assignment_11.py](./DBMS/Mock/Assignment_11.py)   |
| 12         | Python & MySQL       | Menu-driven Student Management System (CRUD Operations)           | [Assignment_12.py](./DBMS/Mock/Assignment_12.py)   |
| 13         | MongoDB (`mongosh`)  | Library Books Collection CRUD Operations (Set A)                  | [Assignment_13.js](./DBMS/Mock/Assignment_13.js)   |
| 14         | MongoDB (`mongosh`)  | Library Books Collection CRUD Operations (Set B)                  | [Assignment_14.js](./DBMS/Mock/Assignment_14.js)   |
| 15         | MongoDB (`mongosh`)  | Tech Articles Collection Aggregation Pipelines & Indexes          | [Assignment_15.js](./DBMS/Mock/Assignment_15.js)   |

---

## 🚀 Execution & Usage Guide

### C++ Programs (DSA)

Compile any C++ source file using `g++`:

```bash
# Compile
g++ -O2 -std=c++17 DSA/Mock/AVL_Tree.cpp -o avl_tree

# Run
./avl_tree
```

### MySQL Scripts

Execute SQL scripts directly into MySQL:

```bash
mysql -u root -p < DBMS/Mock/Assignment_01.sql
```

### PostgreSQL Scripts

Run PL/pgSQL scripts using `psql`:

```bash
sudo service postgresql start
sudo -u postgres psql -d dbms_practical -f DBMS/Mock/Assignment_07.sql
```

### Python MySQL Connectivity

Set up a Python virtual environment and run the application:

```bash
# Set up environment
python3 -m venv venv
source venv/bin/activate  # On Windows: .\venv\Scripts\activate

# Install MySQL connector
pip install mysql-connector-python

# Run application
python DBMS/Mock/Assignment_11.py
```

### MongoDB Scripts

Execute JavaScript MongoDB scripts using `mongosh`:

```bash
mongosh < DBMS/Mock/Assignment_13.js
```
