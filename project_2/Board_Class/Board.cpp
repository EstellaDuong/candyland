#include "Board.h"
#include "functions.h"

Board::Board()
{
    _num_players = 1;
    resetBoard();
}

void Board::resetBoard()
{
    const int COLOR_COUNT = 3;
    const string COLORS[COLOR_COUNT] = {MAGENTA, GREEN, BLUE};
    Tile new_tile;
    string current_color;
    for (int i = 0; i < _BOARD_SIZE - 1; i++)
    {
        current_color = COLORS[i % COLOR_COUNT];
        new_tile = {current_color, "regular tile"};
        _tiles[i] = new_tile;
    }
    new_tile = {ORANGE, "regular tile"};
    _tiles[_BOARD_SIZE - 1] = new_tile;

    _candy_store_count = 0;
    for (int i = 0; i < _MAX_CANDY_STORE; i++)
    {
        _candy_store_position[i] = -1;
    }

    _player_position = 0;
}

void Board::displayBoard()
{
    // First horizontal segment
    for (int i = 0; i <= 23; i++)
    {
        displayTile(i);
    }
    cout << endl;
    // First vertical segment
    for (int i = 24; i <= 28; i++)
    {
        for (int j = 0; j < 23; j++)
        {
            cout << "   ";
        }
        displayTile(i);
        cout << endl;
    }
    // Second horizontal segment
    for (int i = 52; i > 28; i--)
    {
        displayTile(i);
    }
    cout << endl;
    // Second vertical segment
    for (int i = 53; i <= 57; i++)
    {
        displayTile(i);
        for (int j = 0; j < 23; j++)
        {
            cout << "   ";
        }
        cout << endl;
    }
    // Third horizontal segment
    for (int i = 58; i < _BOARD_SIZE; i++)
    {
        displayTile(i);
    }
    cout << ORANGE << "🏰" << RESET << endl;
    // cout << ORANGE << "Castle" << RESET << endl;
}

bool Board::setPlayerPosition(int new_position)
{
    if (new_position >= 0 && new_position < _BOARD_SIZE)
    {
        _player_position = new_position;
        return true;
    }
    return false;
}

void Board::setStorePositions(int pos0, int pos1, int pos2, int pos3)
{
    _candy_store_position[0] = pos0;
    _candy_store_position[1] = pos1;
    _candy_store_position[2] = pos2;
    _candy_store_position[3] = pos3;
    _candy_store_count = 4; 
}

void Board::randomlySetStorePositions()
{
    int position;
    for(int i=0; i<_MAX_CANDY_STORE; i++)
    {
        if(i==0)
        {
            position=0;
        }
        else if (i==1)
        {
            position = randomInt(1, 27);
            while(position%3!=0)
            {
                position = randomInt(1, 27);
            }
        }
        else if (i==2)
        {
            position = randomInt(28, 54);
            while(position%3!=1)
            {
                position = randomInt(28, 54);
            }
        }
        else if (i==3)
        {
            position = randomInt(55, 82);
            while(position%3!=2)
            {
                position = randomInt(55, 82);
            }
        }
        _candy_store_position[i]=position; 
        _candy_store_count++;
    }

    // //for testing - prints store locations
    // for(int i=0; i<_MAX_CANDY_STORE; i++)
    // {
    //     cout<<"store "<< i <<": "<<_candy_store_position[i]<<endl;
    // }

}


int Board::getBoardSize() const
{
    return _BOARD_SIZE;
}

int Board::getCandyStoreCount() const
{
    return _candy_store_count;
}

int Board::getPlayerPosition() const
{
    return _player_position;
}

int Board::getCandyStoreIndex(int location) const
{
    if(location ==0)
    {
        return 0;
    }
    else if(location>=1 && location<=27)
    {
        return 1;
    }
    else if(location>=28 && location<=54)
    {
        return 2;
    }
    else if(location>=55 && location<=82)
    {
        return 3;
    }
    else
    {
        cout<<"Unable to find CandyStoreIndex"<<endl;
        return -1;
    }
}

bool Board::addCandyStore(int position)
{
    if (_candy_store_count >= _MAX_CANDY_STORE)
    {
        return false;
    }
    _candy_store_position[_candy_store_count] = position;
    _candy_store_count++;
    return true;
}

bool Board::isPositionCandyStore(int board_position)
{
    for (int i = 0; i < _candy_store_count; i++)
    {
        if(_candy_store_position[i] == board_position)
        {
            return true;
        }
    }
    return false;
}

bool Board::movePlayer(int tile_to_move_forward)
{
    int new_player_position = tile_to_move_forward + _player_position;
    if(new_player_position < 0 || new_player_position >= _BOARD_SIZE)
    {
        return false;
    }
    _player_position = new_player_position;
    return true;
}

//functions added

void Board::displayTile(int position)
{
    if (position < 0 || position >= _BOARD_SIZE)
    {
        return;
    }
    Tile target = _tiles[position];
    cout << target.color << " ";

    bool printed_blank = false;

    //prints player numbers
    for(int i=0; i<_num_players; i++)
    {
        if (position == _players[i].getPosition())
        {
            cout << i+1;
            printed_blank=true;
        }
    }

    //prints special tiles
    for(int i=0; i<_special_tiles_locations.size(); i++)
    {
        if (position == _special_tiles_locations.at(i) && printed_blank == false)
        {
            cout << "❀";
            printed_blank=true;
        }
    }

    //prints candy stores
    for(int i=0; i<_MAX_CANDY_STORE; i++)
    {
        if (position == _candy_store_position[i] && printed_blank==false)
        {
            cout << "S";
            printed_blank=true;
        }
    }

    //prints blanks
    if (printed_blank==false)
    {
        cout << " ";
        printed_blank = true; 
    }
    
    cout << " " << RESET;
}

Player Board::getPlayer(int index) const
{
    return _players[index];
} 
int Board::getNumPlayers() const
{
    return _num_players;
}
int Board::getStoreLocation(int index) const
{
    return _candy_store_position[index];
}
int Board::getMaxCandyStore() const
{
    return _MAX_CANDY_STORE;
}
void Board::updatePlayers(Player players[4], int num_players)
{
    for (int i=0; i<num_players; i++)
    {
        _players[i] = players[i];
    }
    _num_players = num_players; 
}

int Board::getMaxPlayers() const
{
    return _MAX_PLAYERS;
}

void Board::addSpecialTileLocation(int location)
{
    _special_tiles_locations.push_back(location);
}

vector<int> Board::getSpecialTilesLocations() const
{
    return _special_tiles_locations;
}
int Board::getNumSpecialTiles()
{
    return _special_tiles_locations.size();
}
int Board::getSpecialTilesLocationAtIdx(int i) const
{
    return _special_tiles_locations.at(i);
}