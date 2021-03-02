#include <string>


using namespace std;

// Base Class

class Package {
    public:
        Package(double weightIn, string nameSenderIn, string addressSenderIn, string citySenderIn, string stateSenderIn, string zipCodeSenderIn, 
        string nameReceiverIn, string addressReceiverIn, string cityReceiverIn, string stateReceiverIn, string zipCodeReceiverIn) {

            weight = weightIn;
            
            nameSender = nameSenderIn;
            addressSender = addressSenderIn;
            citySender = citySenderIn;
            stateSender = stateSenderIn;
            zipCodeSender = zipCodeSenderIn;

            nameReceiver = nameReceiverIn;
            addressReceiver = addressReceiverIn;
            cityReceiver = cityReceiverIn;
            stateReceiver = stateReceiverIn;
            zipCodeReceiver = zipCodeReceiverIn;

        }


    private:
        double weight;

        string nameSender;
        string addressSender;
        string citySender;
        string stateSender;
        string zipCodeSender;

        string nameReceiver;
        string addressReceiver;
        string cityReceiver;
        string stateReceiver;
        string zipCodeReceiver;



}

// Class TwoDayPackage derived from Package

class TwoDayPackage: public Package {
    private:

    public: 
        //constructor
        //destructor
    double calculateCost(){
        return 2.5*weight + 5;
    }

}

// Class OvernightPackage derived from Package

class OvernightPackage: public Package {
    private:

    public: 
    //constructor
    //destructor
    double calculateCost(){
        return (1.1*weight + 2.50)*weight + 5;
    }
}

