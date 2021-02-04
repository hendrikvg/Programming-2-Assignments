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
#include <ctime>

class Person {
    private: 
        string firstName;
        string lastName;
        int birthDay;
        int birthMonth;
        int birthYear;


    public:
        Person(string inputFirstName, string inputLastName, int inputBirthDay, int inputBirthMonth, int inputBirthYear) {
            firstName = inputFirstName;
            lastName = inputLastName;
            if (inputBirthDay >= 1 && inputBirthDay <=31) { birthDay = inputBirthDay; } //check if input date is within bounds and if so set private variable to new variable
            else {cout << "input day not a real date\n";} // if not within bounds give error with appropriate text

            if (inputBirthMonth >= 1 && inputBirthMonth <=12) { birthMonth = inputBirthMonth; } //check if input date is within bounds and if so set private variable to new variable
            else {cout << "input month not a real date\n";} // if not within bounds give error with appropriate text

            if (inputBirthYear >= 1 && inputBirthYear <=9999) { birthYear = inputBirthYear; } //check if input date is within bounds and if so set private variable to new variable
            else {cout << "input year n0ot a real date\n";} // if not within bounds give error with appropriate text

        }

        void setName(string inputFirstName, string inputLastName) {
            firstName = inputFirstName;
            lastName = inputLastName;
        }

        void setDates(int day, int month, int year) {
            if (day >= 1 && day <=31) { birthDay = day; } //check if input date is within bounds and if so set private variable to new variable
            else {cout << "input day not a real date\n";} // if not within bounds give error with appropriate text

            if (month >= 1 && month <=12) { birthMonth = month; } //check if input date is within bounds and if so set private variable to new variable
            else {cout << "input month not a real date\n";} // if not within bounds give error with appropriate text

            if (year >= 1 && year <=9999) { birthYear = year; } //check if input date is within bounds and if so set private variable to new variable
            else {cout << "input year not a real date\n";} // if not within bounds give error with appropriate text
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
            stringstream birthDate;
            string outBirthDate;
            birthDate << birthDay << "-" << birthMonth << "-" << birthYear;
            birthDate >> outBirthDate;
            return outBirthDate;
        }
        int getAge() {
            // The next 7 lines come from https://cplusplus.com/forum/beginner/226899/

            time_t tt;
            time( &tt );
            tm TM = *localtime( &tt );

            int curr_Year    = TM.tm_year + 1900;
            int curr_Month   = TM.tm_mon ;
            int curr_Day     = TM.tm_mday;

            // end of cplusplus copy-paste

            int age = int((((curr_Year*12+curr_Month) - (birthYear*12+birthMonth))/12));
            cout << age << endl;
            return age;
        }
};

void menu()
{
    cout << "\nWelcome to the Assignment 1:" << endl;
    cout << "press 0 to quit\n" << endl;
    cout << "Press 1 for the BMI calculator\n" << endl;
    cout << "press 2 for Classes and such\n" << endl;
    cout << "press 3 to input new person and calculate stuff\n" << endl;

    int input = get_integer(3); 
    if (input == 0)
    {
        abort();    // abort quits the program.
    }
    else if (input == 1) // Exercise 1
    {
        evaluateAndPrintBMI(calculateBMI());
        printInfo();
    }
    else if (input == 2) // Exercise 2
    {
        Person Person1("Deniz", "Ugurlu", 13, 04, 1997);
        cout << Person1.getDates() << endl;
        cout << Person1.getNames() << endl;
        int age = Person1.getAge();
        cout << "max BPM: " << calculateMaximumHeartRate(age) << endl << "Optimal Range:\n";
        calculateTargetHeartRates(age);
    }

    else if (input == 3) 
    {
        string first_name;
        string last_name;
        int birthDay;
        int birthMonth;
        int birthYear;

        cout << "Enter first name: \n";
        cin >> first_name;
        cout << "Enter last name: \n";
        cin >> last_name;
        cout << "Enter Year of birth: \n";
        cin >> birthYear;
        cout << "Enter Month of birth: \n";
        cin >> birthMonth;
        cout << "Enter Day of birth: \n";
        cin >> birthMonth;

        Person person1(first_name, last_name, birthDay, birthMonth, birthYear);
        cout << "Your birthday is: " << person1.getDates() << endl;
        cout << "Your Name is: " << person1.getNames() << endl;
        int age = person1.getAge();
        cout << "max BPM: " << calculateMaximumHeartRate(age) << endl << "Optimal Range:\n";
        calculateTargetHeartRates(age);

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