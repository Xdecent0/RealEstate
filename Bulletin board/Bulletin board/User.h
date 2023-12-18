#pragma once

#include <string>

using namespace std;

class User {
private:
    string username;
    string password;
    string phoneNumber;
    bool isBroker;
    bool isLoggedIn;
    int publishedPropertiesCount;

public:
    User( string& name, string& pass, string& phone, bool broker)
        : username(name), password(pass), phoneNumber(phone), isBroker(broker), publishedPropertiesCount(0) {}

    string getUsername() { return username; }
    string getPassword() { return password; }
    string getPhoneNumber() { return phoneNumber; }
    bool getIsBroker() { return isBroker; }
    int getPublishedPropertiesCount() const { return publishedPropertiesCount; }
    void incrementPublishedPropertiesCount() { publishedPropertiesCount++; }
    void setLoggedIn(bool status) { isLoggedIn = status; }
    bool isLoggedInStatus() { return isLoggedIn; }

    string toString() {return "Username: " + username + "\nPhone Number: " + phoneNumber + "\nBroker: " + (isBroker ? "Yes" : "No");}

    bool operator==( User& other) { return username == other.username;}
};
