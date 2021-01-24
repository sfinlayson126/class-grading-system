/*
Filename: ELEX 4618 Lab 2.cpp
Author: Finlayson, Seamus (Conor)
Student Number: A01169421
Date: January 20, 2021
*/

#define _CRT_SECURE_NO_DEPRECATE 1
#define _CRT_NONSTDC_NO_DEPRECATE 1

//homemade objects
#include "CStudent.h"
#include "CCourse.h"

//c libraries
#include <conio.h>      //getch()

//cpp libraries
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <regex>

//constants
#define TRUE 1
#define FALSE 0
#define NO_DATA 0

//function prototypes
int print_menu();

int main() {

    //variable initialization
    char action;
    int quit = FALSE;
    int select_student;
    std::regex whole_number("[[:digit:]]+");
    std::string input;

    CCourse ELEX4618;

    //main loop
    do {

        //print menu
        print_menu();

        //get user input
        action = getche();
        std::cout << std::endl << std::endl;

        //select action to take
        switch (action) {
        case 'A':
        case 'a':

            //add student
            std::cout << "Adding Student" << std::endl << std::endl;
            ELEX4618.add_student();

            //edit new student
            ELEX4618.edit_student(ELEX4618.get_student_vec_size() - 1);

            //inform user
            std::cout << "Student added." << std::endl;
            break;

        case 'E':
        case 'e':
            
            //check if any students are available in the vector
            if (ELEX4618.get_student_vec_size()) {

                //get user to select student
                std::cout << "Student to edit: ";
                std::cin >> input;
                std::istringstream(input) >> select_student;
                std::cout << std::endl;
                
                //check if input is valid
                if ((std::regex_match(input, whole_number)) && (select_student < ELEX4618.get_student_vec_size())) {
                    //inform user of successfully found student
                    std::cout << "Editing student " << input + "." << std::endl <<std::endl;
                    
                    //edit student
                    ELEX4618.edit_student(select_student);
                    std::cout << "Editing complete." << std::endl;
                }
                else {
                    //inform user of invalid selection
                    std::cout << "Student does not exist." << std::endl;
                }
            }
            else {
                std::cout << "No students to edit." << std::endl;
            }
            break;

        case 'P':
        case 'p':

            //print student
            ELEX4618.print_grades();
            break;

        case 'Q':
        case 'q':

            //quit program
            quit = TRUE;
            break;

        case 'D':
        case 'd':

            //check if any students are available in the vector
            if (ELEX4618.get_student_vec_size()) {

                //get user to select student
                std::cout << "Student to delete: ";
                std::cin >> input;
                std::istringstream(input) >> select_student;
                std::cout << std::endl;

                //check if input is valid
                if ((std::regex_match(input, whole_number)) && (select_student < ELEX4618.get_student_vec_size())) {
                    //inform user of successfully deleted student
                    std::cout << "Student " << input << " deleted.";

                    //delete student
                    ELEX4618.delete_student(select_student);
                }
                else {
                    //inform user of invalid selection
                    std::cout << "Student does not exist.";
                }
                std::cout << std::endl;
            }
            else {
                std::cout << "No students to delete." << std::endl;
            }
            break;

        case 'S':
        case 's':
            ELEX4618.save_data();
            break;

        case 'L':
        case 'l':
            ELEX4618.load_data();
            break;
            
        default:
            std::cout << "Invalid selection." << std::endl;
        }

    } while (quit == FALSE);

    //exit main
    return 0;
}

//print menu
int print_menu() {

    std::cout << std::endl << "*******************************************" << std::endl;
    std::cout << "ELEX4618 Grade System, by Seamus Finlayson"  << std::endl;
    std::cout << "*******************************************" << std::endl << std::endl;
    std::cout << "(A)dd student" << std::endl << "(E)dit student" << std::endl << "(D)elete student" << std::endl << "(P)rint course grades" << std::endl ;
    std::cout << "(S)ave course grades" << std::endl << "(L)oad course grades" << std::endl << "(Q)uit" << std::endl;
    std::cout << std::endl << "CMD> ";

    //exit function
    return 0;
}
