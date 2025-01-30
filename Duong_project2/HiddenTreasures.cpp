#include "HiddenTreasures.h"

HiddenTreasures::HiddenTreasures()
{
    _treasure_locations[0] = randomInt(1, 27);
    _treasure_locations[1] = randomInt(28, 54);
    _treasure_locations[2] = randomInt(55, 82);
    readRiddleFile("riddles.txt");
}

int HiddenTreasures::getTreasureLocations(int i) const
{
    return _treasure_locations[i];
}

void HiddenTreasures::setTreasureLocations(int i, int num)
{
    _treasure_locations[i] = num;
}

Player HiddenTreasures::staminaRefill(Player player)
{
    int added_stamina = randomInt(10, 30);
    int new_stamina = added_stamina + player.getStamina();
    if(new_stamina>100)
    {
        new_stamina = 100;
    }
    player.setStamina(new_stamina);
    cout<<"You got a Stamina Refill of "<< added_stamina <<". You now have "<<player.getStamina()<<" stamina."<<endl;
    return player;
}

Player HiddenTreasures::goldWindfall(Player player)
{
    int added_gold = randomInt(20, 40);
    int new_gold = added_gold + player.getGold();
    if(new_gold>100)
    {
        new_gold = 100;
    }
    player.setGold(new_gold);
    cout<<"You got a Gold Windfall of "<< added_gold <<". You now have "<<player.getGold()<<" gold."<<endl;
    return player;
}

Player HiddenTreasures::robbersRepel(Player player)
{
    player.setRobbersRepel(true);
    cout<<"You got Robber's Repel, a powerful anti-robbery shield."<<endl;
    return player; 
}

Player HiddenTreasures::candyAquisition(Player player)
{
   int chance = randomInt(1, 10);
   Candy added_candy;
   if (chance>=1 && chance<=7)
    {
    added_candy = {"Jellybean of Vigor", "Boosts player's stamina by 50 units", "stamina", 50, "magical", 0};
    cout<<"You got Jellybean of Vigor, which regenerates 50 stamina."<<endl;
    }
   else
    {
    added_candy = {"Treasure Hunter's Truffle", "This candy allows the player to unlock a hidden treasure", "other", 0, "N/A", 0};
    cout<<"You got Treasure Hunter's Truffle, which unlocks another Hidden Treasure."<<endl;
    }
    
    if(player.getCandyAmount()==player.getMaxCandyAmount()) //replaces last item in inventory if full
    {
        player.setInventory(player.getMaxCandyAmount()-1, added_candy);
    }
    else
    {
        player.addCandy(added_candy);
    }    
    
    return player; 
}

Player HiddenTreasures::runHiddenTreasure(Player player)
{
    bool is_on_HT_tile = false;
    int chance = randomInt(1,10);
    for(int i=0; i<3; i++)
    {
        if(_treasure_locations[i] == player.getPosition())
        {
            is_on_HT_tile = true;
        }
    }
    if(is_on_HT_tile)
    {
        cout<<"You've discovered a Hidden Treasure! Solve this riddle to open it:"<<endl;
        bool solved = solveRiddle();
        if(solved)
        {
            if(chance>=1 && chance<=3) //30% chance
            {
                player = staminaRefill(player);
            }
            else if(chance>=4 && chance<5) //10% chance
            {
                player = goldWindfall(player);
            }
            else if(chance>=5 && chance<=7) //30% chance
            {
                player = robbersRepel(player);
            }
            else if(chance>=8 && chance<=10) //30% chance
            {
                player = candyAquisition(player);
            }
        }
        
    }
    return player; 
}

//riddles
void HiddenTreasures::readRiddleFile(string file_name)
{
    ifstream riddle_file(file_name);
    string line, line_question, line_answer;

    if(riddle_file.fail())
    {
        cout<<"Failed to open file"<<endl;
    }

    while(getline(riddle_file, line))
    {
        if(line.length()>0)
        {
            stringstream ss(line);
            getline(ss, line_question, '|');
            getline(ss, line_answer, '|');

            Riddle added_riddle = {line_question, line_answer};
            _riddles.push_back(added_riddle);
        }
        
    }
}

bool HiddenTreasures::solveRiddle()
{
    string player_answer;
    Riddle random_riddle = _riddles.at(randomInt(0, _riddles.size()-1));
    cout<<random_riddle.question<<endl;
    cout<<"Your answer: "<<endl;
    cin.clear();
    cin.ignore(999,'\n');
    getline(cin, player_answer);

    if(player_answer==random_riddle.answer)
    {
        cout<<"Correct!! Opening Hidden Treasure..."<<endl;
        return true;
    }
    else
    {
        cout<<"Wrong!!"<<endl;
        return false;
    }
}