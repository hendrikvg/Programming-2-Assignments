/*
==============================================================
 Filename    :  main.cpp
 Authors     :  Hendrik van Gils (s1920677) h.vangils@student.utwente.nl
                Deniz Ugurlu (s1797735) d.a.ugurlu@student.utwente.nl
 Version     :  1.0
 License     :  None other than access to Visual Studio Code.
 Description :  The aim op this program is to calculate desired heart rate according to your personal measurements.
==============================================================
*/

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

float getFloat() {
    float outputFloat;
    string inputString;

    while(1)
    {
        getline(cin,inputString); // gets user input as a string
        stringstream convert(inputString); // makes string into a stream
        if(convert >> outputFloat && !(convert >> inputString)) // checking for valid conversion and any rejects if any unconverted input left
        {
            return outputFloat;
        }
        else
        {
           cin.clear();
           cout << "ERROR!\nwrong input\nPlease enter a FLOAT only" << endl;
        }
    }
}

float calBMI() {

    float weight; // put all variables inside a function to make sure it is only in memory during the running of this function
    float height;
    float BMI;

    cout << "Input weight in kilograms: " << endl; // ask for input
    weight = getFloat();      // use premade function to have user input weight
    
    
    cout << "Input height in meters:  " << endl; // ask for input
    height = getFloat();          // use premade function to have user input height

    
    BMI = weight / (height*height);  // calculate BMI with given values
    cout << "your BMI:" << BMI << endl;      // output BMI to user
    return BMI; // Return BMI variable to main
}

string evaluateAndPrintBMI(float BMI) {
    /*
    Create if/else statements according to following criteria and set output string to class names {underweight, normal, overweight, obese}

    BMI VALUES:
    Underweight:less than 18.5
    Normal:between 18.5 and 24.9
    Overweight:between 25 and 29.9
    Obese:30 or greater
    */
   string catBMI;
   if (BMI < 18.5) {
       catBMI = "underweight";
    } else if (18.5 <= BMI && BMI < 25) { // make sure the conditions are correct and span the entire number range
       catBMI = "normal";
    } else if (25 <= BMI && BMI < 30) {
       catBMI = "overweight";
    } else if ( BMI >= 30) {
       catBMI = "obese";
    } else {                            // if a number is entered and the conditions do not cover all possible options it will output an error notifying the coder of a mistake.
    cout << "ERROR in catBMI! \n " << endl;
    }


    cout << "Which would be classified as: " << endl << catBMI << endl;
    return catBMI;
}


void printInfo() {
    cout << endl << "More information:\nBMI Values:\nUnderweight: less than 18.5\nNormal: between 18.5 and 24.9\nOverweight: between 25 and 29.9\nObese: 30 or greater" << endl;
return;
}

int main()
{

    evaluateAndPrintBMI(calBMI());      //first calculate BMI with calBMI() and use that as input for your category function. Truncate it so you don't have to make a new variable in this scope.
    printInfo();
    system("pause");
    return 0;
}

