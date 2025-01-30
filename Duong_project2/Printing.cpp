#include "Printing.h"

//constructors
Printing::Printing()
{

}

//checking if input works
int Printing::checkInt(int num, int min, int max)
{
    while(num<min || num>max || cin.fail())
        {
            cout<<"Invalid input! Enter a number between "<< min << " and " << max << ": " <<endl;
            cin.clear();
            cin.ignore(10000,'\n');
            cin>>num;
        }
    return num;
}

bool Printing::checkStringMatch(string str, string target)
{
    for(int i=0; i<str.length(); i++)
    {
        str[i] = tolower(str[i]);
    }

    for(int i=0; i<target.length(); i++)
    {
        target[i] = tolower(target[i]);
    }

    if(str==target)
    {
        return true;
    }
    else
    {
        return false; 
    }
}

Player Printing::checkNameMatchInPlayerVec(string name, vector<Player> players)
{
    bool found_match = false;
    Player current_player;
    while (found_match == false)
    {
        for(int i = 0; i<players.size(); i++)
        {
            current_player = players.at(i);
            string check = current_player.getName();
            found_match = checkStringMatch(name, check);
            if(found_match)
            {
                i=players.size();
            }
        }
        if (found_match == false)
        {
            cout<<"Invalid input! Try again: "<<endl;
            cin.clear();
            getline(cin, name);
        }
    }
    return current_player; 
}

Player Printing::checkNameMatchInPlayerArr(string name, Player players[], int size)
{
    bool found_match = false;
    Player current_player=players[0];
    while (found_match == false)
    {
        for(int i = 0; i<size; i++)
        {
            current_player = players[i];
            string check = current_player.getName();
            found_match = checkStringMatch(name, check);
            if(found_match==true)
            {
                i=size;
            }
        }
        if (found_match == false)
        {
            cout<<"Invalid input! Try again: "<<endl;
            cin.clear();
            getline(cin, name);
            // cout<<"retry name: "<<name<<endl; //delete
        }
    }
    return current_player; 
}

int Printing::findIndexOfPlayerInArr(string name, Player players[], int size)
{
    for(int i=0; i<size; i++)
    {
        if(players[i].getName() == name)
        {
            return i;
        }
    }
    return -1;
}

//printing stuff
int Printing::enterNumPlayers()
{
    int num;
    cout<<"Welcome to Candy Land!!"<<endl;
    cout<<"Enter the number of players (max of 4):"<<endl;
    cin>>num;
    num = checkInt(num, 1, 4);
    return num;
}

string Printing::enterPlayerName(int player_number)
{
    string player_name;
    cout<<endl;
    cout<<"Enter player " << player_number << " name:" <<endl;
    cin.clear();
    getline(cin, player_name);
    return player_name;
}

Player Printing::selectCharacter(vector<Player> characters)
{
    string character_name;
    cout<<"Awesome! Here is a list of characters to select from:"<<endl;
    cout<<"--------------------------------------------------------------------------------------"<<endl;
    for(int i=0; i<characters.size(); i++)
    {
        characters.at(i).printPlayerInfo();
        cout<<"--------------------------------------------------------------------------------------"<<endl;
    }
    cout<<"Enter the name of your character: " << endl;
    cin.clear();
    getline(cin, character_name);
    return checkNameMatchInPlayerVec(character_name, characters);
}

int Printing::enterMenuOption(string player_name)
{
    int option;
    cout<<"--------------------------------------------------------------------------------------"<<endl;
    cout<<ORANGE<<player_name<<RESET<<"'s turn!"<<endl;
    cout<<"Please select a menu option: "<<endl;
    cout<<"1. Draw a card (this counts as your turn)" << endl;
    cout<<"2. Use candy" << endl;
    cout<<"3. Show player stats" << endl;
    cout<<"--------------------------------------------------------------------------------------"<<endl;
    cin.clear();
    // cin.ignore(10000,'\n');
    cin>>option;
    return checkInt(option, 1, 3);
}

Player Printing::shopCandyStore(Player player, CandyStore stores[], int location, Board board)
{
    char option;
    string candy;
    CandyStore current_store;
    int candy_store_idx; 
    
    if(board.isPositionCandyStore(location))
        { 
            candy_store_idx = board.getCandyStoreIndex(location);
            current_store = stores[candy_store_idx];
            if(hasEnoughGold(player, current_store) == false)
            {
                cout<<player.getName()<<" is at a candy store, but you don't have enough gold to shop."<<endl;
                return player; 
            }

            cout<<endl;
            cout<<player.getName()<<" is at a candy store! Would you like to enter? (Y/N)"<<endl;
            cin.clear();
            // cin.ignore(10000,'\n');
            cin>>option;
            option = tolower(option);

            while((option!='y' && option!='n') || cin.fail())
            {
                cout<<"Invalid input! Enter Y or N: "<<endl;
                cin.clear();
                cin.ignore(999,'\n');
                cin>>option;
                option = tolower(option);
            }

            if(option=='y')
            {
                cout<<"Your gold: "<<player.getGold()<<endl;
                current_store.printStore();
                cout<<"Enter the name of the candy you'd like to buy: "<<endl;
                cin.clear();
                cin.ignore(999,'\n');
                getline(cin, candy);

                //searches for candy in the store inventory
                int index = foundCandy(candy, current_store);
                Candy chosen_candy = current_store.getInventory(index);

                if(player.getCandyAmount() == player.getMaxCandyAmount()) //runs if player inventory is full
                {
                    cout<<"Your inventory is too full to buy more candy. Would you like to substitute your candy? (Y/N)"<<endl;
                    cin.clear();
                    cin>>option;
                    option = tolower(option);

                    while((option!='y' && option!='n') || cin.fail())
                    {
                        cout<<"Invalid input! Enter Y or N: "<<endl;
                        cin.clear();
                        cin.ignore(999,'\n');
                        cin>>option;
                        option = tolower(option);
                    }

                    if (option == 'y')
                    {
                        string swap_name;
                        cout<<"Here's your inventory: "<<endl;
                        player.printInventory();
                        cout<<endl;
                        cout<<"Enter candy to substitute: "<<endl;
                        cin.clear();
                        cin.ignore(999,'\n');
                        getline(cin, swap_name);

                        //searching for candy in inventory
                        bool found_candy=false;
                        int index=-1;
                        for(int i=0; i<player.getCandyAmount(); i++)
                        {
                            found_candy = checkStringMatch(swap_name, player.getInventoryAtIndex(i).name);
                            if(found_candy)
                            {
                                index = i;
                                i=player.getCandyAmount();
                            }
                        }
                        while(found_candy == false)
                        {
                            cout<<"Candy not in inventory. Try again: "<<endl;
                            cin.clear();
                            getline(cin, swap_name);
                            for(int i=0; i<player.getCandyAmount(); i++)
                            {
                                found_candy = checkStringMatch(swap_name, player.getInventoryAtIndex(i).name);
                                if(found_candy)
                                {
                                    index = i;
                                    i=player.getCandyAmount();
                                }
                            }
                        }

                        player.setInventory(index, chosen_candy); //replaces inventory with another candy
                        
                    }
                    else
                    {
                        return player;
                    }
                }
                else //has inventory space
                {
                    while (player.getGold()<chosen_candy.price) //checks if player has enough gold
                    {
                        cout<<"You do not have enough gold. Buy another candy: "<<endl;
                        cin.clear();
                        getline(cin, candy);
                        // cout<<"another candy: "<<candy<<endl; //delete
                        index = foundCandy(candy, current_store);
                        chosen_candy = current_store.getInventory(index); 
                    }
                    player.addCandy(chosen_candy);
                    player.setGold(player.getGold() - chosen_candy.price);
                }
                cout<<endl;
                cout<<"You now have "<<player.getGold()<<" gold."<<endl;
                cout<<"Here's your updated inventory:"<<endl;
                player.printInventory();
                cout<<endl;
                cout<<endl;
            } 
            
        }

        return player;
}

int Printing::foundCandy(string candy, CandyStore current_store) //returns the index of the matching candy in store's inventory 
{
    bool found_candy=false;
    int index=-1;
    for(int i=0; i<3; i++)
    {
        found_candy = checkStringMatch(candy, current_store.getInventory(i).name);
        if(found_candy)
        {
            index = i;
            return index;
        }
    }

    while(found_candy == false)
    {
        cout<<"Candy not found. Try again: "<<endl;
        cin.clear();
        getline(cin, candy);
        // cout<<"try again: "<< candy << endl; //delete
        for(int i=0; i<3; i++)
        {
            // cout<<"compare: "<<candy<<" with "<< current_store.getInventory(i).name << endl; //delete
            found_candy = checkStringMatch(candy, current_store.getInventory(i).name);
            if(found_candy)
            {
                index = i;
                return index;
            }
        }
    }
    return index;
}

Candy Printing::foundCandy(string candy, Player player) //returns the matching candy in players's inventory 
{
    bool found_candy=false;
    int index=-1;
    for(int i=0; i<player.getCandyAmount(); i++)
    {
        found_candy = checkStringMatch(candy, player.getInventoryAtIndex(i).name);
        if(found_candy)
        {
            index = i;
            break;
        }
    }

    while(found_candy == false)
    {
        cout<<"Candy not found. Try again: "<<endl;
        cin.clear();
        getline(cin, candy);
        // cout<<"try again: "<< candy << endl; //delete
        for(int i=0; i<player.getCandyAmount(); i++)
        {
            // cout<<"compare: "<<candy<<" with "<< player.getInventoryAtIndex(i).name << endl; //delete
            found_candy = checkStringMatch(candy, player.getInventoryAtIndex(i).name);
            if(found_candy)
            {
                index = i;
                break;
            }
        }
    }
    return player.getInventoryAtIndex(index);
}

bool Printing::hasEnoughGold(Player player, CandyStore store)
{
    int player_gold = player.getGold(); 
    bool has_enough = false;
    for(int i=0; i<3; i++)
    {
        if(store.getInventory(i).price < player_gold)
        {
            has_enough = true; 
        }
    }
    return has_enough;
}