#pragma once
#include "Address.h"
#include <string>
#include <vector>
#include "User.h"

using namespace std;

class Properties
{
private:
    Address address;
    unsigned int numRooms;
    double price;
    string type;
    bool isForRent;
    unsigned int houseNumber;
    int floorNumber;
    User userOwner;

public:
    Properties(Address& addr, unsigned int rooms, double p, string& t,
        bool forRent, unsigned int houseNum, int floorNum, User owner)
        : address(addr), numRooms(rooms), price(p), type(t),
        isForRent(forRent), houseNumber(houseNum), floorNumber(floorNum), userOwner(owner) {}

    vector<string> getUniqueCities(vector<Properties>& properties);

    Address& getAddress() { return address; }
    string& getCity() { return address.getCity(); }
    User getUserOwner()  {return userOwner;}
    string& getType() { return type; }
    double getPrice() { return price; }
    bool getIsForRent()  { return isForRent; }
    unsigned int getNumRooms()  { return numRooms; }
    string toString();
    bool operator==(Properties& other) { return userOwner == other.userOwner;}
};
