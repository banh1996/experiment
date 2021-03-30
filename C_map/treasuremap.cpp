#include "treasuremap.h"
#include <iostream>

using namespace std;

TreasureMap::TreasureMap(std::ifstream &file)
{
    if (file.is_open())
    {
        int count = 0;
        std::getline(file, xplor);
        std::string line;
        std::getline(file, line,' ');
        maxRows = std::stoi(line);
        std::getline(file, line, '\n');
        maxCols = std::stoi(line);

        for (int i = 0; i < maxRows; i++)
            for (int j = 0; j < maxCols; j++)
                tmap[i][j] = 'X';

        while (count < maxRows && std::getline(file, line))
        {
            for (int i = 0; i < maxCols; i++)
                tmap[count + 1][i + 1] = line.at(i);
            count++;
        }
        file.close();
    }
}

void TreasureMap::PrintMap()
{
    cout<<"Current map:"<<endl;
    for (int i = 0; i < maxRows; i++)
    {
        for (int j = 0; j < maxCols; j++)
            cout<<" "<<tmap[i+1][j+1];
        cout<<endl;
    }
}

void TreasureMap::FindTreasure(int x, int y, bool &is_treasure)
{
    if (tmap[x][y] == 'L') //right move
    {
        cout<<"Searching "<<x<<","<<y<<endl;
        tmap[x][y] = '*';
        TreasureMap::PrintMap();
        is_treasure = false;
        for (int i = 0; i < 4; i++)
        {
            FindTreasure(x + getMove(xplor.at(i)).first,
                         y + getMove(xplor.at(i)).second,
                         is_treasure);
        }
    }
    else if (tmap[x][y] == 'T') //found treasure
    {
        cout<<"Searching "<<x<<","<<y<<endl;
        is_treasure = true;
    }
}

std::pair<int,int> TreasureMap::getMove(char c)
{
    switch (c)
    {
        case '1':
            return std::make_pair(-1, -1);
        case '2':
            return std::make_pair(-1, 1);
        case '3':
            return std::make_pair(1, 1);
        case '4':
            return std::make_pair(1, -1);
        default:
            break;
    }
    return std::make_pair(0, 0);
}

