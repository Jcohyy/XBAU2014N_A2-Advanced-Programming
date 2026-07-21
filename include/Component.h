#pragma once

#include <string>
#include <sstream>

class Component{
private:
    std::string componentID;
    std::string componentName;
    int maxMarks;
    int weightage;
public:
    //constructor/destructor
    Component(): componentID(""), componentName(""), maxMarks(0), weightage(0){}
    Component(std::string cid, std::string cname, int marks, int weight):
        componentID(cid), componentName(cname), maxMarks(marks), weightage(weight){}
    ~Component(){}

    //getters/setters
    const std::string& getComponentID()const {return componentID;}
    const std::string& getComponentName()const {return componentName;}
    int getMaxMarks()const {return maxMarks;}
    int getWeightage()const {return weightage;}
    void setComponentID(const std::string& cid) {componentID = cid;}
    void setComponentName(const std::string& cname) {componentName = cname;}
    void setMaxMarks(int marks) {maxMarks = marks;}
    void setWeightage(int weight) {weightage = weight;}

    //functions
    static Component fromString(const std::string&, std::string&);
};
