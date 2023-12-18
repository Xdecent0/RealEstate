#include "Properties.h"

string Properties::toString() {
    string propertyType;
    if (type == "Standard Apartment") {
        propertyType = "Standard Apartment";
    }
    else if (type == "Penthouse") {
        propertyType = "Penthouse";
    }
    else if (type == "Private House") {
        propertyType = "Private House";
    }

    string operationType = isForRent ? "For Rent" : "For Sale";
    string floorInfo = floorNumber >= 0 ? "Floor " + to_string(floorNumber) : "";
    string propertyInfo = propertyType + ": " + to_string(numRooms) + " rooms, " + floorInfo + ".\n"
        + "Price: " + to_string(price) + " dollars.\n"
        + "Contact Information: " + userOwner.getUsername() + " " + userOwner.getPhoneNumber() + " (" + (userOwner.getIsBroker() ? "Broker" : "Individual") + ")";

    return operationType + "\n" + propertyInfo;
}
