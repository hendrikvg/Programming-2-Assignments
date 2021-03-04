#include <iostream>
#include <string>
#ifndef PACKAGE_H
#define PACKAGE_H

class Package
{
protected:
    float weight;
    std::string nameRecipient;
    std::string addressRecipient;
    std::string cityRecipient;
    std::string stateRecipient;
    std::string ZIPcodeRecipient;

    std::string nameSender;
    std::string addressSender;
    std::string citySender;
    std::string stateSender;
    std::string ZIPcodeSender;

public:
    // Uitzoeken of deze constructor wel noodzakelijk is
    Package(float weightIn = 0, std::string nameRecipientIn = "unkown", std::string addressRecipientIn = "unkown",
            std::string cityRecipientIn = "unkown", std::string stateRecipientIn = "unkown",
            std::string ZIPcodeRecipientIn = "unkown", std::string nameSenderIn = "unkown",
            std::string addressSenderIn = "unkown", std::string citySenderIn = "unkown",
            std::string stateSenderIn = "unkown", std::string ZIPcodeSenderIn = "unkown")
    {
        if (nameRecipientIn == "unkown" || addressRecipientIn == "unkown" || weightIn <= 0 ||
            cityRecipientIn == "unkown" || stateRecipientIn == "unkown" || ZIPcodeRecipientIn == "unkown")
        {
            std::cerr << "Missing information about recipient or package (weight).\n";
        }
        else
        {
            weight = weightIn;
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
        }
    }

    virtual float calculateCost(){};
};

#endif