#pragma once

#include "Component.h"
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

class Course{
private:
    static constexpr int MAX_COMPONENT = 20;
    Component componentList[MAX_COMPONENT];

    std::string courseCode;
    std::string courseName;
    int creditHour;
    int componentCount;

public:
    //constructor/destructor
    Course():courseCode(""),courseName(""),creditHour(0), componentCount(0){}
    Course(std::string cc, std::string cn, int ch):
        courseCode(cc), courseName(cn), creditHour(ch), componentCount(0){}
    ~Course(){}

    //getters/setters
    const std::string& getCourseCode()const {return courseCode;}
    const std::string& getCourseName()const {return courseName;}
    int getCreditHour()const {return creditHour;}
    void setCreditHour(int newHour) {creditHour = newHour;}
    int getComponentCount()const {return componentCount;}
    const Component& getComponent(int index)const {return componentList[index];}

    //friend function / operator overload
    friend std::ostream& operator<<(std::ostream&, const Course&);

    //functions
    static Course fromString(const std::string&);
    bool addComponent(const Component&);
    void printAllComponents();
    bool hasComponents();
    int getComponentIndex(const std::string&);
    int getTotalComponentsWeightage();
    bool editComponent(int, const std::string&, const std::string&, int, int);
};
