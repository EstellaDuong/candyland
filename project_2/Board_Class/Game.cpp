#include "Game.h"
#include "functions.h"

//constructors
Game::Game()
{
}

vector<Player> Game::readCharactersFile(string file_name, vector<Player> availableCandy)
{
    ifstream chara_file(file_name);
    string line, line_name, line_stamina, line_gold, line_candies;
    vector<Player> charaVec;

    if(chara_file.fail())
    {
        cout<<"Failed to open file"<<endl;
        return charaVec;
    }

    while(getline(chara_file, line))
    {
        if(line.length()>0)
        {
            Candy candies[_MAX_CANDY_AMOUNT];
            stringstream ss(line);
            getline(ss, line_name, '|');
            getline(ss, line_stamina, '|');
            getline(ss, line_gold, '|');
 
            int i=0;
            while(getline(ss, line_candies, ','))
            {
                candies[i] = findCandyAvailable(line_candies);
                i++;
            }
            charaVec.push_back(Player(line_name, stoi(line_stamina), stod(line_gold), candies, _MAX_CANDY_AMOUNT));
        }
        
    }
    return charaVec;
}

Candy Game::findCandyAvailable(string candy_name)
{
    for(int i=0; i<candy_name.length(); i++)
    {
        candy_name[i] = tolower(candy_name[i]);
    }
    for(int i=0; i<_availableCandies.size(); i++)
    {
        Candy current = _availableCandies.at(i);
        for(int j=0; j<current.name.length(); j++)
        {
            current.name[j] = tolower(current.name[j]);
        }
        if(current.name==candy_name)
        {
            return _availableCandies.at(i);
        }
    }
    return Candy{"", "", "", 0, "", 0};
}

vector<Candy> Game::readAvailableCandyFile(string file_name, vector<Candy> candies)
{
    ifstream candy_file(file_name);
    string line, line_name, line_desc, line_effect_type, line_effect_value, line_type, line_price;
    vector<Candy> candyVec = candies;

    if(candy_file.fail())
    {
        cout<<"Failed to open file"<<endl;
        return candies;
    }

    while(getline(candy_file, line))
    {
        if(line.length()>0)
        {
            stringstream ss(line);
            getline(ss, line_name, '|');
            getline(ss, line_desc, '|');
            getline(ss, line_effect_type, '|');
            getline(ss, line_effect_value, '|');
            getline(ss, line_type, '|');
            getline(ss, line_price);
        
            candyVec.push_back(Candy{line_name, line_desc, line_effect_type, stoi(line_effect_value), line_type, stod(line_price)});
        }
        
    }
    return candyVec;
}

Candy Game::randomCandy() const
{
    return _availableCandies.at(randomInt(0, _availableCandies.size()-1)); 
}

CandyStore Game::randomStore() const
{
    Candy candies[3];
    Candy random_candy = randomCandy();
    for (int i=0; i<3; i++)
    {
        while(random_candy.name==candies[0].name || random_candy.name==candies[1].name || random_candy.name==candies[2].name)
        {
            random_candy = randomCandy();
        }
        candies[i] = random_candy; 
    }
    return CandyStore(candies); 
}

//getters and setters
vector<Candy> Game::getAvailableCandies() const
{
    return _availableCandies;
}
void Game::setAvaialableCandies(vector<Candy> newVec)
{
    _availableCandies = newVec; 
}
vector<Player> Game::getAvailableCharacters() const
{
    return _availableCharacters; 
}
void Game::setAvaialableCharacters(vector<Player> newVec)
{
    _availableCharacters = newVec; 
}
vector<int> Game::getGummyTiles() const
{
    return _gummy_tiles; 
}

//functions for different events
Player Game::runSpecialTile(int tile_type, int previous_position, Player player, Tiles tile, Printing print) //special tiles
{
    if(tile_type == 0)
    {
        cout<<ORANGETEXT<<"You landed on a special tile: Shortcut!"<<endl;
        cout<<"Your spirits soar as you're propelled four tiles ahead, closing in on the Candy Castle."<<endl;
        player.setPosition(player.getPosition()+4);
        cout<<"Here's the updated board:" << RESET<<endl;
    }
    else if(tile_type == 1)
    {
        string enter;
        cout<<ORANGETEXT<<"You landed on a special tile: Ice Cream Stop!"<<endl;
        cout<<"Congrats! You get a chance to draw a card again. Enter anything to draw a card:"<<RESET<<endl;
        cin.clear();
        cin.ignore();
        getline(cin, enter);
        player.setPosition(tile.drawCard(player.getPosition()));
    }
    else if(tile_type == 2)
    {
        cout<<ORANGETEXT"You landed on a special tile: Gumdrop Forest"<<endl;
        cout<<"Oops, You head back 4 tiles and lose 5 gold."<<endl;
        player.setPosition(player.getPosition()-4);
        player.setGold(player.getGold()-5);
        cout<<"Here's the updated board:" <<RESET<<endl;
    }
    else if(tile_type == 3)
    {
        cout<<ORANGETEXT<<"You landed on a special tile: Gingerbread House"<<endl;
        cout<<"It's a bittersweet return to your previous location, accompanied by the forfeiture of one immunity candy."<<endl; 
        player.setPosition(previous_position);
        for(int i=0; i<player.getCandyAmount(); i++)
        {
            if(player.getInventoryAtIndex(i).candy_type == "immunity")
            {
                player.removeCandy(player.getInventoryAtIndex(i).name);
                i=player.getCandyAmount();
            }
        }
        cout<<"Here's the updated board:" <<RESET<<endl;
    }     
    return player;
}   

Player Game::checkStaminaAndDeplete(Player player)
{
    int player_stamina = player.getStamina();
    int turns_skipped = player.getTurnsSkipped();
    if(player_stamina>0 && turns_skipped==0)
    {
        player.setStamina(player_stamina-1);
    }
    else if(player_stamina==0)
    {
        cout<<REDTEXT<<"You don't have enough stamina to continue. Rest for 2 more turns."<<RESET<<endl;
        player.incrementTurnsSkipped();
        player.setStamina(player_stamina+10);
    }
    else if(turns_skipped==1)
    {
        cout<<REDTEXT<<"You don't have enough stamina to continue. Rest for 1 more turn."<<RESET<<endl;
        player.incrementTurnsSkipped();
        player.setStamina(player_stamina+10);
    }
    else if(turns_skipped==2)
    {
        cout<<ORANGETEXT<<"After a long rest, you now have 20 stamina to continue your journey"<<RESET<<endl;
        cout<<endl;
        player.resetTurnsSkipped();
        player.setStamina(player_stamina-1);
    }
    return player;

}

void Game::useCandy(Candy selected_candy, Player players[], int i, Printing print, int num_players, HiddenTreasures treasure)
{
    string selected_candy_type = selected_candy.candy_type; 
    string selected_candy_description = selected_candy.description;
    
    if(selected_candy_type == "magical")
    {
        players[i].setStamina(players[i].getStamina()+selected_candy.effect_value);
        players[i].removeCandy(selected_candy.name);
        cout<<ORANGETEXT<<"You used "<<GREENTEXT<<selected_candy.name<<ORANGETEXT<<". This increased your stamina by "<<selected_candy.effect_value<<"."<<RESET<<endl;
        cout<<ORANGETEXT<<"You now have "<<players[i].getStamina()<<" stamina."<<RESET<<endl;
    }    
    else if(selected_candy_type == "poison")
    {
        string opponent_name;
        int opponent_index;
        int player_poison_strength;
        int opponent_immunity_strength = 0;
        bool opponent_has_immunity = false;

        cout<<ORANGETEXT<<"Enter the name of the oponent you'd like to use "<<GREENTEXT<<selected_candy.name<<ORANGETEXT<<" on:"<<RESET<<endl;
        cin.clear();
        getline(cin, opponent_name);
        Player opponent_found = print.checkNameMatchInPlayerArr(opponent_name, players, num_players);
        opponent_name = opponent_found.getName();
        opponent_index = print.findIndexOfPlayerInArr(opponent_name, players, num_players);

        //finds the strength of player's poison
        player_poison_strength = selected_candy.effect_value;
        if(player_poison_strength==-10)
        {
            player_poison_strength=1;
        }
        else if(player_poison_strength==-15)
        {
            player_poison_strength=2;
        }
        else if(player_poison_strength==-20)
        {
            player_poison_strength=2;
        }

        //removes immunity candy from opponent if they have one
        int immunity_index;
        for(int j=0; j<opponent_found.getCandyAmount(); j++) //loops through opponent inventory
        {
            if(opponent_found.getInventoryAtIndex(j).candy_type == "immunity")
            {
                //finds strength of opponents immunity
                int check = opponent_found.getInventoryAtIndex(j).effect_value; 

                if(check==player_poison_strength)
                {
                    opponent_immunity_strength=check;
                    immunity_index=j;
                    opponent_has_immunity=true;
                    j=opponent_found.getCandyAmount(); //exits loop
                }
                else if(check>player_poison_strength && player_poison_strength>opponent_immunity_strength)
                {
                    opponent_immunity_strength=check;
                    immunity_index=j;
                    opponent_has_immunity=true;
                }
            }
        }
        //removes stamina if opponent doesn't have immunity
        if(opponent_has_immunity==false)
        {
            int opponent_stamina = opponent_found.getStamina();
            opponent_found.setStamina(opponent_stamina+selected_candy.effect_value);
            cout<<ORANGETEXT<<"You removed "<<abs(selected_candy.effect_value)<<" stamina from "<<ORANGE<<opponent_name<<ORANGETEXT<<"!"<<ORANGETEXT<<endl;
        }
        else
        {
            cout<<ORANGETEXT<<"You used "<<GREENTEXT<<selected_candy.name<<ORANGETEXT<<", but "<<opponent_name<<" has "<< GREENTEXT<<opponent_found.getInventoryAtIndex(immunity_index).name<<ORANGETEXT<< " to protect against your poison candy"<<RESET<<endl;
            opponent_has_immunity = true; 
            opponent_found.removeCandy(opponent_found.getInventoryAtIndex(immunity_index).name);
        }

        players[i].removeCandy(selected_candy.name);
        players[opponent_index]=opponent_found;
    }    
    else if(selected_candy_type == "gummy")
    {
        int tile_chosen;
        cout<<ORANGETEXT<<"Which tile would you like to place "<<GREENTEXT<<selected_candy.name<<ORANGETEXT<<" (gummy candy)?"<<RESET<<endl;
        cin>>tile_chosen;
        tile_chosen = print.checkInt(tile_chosen, 1, 81);
        _gummy_tiles.push_back(tile_chosen);
        cout<<ORANGETEXT<<"You left a Gummy Candy trap on tile "<<tile_chosen<<"!"<<RESET<<endl;
        players[i].removeCandy(selected_candy.name);
    }
    else if(selected_candy_type == "N/A")
    {
        cin.clear();
        cin.ignore(999,'\n');
        players[i] = treasure.runHiddenTreasure(players[i]);
        players[i].removeCandy(selected_candy.name);
    }
}

Player Game::calamity(Player player)
{
    int chance = randomInt(1, 100);
    if(chance>=1 && chance<=30 )
    {
        int stolen_gold = randomInt(1, 10);
        cout<<ORANGETEXT<<"Oh no! A mischievous gang of candy bandits stole "<<stolen_gold<<" gold from you!"<<ORANGETEXT<<endl;
        player.setGold(player.getGold()-stolen_gold);
    }
    else if(chance>=31 && chance<=65)
    {
        cout<<ORANGETEXT<<"Oh dear! You got lost in the lollipop labyrinth and lose a turn!"<<RESET<<endl;
        if(playRockPaperScissors(player)==false)
        {
            player.setTurnsSkipped(4);

        }
    }
    else if(chance>=66 && chance<=80)
    {
        int stolen_gold = randomInt(5, 10);
        cout<<ORANGETEXT<<"Watch out! A candy avalanche has struck! You'll lose "<<stolen_gold<<" gold and skip a turn."<<RESET<<endl;
        if(playRockPaperScissors(player)==false)
        {
            player.setTurnsSkipped(4);
            player.setGold(player.getGold()-stolen_gold);
        }
    }
    else if(chance>=81 && chance<=100)
    {
        cout<<ORANGETEXT<<"Oops! You are stuck in a sticky taffy trap and lose a turn!" << RESET<< endl;
        
        //checks if player has a magical candy
        for(int i=0; i<player.getCandyAmount(); i++)
        {
            if(player.getInventoryAtIndex(i).candy_type=="magical")
            {
                char use;
                cout<<ORANGETEXT<<"You have a Magical Candy that can recover your lost turn, use it? (Y/N)"<<RESET<<endl;
                cin.clear();
                cin>>use;
                use = tolower(use);

                while((use!='y' && use!='n') || cin.fail())
                {
                    cout<<REDTEXT<<"Invalid input! Enter Y or N: "<<RESET<<endl;
                    cin.clear();
                    cin.ignore(999,'\n');
                    cin>>use;
                    use = tolower(use);
                }

                if(use=='y')
                {
                    cout<<ORANGETEXT<<"You used "<<GREENTEXT<<player.getInventoryAtIndex(i).name<<ORANGETEXT<<" to recover your lost turn!"<<RESET<<endl;
                    player.removeCandy(player.getInventoryAtIndex(i).name);
                    return player;
                }
                else
                {
                    player.setTurnsSkipped(4);
                }
            }
        }
        
    }
    return player;
}

bool Game::playRockPaperScissors(Player player)
{
    char play1='s', play2='s';
    bool player_wins= true;

    cout<<ORANGETEXT<<"You can recover the lost damage by playing rock, paper, scissors against a mysterious force..."<<RESET<<endl;

    while(play1==play2)
    {
        cout<<ORANGETEXT<<"Enter r, p, or s:"<<RESET<<endl;
        cin.clear();
        cin>>play1;
        while(play1!='r' && play1!='p' && play1!='s')
        {
            cout<<REDTEXT<<"Invalid selection!"<<RESET<<endl;
            cin.clear();
            cin>>play1;
        }

        int computer_play = randomInt(1,3);
        if(computer_play==1)
        {
            play2='r';
        }
        else if(computer_play==2)
        {
            play2='p';
        }
        else if(computer_play==3)
        {
            play2='s';
        }
        cout<<ORANGETEXT<<"Your opponent played "<<play2<<"."<<RESET<<endl;

        if(play1==play2)
        {
            cout<<ORANGETEXT<<"Tie! Play again"<<RESET<<endl;
        }
        else if (play1=='r')
        {
            if(play2=='p')
            {
                player_wins = false;
            }
        }
        else if (play1=='p')
        {
            if(play2=='s')
            {
                player_wins = false;
            }
        }
        else if (play1=='s')
        {
            if(play2=='r')
            {
                player_wins = false;
            }
        }
    }

    if(player_wins)
    {
        cout<<ORANGETEXT<<"You won and recovered the damage! :)"<<RESET<<endl;
        return true;
    }
    else if (player_wins == false)
    {
        cout<<ORANGETEXT<<"You lost and took the damage! :("<<RESET<<endl;
        return false;
    }
    return false;
}

bool Game::isOnRegularTile(Player players[], int i, int num_players, Board board, Tiles tile, HiddenTreasures treasure)
{
    int current_position = players[i].getPosition();
    //checks if on store
    for(int j=0; j<board.getCandyStoreCount(); j++)
    {
        if (current_position==board.getStoreLocation(j))
        {
            return false;
        }
    }

    //checks if on special tile
    for(int j=0; j<board.getNumSpecialTiles(); j++)
    {
        if(current_position==board.getSpecialTilesLocationAtIdx(j))
        {
            return false;
        }
    }

    //checks if on another player
    for(int j=0; j<num_players; j++)
    {
        if(tile.onSameTile(players[i], players[j]) && j!=i)
        {
            return false;
        }
    }

    //checks if on hidden treasure
    for(int j=0; j<3; j++)
    {
        if(current_position==treasure.getTreasureLocations(j))
        {
            return false;
        }
    }

    //checks if on gummy 
    for(int j=0; j<_gummy_tiles.size(); j++)
    {
        if(current_position==_gummy_tiles.at(j))
        {
            // cout<<"return false";
            return false;
        }
    }

    //at the end
    if(current_position>=82)
    {
        return false;
    }

    //on regular tile
    return true; 
}
