#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#define RED "\033[;41m"     /* Red */
#define GREEN "\033[;42m"   /* Green */
#define BLUE "\033[;44m"    /* Blue */
#define MAGENTA "\033[;45m" /* Magenta */
#define CYAN "\033[;46m"    /* Cyan */
#define ORANGE "\033[48;2;230;115;0m"  /* Orange (230,115,0)*/
#define RESET "\033[0m"
#include "Player.h"

using namespace std;

// struct Candy
// {
//     string name;
//     string description;
//     double price;
//     string candy_type;
// };

struct Tile
{
    string color;
    string tile_type;
};


class Board
{
private:
    const static int _BOARD_SIZE = 83;
    Tile _tiles[_BOARD_SIZE];
    const static int _MAX_CANDY_STORE = 4;
    int _candy_store_position[_MAX_CANDY_STORE];
    int _candy_store_count; //delete
    int _player_position;

    vector<int> _special_tiles_locations;

    //multi player 
    const static int _MAX_PLAYERS = 4; //add getters and setters
    Player _players[_MAX_PLAYERS]; //add getters and setters
    int _num_players;//add =0 in constructor, setters,getters
    

public:
    Board();

    void resetBoard();
    void displayTile(int);
    void displayBoard();

    bool setPlayerPosition(int);
    void setStorePositions(int, int, int, int);
    void randomlySetStorePositions();

    int getBoardSize() const;
    int getCandyStoreCount() const;
    int getPlayerPosition() const;
    int getCandyStoreIndex(int) const;
    void setNumPlayers(int);
    int getNumPlayers() const;

    bool addCandyStore(int);
    bool isPositionCandyStore(int); 

    bool movePlayer(int tile_to_move_forward);

    //functions added
    Player getPlayer(int) const; 
    int getStoreLocation(int) const;
    int getMaxCandyStore() const;
    void updatePlayers(Player[4], int);
    int getMaxPlayers() const;

    void addSpecialTileLocation(int);
    vector<int> getSpecialTilesLocations() const;
    int getNumSpecialTiles();
    int getSpecialTilesLocationAtIdx(int) const;


};

#endif