#pragma once

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

//const
constexpr int MAX_SIZE = 60;
const std::string COURSE_FILE = "data/course.txt";
const std::string COMPONENT_FILE = "data/components.txt";
const std::string STUDENT_FILE = "data/student.txt";
const std::string MARKS_FILE = "data/marks.txt";
const std::string PRINT_DIVIDER = std::string(60, '=');
const std::string PRINT_DIVIDER2 = std::string(60, '-');

//{functions
//i/o
void readAllFiles();
void saveAllFiles();

//1. student
void printStudentList();
void printStudentDetails(int);
int getStudentIndexfromId(const std::string&);

//2. course
void printCourseList();
void printCourseDetails(int);
int getCourseIndexfromCode(const std::string&);

//3. marks manip
bool courseHasComponents(int);
int getComponentIndexfromCourse(int, const std::string&);
void addMarksToStudent(int, const std::string&, const std::string&, int);

bool studentHasMarks(int);
int getStudentMarksIndex(int, const std::string&, const std::string&);
void editMarksToStudent(int, int, int);

//4. course manip
void editCreditHour(int, int);
bool isCourseMaxWeightage(int);
bool isCourseMaxWeightagePlusInput(int, int);
void addComponentsToCourse(int, const std::string&, const std::string&, int, int);

void getExistingComponentValue(int, int, std::string&, std::string&, int&, int&);
bool isCourseMaxWeightageMinusSelfPlusInput(int, int, int);
void editComponentsToCourse(int, int, const std::string&, const std::string&, int, int);

//5. report
void generateReport(int);

//}
