#include "RealEstate.h"
#include "Properties.h"
#include <iostream>
#include <conio.h>
#include <cstdlib> 
#include <string>
#include "fun_console.h"

using namespace std;

void RealEstate::displayMenu()
{
    SetColor(15, 0);
    cout << "Choose an action:\n";
    cout << "1 - Create an account\n";
    cout << "2 - Log in to an existing account\n";
    cout << "3 - Exit the program\n";
}

void RealEstate::startProgram() {
    int choice;
    do {
        displayMenu();
        cout << "Enter your choice: ";
        if (!(cin >> choice))
        {
            system("cls");
            SetColor(12, 0);
            cout << "Wrong choice.Try again.\n";
            cin.clear();
            while (cin.get() != '\n')
                continue;
            continue;
        }

        switch (choice) {
        case 1:
            system("cls");
            createUser();
            break;
        case 2:
            system("cls");
            loginUser();
            break;
        case 3:
            SetColor(13, 0);
            cout << "Exiting the program.\n";
            break;
        default:
            system("cls");
            SetColor(12, 0);
            cout << "Wrong choice.Try again.\n";
        }

        if (choice == 3) {
            break;
        }

    } while (choice != 3);
}


void RealEstate::createUser()
{
    string newUsername;
    string newPassword;
    string newPhoneNumber;
    bool isBroker;

    while (true)
    {
        SetColor(15, 0);
        cout << "Enter your desired username: ";
        getline(cin, newUsername);

        bool usernameExists = false;

        for (User& user : users)
        {
            if (user.getUsername() == newUsername)
            {
                usernameExists = true;
                SetColor(12, 0);
                cout << "Username already exists. Please choose another.\n";
                break;
            }
        }

        if (!usernameExists && !newUsername.empty())
        {
            break; 
        }
    }

    bool hasDigit = false;
    bool hasSpecialChar = false;

    while (true)
    {
        SetColor(15, 0);
        cout << "Enter a strong password (at least one digit and one of $,% or _): ";
        getline(cin, newPassword);

        for (char c : newPassword)
        {
            if (isdigit(c))
            {
                hasDigit = true;
            }
            else if (c == '$' || c == '%' || c == '_')
            {
                hasSpecialChar = true;
            }

            if (hasDigit && hasSpecialChar)
            {
                break;
            }
        }

        if (!(hasDigit && hasSpecialChar))
        {
            SetColor(12, 0);
            cout << "Password is not strong. Please choose another.\n";
        }

        if (hasDigit && hasSpecialChar)
        {
            break;
        }
    }

    while (true)
    {
        SetColor(15, 0);
        cout << "Enter your phone number (Israeli mobile, 10 digits, starts with 05): ";
        getline(cin, newPhoneNumber);

        if (!isValidIsraeliMobile(newPhoneNumber))
        {
            SetColor(12, 0);
            cout << "Invalid phone number. Please enter a valid Israeli mobile number.\n";
        }
        else
        {
            break;
        }
    }

    while (true)
    {
        SetColor(15, 0);
        cout << "Are you a broker? (Y - yes, N - no): \n";
        char brokerChoice;
        brokerChoice = _getch();

        if (toupper(brokerChoice) == 'Y' || toupper(brokerChoice) == 'N')
        {
            isBroker = (toupper(brokerChoice) == 'Y');
            break;
        }
        else
        {
            SetColor(12, 0);
            cout << "\nInvalid choice. Please enter Y for yes or N for no: ";
        }
    }

    User newUser(newUsername, newPassword, newPhoneNumber, isBroker);
    addUser(newUser);

    SetColor(2, 0);
    cout << "User created successfully!\n";
}


bool RealEstate::isValidIsraeliMobile(string& phoneNumber)
{
    if (phoneNumber.size() != 10 || phoneNumber.substr(0, 2) != "05")
    {
        return false;
    }

    for (char c : phoneNumber)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }

    return true;
}

vector<string> RealEstate::getUniqueCities(vector<Address>& addresses) {
    vector<string> uniqueCities;
    for (Address& address : addresses) {
        string& city = address.getCity();
        if (find(uniqueCities.begin(), uniqueCities.end(), city) == uniqueCities.end()) {
            uniqueCities.push_back(city);
        }
    }
    return uniqueCities;
}

vector<string> RealEstate::getStreetsForCity(vector<Address>& addresses, string& city) {
    vector<string> streetsForCity;
    for (Address& address : addresses) {
        if (address.getCity() == city) {
            string& street = address.getStreet();
            if (find(streetsForCity.begin(), streetsForCity.end(), street) == streetsForCity.end()) {
                streetsForCity.push_back(street);
            }
        }
    }
    return streetsForCity;
}




bool RealEstate::postNewProperty(User& loggedInUser) {
    int maxProperties = loggedInUser.getIsBroker() ? 10 : 3;
    if (loggedInUser.getPublishedPropertiesCount() >= maxProperties) {
        cout << "You have reached the limit for the number of published properties.\n";
        return false;
    }

    cout << "List of cities in the system:\n";
    vector<string> uniqueCities = getUniqueCities(addresses);
    for (string& city : uniqueCities) {
        cout << city << endl;
    }

    string chosenCity;
    cout << "Enter the city name from the list: ";
    cin.ignore();
    getline(cin, chosenCity);

    auto cityIt = find(uniqueCities.begin(), uniqueCities.end(), chosenCity);
    if (cityIt == uniqueCities.end()) {
        cout << "The chosen city name does not exist in the system.\n";
        return false;
    }

    cout << "List of streets for the city " << chosenCity << ":\n";
    vector<string> streetsForCity = getStreetsForCity(addresses, chosenCity);
    for (const string& street : streetsForCity) {
        cout << street << endl;
    }

    string chosenStreet;
    cout << "Enter the street name from the list: ";
    getline(cin, chosenStreet);

    auto streetIt = find(streetsForCity.begin(), streetsForCity.end(), chosenStreet);
    if (streetIt == streetsForCity.end()) {
        cout << "The chosen street name does not exist in the system.\n";
        return false;
    }

    unsigned int rooms = 0, houseNum = 0;
    double price = 0;
    int floorNum = 0;
    bool forRent;
    string type;

    cout << "Choose the type of property (1 - standard apartment, 2 - penthouse, 3 - private house): ";
    while (!(cin >> type) || (type != "1" && type != "2" && type != "3")) {
        cout << "Invalid input. Please enter 1, 2, or 3: ";
        cin.clear();
        while (cin.get() != '\n');
    }

    if (type == "1") {
        cout << "On which floor is the property located? ";
        while (!(cin >> floorNum) || cin.peek() != '\n') {
            cout << "Invalid input. Please enter a numeric value: ";
            cin.clear();
            while (cin.get() != '\n');
        }
    }
    else if (type == "2") { 
        cout << "On which floor is the penthouse located? ";
        while (!(cin >> floorNum) || cin.peek() != '\n') {
            cout << "Invalid input. Please enter a numeric value: ";
            cin.clear();
            while (cin.get() != '\n');
        }
    }
    else if (type == "3") {
        cout << "Enter the number of rooms in the house: ";
        while (!(cin >> rooms) || cin.peek() != '\n') {
            cout << "Invalid input. Please enter a numeric value: ";
            cin.clear();
            while (cin.get() != '\n');
        }

        cout << "Enter the house number: ";
        while (!(cin >> houseNum) || cin.peek() != '\n') {
            cout << "Invalid input. Please enter a numeric value: ";
            cin.clear();
            while (cin.get() != '\n');
        }
    }
    else {
        cout << "Invalid property type selected.\n";
        return false;
    }

    cout << "Is the property for rent? (1 - Yes, 0 - No): ";
    while (!(cin >> forRent) || (forRent != 0 && forRent != 1) || cin.peek() != '\n') {
        cout << "Invalid input. Please enter 0 or 1: ";
        cin.clear();
        while (cin.get() != '\n');
    }

    cout << "Enter the price for the property: ";
    while (!(cin >> price) || cin.peek() != '\n') {
        cout << "Invalid input. Please enter a numeric value: ";
        cin.clear();
        while (cin.get() != '\n');
    }

    Address propertyAddress(chosenCity, chosenStreet);
    Properties newProperty(propertyAddress, rooms, price, type, forRent, houseNum, floorNum, loggedInUser);
    properties.push_back(newProperty);

    loggedInUser.incrementPublishedPropertiesCount();

    cout << "Property successfully posted!\n";
    return true;
}

void RealEstate::removeProperty(User& loggedInUser) {
    if (loggedInUser.getPublishedPropertiesCount() == 0) {
        cout << "You haven't published any properties yet.\n";
        return;
    }

    cout << "Your published properties:\n";
    int propertyCount = 1;
    for (Properties& property : properties) {
        if (property.getUserOwner().getUsername() == loggedInUser.getUsername()) {
            cout << propertyCount << ". " << property.getAddress().getCity() << ", "
                << property.getAddress().getStreet() << ", Property Type: " << property.getType() << endl;
            propertyCount++;
        }
    }

    int chosenProperty;
    cout << "Enter the number of the property you want to remove: ";
    cin >> chosenProperty;

    if (chosenProperty < 1 || chosenProperty >= propertyCount) {
        cout << "Invalid property number.\n";
        return;
    }

    int propertyIndex = 1;
    for (auto it = properties.begin(); it != properties.end(); ++it) {
        if (it->getUserOwner().getUsername() == loggedInUser.getUsername()) {
            if (propertyIndex == chosenProperty) {
                it = properties.erase(it);
                cout << "Property successfully removed.\n";
                return;
            }
            propertyIndex++;
        }
    }
}

void RealEstate::printAllProperties() {
    if (properties.empty()) {
        cout << "There are no assets in the system.\n";
        return;
    }

    cout << "List of all assets in the system: \n";
    for (Properties& property : properties) {
        cout << "City: " << property.getAddress().getCity() << ", Street: " << property.getAddress().getStreet()
            << ", Type: " << property.getType() << ", Price: " << property.getPrice() << "\n";
    }
}

void RealEstate::printAllProperties(User& user) {
    cout << "Properties published by user " << user.getUsername() << ":\n";
    for (Properties& property : properties) {
        if (property.getUserOwner() == user) {
            cout << "City: " << property.getAddress().getCity() << ", Street: " << property.getAddress().getStreet()
                << ", Type: " << property.getType() << ", Price: " << property.getPrice() << "\n";
        }
    }
}

vector<Properties> RealEstate::searchPropertiesByParameters() {
    vector<Properties> resultProperties;

    int forRent;
    cout << "For rent or for sale? (1 - For Rent, 2 - For Sale, 999 - Any): ";

    while (!(cin >> forRent) || (forRent != 1 && forRent != 2 && forRent != 999)) {
        cout << "Invalid input. Please enter 1, 2, or 999: ";
        cin.clear();
        while (cin.get() != '\n');
    }

    string desiredType;
    cout << "What type of property are you looking for? (Enter 999 to ignore): ";
    cin >> desiredType;

    unsigned int desiredNumRooms;
    cout << "Desired number of rooms? (Enter 999 to ignore): ";
    while (!(cin >> desiredNumRooms) || cin.peek() != '\n') {
        cout << "Invalid input. Please enter a numeric value: ";
        cin.clear();
        while (cin.get() != '\n');
    }

    double minPrice, maxPrice;
    cout << "Minimum price range (Enter 999 to ignore): ";
    while (!(cin >> minPrice) || cin.peek() != '\n') {
        cout << "Invalid input. Please enter a numeric value: ";
        cin.clear();
        while (cin.get() != '\n');
    }

    cout << "Maximum price range (Enter 999 to ignore): ";
    while (!(cin >> maxPrice) || cin.peek() != '\n') {
        cout << "Invalid input. Please enter a numeric value: ";
        cin.clear();
        while (cin.get() != '\n');
    }

    for (Properties& property : properties) {
        if ((forRent == 999 || property.getIsForRent() == static_cast<bool>(forRent - 1)) &&
            (desiredType == "999" || property.getType() == desiredType) &&
            (desiredNumRooms == 999 || property.getNumRooms() == desiredNumRooms) &&
            (minPrice == 999 || property.getPrice() >= minPrice) &&
            (maxPrice == 999 || property.getPrice() <= maxPrice)) {
            resultProperties.push_back(property);
        }
    }

    return resultProperties;
}



User* RealEstate::loginUser() {
    string enteredUsername;
    string enteredPassword;
    User* loggedInUser = nullptr;

    cout << "Enter your username: ";
    cin >> enteredUsername;

    cout << "Enter your password: ";
    cin >> enteredPassword;

    for (auto& user : users) {
        if (user.getUsername() == enteredUsername && user.getPassword() == enteredPassword) {
            loggedInUser = &user;
            user.setLoggedIn(true); 
            cout << "Login successful!\n";

            int loggedInChoice;
            do {
                cout << "Choose an action:\n"
                    << "1 - Place new property\n"
                    << "2 - Remove advertisement on a property\n"
                    << "3 - View all assets in the system\n"
                    << "4 - View assets published by the user\n"
                    << "5 - Search for properties by parameters\n"
                    << "6 - Log out and return to the main menu\n"
                    << "Enter your choice: ";

                if (!(cin >> loggedInChoice)) {
                    cout << "Invalid input. Please enter a number.\n";
                    cin.clear();
                    while (cin.get() != '\n')
                        continue;
                    continue;
                }

                switch (loggedInChoice) {
                case 1:
                    system("cls");
                    postNewProperty(*loggedInUser);
                    break;
                case 2:
                    system("cls");
                    removeProperty(*loggedInUser);
                    break;
                case 3:
                    system("cls");
                    printAllProperties();
                    break;
                case 4:
                    system("cls");
                    printAllProperties(*loggedInUser);
                    break;
                case 5:
                    system("cls");
                    searchPropertiesByParameters();
                    break;
                case 6:
                    cout << "Logging out and returning to the main menu.\n";
                    user.setLoggedIn(false);
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
                }
            } while (loggedInChoice != 6);

            return loggedInUser;
        }
    }

    cout << "Invalid username or password. Login failed.\n";
    return nullptr;
}

