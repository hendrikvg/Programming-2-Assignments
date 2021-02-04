#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/*
Following function mostly copied from https://www.cplusplus.com/forum/beginner/130915/
This function makes sure that the input is a floating number and lets the user retry if the input is not a floating number

This is done by converting the inputString to a stringstream, the stringstream then gets put in a floating outputFloat.
While putting the stringstream in outputFloat it outputs a boolean whether this operation was possible.
After that it makes sure there is nothing else stored in the stringstream by trying to put any remaining part of the stringstream back into string inputString.

We ended up using this method as try catch with the stof() and using first_not_of() functions will not give an error when a string is put directly behind a floating number. 
"1.1a" or "1.1.1" would give a floating output 1.1, without giving an error.
These problems could be solved by checking character by character, but we refuse to do that.
*/
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
           cout << "ERROR!\nwrong input\nPlease enter a FLOATING number only" << endl;
        }
    }
}

float InputCheck(){ // This function checks whether the user input is a float and positive.
    float test;
    while(1){
        string mystr;
        getline (cin,mystr);    
        try
        {
            stof(mystr);
        }
            catch(exception&)
        {
            cout << "Error: invalid entry. Please try again. " << endl;
        }

    }
    return test;
}

/*
float getFloat()
{
    string inputString;
    float inputFloat;

    while (1)
    {
        getline(cin, inputString);
        bool isNotNumber = inputString.find_first_not_of("1234567890."); 
        if (isNotNumber)
        {
            break;
        }  
        cout << "\"" << inputString << "\" is not a number!" << endl;
    }
    cout << "zuig m'n pik c++" << endl;
    inputFloat = stof(inputString);

    return inputFloat;
}
*/

float calcBMI(float height,float weight)
{
    float BMI;
    BMI = weight/(height*height);
    return BMI;
}

int main()
{
    cout << "Hello world!" << endl;
    //cout << InputCheck() << endl;
    cout << getFloat() << endl;
    //std::cout << "BMI: " << calcBMI(getFloat(),1) << std::endl;
    cout << "Goodbye world...\n" << endl;
    return 0;
}
