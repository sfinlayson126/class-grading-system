#pragma once

/*
Filename: CCourse.h
Author: Finlayson, Seamus
Date: January 20, 2021
*/

#include <string>
#include <vector>
#include <regex>

class CCourse
{
public:
	CCourse(void);
	~CCourse(void);

	int add_student();
	int edit_student(int which_one);
	int print_grades();
	int delete_student(int pick_student);
	int save_data();
	int load_data();

	float final_grade(int this_student);
	std::string input_validation(std::string request_input, std::regex match_format);

	int get_student_vec_size();

private:
	std::vector<CStudent> students_vec;

};