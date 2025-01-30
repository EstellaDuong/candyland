#include "Tiles.h"
#include "functions.h"

//constructors
    Tiles::Tiles()
    {
        //adds cards
        for(int i=0; i<_MAX_CARDS; i++)
        {
            _cards[i] = Card{i, false};
        }

        //adds special tiles
        for(int type=0; type<4; type++)
        {
            for(int col=0; col<_MAX_SPECIAL_TILES; col++)
            {
                _special_tiles[type][col] = 0;
            }
        }
    }


int Tiles::getSpecialTile(int type, int col) const
{
    return _special_tiles[type][col];
}
int Tiles::getMaxSpecialTiles() const
{
    return _MAX_SPECIAL_TILES;
}


// other functions
// int Tiles::movesNextColor(int current_position, int color)
// {
//     // magenta = position%3!=0
//     // green = position%3!=1
//     // blue = position%3!=2

//     for (int i=1; i<4; i++)
//     {
//         int next_color = (current_position+i)%3;
//         if(color == next_color)
//         {
//             if((current_position+i)>82)
//             {
//                 return(82-current_position);
//             }
//             return i;
//         }
//     }
//     return 0;
// }

int Tiles::movesNextColor(int current_position, Card card)
{
    // magenta = position%3!=0
    // green = position%3!=1
    // blue = position%3!=2

    for (int i=1; i<4; i++)
    {
        int next_color = (current_position+i)%3;
        if(card.color == next_color)
        {
            if((current_position+i)>82)
            {
                return(82-current_position);
            }
            return i;
        }
    }
    return 0;
}

int Tiles::drawCard(int current_position)
{
    // probability of each color: 24%(M), 23%(G), 23%(B) -> (70% total)
    // probability of each double color: 10%(M), 10%(G), 10%(B) -> (30% total)
    int number = randomInt(1, 100);
    int new_position;
    if(number>=1 && number<=24)
    {
        cout<<MAGENTATEXT<<"You drew a "<<MAGENTATEXT<< "Mystical Magenta"<< MAGENTATEXT<< " card! Your game piece advances to the next magenta tile."<<RESET <<endl;
        cout<<ORANGETEXT<<"Here's the updated board:"<<RESET <<endl;
        new_position=current_position+movesNextColor(current_position, _cards[0]);
    }
    else if(number>=25 && number<=47)
    {
        cout<<GREENTEXT<<"You drew a "<<GREENTEXT<<"Minty Green"<<GREENTEXT<<" card! Your game piece advances to the next green tile."<<RESET <<endl;
        cout<<ORANGETEXT<<"Here's the updated board:"<<RESET <<endl;
        new_position=current_position+movesNextColor(current_position, _cards[1]);
    }
    else if(number>=48 && number<=70)
    {
        cout<<BLUETEXT<<"You drew a "<<BLUETEXT<<"Bubblegum Blue"<<BLUETEXT<<" card! Your game piece advances to the next blue tile." <<RESET<<endl;
        cout<<ORANGETEXT<<"Here's the updated board:"<<RESET <<endl;
        new_position = current_position+movesNextColor(current_position, _cards[2]);
    }
    else if(number>=71 && number<=80)
    {
        cout<<MAGENTATEXT<<"You drew a "<<YELLOWTEXT<<"DOUBLE "<<MAGENTATEXT<< "Mystical Magenta"<< MAGENTATEXT<< " card! Your game piece advances 2 magenta tiles." <<RESET<<endl;
        cout<<ORANGETEXT<<"Here's the updated board:"<<RESET <<endl;
        current_position += movesNextColor(current_position, _cards[0]);
        new_position = current_position + movesNextColor(current_position, _cards[0]);
    }
    else if(number>=81 && number<=90)
    {
        cout<<GREENTEXT<<"You drew a "<<YELLOWTEXT<<"DOUBLE "<<GREENTEXT<<"Minty Green"<<GREENTEXT<<" card! Your game piece advances 2 green tiles." <<RESET<<endl;
        cout<<ORANGETEXT<<"Here's the updated board:"<<RESET <<endl;
        current_position += movesNextColor(current_position, _cards[1]);
        new_position = current_position + movesNextColor(current_position, _cards[1]);
    }
    else
    {
        cout<<BLUETEXT<<"You drew a "<<YELLOWTEXT<<"DOUBLE "<<BLUETEXT<<"Bubblegum Blue"<<BLUETEXT<<" card! Your game piece advances 2 blue tiles."<<RESET <<endl;
        cout<<ORANGETEXT<<"Here's the updated board:"<<RESET <<endl;
        current_position += movesNextColor(current_position, _cards[2]);
        new_position = current_position + movesNextColor(current_position, _cards[2]);
    }

    if(new_position>82)
    {
        return 82; 
    }
    return new_position;
}

//special
bool Tiles::checkDuplicateSpecialTile(int location)
{
    for(int type=0; type<4; type++)
    {
        for(int col=0; col<_MAX_SPECIAL_TILES; col++)
        {
            if(location == _special_tiles[type][col])
            {
                return true; 
            }
            
        }
    }
    return false;
}

void Tiles::printSpecialTileLocations() const //for testing
{
    for(int i=0; i<4; i++)
    {
        if(i==0)
            {
                cout<<"shortcut: ";
            }
            else if (i==1)
            {
                cout<<"icecream: ";
            }
            else if(i==2)
            {
                cout<<"gumdrop: ";
            }
            else if(i==3)
            {
                cout<<"gingerbread: ";
            }
        for(int j=0; j<_MAX_SPECIAL_TILES; j++)
        {
            if(i==0)
            {
                cout<< getSpecialTile(i,j) << ",";
            }
            else if (i==1)
            {
                cout<< getSpecialTile(i,j) << ",";
            }
            else if(i==2)
            {
                cout<< getSpecialTile(i,j) << ",";
            }
            else if(i==3)
            {
                cout<< getSpecialTile(i,j) << ",";
            }
        }
        cout<<endl;

    }
}

void Tiles::randomizeTilePositions(Board board)
{
    for(int type=0; type<4; type++)
    {
        for(int col=0; col<_MAX_SPECIAL_TILES; col++)
        {
            int location = randomInt(4, 81);
            while(checkDuplicateSpecialTile(location) == true || (board.getStoreLocation(1)==location || board.getStoreLocation(2)==location || board.getStoreLocation(3)==location))
            {
                location = randomInt(4, 81);
            }
             _special_tiles[type][col] = location; 
        }
    }
}

int Tiles::checkIfOnSpecialTile(int current_position)
{
    for(int type=0; type<4; type++)
    {
        for(int col=0; col<_MAX_SPECIAL_TILES; col++)
        {
             if(current_position == _special_tiles[type][col])
             {
                return type;
             }
        }
    }
    return -1;
}

//same tile 
Player Tiles::updateRobber(Player robber, Player victim, int gold_stolen)
{
    char option;
    cout<<ORANGETEXT<<"You landed on the same tile as "<<ORANGE<< victim.getName()<<RESET<<ORANGETEXT<<". Would you like to attempt to rob them? (Y/N)"<<RESET<<endl;
    cin>>option;
    option = tolower(option);

    while((option!='y' && option!='n') || cin.fail())
    {
        cout<<REDTEXT<<"Invalid input! Enter Y or N: "<<RESET<<endl;
        cin.clear();
        cin.ignore(999,'\n');
        cin>>option;
        option = tolower(option);
    }

    if(victim.getRobbersRepel()==false && option=='y')
    {
        robber.setGold(robber.getGold()+gold_stolen);
        cout<<ORANGETEXT<<"You stole "<<gold_stolen<<" gold from "<<ORANGE<<victim.getName()<<RESET<<ORANGETEXT<<". You now have "<<robber.getGold()<<" gold."<<RESET<<endl;
    }
    else if(victim.getRobbersRepel()==true && option=='y')
    {
        cout<<ORANGETEXT<<"You attempted to steal "<<gold_stolen<<" from "<<ORANGE<<victim.getName()<<RESET<<ORANGETEXT<<" but they evaded you with Robbers Repel :/"<<RESET<<endl;
    }

    return robber;
}   
Player Tiles::updateVictim(Player victim, int gold_stolen)
{
    if(victim.getRobbersRepel()==false)
    {
        victim.setGold(victim.getGold()-gold_stolen);
    }
    return victim;
}
bool Tiles::onSameTile(Player player1, Player player2)
{
    if(player1.getPosition()==player2.getPosition())
    {
        return true;
    }
    return false; 
}
