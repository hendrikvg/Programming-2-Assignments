/*
==============================================================
 Filename    :  functions.cpp
 Authors     :  Hendrik van Gils    (s1920677)      h.vangils@student.utwente.nl
                Deniz Ugurlu        (s1797735)      d.a.ugurlu@student.utwente.nl
 Version     :  1.0
 License     :  None.
 Description :  The aim of this file is to supply the main.cpp with additional functions
==============================================================
*/

#include <iostream>
#include <vector>
#include "Package.h"

// printCosts() prints the costs of all input packages in package pointer
// @param packages Package pointer vector to all packages of which the cost must be displayed
void printCosts(std::vector<Package*> packages)
{
    for (size_t i = 0; i < packages.size(); i++)
    {
        printf("Cost of shipping package %i is: %.2f \n",i + 1, packages[i]->calculateCost());
    }
}