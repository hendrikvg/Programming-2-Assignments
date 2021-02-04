/*
The function check_integer checks whether the string input is a single integer between 0 and the max input. 
If it isn't then the user will be asked to correct their input.
If it is then the input string will be converted to an integer and returned.
Input has to be a digit, with a length no longer than one and not higher that the specified maximum.
*/
int check_integer(string input, int max)
{
    int input_int(input[0] - 48);                                        // Convert the string input (in ASCII) to integer with the 'same' value
    while (!isdigit(input[0]) || input.length() != 1 || input_int > max) // While loop so the user can input as many wrong answers as he/she wants.
    {
        cout << "Input was not a number inside the range of 0 to " << max << ", please try again: " << endl;
        getline(cin, input);
        input_int = input[0] - 48;
    }
    return input_int;
}

/*
The function get_integer gets an input line from the commandline and runs it through check_integer.
When check_integer retuns an integer, get_integer will return the same integer.
*/
int get_integer(int max)
{
    string inputString;
    cout << "Input number between 0 and " << max << ": ";
    getline(cin, inputString);
    int input_int = check_integer(inputString, max);
    return input_int;
}

/*
The function getFloat() was mostly copied from https://www.cplusplus.com/forum/beginner/130915/
This function makes sure that the input is a floating number and lets the user retry if the input is not a floating number

This is done by converting the inputString to a stringstream, the stringstream then gets put in a floating outputFloat.
While putting the stringstream in outputFloat it outputs a boolean whether this operation was possible.
After that it makes sure there is nothing else stored in the stringstream by trying to put any remaining part of the stringstream back into string inputString.

We ended up using this method as try catch with the stof() and using first_not_of() functions will not give an error when a string is put directly behind a floating number. 
"1.1a" or "1.1.1" would give a floating output 1.1, without giving an error.
These problems could be solved by checking character by character, but we refuse to do that.
*/
float getPosFloat() {
    float outputFloat;
    string inputString;

    while(1)
    {
        getline(cin,inputString); // gets user input as a string
        stringstream convert(inputString); // makes string into a stream
        if(convert >> outputFloat && !(convert >> inputString) && (outputFloat >= 0)) // checking for valid conversion and any rejects if any unconverted input left
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
The function caclulateBMI() asks the user for their height and weight and uses this data to return the BMI.
*/
float calculateBMI()
{
    float height;
    float weight;
    float BMI;
    cout << "Please enter your height in meters using numbers and a dot for decimals: " << endl;
    height = getPosFloat();
    cout << "Please enter you weight in kg using numbers and a dot for decimals: " << endl;
    weight = getPosFloat();
    BMI = weight / (height * height);
    return BMI;
}

/*
The function evaluateAndPrintBMI() displays the users BMI and in which category the user falls.
*/
void evaluateAndPrintBMI(float BMI)
{
    cout << "\nYour BMI is: " << BMI << endl;
    if (BMI < 18.5) {
       cout << "You are underweight." << endl;
    } else if (18.5 <= BMI && BMI < 25) { // make sure the conditions are correct and span the entire number range
       cout << "Your weight is normal." << endl;
    } else if (25 <= BMI && BMI < 30) {
       cout << "You are overweight." << endl;
    } else if ( BMI >= 30) {
       cout << "You are obese." << endl;
    } else {                            // if a number is entered and the conditions do not cover all possible options it will output an error notifying the coder of a mistake.
    cerr << "ERROR in while categorizing BMI!" << endl;
    }
}

void printInfo()
{
    cout << "\nBMI VALUES:" << endl;
    cout << "Underweight: \t less than 18.5" << endl;
    cout << "Normal: \t between 18.5 and 24.9" << endl;
    cout << "Overweight: \t between 25 and 29.9" << endl;
    cout << "Obese: \t\t 30 or greater" << endl;
}

int calculateMaximumHeartRate(int age) {
return 220 - age;
}

int calculateTargetHeartRates(int age) {
   int Target_min = int(0.5*(220 - age));
   int Target_max = int(0.85*(220 - age));
   cout << Target_min << " to " << Target_max << endl;
   return Target_min, Target_max;
}