#include "../include/Course.h"

std::ostream& operator<<(std::ostream& out, const Course& c)
{
    out << std:: left << std::setw(11) << c.getCourseCode()
        << std::setw(30) << c.getCourseName()
        << c.getCreditHour();

    return out;
}

Course Course::fromString(const std::string& line)
{
    std::stringstream ss(line);
    std::string cc, cn, ch;

    getline(ss, cc, ';');
    getline(ss, cn, ';');
    getline(ss, ch, ';');

    return Course(cc, cn, std::stoi(ch));
}

bool Course::addComponent(const Component& c)
{
    if (componentCount >= MAX_COMPONENT){
        return false;
    }
    componentList[componentCount++] = c;
    return true;
}

void Course::printAllComponents(){
    std::cout << std::left << std::setw(5) << "ID"
        << std::setw(15) << "Name"
        << std::setw(15) << "Maximum Marks"
        << "Weightage\n";
    for(int i=0; i<componentCount; i++){
        std::cout << std::left << std::setw(5) << componentList[i].getComponentID()
            << std::setw(15) << componentList[i].getComponentName()
            << std::setw(15) << componentList[i].getMaxMarks()
            << componentList[i].getWeightage() << std::endl;
    }
}

bool Course::hasComponents(){
    if(componentCount != 0){
        return true;
    }
    return false;
}

int Course::getComponentIndex(const std::string& componentID){
    for(int i=0; i<componentCount; i++){
        if(componentID == componentList[i].getComponentID()){
            return i;
        }
    }
    return -1;
}

int Course::getTotalComponentsWeightage(){
    int totalWeightage = 0;
    for(int i=0; i<componentCount; i++){
        totalWeightage += componentList[i].getWeightage();
    }
    return totalWeightage;
}

bool Course::editComponent(int index, const std::string& cid, const std::string& cname, int marks, int weight){
    componentList[index].setComponentID(cid);
    componentList[index].setComponentName(cname);
    componentList[index].setMaxMarks(marks);
    componentList[index].setWeightage(weight);
    return true;
}
