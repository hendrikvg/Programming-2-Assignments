// ==============================================================
//  Filename    :  Person.h
//  Authors     :  Hendrik van Gils    (s1920677)      h.vangils@student.utwente.nl
//                 Deniz Ugurlu        (s1797735)      d.a.ugurlu@student.utwente.nl
//  Version     :  1.0
//  License     :  None.
//  Description :  The aims op this file are:
//                 1) to generate the class Person, which can store information about a person
//                 2) retrieve and manipulate data of stored people
// ==============================================================

using namespace std;
#include <iostream>
#include <ctime>

class Person
{
private:              // access specifier private
    string firstName; // data members
    string lastName;
    int birthDay;
    int birthMonth;
    int birthYear;

public: // access specifier public
        
    /*
    constructor:
    
    @param inputFirstName The first name of the `Person`
    @param inputLastName The last name of the `Person`
    @param day The day of the month the `Person` was born
    @param month The month of the year the `Person` was born
    @param year The year the `Person` was born
    */
    Person(string inputFirstName, string inputLastName, int inputBirthDay, int inputBirthMonth, int inputBirthYear)
    {
        setName(inputFirstName, inputLastName);
        setDates(inputBirthDay, inputBirthMonth, inputBirthYear);
    }

    // Setters:
    /*
    setName(string inputFirstName, string inputLastName) changes the first and last name of the `Person`

    @param inputFirstName The first name of the `Person`
    @param inputLastName The last name of the `Person`
    */
    void setName(string inputFirstName, string inputLastName)
    {
        firstName = inputFirstName;
        lastName = inputLastName;
    }

    /*
    setDates(int day, int month, int year) changes the date of birth of the `Person`

    @param day The day of the month the `Person` was born
    @param month The month of the year the `Person` was born
    @param year The year the `Person` was born
    */
    void setDates(int day, int month, int year)
    {
        if (day >= 1 && day <= 31)
        {
            birthDay = day;
        } //check if input date is within bounds and if so set private variable to new variable
        else
        {
            cout << "input day not a real date\n";
        } // if not within bounds give error with appropriate text

        if (month >= 1 && month <= 12)
        {
            birthMonth = month;
        } //check if input date is within bounds and if so set private variable to new variable
        else
        {
            cout << "input month not a real date\n";
        } // if not within bounds give error with appropriate text

        if (year >= 1 && year <= 9999)
        {
            birthYear = year;
        } //check if input date is within bounds and if so set private variable to new variable
        else
        {
            cout << "input year not a real date\n";
        } // if not within bounds give error with appropriate text
    }

    // Getters:
    /*
    @returns The first and last name of the `Person`
    */
    string getNames() const //specify const to let the compiler know that this function should not change variables
    {
        return (firstName + " " + lastName);
    }

    /*
    @returns The first name of the `Person`
    */
    string getFirstName() const //specify const to let the compiler know that this function should not change variables
    {
        return (firstName);
    }

    /*
    @returns The last name of the `Person`
    */
    string getLastName() const //specify const to let the compiler know that this function should not change variables
    {
        return (lastName);
    }

    /*
    @returns The brith date of the `Person`
    */
    string getDates() const //specify const to let the compiler know that this function should not change variables
    {
        return to_string(birthDay) + "-" + to_string(birthMonth) + "-" + to_string(birthYear); //convert integer values to string so they can be concatenated
    }

    /*
    @returns The age of the `Person`
    */
    int getAge() const
    {
        // The next 7 lines come from https://cplusplus.com/forum/beginner/226899/

        time_t tt = time(NULL);          //returns time and writes time to NULL
        tm timeStruct = *localtime(&tt); //localtime creates a time struct and returns the address of that time struct

        int currentYear = timeStruct.tm_year + 1900;
        int currentMonth = timeStruct.tm_mon + 1;
        int currentDay = timeStruct.tm_mday;

        // end of cplusplus copy-paste

        // The if else statement checks whether the person has already had his/her birthday within the current year. If so, the age is adjusted accordingly.
        int age = currentYear - birthYear;
        if (currentMonth == birthMonth)
        {
            if (currentDay < birthDay)
            {
                age--;
            }
        }
        else if (currentMonth < birthMonth)
        {
            age--;
        }
        return age;
    }

    /*
    @returns  Birthday congratulations if it is the `Person`'s birthday
    */
    void checkBirthday() const
    {

        // Get current date
        time_t tt = time(NULL);          //returns time and writes time to NULL
        tm timeStruct = *localtime(&tt); //localtime creates a time struct and returns the address of that time struct

        int currentMonth = timeStruct.tm_mon + 1;
        int currentDay = timeStruct.tm_mday;

        // Check if current date == birthday
        if (currentMonth == birthMonth && currentDay == birthDay) // If current date==birthdate congratulate
        {
            cout << "HAPPY BIRHTDAY " << getFirstName() << "!" << endl;
        }
    }
};