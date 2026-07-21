#include "../include/utils.h"

using namespace std;

bool checkExitInput(const string&);
bool checkExitInput(int); //overload
int getIntInput();
void studentMenu();
void courseMenu();
void addMarksMenu(int);
void editMarksMenu(int);
void generateReportMenu(int);
void addComponentsMenu(int);
void editComponentsMenu(int);

int main(){
    //start - read files
    readAllFiles();
    cout << "\nPress enter to proceed.";
    cin.get();

    //menu
    while(true){
        cout << "\n" << PRINT_DIVIDER << "\n" << string(25, '-') << "MAIN MENU"
            << string(26, '-') << "\n" << PRINT_DIVIDER << endl;
        cout << "What would you like to do?\n" << PRINT_DIVIDER2 << endl;
        cout << "1. View/Manage Students\n";
        cout << "2. View/Manage Course\n";
        cout << "0. Terminate Program\n";
        cout << PRINT_DIVIDER << endl;
        cout << "Enter number: ";
        int input2 = getIntInput(); //check for cin.fail

        switch(input2){
            case 1: //student, marks
                studentMenu();
                break;
            case 2: //course, components
                courseMenu();
                break;
            case 0: //terminate
                cout << "\nTerminating Program..\n";
                //write files
                saveAllFiles();
                return 0;
            default:
                cout << "Invalid choice.\n";
        }
    }

    return 0;
}

void studentMenu(){ //sub-menu of student

    printStudentList();

    string inputId;
    while(true){
        cout << "View Student Details (\"0\" to exit)\n";
        cout << "Enter student ID: ";
        cin >> inputId;

        if(checkExitInput(inputId)){break;}

        int studentIndex = getStudentIndexfromId(inputId);
        if(studentIndex != -1){ //if id exist
            cout << endl << PRINT_DIVIDER;
            cout << "\nSTUDENT DETAILS\n" << PRINT_DIVIDER2 << endl;
            printStudentDetails(studentIndex);
            cout << endl << PRINT_DIVIDER;

            cout << "\nWhat would you like to do?\n" << PRINT_DIVIDER2 << endl;
            cout << "1. Enter Marks\n";
            cout << "2. Update Marks\n";
            cout << "3. Generate Report\n";
            cout << "0. Exit\n";
            cout << PRINT_DIVIDER << endl;
            cout << "Enter number: ";
            int input3 = getIntInput();

            switch(input3){
                case 1: //enter marks
                    addMarksMenu(studentIndex);
                    break;
                case 2: //update marks
                    editMarksMenu(studentIndex);
                    break;
                case 3: //generate report
                    generateReportMenu(studentIndex);
                    break;
                case 0: //exit
                    cout << "Exiting..\n";
                    break;
                default:
                    cout << "Invalid choice.\n";
            }


            break;
        }else{
            cout << "Error: Student ID does not exist.\n\n";
            continue;
        }
    }
    return;
}

void courseMenu(){ //sub-menu of course

    printCourseList();

    string inputCode;
    while(true){
        cout << "View Course Details (\"0\" to exit)\n";
        cout << "Enter course code: ";
        cin >> inputCode;

        if(checkExitInput(inputCode)){break;}

        int courseIndex = getCourseIndexfromCode(inputCode);
        if(courseIndex != -1){ //if code exist
            cout << endl << PRINT_DIVIDER;
            printCourseDetails(courseIndex);
            cout << endl << PRINT_DIVIDER;

            cout << "\nWhat would you like to do?\n" << PRINT_DIVIDER2 << endl;
            cout << "1. Edit Credit Hour\n";
            cout << "2. Add Components\n";
            cout << "3. Edit Components\n";
            cout << "0. Exit\n";
            cout << PRINT_DIVIDER << endl;
            cout << "Enter number: ";
            int input3 = getIntInput();

            switch(input3){
                case 1: //edit credit hour
                    while(true){
                        cout << "\nEdit Credit Hour (\"0\" to exit)";
                        cout << "\nEnter new credit hour: ";
                        int inputHour = getIntInput();

                        if(checkExitInput(inputHour)){break;}

                        if (inputHour > 5 || inputHour < 2){
                            cout << "Error: Enter a number between 2-5.\n";
                            continue;
                        }else{
                            editCreditHour(courseIndex, inputHour);
                            cout << "Successfully updated credit hour.\n\n";
                            break;
                        }
                    }
                    break;

                case 2: //add components
                    addComponentsMenu(courseIndex);
                    break;
                case 3: //edit components
                    editComponentsMenu(courseIndex);
                    break;
                case 0: //exit
                    cout << "Exiting..\n";
                    break;
                default:
                    cout << "Invalid choice.\n";
            }
            break;
        }else{
            cout << "Error: Course code does not exist.\n\n";
            continue;
        }
    }
    return;
}

void addMarksMenu(int studentIndex){
    //prompt user for list of inputs
    cout << "\nEnter Marks (\"0\" to exit)\n";
    string inputCourseCode, inputComponentID;
    int courseIndex, inputMarks;

    //1. course code
    while(true){
        cout << "Enter course code: ";
        cin >> inputCourseCode;

        if(checkExitInput(inputCourseCode)){return;}

        courseIndex = getCourseIndexfromCode(inputCourseCode);
        if(courseIndex != -1){ //if code exist
            cout << endl << PRINT_DIVIDER;
            printCourseDetails(courseIndex);
            cout << endl;

            //if course has no components, reprompt
            if(!courseHasComponents(courseIndex)){
                cout << "Error: Course has no components to add marks to.\n\n";
                continue;
            }
            break;
        }else{
            cout << "Error: Course code does not exist.\n\n";
            continue;
        }
    }

    //2. component id
    while(true){
        cout << "Enter component ID: ";
        cin >> inputComponentID;

        if(checkExitInput(inputComponentID)){return;}

        //check if component at courseIndex exist
        int componentIndex = getComponentIndexfromCourse(courseIndex, inputComponentID);
        if(componentIndex != -1){ //if component is found
            break;
        }else{
            cout << "Error: Component does not exist in this course.\n\n";
            continue;
        }
    }

    //check if already has existing record of marks
    int studentMarksIndex = getStudentMarksIndex(studentIndex, inputCourseCode, inputComponentID);
    if(studentMarksIndex != -1){ //if exist in student marks list
        cout << "Error: Marks already exist for this component.\n";
        return;
    }

    //3. marks obtained
    while(true){
        cout << "Enter marks obtained: ";
        inputMarks = getIntInput();
        if (inputMarks <= 100 && inputMarks >= 0){
            //add everything to student at index
            addMarksToStudent(studentIndex, inputCourseCode, inputComponentID, inputMarks);
            break;
        }else{
            cout << "Error: Invalid number for marks.\n\n";
            continue;
        }
    }

}

void editMarksMenu(int studentIndex){

    //check if student has marks first
    if(!studentHasMarks(studentIndex)){
        cout << "Student does not have marks to update.\n";
        return;
    }

    //prompt user for list of inputs
    cout << "\nUpdate Marks (\"0\" to exit)\n";
    string inputCourseCode, inputComponentID;
    int studentMarksIndex, inputMarks;

    //1. course code + component id
    while(true){
        cout << "Enter course code: ";
        cin >> inputCourseCode;
        cout << "Enter component ID: ";
        cin >> inputComponentID;

        if(checkExitInput(inputCourseCode)){return;}
        if(checkExitInput(inputComponentID)){return;}

        studentMarksIndex = getStudentMarksIndex(studentIndex, inputCourseCode, inputComponentID);
        if(studentMarksIndex != -1){ //if exist in student marks list
            break;
        }else{
            cout << "Error: Course component does not exist.\n\n";
            continue;
        }
    }

    //2. update new marks
    while(true){
        cout << "Enter new marks obtained: ";
        inputMarks = getIntInput();
        if (inputMarks <= 100 && inputMarks >= 0){
            //update marksobtained at marks index
            editMarksToStudent(studentIndex, studentMarksIndex, inputMarks);
            return;
        }else{
            cout << "Error: Invalid number for marks.\n\n";
            continue;
        }
    }
}

void generateReportMenu(int studentIndex){
    //check if student has marks first
    if(!studentHasMarks(studentIndex)){
        cout << "\nStudent does not have marks to generate performance report.\n";
    }else{
        generateReport(studentIndex);
    }

//    char input;
//    cout << "\nWould you like to save report to disk? (y/n)\n";
//    cin >> input;
//    if (input == 'y'){
//        saveReportToDisk();
//        return;
//    }

    return;
}

void addComponentsMenu(int courseIndex){

    //checks if total course weightage is 100 (max)
    if(isCourseMaxWeightage(courseIndex)){
        cout << "Error: Components total weightage is maxed. Unable to add new components.\n";
        return;
    }

    //prompt user for list of inputs
    cout << "\nAdd Components (\"0\" to exit)\n";
    string inputComponentID, inputComponentName;
    int inputMaxMarks, inputWeightage;


    //1. component id
    while(true){
        cout << "Enter component ID (eg. C1): ";
        cin >> inputComponentID;

        if(checkExitInput(inputComponentID)){return;}

        //check if component at courseIndex exist
        int componentIndex = getComponentIndexfromCourse(courseIndex, inputComponentID);
        if(componentIndex != -1){ //if component is found
            cout << "Error: Component ID already exists.\n\n";
            continue;
        }else{
            break;
        }
    }

    //2. component name (no checks)
    cout << "Enter component name: ";
    cin.ignore();
    getline(cin, inputComponentName); //accomodate for space in "Final Test"

    if(checkExitInput(inputComponentName)){return;}


    //3. max marks
    while(true){
        cout << "Enter maximum marks: ";
        inputMaxMarks = getIntInput();

        if(checkExitInput(inputMaxMarks)){return;}

        if (inputMaxMarks <= 100 && inputMaxMarks >= 1){
            break;
        }else{
            cout << "Error: Invalid number for maximum marks.\n\n";
            continue;
        }
    }

    //4. weightage
    while(true){
        cout << "Enter weightage: ";
        inputWeightage = getIntInput();

        if(checkExitInput(inputWeightage)){return;}

        if (inputWeightage <= 100 && inputWeightage >= 1){

            //check total weightage is not >= 100
            if(!isCourseMaxWeightagePlusInput(courseIndex, inputWeightage)){
                //add everything to course at index
                addComponentsToCourse(courseIndex, inputComponentID, inputComponentName, inputMaxMarks, inputWeightage);
                break;
            }else{
                cout << "Error: Course total weightage exceeded 100.\n\n";
                continue;
            }

        }else{
            cout << "Error: Invalid number for weightage.\n\n";
            continue;
        }
    }

}

void editComponentsMenu(int courseIndex){

    //check if course has components
    if(!courseHasComponents(courseIndex)){
        cout << "Error: Course does not have components to edit.\n";
        return;
    }

    //prompt user for list of inputs
    cout << "\nEdit Components (\"0\" to exit)\n";
    string inputComponentID, inputComponentName;
    int componentIndex, inputMaxMarks, inputWeightage;

    //get component id
    while(true){
        cout << "Enter component ID (eg. C1): ";
        cin >> inputComponentID;

        if(checkExitInput(inputComponentID)){return;}

        //check if component at courseIndex exist
        componentIndex = getComponentIndexfromCourse(courseIndex, inputComponentID);
        if(componentIndex != -1){ //if component is found (invert of add)
            break;
        }else{
            cout << "Error: Component does not exists.\n\n";
            continue;
        }
    }

    //retrieve exiting values first if user does not modify later on
    getExistingComponentValue(courseIndex, componentIndex, inputComponentID,
                              inputComponentName, inputMaxMarks, inputWeightage);


    //menu prompt on what to edit
    while(true){
        int input;
        cout << "\nWhat would you like to edit?\n";
        cout << "1. Component ID\n";
        cout << "2. Component Name\n";
        cout << "3. Maximum Marks\n";
        cout << "4. Weightage\n";
        cout << "0. Save/Exit\n";
        cout << PRINT_DIVIDER2 << endl;
        cout << "Enter number: ";
        input = getIntInput();

        switch(input){
            case 1:
                //1. component id
                while(true){
                    cout << "Enter new component ID (eg. C1): ";
                    cin >> inputComponentID;

                    if(checkExitInput(inputComponentID)){return;}

                    //check if component at courseIndex exist
                    int componentIndex = getComponentIndexfromCourse(courseIndex, inputComponentID);
                    if(componentIndex != -1){ //if component is found
                        cout << "Error: Component ID already exists.\n\n";
                        continue;
                    }else{
                        break;
                    }
                }
                break;


            case 2:
                //2. component name (no checks)
                cout << "Enter new component name: ";
                cin.ignore();
                getline(cin, inputComponentName);

                if(checkExitInput(inputComponentName)){return;}

                break;

            case 3:
                //3. max marks
                while(true){
                    cout << "Enter new maximum marks: ";
                    inputMaxMarks = getIntInput();

                    if(checkExitInput(inputMaxMarks)){return;}

                    if (inputMaxMarks <= 100 && inputMaxMarks >= 1){
                        break;
                    }else{
                        cout << "Error: Invalid number for maximum marks.\n\n";
                        continue;
                    }
                }
                break;

            case 4:
                //4. weightage
                while(true){
                    cout << "Enter new weightage: ";
                    inputWeightage = getIntInput();

                    if(checkExitInput(inputWeightage)){return;}

                    if (inputWeightage <= 100 && inputWeightage >= 1){

                        //check total weightage is not >= 100 (minus self + new weightage)
                        if(!isCourseMaxWeightageMinusSelfPlusInput(courseIndex, componentIndex, inputWeightage)){
                            break;
                        }else{
                            cout << "Error: Course total weightage exceeded 100.\n\n";
                            continue;
                        }

                    }else{
                        cout << "Error: Invalid number for weightage.\n\n";
                        continue;
                    }
                    break;
                }
                break;

            case 0: //save + exit

                //update at courseIndex componentIndex
                editComponentsToCourse(courseIndex, componentIndex, inputComponentID,
                                        inputComponentName, inputMaxMarks, inputWeightage);
                cout << "Exiting..\n";
                return;

            default:
                cout << "Invalid choice.\n";
        }
    }
}

//{helpers
bool checkExitInput(const string& input){
    if (input == "0"){
        cout << "Exiting..\n";
        return true;
    }
    return false;
}

bool checkExitInput(int input){ //overloaded for int input
    if (input == 0){
        cout << "Exiting..\n";
        return true;
    }
    return false;
}

int getIntInput() //check for invalid cin for int
{
    int value;
    while (true)
    {
        cin >> value;

        if (!cin.fail()){
            return value;
        }
        cout << "Invalid input. Please enter a number.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        continue;
    }
}
//}
