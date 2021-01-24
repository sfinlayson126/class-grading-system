#pragma once

/*
Filename: CStudent.h
Author: Finlayson, Seamus
Date: January 20, 2021
*/

#include <string>

class CStudent
{
public:
	CStudent(void);
	~CStudent(void);

    std::string student_number;
    float lab_grade;
    float quiz_grade;
    float midterm_grade;
    float final_exam_grade;
private:

};
