#include "../include/utils.h"
#include "../include/Student.h"
#include "../include/Marks.h"
#include "../include/Course.h"
#include "../include/Component.h"

using namespace std;

static Student studentList[MAX_SIZE];
static Course courseList[MAX_SIZE];
static int studentCount = 0;
static int courseCount = 0;


//{ file input
void readStudentFile()
{
    ifstream inFile(STUDENT_FILE);

    if (!inFile){
        cout << "Error: Could not open file \"" << STUDENT_FILE << "\"" << endl;
        return;
    }

    string line;

    while (getline(inFile, line) && studentCount < MAX_SIZE){
        if (line.empty())
            continue;
        studentList[studentCount++] = Student::fromString(line);
    }
    cout << "Successfully read file \"" << STUDENT_FILE << "\"" << endl;
}

void readMarksFile() //+assigns marks to students
{
    ifstream inFile(MARKS_FILE);

    if (!inFile){
        cout << "Error: Could not open file \"" << MARKS_FILE << "\"" << endl;
        return;
    }

    string line;

    while (getline(inFile, line)){
        if (line.empty())
            continue;

        string studentId;

        Marks mark = Marks::fromString(line, studentId); //returns student id
        bool found = false;
        //find the student and add mark obj to student obj
        for (int i = 0; i < studentCount; i++){
            if (studentList[i].getId() == studentId)
            {
                studentList[i].addMark(mark);
                found = true;
                break;
            }
        }

        if(!found){
            cout << "Error: Cannot find student Id: \"" << studentId << "\" to add marks." << endl;
        }
    }
    cout << "Successfully read file \"" << MARKS_FILE << "\"" << endl;
}

void readCourseFile()
{
    ifstream inFile(COURSE_FILE);

    if (!inFile){
        cout << "Error: Could not open file \"" << COURSE_FILE << "\"" << endl;
        return;
    }

    string line;

    while (getline(inFile, line) && courseCount < MAX_SIZE){
        if (line.empty())
            continue;

        courseList[courseCount++] = Course::fromString(line);
    }
    cout << "Successfully read file \"" << COURSE_FILE << "\"" << endl;
}

void readComponentFile() //+assigns marks to students
{
    ifstream inFile(COMPONENT_FILE);

    if (!inFile){
        cout << "Error: Could not open file \"" << COMPONENT_FILE << "\"" << endl;
        return;
    }

    string line;

    while (getline(inFile, line)){
        if (line.empty())
            continue;

        string courseCode;

        Component component = Component::fromString(line, courseCode); //returns course code
        bool found = false;
        //find the course and add component obj to course obj
        for (int i = 0; i < courseCount; i++){
            if (courseList[i].getCourseCode() == courseCode){
                courseList[i].addComponent(component);
                found = true;
                break;
            }
        }

        if(!found){
            cout << "Error: Cannot find course code: \"" << courseCode << "\" to add component." << endl;
        }
    }
    cout << "Successfully read file \"" << COMPONENT_FILE << "\"" << endl;
}

void readAllFiles() //read all files provided and adds composition
{
    readStudentFile();
    readMarksFile();
    readCourseFile();
    readComponentFile();
}
//}

//{ file output
void writeStudentFile(){
    ofstream outFile(STUDENT_FILE);

    if (!outFile){
        cout << "Error: Could not open file \"" << STUDENT_FILE << "\"" << endl;
        return;
    }

    for (int i = 0; i < studentCount; i++){
        outFile << studentList[i].getId() << ";"
                << studentList[i].getName()
                << endl;
    }

    cout << "Successfully written file \""
         << STUDENT_FILE << "\"" << endl;
}

void writeMarksFile(){
    ofstream outFile(MARKS_FILE);

    if (!outFile){
        cout << "Error: Could not open file \"" << MARKS_FILE << "\"" << endl;
        return;
    }

    for (int i = 0; i < studentCount; i++){
        for (int j = 0; j < studentList[i].getMarksCount(); j++){
            Marks mark = studentList[i].getMark(j);

            outFile << studentList[i].getId() << ";"
                    << mark.getCourseCode() << ";"
                    << mark.getComponentId() << ";"
                    << mark.getMarks()
                    << endl;
        }
    }

    cout << "Successfully written file \""
         << MARKS_FILE << "\"" << endl;
}

void writeCourseFile(){
    ofstream outFile(COURSE_FILE);

    if (!outFile){
        cout << "Error: Could not open file \"" << COURSE_FILE << "\"" << endl;
        return;
    }

    for (int i = 0; i < courseCount; i++){
        outFile << courseList[i].getCourseCode() << ";"
                << courseList[i].getCourseName() << ";"
                << courseList[i].getCreditHour()
                << endl;
    }

    cout << "Successfully written file \""
         << COURSE_FILE << "\"" << endl;
}

void writeComponentFile(){
    ofstream outFile(COMPONENT_FILE);

    if (!outFile){
        cout << "Error: Could not open file \"" << COMPONENT_FILE << "\"" << endl;
        return;
    }

    for (int i = 0; i < courseCount; i++){
        for (int j = 0; j < courseList[i].getComponentCount(); j++){
            Component component = courseList[i].getComponent(j);

            outFile << courseList[i].getCourseCode() << ";"
                    << component.getComponentID() << ";"
                    << component.getComponentName() << ";"
                    << component.getMaxMarks() << ";"
                    << component.getWeightage()
                    << endl;
        }
    }

    cout << "Successfully written file \""
         << COMPONENT_FILE << "\"" << endl;
}

void saveAllFiles() //save all the files
{
    writeStudentFile();
    writeMarksFile();
    writeCourseFile();
    writeComponentFile();
}
//}

//{ 1. student generic
void printStudentList(){
    cout << "\nSTUDENT LIST\n" << PRINT_DIVIDER2 << endl;
    cout << left << setw(6) << "No. |" << setw(10) << "ID" << "Name\n";
    cout << PRINT_DIVIDER2 << endl;

    for (int i=0; i < studentCount; i++){
        string label = to_string(i+1)+".";
        cout << left << setw(4) << label << "| ";
        cout << studentList[i] << endl;
    }
    cout << endl;
}

void printStudentDetails(int studentIndex){
    cout << left << setw(8) << "ID" << "Name\n";
    cout << studentList[studentIndex] << endl << PRINT_DIVIDER2 << endl;

    if (studentList[studentIndex].hasMarks()){ //if marks exist
        studentList[studentIndex].printAllMarks();
    }else{
        cout << "Student has no marks records.\n";
    }
}

int getStudentIndexfromId(const string& studentId){ //return index of student
    for(int i=0;i<studentCount;i++){
        if(studentId == studentList[i].getId()){
            return i;
        }
    }
    return -1;
}
//}

//{ 2. course generic
void printCourseList(){
    cout << "\nCOURSE LIST\n" << PRINT_DIVIDER2 << endl;
    cout << left << setw(6) << "No. |" << setw(11) << "Code"
        << setw(30)<< "Name" << "Credit Hour\n" ;
    cout << PRINT_DIVIDER2 << endl;
    for (int i=0; i < courseCount; i++)
    {
        string label = to_string(i+1)+".";
        cout << left << setw(4) << label << "| ";
        cout << courseList[i] << endl;
    }
    cout << endl;
}

void printCourseDetails(int courseIndex){
    cout << "\nCOURSE DETAILS\n" << PRINT_DIVIDER2 << endl;
    cout << left << setw(11) << "Code"
        << setw(30)<< "Name" << "Credit Hour\n";
    cout << courseList[courseIndex] << endl << PRINT_DIVIDER2 << endl;

    if (courseList[courseIndex].hasComponents()){ //if components exist
        courseList[courseIndex].printAllComponents();
    }else{
        cout << "Course has no components records.\n";
    }
}

int getCourseIndexfromCode(const string& courseCode){ //return index of course
    for(int i=0;i<courseCount;i++){
        if(courseCode == courseList[i].getCourseCode()){
            return i;
        }
    }
    return -1;
}



//}

//{ 3. marks manip
//3.1 enter
bool courseHasComponents(int courseIndex){
    if(courseList[courseIndex].hasComponents()){
        return true;
    }
    return false;
}

int getComponentIndexfromCourse(int courseIndex, const string& componentID){ //return index of component
    return courseList[courseIndex].getComponentIndex(componentID);
}

void addMarksToStudent(int studentIndex, const string& courseCode, const string& componentID, int marksObtained){
    Marks mark = Marks(courseCode, componentID, marksObtained);
    if(studentList[studentIndex].addMark(mark)){
        cout << "\nSuccessfully added marks to student.\n";
    }else{
        cout << "\nError: Unable to add more marks to student.\n";
    }
}

//3.2 update
bool studentHasMarks(int studentIndex){
    if(studentList[studentIndex].hasMarks()){
        return true;
    }
    return false;
}

//returns index of course/component to update
int getStudentMarksIndex(int studentIndex, const string& targetCourse, const string& targetComponent){
    return studentList[studentIndex].getMarksIndex(targetCourse, targetComponent); //returns -1 if not exist
}

void editMarksToStudent(int studentIndex, int markIndex, int newMark){;
    if(studentList[studentIndex].editMark(markIndex, newMark)){
        cout << "\nSuccessfully updated marks to student.\n";
    }else{
        cout << "\nError: Unable to update marks to student.\n"; //should never call
    }
}

//}

//{ 4. course manip
void editCreditHour(int courseIndex, int inputHour){
    courseList[courseIndex].setCreditHour(inputHour);
}

//4.2 add
bool isCourseMaxWeightage(int courseIndex){
    int totalWeightage = courseList[courseIndex].getTotalComponentsWeightage();
    if(totalWeightage >= 100){
        return true;
    }
    return false;
}

bool isCourseMaxWeightagePlusInput(int courseIndex, int inputWeightage){
    int totalWeightage = courseList[courseIndex].getTotalComponentsWeightage() + inputWeightage;
    if(totalWeightage > 100){
        return true;
    }
    return false;
}

void addComponentsToCourse(int courseIndex, const std::string& componentId, const std::string& componentName, int maxMarks, int weightage){
    Component component = Component(componentId, componentName, maxMarks, weightage);
    if(courseList[courseIndex].addComponent(component)){
        cout << "\nSuccessfully added component to course.\n";
    }else{
        cout << "\nError: Unable to add more components to course.\n"; //should never call unless weightage is odd
    }
}

//4.3 edit
void getExistingComponentValue(int courseIndex, int componentIndex, std::string& componentId,
                                std::string& componentName, int& maxMarks, int& weightage){
    componentId = courseList[courseIndex].getComponent(componentIndex).getComponentID();
    componentName = courseList[courseIndex].getComponent(componentIndex).getComponentName();
    maxMarks = courseList[courseIndex].getComponent(componentIndex).getMaxMarks();
    weightage = courseList[courseIndex].getComponent(componentIndex).getWeightage();
}

bool isCourseMaxWeightageMinusSelfPlusInput(int courseIndex, int componentIndex, int inputWeightage){
    int totalWeightage = courseList[courseIndex].getTotalComponentsWeightage() + inputWeightage
        - courseList[courseIndex].getComponent(componentIndex).getWeightage();
    if(totalWeightage > 100){
        return true;
    }
    return false;
}

void editComponentsToCourse(int courseIndex, int componentIndex, const std::string& componentId,
                            const std::string& componentName, int maxMarks, int weightage){
    if(courseList[courseIndex].editComponent(componentIndex, componentId, componentName, maxMarks, weightage)){
        cout << "\nSuccessfully edited component to course.\n";
    }else{
        cout << "\nError: Unable to edit component to course.\n"; //should never call
    }
}

//}

//{ 5. report
void calculateGrade(double mark, string& grade, double& gpa, string& remarks){
    if(mark>=85){
        grade = "A+";
        gpa = 4.00;
        remarks = "High Distinction";
    }else if(mark>=80){
        grade = "A";
        gpa = 4.00;
        remarks = "Distinction";
    }else if(mark>=75){
        grade = "A-";
        gpa = 3.67;
        remarks = "Good";
    }else if(mark>=70){
        grade = "B+";
        gpa = 3.33;
        remarks = "High Credit";
    }else if(mark>=65){
        grade = "B";
        gpa = 3.00;
        remarks = "Credit";
    }else if(mark>=60){
        grade = "B-";
        gpa = 2.67;
        remarks = "Satisfactory";
    }else if(mark>=55){
        grade = "C+";
        gpa = 2.33;
        remarks = "Commendable Pass";
    }else if(mark>=50){
        grade = "C";
        gpa = 2.00;
        remarks = "Pass";
    }else if(mark>=40){
        grade = "D";
        gpa = 1.00;
        remarks = "Marginal Fail";
    }else{
        grade = "F";
        gpa = 0.00;
        remarks = "Fail";
    }
    return;
}

void generateReport(int studentIndex){
    int studentMarksCount = studentList[studentIndex].getMarksCount();
    double cgpa = 0;
    double totalWeighted = 0;
    double totalGradePoint = 0;
    int uniqueCount = 0;
    int totalCreditHour = 0;
    double weightedMarks[studentMarksCount] = {};
    double courseTotalWeighted[courseCount] = {};
    int uniqueCourseIndex[courseCount] = {};

    cout << endl << PRINT_DIVIDER;
    cout << "\nSTUDENT REPORT\n" << PRINT_DIVIDER2 << endl;
    cout << left << setw(12) << "Course" << setw(11) << "Component"
        << setw(7) << "Marks" << setw(11) << "Weightage" << "Wtd. Marks\n";

    //1. calculate all marks in student
    for(int i=0; i<studentMarksCount; i++){

        //get all necessary data
        const Marks& m = studentList[studentIndex].getMark(i);
        int courseIndex = getCourseIndexfromCode(m.getCourseCode());
        int componentIndex = getComponentIndexfromCourse(courseIndex, m.getComponentId());
        int creditHour = courseList[courseIndex].getCreditHour();
        int weightage = courseList[courseIndex].getComponent(componentIndex).getWeightage();

        //calculate weightage
        double weighted = m.getMarks() * (weightage/100.0);

        //store all relevant data to calculate later
        weightedMarks[i] = weighted;
        courseTotalWeighted[courseIndex] += weighted;

        bool exists = false;
        //check if courseIndex already exists
        for(int j=0; j<uniqueCount; j++){
            if(uniqueCourseIndex[j] == courseIndex){
                exists = true;
                break;
            }
        }

        //if it is not found, add it
        if(!exists){
            uniqueCourseIndex[uniqueCount] = courseIndex;
            uniqueCount++;
        }

        cout << left << setw(12) << m.getCourseCode()
            << setw(11) << m.getComponentId()
            << setw(7) << m.getMarks()
            << setw(11) << weightage << weightedMarks[i] << endl;
    }

    //2. calculate by course + cgpa
    cout << "\n" << PRINT_DIVIDER2 << endl;
    cout << setw(12) << "Course" << setw(12) << "Wtd. Marks"
        << setw(8) << "Grade" << setw(7) << "GPA" << "Remarks\n" ;
    for(int i=0; i<uniqueCount; i++){
        int courseIndex = uniqueCourseIndex[i];

        if(courseTotalWeighted[courseIndex] > 0){
            string igrade, iremarks;
            double igpa;

            calculateGrade(courseTotalWeighted[courseIndex], igrade, igpa, iremarks);

            int creditHour = courseList[courseIndex].getCreditHour();

            // CGPA calculation
            totalGradePoint += igpa * creditHour;
            totalCreditHour += creditHour;

            cout << setw(12) << courseList[courseIndex].getCourseCode()
                << setw(12) << courseTotalWeighted[courseIndex]
                << setw(8) << igrade << setw(7) << igpa
                << iremarks << endl;
        }
    }
    cgpa = totalGradePoint / totalCreditHour;

    cout << "\nCGPA: " << fixed << setprecision(2) << cgpa << endl;
    cout << PRINT_DIVIDER <<endl;
}




