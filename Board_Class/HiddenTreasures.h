#ifndef HIDDENTREASURES_H
#define HIDDENTREASURES_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>

#include "Player.h"
#include "functions.h"

using namespace std;

struct Riddle
{
    string question;
    string answer;
};

class HiddenTreasures
{
    public:
        HiddenTreasures();
        int getTreasureLocations(int) const;
        void setTreasureLocations(int, int);
        Player staminaRefill(Player);
        Player goldWindfall(Player);
        Player robbersRepel(Player);
        Player candyAquisition(Player);
        Player runHiddenTreasure(Player);

        void readRiddleFile(string file_name);
        bool solveRiddle();


    private:
        int _treasure_locations[3];
        vector<Riddle> _riddles;

};

#endif