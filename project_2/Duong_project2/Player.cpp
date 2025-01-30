#include<iostream>
#include<vector>
#include<cmath>
#include <cstring>
#include "Player.h"

using namespace std;

Player::Player()
{
    _position = 0;
    _name = "No Name";
    _character = "";
    _stamina = 0;
    _gold = 0;
    _candy_amount = 0;
    for(int i=0; i<_MAX_CANDY_AMOUNT; i++)
    {
        _inventory[i] = Candy{"", "", "", 0, "", 0};
    }

    _has_robbers_repel = false;
    _turns_skipped = 0;
}
Player::Player(string name, int stamina, double gold, Candy candy_array[], const int CANDY_ARR_SIZE)
{
    _position = 0;
    _name = name;
    _character = "";
    _stamina = stamina;
    _gold = gold;
    _candy_amount = 0;
    for(int i=0; i<_MAX_CANDY_AMOUNT; i++)
    {
        _inventory[i] = Candy{"", "", "", 0, "", 0};
    }

    _has_robbers_repel = false;
    _turns_skipped = 0;

    for(int i=0; i<CANDY_ARR_SIZE; i++)
    {
        Candy current = candy_array[i];
        if (current.name!="" && current.description!="" && current.price!=0 && current.candy_type!="" && _candy_amount<_MAX_CANDY_AMOUNT)
        {
            _inventory[_candy_amount] = current;
            _candy_amount++;
        }
    }
}

//getters and setters
int Player::getPosition() const
{
    return _position;
}
void Player::setPosition(int pos)
{
    if(pos<0)
    {
        _position = 0;
    }
    else if(pos>82)
    {
        _position=82; 
    }
    else
    {
        _position = pos; 
    }
}
string Player::getName() const
{
    return _name;
}
void Player::setName(string name)
{
    _name = name;
}
string Player::getCharacter() const
{
    return _character;
}
void Player::setCharacter(string name)
{
    _character = name;
}
int Player::getCandyAmount() const
{
    return _candy_amount;
}
void Player::setCandyAmount(int amt)
{
    _candy_amount = amt;
}
int Player::getMaxCandyAmount() const
{
    return _MAX_CANDY_AMOUNT;
}
void Player::setRobbersRepel(bool has)
{
    _has_robbers_repel = has;
}
bool Player::getRobbersRepel() const
{
    return _has_robbers_repel; 
}
void Player::resetTurnsSkipped()
{
    _turns_skipped=0;
}
void Player::incrementTurnsSkipped()
{
    _turns_skipped++;
}
int Player::getTurnsSkipped() const
{
    return _turns_skipped;
}
void Player::setTurnsSkipped(int turns)
{
    _turns_skipped=turns;
}





void Player::printInventory() const
{
    for(int i=0; i<_MAX_CANDY_AMOUNT; i++)
    {
        if(_inventory[i].name == "Empty" || _inventory[i].name == "")
        {
            return;
        }   
        else if(i%3==0)
        {
            if(i>0)
            {
                cout<<endl;
            }
            cout<<"["<< _inventory[i].name << "]";
        }
        else
        {
            cout<<"  [" << _inventory[i].name << "]";
        }   
    }
}
void Player::setStamina(int stamina)
{
    if(stamina<0)
    {
        _stamina=0;
    }
    else if(stamina>100)
    {
        _stamina=100;
    }
    else
    {
        _stamina = stamina;
    }
}
int Player::getStamina() const
{
    return _stamina;
}
void Player::setGold(double gold)
{
    if(gold<0)
    {
        _gold=0;
    }
    else if(gold>100)
    {
        _gold=100;
    }
    else
    {
        _gold = gold;
    }
}
double Player::getGold() const
{
    return _gold;
}
void Player::setPlayerNumber(double num)
{
    _player_number = num;
}
int Player::getPlayerNumber() const
{
    return _player_number;
}
void Player::setInventory(int index, Candy candy)
{
    _inventory[index] = candy;
}
Candy Player::getInventoryAtIndex(int index) const
{
    return _inventory[index];
}

void Player::printPlayerInfo() const
{
    cout<<"Name: "<< _name<<endl;
    cout<<"Stamina: "<< _stamina<<endl;
    cout<<"Gold: "<< _gold<<endl;
    cout<<"Candies: "<<endl;
    printInventory(); 
    cout<<endl; 
}


Candy Player::findCandyInventory(string candy_name)
{
    for(int i=0; i<candy_name.length(); i++)
    {
        candy_name[i] = tolower(candy_name[i]);
    }
    for(int i=0; i<_MAX_CANDY_AMOUNT; i++)
    {
        Candy current = _inventory[i];
        for(int j=0; j<current.name.length(); j++)
        {
            current.name[j] = tolower(current.name[j]);
        }
        if(current.name==candy_name)
        {
            return _inventory[i];
        }
    }
    return Candy{"", "", "", 0, "", 0};
}

bool Player::addCandy(Candy candy)
{
    if(_candy_amount==_MAX_CANDY_AMOUNT)
    {
        return false;
    }
    else
    {
        _inventory[_candy_amount] = candy;
        _candy_amount++; 
        return true; 
    }
}

bool Player::removeCandy(string candy_name)
{
    for(int i=0; i<candy_name.length(); i++)
    {
        candy_name[i] = tolower(candy_name[i]);
    }

    for(int i=0; i<_MAX_CANDY_AMOUNT; i++)
    {
        string check=_inventory[i].name;
        for(int j=0; j<check.length(); j++)
        {
            check[j] = tolower(check[j]);
        }

        if(check == candy_name)
        {
            for(int k=i; k<_MAX_CANDY_AMOUNT-1; k++)
            {
                _inventory[k] = _inventory[k+1];
            }
            _inventory[_candy_amount-1] = Candy{"", "", "", 0, "", 0};
            _candy_amount--;
            return true;
        }
    }
    return false;
}

