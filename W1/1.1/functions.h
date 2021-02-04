#include <sstream>
#include <string>
using namespace std;

/*
Following function mostly copied from https://www.cplusplus.com/forum/beginner/130915/
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
           cout << "ERROR!\nwrong input\nPlease enter a FLOAT only" << endl;
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


float calcBMI(float height,float weight)
{
    float BMI;
    BMI = weight/(height*height);
    return BMI;
}

