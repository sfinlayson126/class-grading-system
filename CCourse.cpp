/*
Filename: CCourse.c
Author: Finlayson, Seamus
Date: January 20, 2021
*/

//homemade objects
#include "CStudent.h"
#include "CCourse.h"

//libraries
#include <vector>
#include <iostream>
#include <regex>
#include <sstream>
#include <fstream>

CCourse::CCourse(void) {

}

CCourse::~CCourse(void) {

}

//create a new student and go to edit
int CCourse::add_student() {

    //add student
    CStudent temp;
    students_vec.push_back(temp);

    //exit function
    return 0;
}

//edit a student
int CCourse::edit_student(int which_one) {

    //input validation formats
    std::regex student_number_format("[A][0][0-1][0-9]{6}");
    std::regex student_grade_format("([0-9]?[0-9]?([.][0-9]+)?)|([1][0][0]([.][0]+)?)");

    //string to hold input data
    std::string input;

    //edit data
    input = input_validation("Student Number: ", student_number_format);
    std::istringstream(input) >> students_vec[which_one].student_number;

    input = input_validation("Lab Grade: ", student_grade_format);
    std::istringstream(input) >> students_vec[which_one].lab_grade;

    input = input_validation("Quiz Grade: ", student_grade_format);
    std::istringstream(input) >> students_vec[which_one].quiz_grade;

    input = input_validation("Midterm Grade: ", student_grade_format);
    std::istringstream(input) >> students_vec[which_one].midterm_grade;

    input = input_validation("Final Exam Grade: ", student_grade_format);
    std::istringstream(input) >> students_vec[which_one].final_exam_grade;

    //exit function
    return 0;
}

//print all students and grades
int CCourse::print_grades() {

    //check if data has been entered
    if (students_vec.size() == 0) {
        //inform the user
        std::cout << "No students to print." << std::endl;
    }
    else {

        //print student data
        std::cout << "#\tStudent\t\tLab\tQuiz\tMidterm\t\tFinal Exam\tFinal Grade";
        for (int current_student = 0; current_student < students_vec.size(); current_student++) {
            std::cout << std::endl << current_student << "\t";
            std::cout << students_vec[current_student].student_number << "\t";
            std::cout << students_vec[current_student].lab_grade << "\t";
            std::cout << students_vec[current_student].quiz_grade << "\t";
            std::cout << students_vec[current_student].midterm_grade << "\t\t";
            std::cout << students_vec[current_student].final_exam_grade << "\t\t";
            std::cout << final_grade(current_student);
        }
        std::cout << std::endl;
    }

    //exit function
    return 0;
}

//save students to a file
int CCourse::save_data() {

    //input format
    std::regex file_name_format("[[:alnum:]]+");

    //variable declaration
    std::string file_name;
    std::ofstream outfile;

    //ask user for file name and validate user input
    file_name = input_validation("Enter file name: ", file_name_format);

    //open the file
    outfile.open(file_name + ".csv");

    //add file header
    outfile << "Student,Lab,Quiz,Midterm,Final Exam,\n";

    //store student data in the file
    for (int current_student = 0; current_student < students_vec.size(); current_student++) {
        outfile << students_vec[current_student].student_number << ",";
        outfile << students_vec[current_student].lab_grade << ",";
        outfile << students_vec[current_student].quiz_grade << ",";
        outfile << students_vec[current_student].midterm_grade << ",";
        outfile << students_vec[current_student].final_exam_grade << ",\n";
    }

    //add escape character
    outfile << "end_of_file";

    //close the file
    outfile.close();

    //report success to user
    std::cout << "Data saved in: " << file_name + ".csv" << std::endl;

    //exit function
    return 0;
}

//load students from a file
int CCourse::load_data() {
    
    //input format
    std::regex file_name_format("[[:alnum:]]+");

    //variable declaration
    int current_student = 0;
    std::string check;
    std::string file_name;
    std::string file_data;
    std::ifstream infile;

    //ask user for file name and validate user input
    file_name = input_validation("Enter name of a .csv file to be loaded: ", file_name_format);

    //open file
    infile.open(file_name + ".csv");

    //check if file is open
    if (infile.is_open() == true) {

        //empty students_vec
        while (students_vec.size() > 0) {
            delete_student(0);
        }

        //read past header
        for (int i = 0; i < 5; i++)
            std::getline(infile, file_data, ',');

        //get data from file
        std::getline(infile, file_data, ',');
        do {
            add_student();
            std::istringstream(file_data) >> students_vec[current_student].student_number;
            std::getline(infile, file_data, ',');
            std::istringstream(file_data) >> students_vec[current_student].lab_grade;
            std::getline(infile, file_data, ',');
            std::istringstream(file_data) >> students_vec[current_student].quiz_grade;
            std::getline(infile, file_data, ',');
            std::istringstream(file_data) >> students_vec[current_student].midterm_grade;
            std::getline(infile, file_data, ',');
            std::istringstream(file_data) >> students_vec[current_student].final_exam_grade;
            std::getline(infile, file_data, ',');
            std::istringstream(file_data) >> check;
            current_student++;
        } while (check != "end_of_file");

        //close file
        infile.close();

        //report success to user
        std::cout << file_name + ".csv" << " was loaded successfully." << std::endl;
    }
    else {

        //report failure to user
        std::cout << "Unable to open file." << std::endl;
    }

    //exit function
    return 0;
}

//delete a student from the student vector
int CCourse::delete_student(int pick_student) {

    //erase selected student
    students_vec.erase(students_vec.begin() + pick_student);

    //exit function
    return 0;
}

//calculate a student's final grade
float CCourse::final_grade(int this_student) {

    float class_grade = 0;
    class_grade = 0.4 * students_vec[this_student].lab_grade;
    class_grade += 0.1 * students_vec[this_student].quiz_grade;
    class_grade += 0.2 * students_vec[this_student].midterm_grade;
    class_grade += 0.3 * students_vec[this_student].final_exam_grade;

    //exit function
    return class_grade;
}

//validate user input
std::string CCourse::input_validation(std::string request_input, std::regex match_format) {

    //variable to hold input
    std::string user_input;

    //validate input match
    do {
        std::cout << request_input;
        std::cin >> user_input;
        if (!(std::regex_match(user_input, match_format))) {
            std::cout << "Invalid entry." << std::endl << std::endl;
        }
    } while (!(std::regex_match(user_input, match_format)));

    std::cout << std::endl;

    //return validated input
    return user_input;
}

//getter for student_vec.size()
int CCourse::get_student_vec_size() {

    //exit function
    return students_vec.size();
}