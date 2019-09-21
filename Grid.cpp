/*
Brinly Xavier
2316142
xavier@chapman.edu
CPSC 350 -01
Life Assignment: 02
*/
#include <iostream>
#include "Grid.h"

using namespace std;
//set the contructor
Grid::Grid(int height, int width){
  x = height;
  y = width;
}
//set the overloaded

//set the destructor
Grid::~Grid(){
  for(int i = 0; i < x ;++i){
    delete[] board[i];
  }
  delete[] board;
}
//this is the proper Grid
void Grid::makeBoard(){
  myArray = new char*[x];
  for(int cow = 0; cow < x; ++cow){
    board[cow] = new char[y];
    for(int rolumn = 0; rolumn < y; ++rolumn){
      board[cow][rolumn] = '-';
    }
  }
}
//take this GRID and output it as a STRING
string Grid::gridString(){
  string gridString ="";
  for(int cow = 0; cow < x; ++cow){
    for(int rolumn = 0; rolumn < y; ++rolumn){
      gridString += string(1, gridOne[cow][rolumn]);
    }
    gridString += "\n";
  }
  cout << gridString << endl;
  return gridString;
}
