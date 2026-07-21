#include "../include/Student.h"

std::ostream& operator<<(std::ostream& out, const Student& s)
{
    out << s.getId() << "\t";
    out << s.getName();

    return out;
}

Student Student::fromString(const std::string& line)
{
    std::stringstream ss(line);
    std::string id, name;

    getline(ss, id, ';');
    getline(ss, name, ';');

    return Student(id, name);
}

bool Student::addMark(const Marks& m)
{
    if (marksCount >= MAX_MARKS){
        return false;
    }
    marksList[marksCount++] = m;
    return true;
}

void Student::printAllMarks(){
    std::cout << std::left << std::setw(12) << "Course"
        << std::setw(11) << "Component"
        << "Marks Obtained\n";
    for(int i=0; i<marksCount; i++){
        std::cout << std::left << std::setw(12) << marksList[i].getCourseCode()
            << std::setw(11) << marksList[i].getComponentId()
            << marksList[i].getMarks() << std::endl;
    }
}

bool Student::hasMarks(){
    if(marksCount != 0){
        return true;
    }
    return false;
}

int Student::getMarksIndex(const std::string& targetCourse, const std::string& targetComponent){
    for(int i=0; i<marksCount; i++){
        if(targetCourse == marksList[i].getCourseCode() &&
           targetComponent == marksList[i].getComponentId()){
            return i;
        }
    }
    return -1;
}

bool Student::editMark(int index, int newMarks){
    marksList[index].setMarks(newMarks);
    return true;
}







