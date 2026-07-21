#include "../include/Component.h"

Component Component::fromString(const std::string& line, std::string& courseCode)
{
    std::stringstream ss(line);
    std::string cid, cname, marks, weight;

    getline(ss, courseCode, ';');
    getline(ss, cid, ';');
    getline(ss, cname, ';');
    getline(ss, marks, ';');
    getline(ss, weight, ';');

    return Component(cid, cname, std::stoi(marks), std::stoi(weight));
}
