#pragma once
#include <string>

using namespace std;

class Address
{
private: 
	string city;
	string street;

public:
	Address(string c, string s) : city(c), street(s) {}

	string& getCity() { return city; }
	string& getStreet() { return street; }

	string toString()  {return city + ", " + street;}
};

