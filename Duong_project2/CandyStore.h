#ifndef CANDYSTORE_H
#define CANDYSTORE_H

#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "Board.h"

using namespace std; 

class CandyStore
{
    public:
        //constructors
        CandyStore();
        CandyStore(string);
        CandyStore(Candy[]);

        //getters and setters
        string getStoreName() const;
        void setStoreName(string);
        Candy getInventory(int) const; 
        void setInventory(int, Candy);

        //functions
        void printStore();
        void addCandy(Candy); 
        
    private:
        string _store_name; //might not be necessary
        int static const _MAX_INVENTORY = 3;
        Candy _store_inventory[_MAX_INVENTORY];




};

#endif