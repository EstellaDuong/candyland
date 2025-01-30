#include "Board.h"
#include "CandyStore.h"

//constructors
CandyStore::CandyStore()
{
    _store_name = "No Name";
    _store_inventory[0] = Candy{"", "", "", 0, "", 0};
    _store_inventory[1] = Candy{"", "", "", 0, "", 0};
    _store_inventory[2] = Candy{"", "", "", 0, "", 0};
}
CandyStore::CandyStore(string name)
{
    _store_name = name;
    _store_inventory[0] = Candy{"", "", "", 0, "", 0};
    _store_inventory[1] = Candy{"", "", "", 0, "", 0};
    _store_inventory[2] = Candy{"", "", "", 0, "", 0};
}
CandyStore::CandyStore(Candy candies[])
{
    _store_name = "No Name";
    _store_inventory[0] = candies[0];
    _store_inventory[1] = candies[1];
    _store_inventory[2] = candies[2];
}

//setters and getters
string CandyStore::getStoreName() const
{
    return _store_name;
}
void CandyStore::setStoreName(string name)
{
    _store_name = name;
}
Candy CandyStore::getInventory(int index) const
{
    return _store_inventory[index];
}
void CandyStore::setInventory(int index, Candy candy)
{
    _store_inventory[index] = candy; 
}

//functions

void CandyStore::printStore()
{
    // cout<<"Candies present in " << _store_name << " are: " << endl; 
    cout<<ORANGETEXT<<"Here are the candies avaialable to buy: "<<RESET<<endl;
    for(int i=0; i<3; i++)
    {
        cout<<ORANGETEXT<<"-------------------------------------------"<<RESET<<endl;
        if(_store_inventory[i].name == "")
        {
            cout<<"Out of stock"<<endl; 
        }
        else
        {
            cout<<ORANGETEXT<<"Name: "<<YELLOWTEXT<<_store_inventory[i].name<<RESET<<endl;
            cout<<ORANGETEXT<<"Description: "<<_store_inventory[i].description<<RESET<<endl;
            cout<<ORANGETEXT<<"Price: "<<_store_inventory[i].price<<RESET<<endl;
            cout<<ORANGETEXT<<"Type: "<<_store_inventory[i].candy_type<<RESET<<endl;
        }
    }
    cout<<ORANGETEXT<<"-------------------------------------------"<<RESET<<endl;
}

void CandyStore::addCandy(Candy candy)
{
    if(_store_inventory[_MAX_INVENTORY-1].name!="")
    {
        cout<<"No space in inventory to add candy."<<endl;
    }
    else
    {
        for (int i=0; i<_MAX_INVENTORY; i++)
        {
            if(_store_inventory[i].name=="")
            {
                _store_inventory[i] = candy; 
                return;
            }
        }
    }
}