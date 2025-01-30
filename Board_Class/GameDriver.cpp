#include<iostream>
#include<vector>
#include<cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include "Game.h"
#include "Player.h"
#include "Board.h"
#include "CandyStore.h"
#include "Printing.h"
#include "Tiles.h"
#include "HiddenTreasures.h"

using namespace std;

vector<Player> removePlayer(string player_name, vector<Player> players)
{
    vector<Player> newVec;
    for(int i=0; i<players.size(); i++)
    {
        if(players.at(i).getName() != player_name)
        {
            newVec.push_back(players.at(i));
        }
    }
    return newVec;
}

void printAllInfo(Player players[], int num_players, Board board) //for testing purposes
{
    cout<<endl;
    // cout<<"_______ debug: _________" << endl;
    for(int i=0; i<num_players; i++)
    {
        cout<<endl;
        players[i].printPlayerInfo();
        cout<<"_candy_amount: "<< players[i].getCandyAmount()<<endl;
        cout<<"_position: "<< players[i].getPosition()<<endl;
        cout<<"_has_robbers_repel: "<< players[i].getRobbersRepel()<<endl;
        cout<<"_turns_skipped: "<< players[i].getTurnsSkipped()<<endl;
    }

    cout<<endl;
    // cout<<"_______ board: _________" << endl;
    for(int i=0; i<board.getNumPlayers(); i++)
    {
        cout<<endl;
        board.getPlayer(i).printPlayerInfo();
        cout<<"_candy_amount: "<< board.getPlayer(i).getCandyAmount()<<endl;
        cout<<"_position: "<< board.getPlayer(i).getPosition()<<endl;
        cout<<"_has_robbers_repel: "<< board.getPlayer(i).getRobbersRepel()<<endl;
        cout<<"_turns_skipped: "<< board.getPlayer(i).getTurnsSkipped()<<endl;
    }
}

int main()
{
    srand(time(0)); //only call once in entire program

    Board board;
    Game game; 
    Printing print;
    Tiles tile; 
    HiddenTreasures treasure;

    const int MAX_PLAYERS = 4;
    Player players[MAX_PLAYERS];
    int num_players;
    num_players = 1; 
    int winner_found = -1;

    //sets available candies and characters 
    vector<Candy> available_candies;
    vector<Player> available_characters;
    available_candies = game.readAvailableCandyFile("candies.txt", available_candies);
    game.setAvaialableCandies(available_candies);
    available_characters = game.readCharactersFile("characters.txt", available_characters);
    game.setAvaialableCharacters(available_characters);  

    //creates random stores on the board  
    CandyStore candyStores[4];
    candyStores[0] = game.randomStore(); 
    candyStores[1] = game.randomStore(); 
    candyStores[2] = game.randomStore(); 
    candyStores[3] = game.randomStore(); 
    board.randomlySetStorePositions(); 


    //sets locations of special tiles
    tile.randomizeTilePositions(board); //add back
    for(int i=0; i<4; i++)
    {
        for (int j=0; j<tile.getMaxSpecialTiles(); j++)
        {
            board.addSpecialTileLocation(tile.getSpecialTile(i, j));
        }
    }

    // CREATING PLAYERS IN GAME
    board.displayBoard();
    num_players = print.enterNumPlayers();
    cin.ignore();

    for(int i=0; i<num_players; i++)
    {
        string player_name = print.enterPlayerName(i+1);
        Player selected_character = print.selectCharacter(available_characters);
        players[i] = selected_character;
        players[i].setName(player_name);
        players[i].setCharacter(selected_character.getName());
        available_characters = removePlayer(selected_character.getName(), available_characters);
    }

    // updates variables in other classes
    game.setAvaialableCandies(available_candies);
    game.setAvaialableCharacters(available_characters);
    board.updatePlayers(players, num_players);

    //testing for shopping with full inventory
    // players[0].addCandy(available_candies.at(0));
    // players[0].addCandy(available_candies.at(0));
    // players[0].addCandy(available_candies.at(0));
    // players[0].addCandy(available_candies.at(0));
    // players[0].addCandy(available_candies.at(0));
    

    // GAME STARTS

    //everyone starts by shopping at the store
    for(int i=0; i<num_players; i++)
    {
        players[i]=print.shopCandyStore(players[i], candyStores, players[i].getPosition(), board);
        board.updatePlayers(players, num_players);
    }

    while(winner_found==-1)
    {
        
        for(int i=0; i<num_players; i++)
        {
            int previous_position;
            int choice = print.enterMenuOption(players[i].getName()); //prints the menu with 3 choices

            if (choice==1) //draw card
            {
                //checks if player has enough stamina to move
                players[i] = game.checkStaminaAndDeplete(players[i]); 
                board.updatePlayers(players, num_players);

                //draws a card and moves player
                if(players[i].getTurnsSkipped()==0)
                {
                    previous_position = players[i].getPosition(); 
                    players[i].setPosition(tile.drawCard(players[i].getPosition()));
                    board.updatePlayers(players, num_players);
                    board.displayBoard();
                }
                else if(players[i].getTurnsSkipped() == 3)
                {
                    cout<<ORANGETEXT<<"You're stuck on a gummy candy and must skip a turn."<<RESET<<endl;
                }
                else if(players[i].getTurnsSkipped()==4)
                {
                    cout<<ORANGETEXT<<"You must skip a turn due to the calamity."<<RESET<<endl;
                }

                //checks if player reached castle
                if(players[i].getPosition()==82)
                {
                    winner_found = i;
                }
                else 
                {
                    //if player lands on a special tile
                    int current_special_tile = tile.checkIfOnSpecialTile(players[i].getPosition());
                    while(current_special_tile>-1 && players[i].getTurnsSkipped()==0)
                    {
                        Player updated_player = game.runSpecialTile(current_special_tile, previous_position, players[i], tile, print);
                        players[i] = updated_player;
                        board.updatePlayers(players, num_players);
                        board.displayBoard();
                        current_special_tile = tile.checkIfOnSpecialTile(players[i].getPosition());
                    }  

                    //if player lands on a hidden treasure
                    if(players[i].getTurnsSkipped()==0)
                    {
                        players[i] = treasure.runHiddenTreasure(players[i]);
                        board.updatePlayers(players, num_players);
                    }
                    

                    //if player lands on another player
                    for(int j=0; j<num_players; j++)
                    {
                        if(tile.onSameTile(players[i], players[j]) && j!=i && players[i].getTurnsSkipped()==0)
                        {
                            int stolen_gold=randomInt(5, 30);
                            players[i]=tile.updateRobber(players[i], players[j], stolen_gold);
                            players[j]=tile.updateVictim(players[j], stolen_gold); 
                        }
                    }
                    board.updatePlayers(players, num_players);

                    //if player lands on a store
                    if (board.isPositionCandyStore(players[i].getPosition()) && players[i].getTurnsSkipped()==0)
                    {
                        players[i]=print.shopCandyStore(players[i], candyStores, players[i].getPosition(), board);
                        board.updatePlayers(players, num_players);
                    }

                    //if player lands on a gummy tile
                    for(int j=0; j<game.getGummyTiles().size(); j++)
                    {
                        if(players[i].getPosition() == game.getGummyTiles().at(j) && players[i].getTurnsSkipped()==0)
                        {
                            cout<<ORANGETEXT<<"You landed on a gummy candy and must skip your next turn."<<RESET<<endl;
                            players[i].setTurnsSkipped(3);
                            j=game.getGummyTiles().size();
                        }
                        else if(players[i].getPosition() == game.getGummyTiles().at(j) && players[i].getTurnsSkipped()==3)
                        {
                            players[i].resetTurnsSkipped();
                        }
                    }
                    board.updatePlayers(players, num_players);

                    //possible calamity
                    if(game.isOnRegularTile(players, i, num_players, board, tile, treasure) && players[i].getTurnsSkipped()==0)
                    {
                        int calamity_chance = randomInt(1, 10);
                        if(calamity_chance>=1 && calamity_chance<=4)
                        {
                            players[i]=game.calamity(players[i]);
                            board.updatePlayers(players, num_players);
                        }
                        
                    }
                    else if (players[i].getTurnsSkipped()==4)
                    {
                        players[i].resetTurnsSkipped();
                    }
                    board.updatePlayers(players, num_players);

                }               

            }
            else if (choice == 2)
            {
                //checking if there are only immunity candies
                bool only_immunity_left=true;
                for(int j=0; j<players[i].getCandyAmount(); j++) 
                {
                    if(players[i].getInventoryAtIndex(j).candy_type!="immunity")
                    {
                        only_immunity_left=false;
                    }
                }

                if(players[i].getCandyAmount()==0)
                {
                    
                    cout<<REDTEXT<<"you don't have any candy to use."<<RESET<<endl;
                }
                else if(only_immunity_left==true)
                {
                    cout<<REDTEXT<<"you only have immunity candies, which you can't directly use."<<RESET<<endl;
                }
                else
                {
                    string use_candy;
                    cout<<ORANGETEXT<<"Here is a list of all your candies:"<<RESET<<endl;
                    players[i].printInventory();
                    cout<<endl;
                    cout<<ORANGETEXT<<"Enter a candy you wish to use:"<<RESET<<endl;
                    cin.clear();
                    cin.ignore(999,'\n');
                    getline(cin, use_candy);

                    Candy selected_candy=print.foundCandy(use_candy, players[i]); //gets the candy the player wants to use

                    while(selected_candy.candy_type=="immunity")
                    {
                        cout<<REDTEXT<<"You can't directly use an immunity candy. Selected a different candy:"<<RESET<<endl;
                        cin.clear();
                        getline(cin, use_candy);
                        selected_candy=print.foundCandy(use_candy, players[i]);
                    }

                    game.useCandy(selected_candy, players, i, print, num_players, treasure);
                    board.updatePlayers(players, num_players);
                }
                i--;
            }
            else
            {
                cout<<ORANGETEXT<<"Here are your stats:"<<RESET<<endl;
                cout<<ORANGETEXT<<"------------------------------------------------------"<<RESET<<endl;
                players[i].printPlayerInfo();
                // cout<<"------------------------------------------------------"<<endl;
                i--;
            }
        }
    }

    //game ends
    cout<<endl;
    cout<<"════════════════*.·:·.✧ ✦ ✧.·:·.*════════════════"<<endl;
    cout<<endl;
    cout<<ORANGETEXT<<"Congrats, "<<ORANGE<<players[winner_found].getName()<<RESET<<ORANGETEXT<<"! You reached the castle first and won!"<<RESET<<endl;
    cout<<endl;
    cout<<"Here are your final stats: "<<endl;
    cout<<"------------------------------------------------------"<<endl;
    players[winner_found].printPlayerInfo();
    cout<<"------------------------------------------------------"<<endl;
    cout<<endl;
    cout<<"Thanks for playing :)"<<endl;
    cout<<endl;
    cout<<"════════════════*.·:·.✧ ✦ ✧.·:·.*════════════════"<<endl;
    //writes info to out file
    ofstream results("results.txt");
    for(int i=0; i<num_players; i++)
    {
        results<<players[i].getName()<<"|"<<players[i].getCharacter()<<"|"<<players[i].getGold()<<"|"<<players[i].getStamina()<<"|";
        for(int j=0; j<players[i].getCandyAmount(); j++)
        {
            if(j==players[i].getCandyAmount()-1) //leaves off comma for last element
            {
                results<<players[i].getInventoryAtIndex(j).name;
            }
            else
            {
                results<<players[i].getInventoryAtIndex(j).name<<",";
            }
            
        }
        results<<endl;
    }




    return 0;
}