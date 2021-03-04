#ifndef TWODAYPACKAGE_H
#define TWODAYPACKAGE_H
#include "Package.h"

class TwoDayPackage: public Package
{
public:
    TwoDayPackage(float weightIn=0, std::string nameRecipientIn="unkown", std::string addressRecipientIn="unkown", 
    std::string cityRecipientIn="unkown", std::string stateRecipientIn="unkown", 
    std::string ZIPcodeRecipientIn="unkown", std::string nameSenderIn="unkown", 
    std::string addressSenderIn="unkown", std::string citySenderIn="unkown", 
    std::string stateSenderIn="unkown", std::string ZIPcodeSenderIn="unkown")
    {
        if (nameRecipientIn=="unkown" || addressRecipientIn=="unkown" || weightIn <= 0 ||
        cityRecipientIn=="unkown" || stateRecipientIn=="unkown" || ZIPcodeRecipientIn=="unkown")
        {
            std::cerr << "Missing information about recipient or package (weight).\n";
        } else {
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

    float calculateCost() override
    {
        return 2.5*weight + 5;
    }
};

#endif