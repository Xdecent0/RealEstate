#pragma once

#include <iostream>
#include <vector>
#include "User.h"
#include "Properties.h"
#include "Address.h"

using namespace std;
class RealEstate {
private:
    vector<User> users;
    vector<Properties> properties;
    vector<Address> addresses;

public:
    void addUser( User& user) { users.push_back(user); }

    vector<User>& getUsers()  { return users; }

    void addProperty(Properties& property) { properties.push_back(property); }

    vector<Properties>& getProperties() { return properties; }

    void addAddress(Address& address) { addresses.push_back(address); }

    vector<Address>& getAddresses()  { return addresses; }
    void startProgram();
    void displayMenu();
    void createUser();
    User* loginUser();
    bool isValidIsraeliMobile(string& phoneNumber);
    bool postNewProperty(User& loggedInUser);
    void removeProperty(User& loggedInUser);
    void printAllProperties();
    void printAllProperties(User& user);
    vector<Properties> searchPropertiesByParameters();
    vector<string> getUniqueCities(vector<Address>& addressess);
    vector<string> getStreetsForCity(vector<Address>& addresses,  string& city);

};
