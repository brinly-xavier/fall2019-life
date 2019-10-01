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
  //this checks to make sure that the file that the user wants to open is legit
  if (exboard.is_open())
  {
  cout<< "File successfully open";
  }
  else
  {
    throw runtime_error("The file you entered could not be opened. Try again Later.");
  }
  //this sets the variables for the given filename
  string sRow = "";
  string sColumn = "";
  getline(exboard, sRow);
  getline(exboard, sColumn);
  //this sets the height and width from the file
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
        //3 neighbors and it lives
        outString += string(1, 'X');
      }
      else if(neighCount(cow, rolumn) == 2 && board[cow][rolumn] == 'X'){
        //2 neighbors and it remains how it is
        outString += string(1, 'X');
      }
      else{
        //anything else is just emptiness
        outString += string(1, '-');
      }
    }
  }
  return outString;
}

//set the destructor
//this helps resetting the board each time it goes through a loop
Grid::~Grid(){
  for(int i = 0; i < x ;++i){
    delete[] board[i];
  }
  delete[] board;
}

//take the dimensions provided and creates a string; then it is randomized
//this takes the string and places it into a board
void Grid::gridPop(){
//x is the height
//y is the width
    int p = x * y;
    //the poplation density is calculated here
    int pdense = p * density;
    string boardString = "";
    //this makes a string of the characters based off the densitys
    for (int i = 0; i < pdense; ++i){
      boardString+= "X";
    }
    int remain = p - pdense;
    for (int i = 0; i < remain; ++i){
      boardString+="-";
    }
    //this randomizes it
    random_shuffle(boardString.begin(), boardString.end());
    int counter = 0;
    for(int cow = 0; cow < x; ++cow){
      for(int rolumn = 0; rolumn < y; ++rolumn){
        //psets the string into the board
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
      //sets the next string into the board during the loop
      board[cow][rolumn] = nextGen[counter];
      ++counter;
    }
  }
}
//this takes the cell that was set to true and then counts all of its neighbors
int Grid::neighCount(int cow, int rolumn){
  nCount = 0;
  if(isReal(cow + 1, rolumn) == true ){
    //if there is a neighbor there
    //add to the count
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
    //JUST A DISCLAIMER!!:
    /*i occasionally enjoy creating chaos in my variable names
    z and a are the x and y variables for the board
    x and y are the lengths of the rows and columns
    i do this bc it keeps life interesting
    */
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
    //This checks the corners of the grid and sets anything to the outside
    //of the mirror to the corner and counts it for neighbors
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
    //as mentioned earlier
    //it will set the neighbors outside the grid to it so that it can then check
    //whether or not to check for it
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
  //this allows for the grid to become a string
  //makes it easier to compare, test and print
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
  //this makes a basic empty board
  //based off of the given dimensions
  board = new char*[x];
  for(int cow = 0; cow < x; ++cow){
    board[cow] = new char[y];
    for(int rolumn = 0; rolumn < y; ++rolumn){
      board[cow][rolumn] = '-';
    }
  }
}
