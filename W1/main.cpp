/*
==============================================================
 Filename    :  main.cpp
 Authors     :  Hendrik van Gils    (s1920677)      h.vangils@student.utwente.nl
                Deniz Ugurlu        (s1797735)      d.a.ugurlu@student.utwente.nl
 Version     :  1.0
 License     :  None other than access to Visual Studio Code.
 Description :  The aims op this program are:
                1) to calculate and display the users BMI.
                2) to calculate the maximum and target heartrate.
==============================================================
*/

using namespace std;
#include <iostream>
#include <string>
#include <sstream>
#include "functions.h"

class Personal {
    private: 
        string firstName;
        string lastName;
        int birthDay;
        int birthMonth;
        int birthYear;


    public:
        void setName(string inputFirstName, string inputLastName) {
            firstName = inputFirstName;
            lastName = inputLastName;
        }
        void setDates(int day, int month, int year) {
            if (day >= 1 && day <=31) { birthDay = day; } //check if input date is within bounds and if so set private variable to new variable
            else {cout << "input day not a real date\n"} // if not within bounds give error with appropriate text

            if (month >= 1 && month <=12) { birthMonth = month; } //check if input date is within bounds and if so set private variable to new variable
            else {cout << "input month not a real date\n"} // if not within bounds give error with appropriate text

            if (year >= 1 && year <=9999) { birthYear = year; } //check if input date is within bounds and if so set private variable to new variable
            else {cout << "input year not a real date\n"} // if not within bounds give error with appropriate text
        }

        string getNames() {
            return (firstName + " " + lastName);
        }

        string getinputFirstName() {
            return (firstName);
        }
    
        string getinputLastName() {
            return (lastName);
        }
        string getDates() {
            return (string(birthDay) + "-" + string(birthMonth) + "-" + string(birthYear));
        }
};

void menu()
{
    cout << "\nWelcome to the Assignment 1:" << endl;
    cout << "press 0 to quit\n" << endl;
    cout << "Press 1 for the BMI calculator\n" << endl;
    cout << "press 2 for an error\n" << endl;
    
    int input = get_integer(1); 
    if (input == 0)
    {
        abort();    // abort quits the program.
    }
    else if (input == 1)
    {
        evaluateAndPrintBMI(calculateBMI());
        printInfo();
    }
}

int main()
{
    cout << "\nHello world!" << endl;
    while (true)    // 'infinite' loop for the menu (except that the menu can close the program)
    {
        menu();
    }
    cout << "Goodbye world...\n" << endl;
    return 0;
}