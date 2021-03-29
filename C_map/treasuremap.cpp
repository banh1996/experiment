#include "treasuremap.h"
#include <iostream>

using namespace std;

int main()
{
    return 0;
}
int input()
{
    fstream f;
    f.open("treasuremap.txt", ios::in);
    string data;
    string line;
    while (!f.eof())
    {
        getline(f, line);
        data += line;
    }
    f.close();
    cout<< data;
}
int Row_Col(int row, int column)
{
    ifstream f1;
    char c;
    int numlines = 0;
    f1.get(c);
    while(f1)
    {
        while(numlines == 2)
        {
            numlines = numlines ++;
            f1.get(c);
        }
    }
}
void PrintMap()
{
    int row=1;
    int column=1;
    fstream f;
    f.open("treasuremap.txt", ios::out);
    char b;
    
}
void FindTreasure(int, int, bool&)
{
    int row, column;
    bool a;
    char c;
    input();
    fstream f;
    f.get(c);
    int numchars = 0;
    int numlines = 0;
    while (f)
    {
        while (f && c != '\n');
        {
            numchars = numchars + 1;
            f.get(c);
        }
        numlines = numlines + 1;
        f.get(c);
    }
    row = numlines;
    column = numchars;
    if(c == 'T')
    printf("Treasure Found!");
}
void getMove(char c)
{
    
}
bool SolveTreasure(char Treasure[N][N], int x, int y, char sol[N][N]);
void PrintSolve(char sol[N][N])
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        printf(" %d ", sol[i][j]);
        printf("\n");   
    }
}
bool isSafe(char Treasure[N][N], int x, int y)
{
    if(x>=0 && x<N && y>=0 && y<N && Treasure[x][y] == 'L')
    return true;
    return false;
}
bool SolveTreasure(char Treasure[N][N])
{
    char sol[N][N] =
    {input()}
};


