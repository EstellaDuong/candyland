#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string.h>
#include <cmath>

#include "Board.h"
#include "Player.h"
#include "CandyStore.h"
#include "Tiles.h"
#include "Printing.h"
#include "HiddenTreasures.h"
#include "functions.h"



class Game
{
    public:
        Game();

        //functions to call before game starts 
        Candy findCandyAvailable(string);
        vector<Player> readCharactersFile(string, vector<Player>);
        vector<Candy> readAvailableCandyFile(string, vector<Candy>);
        //note: randomlySetStoreLocations() is in Board
        Candy randomCandy() const; 
        CandyStore randomStore() const;         

        //getters and setters
        vector<Candy> getAvailableCandies() const;
        void setAvaialableCandies(vector<Candy>);
        vector<Player> getAvailableCharacters() const;
        void setAvaialableCharacters(vector<Player>);
        vector<int> getGummyTiles() const;

        //functions for different events
        Player runSpecialTile(int, int, Player, Tiles, Printing);
        Player checkStaminaAndDeplete(Player);
        void useCandy(Candy selected_candy, Player players[], int i, Printing print, int num_players, HiddenTreasures treasure);
        Player calamity(Player player);
        bool playRockPaperScissors(Player);

        //other
        bool isOnRegularTile(Player players[], int i, int num_players, Board board, Tiles tile, HiddenTreasures treasure);


    private:
        const static int _MAX_CANDY_AMOUNT = 9;
        vector<Candy> _availableCandies;
        vector<Player> _availableCharacters;
        vector<int> _gummy_tiles;

};

#endif

