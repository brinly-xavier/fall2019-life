/*
Brinly Xavier
2316142
xavier@chapman.edu
CPSC 350 -01
Life Assignment: 02
*/
#include <iostream>
using namespace std;

class Grid{
  public:
    //constructor for random grid
    Grid(int height, int width, float density, string mode);
    //constructor for file grid
    Grid(string filename, string mode);
    //overloaded
    //destructor
    ~Grid();
    void makeBoard();
    void getFile(string filename);
    void gridPop();
    string gridString();
    int neighCount(int cow, int rolumn);
    bool isReal(int z, int a);
    string nextGen();
    void nextGrid(string nextGen);
    //set the arrays and also the dimensions
    char ** board;
    int x;
    int y;
    string mode;
    float density;
};
