#pragma once

#include <string>

//parent class of Student, Lecturer
class Person{
protected:
    std::string id;
    std::string name;

    //constructor/destructor
    Person():id(""), name(""){}
    Person(std::string i, std::string n): id(i), name(n){}
    ~Person(){}

public:
//    void setName(const std::string& n);
//    void setId(const std::string& i);
//    std::string getName()const;

    //getters/setters
    const std::string& getName()const {return name;};
    const std::string& getId()const {return id;}
};
