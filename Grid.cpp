/*
Brinly Xavier
2316142
xavier@chapman.edu
CPSC 350 -01
Life Assignment: 02
*/
#include <iostream>
#include "Grid.h"
#include <fstream>
#include <algorithm>
#include <string>

int nCount;
using namespace std;
//set the contructor
void Grid::getFile(string filename){
  //this gets the different dimensions from the file is the reader
  //wants to read from a file
  ifstream exboard;
  string line;
  exboard.open(filename);
  if (exboard.is_open())
  {
  cout<< "File successfully open";
  }
  else
  {
    throw runtime_error("The file you entered could not be opened. Try again Later.");
  }

  string sRow = "";
  string sColumn = "";
  cout<<"Opened file: "<<filename<<"\n";
  getline(exboard, sRow);
  getline(exboard, sColumn);
  x = stoi(sRow);
  y = stoi(sColumn);
  int rowCount = 0;
  int columnCount = 0;

makeBoard();

  while(getline(exboard, line)){
//this for loop takes the characters from the file and sets them into the board
    for(int i = 0; i < line.length(); ++i){
      board[rowCount][columnCount] = line[i];
      columnCount++;
    }
    rowCount++;
    columnCount = 0;
}
exboard.close();
}

Grid::Grid(int height, int width, float density, string mode){
  //this is the constructor for the board if it is random
  x = height;
  y = width;
  this->mode = mode;
  this->density = density;
  makeBoard();
}

Grid::Grid(string filename,string mode)
{
  //this is the constructor for the board if the user is reading from a file
  getFile(filename);
  this->mode = mode;
}


string Grid::nextGen(){
  //this sets the rules to check up on the future for each cell based on the
  //neighbor count
  string outString ="";
  for(int cow = 0; cow < x; ++cow){
    for(int rolumn = 0; rolumn < y; ++rolumn){
      if(neighCount(cow, rolumn) == 3){
        outString += string(1, 'X');
      }
      else if(neighCount(cow, rolumn) == 2 && board[cow][rolumn] == 'X'){
        outString += string(1, 'X');
      }
      else{
        outString += string(1, '-');
      }
    }
  }
  return outString;
}

//set the destructor
Grid::~Grid(){
  for(int i = 0; i < x ;++i){
    delete[] board[i];
  }
  delete[] board;
}

//take the dimensions provided and creates a string; then it is randomized
//this takes the string and places it into a board
void Grid::gridPop(){
    int p = x * y;
    int pdense = p * density;
    string boardString = "";
    for (int i = 0; i < pdense; ++i){
      boardString+= "X";
    }
    int remain = p - pdense;
    for (int i = 0; i < remain; ++i){
      boardString+="-";
    }
    random_shuffle(boardString.begin(), boardString.end());
    int counter = 0;
    for(int cow = 0; cow < x; ++cow){
      for(int rolumn = 0; rolumn < y; ++rolumn){
        board[cow][rolumn] = boardString[counter];
        ++counter;
      }
    }
}
//this takes the next generation string and sets it to the grid
void Grid::nextGrid(string nextGen){
  int counter = 0;
  for(int cow = 0; cow < x; ++cow){
    for(int rolumn = 0; rolumn < y; ++rolumn){
      board[cow][rolumn] = nextGen[counter];
      ++counter;
    }
  }
}
//this takes the cell that was set to true and then counts all of its neighbors
int Grid::neighCount(int cow, int rolumn){
  nCount = 0;
  if(isReal(cow + 1, rolumn) == true ){
    nCount++;
  }
  if(isReal(cow - 1, rolumn) == true){
    nCount++;
  }
  if(isReal(cow, rolumn + 1) == true){
    nCount++;
  }
  if(isReal(cow, rolumn - 1) == true){
    nCount++;
  }
  if(isReal(cow + 1, rolumn + 1) == true){
    nCount++;
  }
  if(isReal(cow - 1, rolumn - 1) == true){
    nCount++;
  }
  if(isReal(cow + 1, rolumn - 1) == true){
    nCount++;
  }
  if(isReal(cow - 1, rolumn + 1) ==  true){
    nCount++;
  }
  return nCount;
}
//this boolean checks if the cell is worth checking or tells where to checks
//if true then it will count the neighbors (refer to the function above)
bool Grid::isReal(int z, int a){
  if(mode == "classic"){
    //when the user chooses the mode it will go into each different section
    if(z < 0 || a < 0 || z>=x || a>=y ){
      return false;
    }
    else if(board[z][a] == 'X'){
      return true;
    }
    else{
      return false;
    }
    }
  if(mode == "doughnut"){
    /*i occasionally enjoy creating chaos in my variable names
    z and a are the x and y variables for the board
    x and y are the lengths of the rows and columns
    i do this bc it keeps life interesting
    */
    if(z < 0|| a < 0|| z>= x|| a >=y){
      if(z >= x){
        z = 0;
        //if the
      }
      if(a >= y){
        a = 0;
      }
      if(z < 0){
        z = x -1;
      }
      if(a < 0){
        a = y -1;
      }
      if(board[z][a] =='X'){
        return true;
      }
    }
    else if (board[z][a] == 'X')
    {
      return true;
    }
    else{
      return false;
    }
    return false;
  }
  if(mode == "mirror"){
    if(a < 0){
      a = 0;
    }
    if(z < 0){
      z = 0;
    }
    if(z > x - 1){
      z = x - 1;
    }
    if(a > y -1){
      a = y -1;
    }
    if (board[z][a] == 'X')
    {
      return true;
    }
    else{
      return false;
    }
  }
  else {
    cout<<"That didnt work"<<endl;
    exit(1);
  }
  }

string Grid::gridString(){
  string gridString ="";

  for(int cow = 0; cow < x; ++cow){
    for(int rolumn = 0; rolumn < y; ++rolumn){
      gridString += string(1, board[cow][rolumn]);
    }
    gridString += "\n";
  }
  return gridString;
}
void Grid::makeBoard(){
  board = new char*[x];
  for(int cow = 0; cow < x; ++cow){
    board[cow] = new char[y];
    for(int rolumn = 0; rolumn < y; ++rolumn){
      board[cow][rolumn] = '-';
    }
  }
}
