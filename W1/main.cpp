/*
==============================================================
 Filename    :  main.cpp
 Authors     :  Hendrik van Gils    (s1920677)      h.vangils@student.utwente.nl
                Deniz Ugurlu        (s1797735)      d.a.ugurlu@student.utwente.nl
 Version     :  1.0
 License     :  None
 Description :  The aims op this program are:
                1) to calculate and display the users BMI.
                2) to calculate the maximum and target heartrate.
==============================================================
*/

using namespace std;
#include <iostream> //Needed to compile standard library
#include <string>
#include <sstream>
#include "functions.h" //Includes our functions
#include <ctime>       //Includes library to retrieve current date
#include "Person.h"    //Includes our class

void menu()
{
    cout << "\nWelcome to Assignment 1:" << endl;
    cout << "press 0 to quit" << endl;
    cout << "Press 1 for the BMI calculator" << endl;
    cout << "press 2 for Classes and such" << endl;
    cout << "press 3 to input new person and calculate stuff" << endl;

    int input = getInteger(0, 3); // get an integer between 0 and 3
    if (input == 0)
    {
        cout << "Goodbye world...\n";
        exit(EXIT_SUCCESS); // exits the program with cleaning up.
    }
    else if (input == 1) // Exercise 1
    {
        evaluateAndPrintBMI(calculateBMI()); //input the output of calculateBMI into evaluateAndPrintBMI
        printInfo();                         //prints the info from the health services to the terminal for user reference
    }
    else if (input == 2) // Exercise 2 part 1
    {
        Person person1("Mel", "Guru", 13, 05, 1997);                                               //create object called person1 with the constructor
        cout << "Name of person is: " << person1.getNames() << endl;                               //Ouput the full name of the object
        cout << "Birthday of " << person1.getFirstName() << " is: " << person1.getDates() << endl; //Output the birth dates to the user
        person1.checkBirthday();                                                                   //Check if today is person1's birthday :), if so congratulate
        cout << "The maximum heart rate of " << person1.getFirstName() << " is: "
             << calculateMaximumHeartRate(person1.getAge()) << " BPM." << endl;            //Calculate the maximum BPM of person1 with function.
        TargetHeartRates targetHeartRates = calculateTargetHeartRates(person1.getAge()); //calculate the BPM range making use of the variable addresses defined at 49 and 50
        cout << "The target heart range of " << person1.getFirstName()
             << " is between " << targetHeartRates.targetHeartRate << " and " << targetHeartRates.maxHeartRate << " BPM." << endl; //print the range
    }

    else if (input == 3) // Exercise 2 part 2
    {
        string first_name;
        string last_name;
        int birthDay;
        int birthMonth;
        int birthYear;

        // Start by prompting the user for names and dates of object to be constructed

        cout << "Enter first name: \n";
        getline(cin, first_name); //prompt user for first name
        cout << "Enter last name: \n";
        getline(cin, last_name); //promt user for last name
        cout << "Enter Year of birth: \n";
        birthYear = getInteger(1900, 2020); //get int between given boundaries from user
        cout << "Enter Month of birth: \n";
        birthMonth = getInteger(1, 12); //get int between given boundaries from user
        cout << "Enter Day of birth: \n";
        birthDay = getInteger(1, 31); //get int between given boundaries from user

        // Construct new object with given data and output max bpm and optimal range

        Person person1(first_name, last_name, birthDay, birthMonth, birthYear);                    // Construct new object with given variables
        cout << "Name of person is: " << person1.getNames() << endl;                               //Ouput the full name of the object
        cout << "Birthday of " << person1.getFirstName() << " is: " << person1.getDates() << endl; //Output the birth dates to the user
        person1.checkBirthday();                                                                   //Check if today is person1's birthday :), if so congratulate
        cout << person1.getFirstName() << " is " << person1.getAge() << " years old." << endl;
        cout << "The maximum heart rate of " << person1.getFirstName() << " is: "
             << calculateMaximumHeartRate(person1.getAge()) << " BPM." << endl;            //Calculate the maximum BPM of person1 with function.
        TargetHeartRates targetHeartRates = calculateTargetHeartRates(person1.getAge()); //calculate the BPM range making use of the variable addresses defined at 49 and 50
        cout << "The target heart range of " << person1.getFirstName()
             << " is between " << targetHeartRates.targetHeartRate << " and " << targetHeartRates.maxHeartRate << " BPM." << endl; //print the range
    }
}

int main()
{
    cout << "\nHello world!" << endl;
    while (true) // 'infinite' loop for the menu (except that the menu can close the program)
    {
        menu(); // Start menu to allow user to choose which program to run
    }

    return 0;
}
