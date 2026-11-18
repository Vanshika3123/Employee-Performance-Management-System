/*
 * ============================================================================
 * Project Name : Employee Performance & KPI Dashboard (CLI)
 * Author       : First-Year B.Tech Student
 * Language     : C (Standard C99 / C11)
 * Compiler     : GCC
 * Description  : A beginner-friendly command-line dashboard to track employee
 *                records, calculate Key Performance Indicators (KPIs), sort,
 *                filter, analyze performance trends, and persist data in a file.
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define MAX_STR 50
#define FILENAME "employees.txt"
#define INITIAL_CAPACITY 5

/* -------------------------------------------------------------------------
 * Structure: Employee
 * Purpose  : Holds information about a single employee, along with their
 *            calculated KPIs and performance metrics.
 * ------------------------------------------------------------------------- */
struct Employee {
    int id;                     /* Unique Employee Identification Number */
    char name[MAX_STR];         /* Full Name of Employee */
    char department[MAX_STR];   /* Department (e.g., IT, HR, Sales) */
    int tasksCompleted;         /* Number of tasks finished */
    float workingHours;         /* Total working hours logged */
    float qualityScore;         /* Current Quality Score (0 to 100) */
    float previousQualityScore; /* Previous Quality Score for trend comparison */
    float productivityScore;    /* Calculated KPI: tasksCompleted / workingHours */
    float reliabilityIndex;     /* Calculated KPI: Quality Score as % */
    char performanceGrade[25];  /* Grade: Excellent, Good, Average, Needs Improvement */
};

/* -------------------------------------------------------------------------
 * Function Prototypes
 * ------------------------------------------------------------------------- */
void displayMenu(void);
void clearInputBuffer(void);
void getStringInput(char *str, int maxLength);
int compareIgnoreCase(const char *s1, const char *s2);

void calculateKPIs(struct Employee *emp);
int findEmployeeIndexById(const struct Employee *employees, int count, int id);

void addEmployee(struct Employee **employees, int *count, int *capacity);
void displayAllEmployees(const struct Employee *employees, int count);
void searchEmployee(const struct Employee *employees, int count);
void sortEmployeesByProductivity(struct Employee *employees, int count);
void filterEmployeesByDepartment(const struct Employee *employees, int count);
void showPerformanceWarnings(const struct Employee *employees, int count);
void updatePerformanceTrend(struct Employee *employees, int count);
void saveRecords(const struct Employee *employees, int count);
void loadRecords(struct Employee **employees, int *count, int *capacity);

/* -------------------------------------------------------------------------
 * Function: main
 * Purpose : Program entry point. Initializes memory, loads data from file,
 *           and executes the interactive menu loop.
 * ------------------------------------------------------------------------- */
int main(void) {
    int count = 0;
    int capacity = INITIAL_CAPACITY;
    int choice;

    /* Dynamic memory allocation for storing employees */
    struct Employee *employees = malloc((size_t)capacity * sizeof(struct Employee));
    if (employees == NULL) {
        printf("[ERROR] Memory allocation failed on startup!\n");
        return 1;
    }

    /* Load existing employee records from file if available */
    loadRecords(&employees, &count, &capacity);

    /* Main Menu Loop */
    do {
        displayMenu();
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("\n[ERROR] Invalid input! Please enter a numeric choice.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer(); /* Clear leftover newline from input stream */

        switch (choice) {
            case 1:
                addEmployee(&employees, &count, &capacity);
                break;
            case 2:
                displayAllEmployees(employees, count);
                break;
            case 3:
                searchEmployee(employees, count);
                break;
            case 4:
                sortEmployeesByProductivity(employees, count);
                break;
            case 5:
                filterEmployeesByDepartment(employees, count);
                break;
            case 6:
                showPerformanceWarnings(employees, count);
                break;
            case 7:
                updatePerformanceTrend(employees, count);
                break;
            case 8:
                saveRecords(employees, count);
                break;
            case 9:
                /* Auto-save before quitting */
                saveRecords(employees, count);
                printf("\nThank you for using Employee Performance & KPI Dashboard. Goodbye!\n");
                break;
            default:
                printf("\n[ERROR] Invalid choice (%d)! Please choose an option from 1 to 9.\n", choice);
                break;
        }

        if (choice != 9) {
            printf("\nPress Enter to return to the main menu...");
            getchar();
        }

    } while (choice != 9);

    /* Free dynamically allocated memory before program termination */
    free(employees);
    employees = NULL;

    return 0;
}

/* -------------------------------------------------------------------------
 * Function: displayMenu
 * Purpose : Prints the user-friendly CLI menu.
 * ------------------------------------------------------------------------- */
void displayMenu(void) {
    printf("\n");
    printf("========================================\n");
    printf("  EMPLOYEE PERFORMANCE & KPI DASHBOARD  \n");
    printf("========================================\n");
    printf("  1. Add Employee\n");
    printf("  2. Display All Employees\n");
    printf("  3. Search Employee\n");
    printf("  4. Sort Employees by Productivity\n");
    printf("  5. Filter Employees by Department\n");
    printf("  6. Show Employees Needing Improvement\n");
    printf("  7. Update Performance Trend\n");
    printf("  8. Save Records\n");
    printf("  9. Exit\n");
    printf("========================================\n");
}

/* -------------------------------------------------------------------------
 * Function: clearInputBuffer
 * Purpose : Flushes standard input buffer up to newline or EOF to avoid
 *           skipping subsequent input prompts.
 * ------------------------------------------------------------------------- */
void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* Discard remaining characters */
    }
}

/* -------------------------------------------------------------------------
 * Function: getStringInput
 * Purpose : Safely reads a string from user input using fgets and removes
 *           trailing newline or carriage return characters.
 * ------------------------------------------------------------------------- */
void getStringInput(char *str, int maxLength) {
    if (fgets(str, maxLength, stdin) != NULL) {
        size_t len = strlen(str);
        if (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r')) {
            str[len - 1] = '\0';
        }
        if (len > 1 && str[len - 2] == '\r') {
            str[len - 2] = '\0';
        }
    }
}

/* -------------------------------------------------------------------------
 * Function: compareIgnoreCase
 * Purpose : Compares two strings case-insensitively using standard C logic.
 *           Returns 0 if both strings match irrespective of case.
 * ------------------------------------------------------------------------- */
int compareIgnoreCase(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        char c1 = (*s1 >= 'A' && *s1 <= 'Z') ? (char)(*s1 + 32) : *s1;
        char c2 = (*s2 >= 'A' && *s2 <= 'Z') ? (char)(*s2 + 32) : *s2;
        if (c1 != c2) {
            return c1 - c2;
        }
        s1++;
        s2++;
    }
    return (unsigned char)*s1 - (unsigned char)*s2;
}

/* -------------------------------------------------------------------------
 * Function: calculateKPIs
 * Purpose : Computes Key Performance Indicators for an employee:
 *           - Productivity Score = Tasks Completed / Working Hours
 *             (prevents division by zero if hours == 0)
 *           - Reliability Index = Quality Score as percentage
 *           - Performance Grade based on quality score ranges:
 *             >= 85 : Excellent
 *             >= 70 : Good
 *             >= 50 : Average
 *             <  50 : Needs Improvement
 * ------------------------------------------------------------------------- */
void calculateKPIs(struct Employee *emp) {
    /* Prevent division by zero */
    if (emp->workingHours > 0.0f) {
        emp->productivityScore = (float)emp->tasksCompleted / emp->workingHours;
    } else {
        emp->productivityScore = 0.0f;
    }

    /* Reliability Index corresponds to Quality Score percentage */
    emp->reliabilityIndex = emp->qualityScore;

    /* Performance Grade mapping */
    if (emp->qualityScore >= 85.0f) {
        strcpy(emp->performanceGrade, "Excellent");
    } else if (emp->qualityScore >= 70.0f) {
        strcpy(emp->performanceGrade, "Good");
    } else if (emp->qualityScore >= 50.0f) {
        strcpy(emp->performanceGrade, "Average");
    } else {
        strcpy(emp->performanceGrade, "Needs Improvement");
    }
}

/* -------------------------------------------------------------------------
 * Function: findEmployeeIndexById
 * Purpose : Linear search algorithm to find an employee by their unique ID.
 *           Returns array index if found, or -1 if not found.
 * ------------------------------------------------------------------------- */
int findEmployeeIndexById(const struct Employee *employees, int count, int id) {
    for (int i = 0; i < count; i++) {
        if (employees[i].id == id) {
            return i; /* Found */
        }
    }
    return -1; /* Not found */
}

/* -------------------------------------------------------------------------
 * Function: addEmployee
 * Purpose : Prompts user for employee details, validates inputs (duplicate ID,
 *           negative hours/tasks, quality score bounds), dynamically resizes
 *           the array using realloc if needed, and stores the record.
 * ------------------------------------------------------------------------- */
void addEmployee(struct Employee **employees, int *count, int *capacity) {
    int id;
    char name[MAX_STR];
    char department[MAX_STR];
    int tasks;
    float hours;
    float quality;

    printf("\n--- Add New Employee ---\n");

    /* Employee ID Input & Validation */
    printf("Enter Employee ID: ");
    if (scanf("%d", &id) != 1 || id <= 0) {
        printf("[ERROR] Employee ID must be a positive integer!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    /* Duplicate ID check */
    if (findEmployeeIndexById(*employees, *count, id) != -1) {
        printf("[ERROR] An employee with ID %d already exists! Duplicate IDs are not allowed.\n", id);
        return;
    }

    /* Employee Name Input */
    printf("Enter Employee Name: ");
    getStringInput(name, sizeof(name));
    if (strlen(name) == 0) {
        printf("[ERROR] Employee name cannot be empty!\n");
        return;
    }

    /* Department Input */
    printf("Enter Department: ");
    getStringInput(department, sizeof(department));
    if (strlen(department) == 0) {
        printf("[ERROR] Department cannot be empty!\n");
        return;
    }

    /* Tasks Completed Input & Validation */
    printf("Enter Total Tasks Completed: ");
    if (scanf("%d", &tasks) != 1 || tasks < 0) {
        printf("[ERROR] Tasks completed cannot be negative!\n");
        clearInputBuffer();
        return;
    }

    /* Working Hours Input & Validation */
    printf("Enter Total Working Hours: ");
    if (scanf("%f", &hours) != 1 || hours < 0.0f) {
        printf("[ERROR] Working hours cannot be negative!\n");
        clearInputBuffer();
        return;
    }

    /* Quality Score Input & Validation (0 - 100) */
    printf("Enter Quality Score (0 to 100): ");
    if (scanf("%f", &quality) != 1 || quality < 0.0f || quality > 100.0f) {
        printf("[ERROR] Quality score must be between 0 and 100!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    /* Resize dynamic array if capacity is reached */
    if (*count >= *capacity) {
        int newCapacity = (*capacity == 0) ? INITIAL_CAPACITY : (*capacity * 2);
struct Employee *temp = realloc(*employees, (size_t)newCapacity * sizeof(struct Employee));
        if (temp == NULL) {
            printf("[ERROR] Memory reallocation failed! Could not add employee.\n");
            return;
        }
        *employees = temp;
        *capacity = newCapacity;
    }

    /* Populate the new employee structure */
    struct Employee *newEmp = &((*employees)[*count]);
    newEmp->id = id;
    strncpy(newEmp->name, name, sizeof(newEmp->name) - 1);
    newEmp->name[sizeof(newEmp->name) - 1] = '\0';
    strncpy(newEmp->department, department, sizeof(newEmp->department) - 1);
    newEmp->department[sizeof(newEmp->department) - 1] = '\0';
    newEmp->tasksCompleted = tasks;
    newEmp->workingHours = hours;
    newEmp->qualityScore = quality;
    newEmp->previousQualityScore = quality; /* Initially, previous equals current */

    /* Compute KPIs */
    calculateKPIs(newEmp);

    (*count)++;

    printf("\n[SUCCESS] Employee '%s' (ID: %d) added successfully!\n", newEmp->name, newEmp->id);
    printf("Calculated Productivity: %.2f tasks/hr | Grade: %s\n", newEmp->productivityScore, newEmp->performanceGrade);
}

/* -------------------------------------------------------------------------
 * Function: displayAllEmployees
 * Purpose : Prints all employee records in a neatly aligned tabular format.
 * ------------------------------------------------------------------------- */
void displayAllEmployees(const struct Employee *employees, int count) {
    if (count == 0) {
        printf("\n[INFO] No employee records available to display.\n");
        return;
    }

    printf("\n------------------------------------------------------------------------------------------------------------------\n");
    printf("| %-5s | %-20s | %-15s | %-5s | %-6s | %-7s | %-12s | %-17s |\n",
           "ID", "Name", "Department", "Tasks", "Hours", "Quality", "Productivity", "Performance Grade");
    printf("------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("| %-5d | %-20s | %-15s | %5d | %6.1f | %7.1f | %12.2f | %-17s |\n",
               employees[i].id,
               employees[i].name,
               employees[i].department,
               employees[i].tasksCompleted,
               employees[i].workingHours,
               employees[i].qualityScore,
               employees[i].productivityScore,
               employees[i].performanceGrade);
    }
    printf("------------------------------------------------------------------------------------------------------------------\n");
    printf("Total Employees: %d\n", count);
}

/* -------------------------------------------------------------------------
 * Function: searchEmployee
 * Purpose : Linear search for an employee by ID and displays complete
 *           detailed information if found.
 * ------------------------------------------------------------------------- */
void searchEmployee(const struct Employee *employees, int count) {
    if (count == 0) {
        printf("\n[INFO] No employee records available to search.\n");
        return;
    }

    int searchId;
    printf("\n--- Search Employee by ID ---\n");
    printf("Enter Employee ID to search: ");
    if (scanf("%d", &searchId) != 1) {
        printf("[ERROR] Invalid ID format!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    int index = findEmployeeIndexById(employees, count, searchId);
    if (index == -1) {
        printf("\n[RESULT] Employee not found with ID: %d\n", searchId);
        return;
    }

    const struct Employee *emp = &employees[index];
    printf("\n========================================\n");
    printf("       EMPLOYEE DETAILS (ID: %d)       \n", emp->id);
    printf("========================================\n");
    printf("  Name               : %s\n", emp->name);
    printf("  Department         : %s\n", emp->department);
    printf("  Tasks Completed    : %d\n", emp->tasksCompleted);
    printf("  Working Hours      : %.2f hrs\n", emp->workingHours);
    printf("  Quality Score      : %.2f / 100\n", emp->qualityScore);
    printf("  Productivity Score : %.2f tasks/hr\n", emp->productivityScore);
    printf("  Reliability Index  : %.1f%%\n", emp->reliabilityIndex);
    printf("  Performance Grade  : %s\n", emp->performanceGrade);
    printf("  Previous Quality   : %.2f\n", emp->previousQualityScore);
    printf("========================================\n");
}

/* -------------------------------------------------------------------------
 * Function: sortEmployeesByProductivity
 * Purpose : Uses Bubble Sort algorithm to sort employees in descending order
 *           of their productivity score (highest to lowest).
 * ------------------------------------------------------------------------- */
void sortEmployeesByProductivity(struct Employee *employees, int count) {
    if (count == 0) {
        printf("\n[INFO] No employee records available to sort.\n");
        return;
    }

    if (count == 1) {
        printf("\nOnly 1 employee record exists. Already sorted:\n");
        displayAllEmployees(employees, count);
        return;
    }

    /* Bubble Sort Implementation */
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            /* Compare adjacent elements for descending order */
            if (employees[j].productivityScore < employees[j + 1].productivityScore) {
                /* Swap elements */
                struct Employee temp = employees[j];
                employees[j] = employees[j + 1];
                employees[j + 1] = temp;
            }
        }
    }

    printf("\n[SUCCESS] Employees sorted by Productivity Score (High to Low):\n");
    displayAllEmployees(employees, count);
}

/* -------------------------------------------------------------------------
 * Function: filterEmployeesByDepartment
 * Purpose : Displays all employees belonging to a specific department.
 * ------------------------------------------------------------------------- */
void filterEmployeesByDepartment(const struct Employee *employees, int count) {
    if (count == 0) {
        printf("\n[INFO] No employee records available to filter.\n");
        return;
    }

    char targetDept[MAX_STR];
    printf("\n--- Filter Employees by Department ---\n");
    printf("Enter Department Name: ");
    getStringInput(targetDept, sizeof(targetDept));

    if (strlen(targetDept) == 0) {
        printf("[ERROR] Department name cannot be empty!\n");
        return;
    }

    int matchCount = 0;
    for (int i = 0; i < count; i++) {
        if (compareIgnoreCase(employees[i].department, targetDept) == 0) {
            matchCount++;
        }
    }

    if (matchCount == 0) {
        printf("\n[RESULT] No employees found in department: '%s'\n", targetDept);
        return;
    }

    printf("\nFound %d employee(s) in department '%s':\n", matchCount, targetDept);
    printf("------------------------------------------------------------------------------------------------------------------\n");
    printf("| %-5s | %-20s | %-15s | %-5s | %-6s | %-7s | %-12s | %-17s |\n",
           "ID", "Name", "Department", "Tasks", "Hours", "Quality", "Productivity", "Performance Grade");
    printf("------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        if (compareIgnoreCase(employees[i].department, targetDept) == 0) {
            printf("| %-5d | %-20s | %-15s | %5d | %6.1f | %7.1f | %12.2f | %-17s |\n",
                   employees[i].id,
                   employees[i].name,
                   employees[i].department,
                   employees[i].tasksCompleted,
                   employees[i].workingHours,
                   employees[i].qualityScore,
                   employees[i].productivityScore,
                   employees[i].performanceGrade);
        }
    }
    printf("------------------------------------------------------------------------------------------------------------------\n");
}

/* -------------------------------------------------------------------------
 * Function: showPerformanceWarnings
 * Purpose : Identifies and displays employees whose quality score is below 50,
 *           highlighting that they need performance improvement.
 * ------------------------------------------------------------------------- */
void showPerformanceWarnings(const struct Employee *employees, int count) {
    if (count == 0) {
        printf("\n[INFO] No employee records available to check for warnings.\n");
        return;
    }

    int warningCount = 0;
    printf("\n========================================================================\n");
    printf("                 PERFORMANCE WARNINGS AUDIT                             \n");
    printf("========================================================================\n");

    for (int i = 0; i < count; i++) {
        if (employees[i].qualityScore < 50.0f) {
            warningCount++;
            printf("[!] Warning: This employee needs performance improvement.\n");
            printf("    ID             : %d\n", employees[i].id);
            printf("    Name           : %s\n", employees[i].name);
            printf("    Department     : %s\n", employees[i].department);
            printf("    Quality Score  : %.2f / 100\n", employees[i].qualityScore);
            printf("    Performance    : %s\n", employees[i].performanceGrade);
            printf("    Productivity   : %.2f tasks/hr\n", employees[i].productivityScore);
            printf("    ----------------------------------------------------------------\n");
        }
    }

    if (warningCount == 0) {
        printf("[OK] Good news! All employees are currently meeting performance standards.\n");
        printf("     No employees have a quality score below 50.\n");
    } else {
        printf("Total flagged employees needing improvement: %d\n", warningCount);
    }
    printf("========================================================================\n");
}

/* -------------------------------------------------------------------------
 * Function: updatePerformanceTrend
 * Purpose : Allows updating an employee's quality score and determines the
 *           direction of change:
 *           - New > Previous : "Performance Improving"
 *           - New < Previous : "Performance Worsening"
 *           - New == Previous: "Performance Unchanged"
 * ------------------------------------------------------------------------- */
void updatePerformanceTrend(struct Employee *employees, int count) {
    if (count == 0) {
        printf("\n[INFO] No employee records available to update.\n");
        return;
    }

    int searchId;
    printf("\n--- Update Employee Performance Trend ---\n");
    printf("Enter Employee ID: ");
    if (scanf("%d", &searchId) != 1) {
        printf("[ERROR] Invalid ID format!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    int index = findEmployeeIndexById(employees, count, searchId);
    if (index == -1) {
        printf("\n[RESULT] Employee not found with ID: %d\n", searchId);
        return;
    }

    struct Employee *emp = &employees[index];
    float newScore;

    printf("\nSelected Employee      : %s (ID: %d)\n", emp->name, emp->id);
    printf("Current Quality Score  : %.2f\n", emp->qualityScore);
    printf("Previous Quality Score : %.2f\n", emp->previousQualityScore);

    printf("Enter New Quality Score (0 to 100): ");
    if (scanf("%f", &newScore) != 1 || newScore < 0.0f || newScore > 100.0f) {
        printf("[ERROR] Quality score must be a number between 0 and 100!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    /* Store previous score and update current score */
    emp->previousQualityScore = emp->qualityScore;
    emp->qualityScore = newScore;

    /* Recalculate KPIs and Grade */
    calculateKPIs(emp);

    /* Trend Analysis Output */
    printf("\n========================================\n");
    printf("       PERFORMANCE TREND RESULT         \n");
    printf("========================================\n");
    printf("  Employee Name    : %s\n", emp->name);
    printf("  Previous Score   : %.2f\n", emp->previousQualityScore);
    printf("  New Score        : %.2f\n", emp->qualityScore);
    printf("  New Grade        : %s\n", emp->performanceGrade);

    if (newScore > emp->previousQualityScore) {
        printf("  Trend Analysis   : Performance Improving.\n");
    } else if (newScore < emp->previousQualityScore) {
        printf("  Trend Analysis   : Performance Worsening.\n");
    } else {
        printf("  Trend Analysis   : Performance Unchanged.\n");
    }
    printf("========================================\n");
    printf("[SUCCESS] Performance trend record updated!\n");
}

/* -------------------------------------------------------------------------
 * Function: saveRecords
 * Purpose : Writes all employee records to a persistent text file
 *           ("employees.txt") using pipe-delimited format to preserve spaces.
 * ------------------------------------------------------------------------- */
void saveRecords(const struct Employee *employees, int count) {
    FILE *fp = fopen(FILENAME, "w");
    if (fp == NULL) {
        printf("[ERROR] Could not open file '%s' for saving!\n", FILENAME);
        return;
    }

    for (int i = 0; i < count; i++) {
        /* Format: ID|Name|Department|Tasks|Hours|QualityScore|PreviousQualityScore */
        fprintf(fp, "%d|%s|%s|%d|%.2f|%.2f|%.2f\n",
                employees[i].id,
                employees[i].name,
                employees[i].department,
                employees[i].tasksCompleted,
                employees[i].workingHours,
                employees[i].qualityScore,
                employees[i].previousQualityScore);
    }

    fclose(fp);
    printf("\n[SUCCESS] Saved %d employee record(s) to '%s'.\n", count, FILENAME);
}

/* -------------------------------------------------------------------------
 * Function: loadRecords
 * Purpose : Reads employee records from "employees.txt" on startup.
 *           Gracefully handles non-existent file, parses records with spaces,
 *           and dynamically expands memory as needed.
 * ------------------------------------------------------------------------- */
void loadRecords(struct Employee **employees, int *count, int *capacity) {
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        printf("[INFO] No existing data file '%s' found. Starting with 0 records.\n", FILENAME);
        return;
    }

    char line[256];
    int loaded = 0;

    while (fgets(line, sizeof(line), fp) != NULL) {
        /* Remove trailing newline characters */
        size_t len = strlen(line);
        if (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r')) {
            line[len - 1] = '\0';
        }
        if (len > 1 && line[len - 2] == '\r') {
            line[len - 2] = '\0';
        }

        if (strlen(line) == 0) {
            continue; /* Skip empty lines */
        }

        int id, tasks;
        char name[MAX_STR];
        char department[MAX_STR];
        float hours, quality, prevQuality;

        /* Parse pipe-delimited line */
        int parsed = sscanf(line, "%d|%49[^|]|%49[^|]|%d|%f|%f|%f",
                            &id, name, department, &tasks, &hours, &quality, &prevQuality);

        if (parsed >= 6) {
            /* If previousQuality wasn't stored, default to quality */
            if (parsed == 6) {
                prevQuality = quality;
            }

            /* Expand memory if capacity reached */
            if (*count >= *capacity) {
                int newCapacity = (*capacity == 0) ? INITIAL_CAPACITY : (*capacity * 2);
                struct Employee *temp = realloc(*employees, (size_t)newCapacity * sizeof(struct Employee));
                if (temp == NULL) {
                    printf("[ERROR] Memory reallocation failed while reading file!\n");
                    break;
                }
                *employees = temp;
                *capacity = newCapacity;
            }

            struct Employee *emp = &((*employees)[*count]);
            emp->id = id;
            strncpy(emp->name, name, sizeof(emp->name) - 1);
            emp->name[sizeof(emp->name) - 1] = '\0';
            strncpy(emp->department, department, sizeof(emp->department) - 1);
            emp->department[sizeof(emp->department) - 1] = '\0';
            emp->tasksCompleted = tasks;
            emp->workingHours = hours;
            emp->qualityScore = quality;
            emp->previousQualityScore = prevQuality;

            /* Compute KPIs */
            calculateKPIs(emp);

            (*count)++;
            loaded++;
        }
    }

    fclose(fp);
    if (loaded > 0) {
        printf("[INFO] Successfully loaded %d employee record(s) from '%s'.\n", loaded, FILENAME);
    }
}
