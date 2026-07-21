# University Management System Using Object-Oriented Programming

**UOW XBAU2014N Advanced Programming A2**

**Author:** Joie Khoo Huan Yun  
**Student ID:** 0209184  
**Date:** 21/7/2026  
**Github Repo:** https://github.com/Jcohyy/XBAU2014N_A2-Advanced-Programming  

---

## Overview
This management system allows university lecturers or admins to view and modify student details and their obtained marks, alongside managing course details and coursework components. The program demonstrates the four core principles of object-oriented programming (OOP): inheritance, encapsulation, polymorphism, and abstraction.

---

## How to Run

1. Build and run the project using your preferred C++ IDE (e.g. Code::Blocks, Visual Studio) or execute the compiled `.exe`.
2. Ensure the required data files are in the same directory as the executable:
   - `course.txt`
   - `components.txt`
   - `student.txt`
   - `marks.txt`
3. If all files are read successfully, press **Enter** to continue.
4. From the main menu, choose:
   - **1** � Students Menu
   - **2** � Course Menu
   - **0** � Save all data and exit

---

## UML Class Diagram

![UML Class Diagram](images/class_diagram.png)

---

## Features

### Students
- View student details
- Enter coursework marks
- Update existing marks
- Generate student reports with grades and CGPA

### Courses
- View course details
- Edit credit hours (2�5)
- Add coursework components
- Edit existing components

### Validation
- Validates all user input
- Prevents invalid marks, weightages, and duplicate entries
- Allows users to exit any input prompt safely

---

## Implementation

- Uses fixed-size arrays to store students, courses, components, and marks.
- Reads and writes all data using `fstream` in a semicolon-separated format.
- Uses composition:
  - `Student` contains `Marks`
  - `Course` contains `Component`
- `Person` serves as the parent class of `Student`.
- Menu logic is implemented using `while(true)` loops with `switch` statements.
- Operational functions are implemented in `utils.cpp`, while object-specific functions are implemented within their respective classes.
- Objects are retrieved and modified efficiently using indexes (`studentIndex`, `courseIndex`, `componentIndex`, etc.) instead of repeatedly searching arrays.

---

## File Format

### `course.txt`
```
CourseCode;CourseName;CreditHour
```

### `components.txt`
```
CourseCode;ComponentID;ComponentName;MaxMarks;Weightage
```

### `student.txt`
```
StudentID;StudentName
```

### `marks.txt`
```
StudentID;CourseCode;ComponentID;MarksObtained
```


