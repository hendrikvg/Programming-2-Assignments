/*
==============================================================
 Filename    :  functions.h
 Authors     :  Hendrik van Gils    (s1920677)      h.vangils@student.utwente.nl
                Deniz Ugurlu        (s1797735)      d.a.ugurlu@student.utwente.nl
 Version     :  1.0
 License     :  None.
 Description :  The aims op this file are to supply some basic, and some less basic functions to the main script.
==============================================================
*/

/*
The function getFloat() was mostly copied from https://www.cplusplus.com/forum/beginner/130915/
This function makes sure that the input is a floating number and lets the user retry if the input is not a floating number
This is done by converting the inputString to a stringstream, the stringstream then gets put in a floating outputFloat.
While putting the stringstream in outputFloat it outputs a boolean whether this operation was possible.
After that it makes sure there is nothing else stored in the stringstream by trying to put any remaining part of the stringstream back into string inputString.
We ended up using this method as try catch with the stof() and using first_not_of() functions will not give an error when a string is put directly behind a floating number. 
"1.1a" or "1.1.1" would give a floating output 1.1, without giving an error.
These problems could be solved by checking character by character, but we refuse to do that.

@returns A floating number from user input that is positive
*/
float getPosFloat()
{
    float outputFloat;
    string inputString;

    while (1)
    {
        getline(cin, inputString);                                                     // gets user input as a string
        stringstream convert(inputString);                                             // makes string into a stream
        if (convert >> outputFloat && !(convert >> inputString) && (outputFloat >= 0)) // checking for valid conversion and any rejects if any unconverted input left
        {
            return outputFloat;
        }
        else
        {
            cin.clear();
            cout << "ERROR!\nwrong input\nPlease enter a POSITIVE FLOATING NUMBER ONLY" << endl;
        }
    }
}

/*
The function getInteger() makes sure the input string is an integer the minimum and the maximum input. 
If it isn't then the user will be asked to correct their input.
If it is then the input string will be converted to an integer and returned.

@param minimum The minimum value of the integer that will be recieved
@param maximum The maximum value of the integer that will be recieved
@returns An integer from user input between the minimum and maximum
*/
int getInteger(int minimum, int maximum)
{
    int outputInteger;
    string inputString;

    while (1)
    {
        getline(cin, inputString);                                                                                             // gets user input as a string
        stringstream convert(inputString);                                                                                     // makes string into a stream
        if (convert >> outputInteger && !(convert >> inputString) && (outputInteger >= minimum) && (outputInteger <= maximum)) // checking for valid conversion and any rejects if any unconverted input left
        {
            return outputInteger;
        }
        else
        {
            cin.clear(); // clear the input
            cout << "ERROR!\nwrong input\nPlease enter an INTEGER between " << minimum << " and " << maximum << endl;
        }
    }
}

/*
The function caclulateBMI() asks the user for their height and weight and uses this data to return the BMI.

@returns A floating number that represents the BMI.
*/
float calculateBMI()
{
    cout << "Please enter your height in meters using numbers and a dot for decimals: " << endl;
    float height = getPosFloat(); // Use premade get functions to prompt user for information
    cout << "Please enter you weight in kg using numbers and a dot for decimals: " << endl;
    float weight = getPosFloat(); // Use premade get functions to prompt user for information
    float BMI = weight / (height * height);
    return BMI;
}

/*
The function evaluateAndPrintBMI() displays the users BMI and in which category the user falls.

@param BMI A BMI number.
*/
void evaluateAndPrintBMI(float BMI)
{
    cout << "\nYour BMI is: " << BMI << endl;
    if (BMI < 18.5)
    {
        cout << "You are underweight." << endl;
    }
    else if (18.5 <= BMI && BMI < 25)
    { // make sure the conditions are correct and span the entire number range
        cout << "Your weight is normal." << endl;
    }
    else if (25 <= BMI && BMI < 30)
    {
        cout << "You are overweight." << endl;
    }
    else if (BMI >= 30)
    {
        cout << "You are obese." << endl;
    }
    else
    { // if a number is entered and the conditions do not cover all possible options it will output an error notifying the coder of a mistake.
        cerr << "ERROR in while categorizing BMI!" << endl;
    }
}

/*
The function printInfo() prints a preset piece of text from the health services for the users' reference.
*/
void printInfo()
{
    cout << "\nBMI VALUES:" << endl;
    cout << "Underweight: \t less than 18.5" << endl;
    cout << "Normal: \t between 18.5 and 24.9" << endl;
    cout << "Overweight: \t between 25 and 29.9" << endl;
    cout << "Obese: \t\t 30 or greater" << endl;
}

/*
calculateMaximiumHeartRate() calculates the objects' max BPM according to formula 220 - age

@param age The age of the `Person`.
@returns The maximum heartrate of a person of the provided age.
*/
int calculateMaximumHeartRate(int age)
{
    return 220 - age;
}

/*

*/
struct TargetHeartRates { // Make a struct called TargetHeartRates containing two floats called targetHeartRate and maxHeartRate
    float targetHeartRate;
    float maxHeartRate;
};

/*
calculateTargetHeartRates() calculates the objects' optimum BPM range according to formula (220 - age)*0.5 and (220 - age)*0.85.
The struct defined above is used to return two floating point values.
As can be observed we have tried to maximize the amount of times "HeartRate" is stated in the following function.
We believe that with an average of 1.57 average occurances per line this goal has been achieved.

@param age The age of the `Person`.
@returns A TargetHeartRates struct containing minimum and maximum target heartrates.
*/
TargetHeartRates calculateTargetHeartRates(int age)
{
    TargetHeartRates targetHeartRates; // initiate struct called targetHeartRates
    targetHeartRates.targetHeartRate = .5 * calculateMaximumHeartRate(age);
    targetHeartRates.maxHeartRate = .85 * calculateMaximumHeartRate(age);
    return targetHeartRates;
}