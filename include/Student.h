#pragma once

#include "Person.h"
#include "Marks.h"
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <ostream>

class Student : public Person{ //person has id, name
private:
    static constexpr int MAX_MARKS = 20;
    Marks marksList[MAX_MARKS];
    int marksCount;

public:
    //constructor/destructor
    Student(): Person(), marksCount(0){}
    Student(std::string id,std::string name): Person(id, name), marksCount(0){}
    ~Student(){}

    //getter
    int getMarksCount()const {return marksCount;}
    const Marks& getMark(int index)const {return marksList[index];}

    //friend function / operator overload
    friend std::ostream& operator<<(std::ostream&, const Student&);

    //functions
    static Student fromString(const std::string&);
    bool addMark(const Marks&);
    void printAllMarks();
    bool hasMarks();
    int getMarksIndex(const std::string&, const std::string&);
    bool editMark(int, int);
};
