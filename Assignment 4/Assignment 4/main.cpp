#include <iostream>
#include <string>
#include <vector>
#include "Package.h"
#include "OvernightPackage.h"
#include "TwoDayPackage.h"
#include "functions.cpp"

int main()
{
    TwoDayPackage twoDayPackage0(1,"Joop","Hopelane 12","Brightholme","Sanctum","71239 XH");
    OvernightPackage overnightPackage0(1,"Joop","Hopelane 12","Brightholme","Sanctum","71239 XH");
    Package *package0 = &twoDayPackage0;
    Package *package1 = &overnightPackage0;
    std::vector<Package*> packages = {package0, package1};
    printCosts(packages);
    return 0;
}