/* Name
 * CSCI 3110-00X ()
 * Project 5
 * Due: 
 */

#include <iostream>
#include "treasuremap.h"

using namespace std;

int main()
{
    bool is_treasure = false;

    std::ifstream file("treasuremap.txt");
    TreasureMap map(file);

    map.PrintMap();
    cout<<"Start position: 1,1"<<endl;
    map.FindTreasure(1, 1, is_treasure);
    if (is_treasure)
        cout<<"Treasure found!"<<endl;
    else
        cout<<"No treasure!"<<endl;

    return 0;
}
