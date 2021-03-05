/*
==============================================================
 Filename    :  TwoDayPackage.h
 Authors     :  Hendrik van Gils    (s1920677)      h.vangils@student.utwente.nl
                Deniz Ugurlu        (s1797735)      d.a.ugurlu@student.utwente.nl
 Version     :  1.0
 License     :  None.
 Description :  The aims of this file are to make a class that inherits attributes attributes from the class Package and overrides the calculateCost() function.
==============================================================
*/

#ifndef TWODAYPACKAGE_H
#define TWODAYPACKAGE_H
#include "Package.h"

class TwoDayPackage : public Package
{
public:
    // Constructor
    // @param weightIn mass of the package in kg, default = 0
    // @param nameRecipientIn name of the recipient, default = "unknown"
    // @param addressRecipientIn address of the recipient, default = "unknown"
    // @param cityRecipientIn city of the recipient, default = "unknown"
    // @param stateRecipientIn state of the recipient, default = "unknown"
    // @param ZIPcodeRecipientIn ZIP code of the recipient, default = "unknown"
    // @param nameSenderIn name of the sender, default = "unknown"
    // @param addressSenderIn address of the sender, default = "unknown"
    // @param citySenderIn city of the sender, default = "unknown"
    // @param stateSenderIn state of the sender, default = "unknown"
    // @param ZIPcodeSenderIn ZIP code of the sender, default = "unknown"
    TwoDayPackage(float weightIn = 0, std::string nameRecipientIn = "unkown", std::string addressRecipientIn = "unkown",
                  std::string cityRecipientIn = "unkown", std::string stateRecipientIn = "unkown",
                  std::string ZIPcodeRecipientIn = "unkown", std::string nameSenderIn = "unkown",
                  std::string addressSenderIn = "unkown", std::string citySenderIn = "unkown",
                  std::string stateSenderIn = "unkown", std::string ZIPcodeSenderIn = "unkown")
    {
        if (nameRecipientIn == "unkown" || addressRecipientIn == "unkown" || weightIn <= 0 || // If the weight is 0 or lower or some data of the recipient is unknown
            cityRecipientIn == "unkown" || stateRecipientIn == "unkown" || ZIPcodeRecipientIn == "unkown")
        {
            std::cerr << "Missing information about recipient or package (weight).\n"; // Display error message
        }
        else
        {
            weight = weightIn; // If all data is ok, fill in values
            nameRecipient = nameRecipientIn;
            addressRecipient = addressRecipientIn;
            cityRecipient = cityRecipientIn;
            stateRecipient = stateRecipientIn;
            ZIPcodeRecipient = ZIPcodeRecipientIn;
            nameSender = nameSenderIn;
            addressSender = addressSenderIn;
            citySender = citySenderIn;
            stateSender = stateSenderIn;
            ZIPcodeSender = ZIPcodeSenderIn;
        } // endif
    }

    // calculateCost() calculates the cost of this package
    // @returns the cost as a floating number
    float calculateCost() override
    {
        return 2.5 * weight + 5;
    }
};

#endif