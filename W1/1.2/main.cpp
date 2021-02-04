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
using namespace std;

class Personal {
    private: 
        string first_name;
        string last_name;
        int day;
        int month;
        int year;


    public:
        void setName(string fname, string lname) {
            first_name = fname;
            last_name = lname;
        }
        void setDates(int d, int m, int y) {
            if (d >= 1 && d <=31) { day=d; } //check if input date is within bounds and if so set private variable to new variable
            else {cout << "input day not a real date\n"} // if not within bounds give error with appropriate text

            if (m >= 1 && m <=12) { month=m; } //check if input date is within bounds and if so set private variable to new variable
            else {cout << "input month not a real date\n"} // if not within bounds give error with appropriate text

            if (y >= 1 && y <=9999) { year=y; } //check if input date is within bounds and if so set private variable to new variable
            else {cout << "input year not a real date\n"} // if not within bounds give error with appropriate text
        }

        string getNames() {
            return (first_name + " " + last_name);
        }

        string getFName() {
            return (first_name);
        }
    
        string getLName() {
            return (last_name);
        }
        string getDates() {
            return (string(day) + "-" + string(month) + "-" + string(year));
        }
};



int main()
{

    



    system("pause");
    return 0;
}
