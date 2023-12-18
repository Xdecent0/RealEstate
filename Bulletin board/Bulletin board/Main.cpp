#include <iostream>
#include "RealEstate.h"
#include "Address.h"

using namespace std;

int main()
{
    RealEstate realEstate;
    Address address1("Kyiv", "Khreschatyk Street");
    Address address2("Lviv", "Rynok Square");
    Address address3("Kharkiv", "Svobody Avenue");
    Address address4("Odesa", "Deribasovskaya");
    Address address5("Kyiv", "Vladimirskaya");
    Address address6("Lviv", "Shevchenko");
    Address address7("Kherson", "Suvorova Street");
    Address address8("Dnipro", "8 March Street");
    Address address9("Odesa", "Primorsky Boulevard");
    Address address10("Zaporizhzhia", "Lenina Avenue");

    realEstate.addAddress(address1);
    realEstate.addAddress(address2);
    realEstate.addAddress(address3);
    realEstate.addAddress(address4);
    realEstate.addAddress(address5);
    realEstate.addAddress(address6);
    realEstate.addAddress(address7);
    realEstate.addAddress(address8);
    realEstate.addAddress(address9);
    realEstate.addAddress(address10);

    realEstate.startProgram();

    return 0;

}
