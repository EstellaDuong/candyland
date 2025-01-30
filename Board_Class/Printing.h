#ifndef PRINTING_H
#define PRINTING_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <cstring>


#include "Board.h"
#include "Player.h"
#include "CandyStore.h"
#include "functions.h"

class Printing
{
    public:
    Printing();
    
    // functions to check for valid input
    int checkInt(int, int, int);
    bool checkStringMatch(string, string);
    Player checkNameMatchInPlayerVec(string, vector<Player>);
    Player checkNameMatchInPlayerArr(string name, Player players[], int size);
    int findIndexOfPlayerInArr(string name, Player players[], int size);

    //functions that print and get info
    int enterNumPlayers();
    string enterPlayerName(int);
    Player selectCharacter(vector<Player>); //does NOT remove the character from the vector, must do in driver
    int enterMenuOption(string);
    Player shopCandyStore(Player player, CandyStore stores[], int location, Board board);
    int foundCandy(string candy, CandyStore current_store);
    Candy foundCandy(string candy, Player player);
    bool hasEnoughGold(Player player, CandyStore store);
    
    
    private:


};


#endif