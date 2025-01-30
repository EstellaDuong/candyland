#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "functions.h"

using namespace std;

struct Candy
{
    string name;
    string description;
    string effect_type;
    int effect_value;
    string candy_type;
    double price;
};

class Player
{
    public: 
    Player();
    Player(string, int, double, Candy[], const int);

    //getters and setters
    int getPosition() const;
    void setPosition(int);

    string getName() const;
    void setName(string);

    string getCharacter() const;
    void setCharacter(string);

    int getCandyAmount() const;
    void setCandyAmount(int);
    int getMaxCandyAmount() const;

    void setStamina(int);
    int getStamina() const;

    void setGold(double);
    double getGold() const;

    int getPlayerNumber() const;
    void setPlayerNumber(double);

    void setInventory(int, Candy);
    Candy getInventoryAtIndex(int) const;
    
    void setRobbersRepel(bool);
    bool getRobbersRepel() const;

    void resetTurnsSkipped();
    void incrementTurnsSkipped();
    int getTurnsSkipped() const;
    void setTurnsSkipped(int turns);

    //other functions 
    void printInventory() const;
    void printPlayerInfo() const; 
    Candy findCandyInventory(string);
    bool addCandy(Candy);
    bool removeCandy(string);
        
    private:
        string _name;
        string _character;
        int _stamina;
        double _gold;
        int _player_number; 
        const static int _MAX_CANDY_AMOUNT = 9;
        Candy _inventory[_MAX_CANDY_AMOUNT];
        int _candy_amount;
        int _position;
        bool _has_robbers_repel;
        int _turns_skipped;
        



        
};

#endif