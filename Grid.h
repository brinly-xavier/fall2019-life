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
    //constructor
    Grid(int height, int width);
    //overloaded
    Grid(int );//fix this
    //destructor
    ~Grid();
    void makeBoard();
    string gridString();
    //set the arrays and also the dimensions
    char ** myArray;
    int x;
    int y;


}
