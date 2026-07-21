#include "../include/Marks.h"

Marks Marks::fromString(const std::string& line, std::string& studentId)
{
    std::stringstream ss(line);
    std::string cc, cid, marks;

    getline(ss, studentId, ';');
    getline(ss, cc, ';');
    getline(ss, cid, ';');
    getline(ss, marks, ';');

    int intmark = std::stoi(marks);
    return Marks(cc, cid, intmark);
}


