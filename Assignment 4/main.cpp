/*
==============================================================
 Filename    :  main.cpp
 Authors     :  Hendrik van Gils    (s1920677)      h.vangils@student.utwente.nl
                Deniz Ugurlu        (s1797735)      d.a.ugurlu@student.utwente.nl
 Version     :  1.0
 License     :  None.
 Description :  The aims of this file are to make a flexible system where different packages can be created and their shipping costs displayed.
==============================================================
*/

#include <iostream>
#include <string>
#include <vector>
#include "Package.h"            // Base class
#include "OvernightPackage.h"   // Derived class
#include "TwoDayPackage.h"      // Derived class
#include "functions.cpp"        // The printCosts() function

int main()
{
    TwoDayPackage twoDayPackage0(1,"Joop","Hopelane 12","Brightholme","Sanctum","71239 XH");        // Construct shipping method
    OvernightPackage overnightPackage0(1,"Joop","Hopelane 12","Brightholme","Sanctum","71239 XH");  // Package may be created without info of the sender
    Package *package0 = &twoDayPackage0;                                                            // Package pointer to the first shipping method
    Package *package1 = &overnightPackage0;                                                         // Package pointer to the second shipping method
    std::vector<Package*> packages = {package0, package1};                                          // Add packages to package pointer "packages"
    printCosts(packages);                                                                           // Print the costs of packages
    return 0;
}