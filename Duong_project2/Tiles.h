#ifndef TILES_H
#define TILES_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>

#include "Player.h"
#include "Board.h"
#include "functions.h"

using namespace std;

class Tiles
{
    public:
    //constructors
    Tiles();

    int getSpecialTile(int, int) const;
    int getMaxSpecialTiles() const;

    //regular tiles
    int movesNextColor(int, int); 
    int drawCard(int);

    //special tiles
    void printSpecialTileLocations() const; //for testing purposes only
    bool checkDuplicateSpecialTile(int);
    void randomizeTilePositions(Board);
    int checkIfOnSpecialTile(int);
    // Player runSpecialTile(Player);        

    //same tile constraints
    Player updateRobber(Player, Player, int);    
    Player updateVictim(Player, int);    
    bool onSameTile(Player player1, Player player2);                                                                                           

    private:
    const static int _MAX_SPECIAL_TILES = 4;
    int _special_tiles[4][_MAX_SPECIAL_TILES]; //row 0=shortcut, 1=icecream, 2=gumdrop, 3=gingerbread
};

#endif