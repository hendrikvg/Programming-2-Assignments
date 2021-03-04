#include <iostream>
#include <string>
#include <vector>

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
    // Package(float weightIn=0, std::string nameRecipientIn="unkown", std::string addressRecipientIn="unkown", 
    // std::string cityRecipientIn="unkown", std::string stateRecipientIn="unkown", 
    // std::string ZIPcodeRecipientIn="unkown", std::string nameSenderIn="unkown", 
    // std::string addressSenderIn="unkown", std::string citySenderIn="unkown", 
    // std::string stateSenderIn="unkown", std::string ZIPcodeSenderIn="unkown")
    // {
    //     if (nameRecipientIn=="unkown" || addressRecipientIn=="unkown" || weightIn <= 0 ||
    //     cityRecipientIn=="unkown" || stateRecipientIn=="unkown" || ZIPcodeRecipientIn=="unkown")
    //     {
    //         // std::cerr << "Missing information about recipient or package (weight).\n";
    //     } else {
    //         weight = weightIn;
    //         nameRecipient = nameRecipientIn;
    //         addressRecipient = addressRecipientIn;
    //         cityRecipient = cityRecipientIn;
    //         stateRecipient = stateRecipientIn;
    //         ZIPcodeRecipient = ZIPcodeRecipientIn;
    //         nameSender = nameSenderIn;
    //         addressSender = addressSenderIn;
    //         citySender = citySenderIn;
    //         stateSender = stateSenderIn;
    //         ZIPcodeSender = ZIPcodeSenderIn;
    //     }
    // }

    virtual float calculateCost() const {}
};

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

    float calculateCost() const override
    {
        return 2.5*weight + 5;
    }
};

class OvernightPackage: public Package
{
public:
    OvernightPackage(float weightIn=0, std::string nameRecipientIn="unkown", std::string addressRecipientIn="unkown", 
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

    float calculateCost() const override
    {
        return 2.5*weight + 5 + 1.10*weight*weight;
    }
};

void printCosts(std::vector<Package*> packages)
{
    for (size_t i = 0; i < packages.size(); i++)
    {
        printf("Cost of shipping package %i is: %.2f \n",i + 1, packages[i]->calculateCost());
    }
}

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