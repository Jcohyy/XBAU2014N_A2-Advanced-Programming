#pragma once

#include <string>
#include <sstream>

class Marks{
private:
    std::string courseCode;
    std::string componentId;
    int marksObtained;

public:
    //constructor/destructor
    Marks(): courseCode(""), componentId(""), marksObtained(0){}
    Marks(std::string cc, std::string cid, int marks):
        courseCode(cc), componentId(cid), marksObtained(marks){}
    ~Marks(){}

    //getters/setters
    const std::string& getCourseCode()const {return courseCode;}
    const std::string& getComponentId()const {return componentId;}
    int getMarks()const {return marksObtained;}
    void setMarks(int newMarks) {marksObtained = newMarks;}

    //functions
    static Marks fromString(const std::string&, std::string&);


};
