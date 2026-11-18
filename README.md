# Employee Performance & KPI Dashboard (CLI)

A simple, beginner-friendly Command-Line Interface (CLI) application developed in **C** to manage employee records, track performance metrics, compute Key Performance Indicators (KPIs), sort and filter data, monitor performance trends, and persist records across sessions using standard file handling.


---

## 1. Project Introduction

In any organization, monitoring employee output and identifying team members who excel or require mentoring is essential. The **Employee Performance & KPI Dashboard** provides an interactive command-line solution to enter, evaluate, search, sort, and store employee records.

The project demonstrates core procedural programming in C—utilizing structures, dynamic arrays, pointers, modular functions, text-based file I/O, linear search, and the bubble sort algorithm—without requiring external libraries or complicated enterprise dependencies.

---

## 2. Project Objectives

1. **Record Management:** Store essential employee details including ID, Name, Department, Tasks Completed, Working Hours, and Quality Score.
2. **KPI Computation:** Automatically compute mathematical performance metrics:
   - **Productivity Score:** $\text{Tasks Completed} / \text{Working Hours}$ (with zero-division prevention).
   - **Reliability Index:** Quality score represented as a percentage out of 100%.
   - **Performance Grade:** Categorization into *Excellent*, *Good*, *Average*, or *Needs Improvement*.
3. **Data Organization:** Enable linear search by Employee ID and Bubble Sort by productivity score in descending order.
4. **Targeted Filtering:** Filter employee records by department name (case-insensitive).
5. **Early Performance Warnings:** Proactively flag employees scoring below 50 so managers can provide timely training.
6. **Performance Trend Analysis:** Track performance trajectory by comparing a newly entered quality score against previous scores (*Improving*, *Worsening*, or *Unchanged*).
7. **Persistent Storage:** Retain records across application restarts using standard C file handling (`employees.txt`).

---

## 3. Features Implemented

| Feature # | Feature Name | Description |
|---|---|---|
| **Feature 1** | **Add Employee** | Enters ID, Name, Department, Tasks, Hours, and Quality Score with duplicate ID and input validation. |
| **Feature 2** | **Display All Employees** | Renders all records in a formatted ASCII table showing IDs, names, departments, hours, scores, and grades. |
| **Feature 3** | **Calculate Performance KPIs** | Evaluates Productivity Score, Reliability Index, and Performance Grade using conditional logic and zero-division protection. |
| **Feature 4** | **Search Employee** | Performs a Linear Search by Employee ID and displays an itemized summary card if found. |
| **Feature 5** | **Sort by Productivity** | Employs the **Bubble Sort** algorithm to arrange employees from highest to lowest productivity score. |
| **Feature 6** | **Department Filter** | Filters and displays employees belonging to a specified department (handles spaces and case-insensitivity). |
| **Feature 7** | **Performance Warnings** | Audits all records and highlights team members whose quality score is below 50. |
| **Feature 8** | **Performance Trend** | Compares an updated score with the previous score and reports *Improving*, *Worsening*, or *Unchanged*. |
| **Feature 9** | **Save & Load Records** | Automatically loads records from `employees.txt` at startup and saves changes upon exit or manual trigger. |

---

## 4. Technologies Used

- **Language:** C (Standard C99 / C11)
- **Compiler:** GCC / Clang (MinGW-w64 on Windows, GCC on Linux/macOS)
- **Interface:** Command-Line Interface (CLI / Terminal)
- **Editor / IDE:** Visual Studio Code (VS Code)
- **Storage:** Plain text file (`employees.txt`)
- **Libraries:** Standard C Library only (`<stdio.h>`, `<stdlib.h>`, `<string.h>`)

---

## 5. C Programming Concepts Applied

This project covers key concepts taught in a first-year undergraduate C programming curriculum:

1. **Standard Input & Output (`printf`, `scanf`, `fgets`):**
   - Formatted table printing using field-width specifiers (`%-20s`, `%6.1f`, etc.).
   - Buffer flushing with `clearInputBuffer()` to eliminate common `scanf` newline bugs.
   - Safe multi-word string input using `fgets()`.
2. **Data Types & Variables:** Use of `int`, `float`, `char`, and `size_t`.
3. **Conditional Logic (`if`, `else if`, `else`, `switch`):**
   - Input boundary validation (e.g., Quality Score $0 - 100$, non-negative hours).
   - Division-by-zero protection.
   - Menu routing via `switch-case`.
4. **Loops (`while`, `do-while`, `for`):**
   - Continuous interactive menu loop (`do-while`).
   - Iteration through records for display, search, and audit (`for`).
5. **User-Defined Data Types (`struct`):**
   - Encapsulation of employee attributes and calculated KPIs inside `struct Employee`.
6. **Pointers & Pass-by-Reference:**
   - Passing pointers and double pointers (`struct Employee **`) to functions so that modifications persist in `main()`.
7. **Dynamic Memory Allocation (`malloc`, `realloc`, `free`):**
   - Initial array allocation via `malloc()`.
   - On-demand array expansion when capacity is reached via `realloc()`.
   - Complete memory cleanup using `free()` before exit to avoid memory leaks.
8. **Searching Algorithm (Linear Search):**
   - Sequential scan through records to find matching employee ID in $O(N)$ time.
9. **Sorting Algorithm (Bubble Sort):**
   - Elementary comparison and adjacent swapping to order employees by productivity score in $O(N^2)$ time.
10. **File Handling (`fopen`, `fprintf`, `fgets`, `sscanf`, `fclose`):**
    - Pipe-delimited (`|`) file serialization that cleanly handles multi-word names and departments without parsing errors.

---

## 6. How to Compile the Program

### Method A: Using GCC in VS Code / Command Prompt

1. Open a terminal or Command Prompt in the project folder:
   ```bash
   cd c:\Users\Asus\OneDrive\Desktop\CProject
   ```
2. Compile `main.c` with GCC:
   ```bash
   gcc main.c -o dashboard.exe
   ```
   *(Optional flags for strict compliance: `gcc -Wall -Wextra -std=c99 main.c -o dashboard.exe`)*

### Method B: Using Clang

```bash
clang main.c -o dashboard.exe
```

---

## 7. How to Run the Program

After compilation, launch the generated executable:

### Windows:
```cmd
dashboard.exe
```
or in PowerShell:
```powershell
.\dashboard.exe
```

### Linux / macOS:
```bash
./dashboard
```

---

## 8. Sample Output & Walkthrough

### 1. Main Menu
```text
========================================
  EMPLOYEE PERFORMANCE & KPI DASHBOARD  
========================================
  1. Add Employee
  2. Display All Employees
  3. Search Employee
  4. Sort Employees by Productivity
  5. Filter Employees by Department
  6. Show Employees Needing Improvement
  7. Update Performance Trend
  8. Save Records
  9. Exit
========================================
Enter your choice: 2
```

### 2. Display All Records
```text
------------------------------------------------------------------------------------------------------------------
| ID    | Name                 | Department      | Tasks | Hours  | Quality | Productivity | Performance Grade |
------------------------------------------------------------------------------------------------------------------
| 101   | Rahul Sharma         | IT              |    20 |   40.0 |    85.0 |         0.50 | Excellent         |
| 102   | Priya Patel          | HR              |    15 |   35.0 |    92.0 |         0.43 | Excellent         |
| 103   | Amit Verma           | Marketing       |    18 |   45.0 |    65.0 |         0.40 | Average           |
| 104   | Sneha Rao            | IT              |    25 |   38.0 |    88.0 |         0.66 | Excellent         |
| 105   | Vikas Kumar          | Sales           |    10 |   40.0 |    45.0 |         0.25 | Needs Improvement |
------------------------------------------------------------------------------------------------------------------
Total Employees: 5
```

### 3. Search Employee (ID: 101)
```text
========================================
       EMPLOYEE DETAILS (ID: 101)       
========================================
  Name               : Rahul Sharma
  Department         : IT
  Tasks Completed    : 20
  Working Hours      : 40.00 hrs
  Quality Score      : 85.00 / 100
  Productivity Score : 0.50 tasks/hr
  Reliability Index  : 85.0%
  Performance Grade  : Excellent
  Previous Quality   : 85.00
========================================
```

### 4. Performance Warnings (Flagging Score < 50)
```text
========================================================================
                 PERFORMANCE WARNINGS AUDIT                             
========================================================================
[!] Warning: This employee needs performance improvement.
    ID             : 105
    Name           : Vikas Kumar
    Department     : Sales
    Quality Score  : 45.00 / 100
    Performance    : Needs Improvement
    Productivity   : 0.25 tasks/hr
    ----------------------------------------------------------------
Total flagged employees needing improvement: 1
========================================================================
```

### 5. Performance Trend Analysis
```text
--- Update Employee Performance Trend ---
Enter Employee ID: 103

Selected Employee      : Amit Verma (ID: 103)
Current Quality Score  : 65.00
Previous Quality Score : 65.00
Enter New Quality Score (0 to 100): 78

========================================
       PERFORMANCE TREND RESULT         
========================================
  Employee Name    : Amit Verma
  Previous Score   : 65.00
  New Score        : 78.00
  New Grade        : Good
  Trend Analysis   : Performance Improving.
========================================
[SUCCESS] Performance trend record updated!
```

---


## 9. Authors & Acknowledgments

- **Name:** Vanshika
- **Developer:** First-Year B.Tech Student
- **Course:** Computer Programming in C / Problem Solving through C
- **Academic Year:** 2026-2027
