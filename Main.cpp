/*
Brinly Xavier
2316142
xavier@chapman.edu
CPSC 350 -01
Life Assignment: 02
*/
#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <stdio.h>
#include <string>
#include <time.h>
#include "Grid.h"
#include <algorithm>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

//globalizing all of the variables
bool loop = true;
string input;
string filename;
int counter = 1;
string mode;
float density;
int pdense;
int width;
int height;
string boardString;
string strArray[3];
string output;
int main(int argc, char ** argv){
  //when the random grid choice is selected, this guarantees that every time it randomizes
  //it wont be the same
  srand(time(NULL));
  cout<<"Welcome to the Game of Life"<<endl;
  cout<<"Would you life to provide a file or offer dimensions? Enter 'file' or 'random'"<<endl;
  cin>>input;
  //this takes the input and sets it to lower case
  std::transform(input.begin(), input.end(), input.begin(), ::tolower);

//if you choose to open up a file for the grid
//this takes an input
  if(input == "file"){
    cout<<"Enter the file name\n";
    cout<<"if other is used then beware of what could happen"<<endl;
    cin>>filename;
  }
  //this takes the dimensions for the grid

  else if(input == "random"){
    string rInp = "";
    cout<<"Please input the height *integers only!* : "<<endl;
    cin>>rInp;
    try{
      height = stoi(rInp);
    }
    catch (invalid_argument e)
    {
      cout <<"Please enter an integer next time. Thanks."<<endl;
      return 1;
    }
    cout<<"Please input the width *integers only* : "<<endl;
    cin>>rInp;
    try{
      width = stoi(rInp);
    }
    catch (invalid_argument e)
    {
      cout <<"Please enter an integer next time. Thanks."<<endl;
      return 1;
    }
    cout<<"Please enter population density that you would like to work with."<<endl;
    cout<<"Choose a number between 0 and 1"<<endl;
    cin>>rInp;
    try{
      density = stof(rInp);
      if (density < 0 || density > 1){
        throw runtime_error("The density was not in the proper boundaries");
      }
    }
    catch (...)
    {
      cout <<"Please enter a proper number next time. Thanks."<<endl;
      return 1;
    }
  }
  //anything else is straight up wrong
  else{
    cout<<"This is wrong...HERESEY"<<endl;
    cout<<"GoodBye"<<endl;
    return 0;
  }
  //this takes an input on what mode the user wants to do
  cout<<"What method would you like to follow? 'classic', 'doughnut' or 'mirror'";
  cin>>mode;
  std::transform(mode.begin(), mode.end(), mode.begin(), ::tolower);
  //this error checks to make sure that the user does not input something stupid
  //pardon my french
  bool forMode = false;
  if(mode == "classic"){
    forMode = true;
  }
  else if(mode == "doughnut"){
    forMode = true;
  }
  else if(mode == "mirror"){
    forMode = true;
  }
  if(forMode == false){
    cout<<"The correct mode was not displayed"<<endl;
    cout<<"Goodbye"<<endl;
    return 1;
  }

//once printing out each generation the user has the option to print out to a file, pause or press enter to
//move through generations
  cout<<"Would you like to pause between generations or output to a file? Enter 'map' 'pause' or 'enter'"<<endl;
  cin>>output;
  std::transform(output.begin(), output.end(), output.begin(), ::tolower);

  //this error checks to make sure that the user does not input something stupid
  //pardon my french

  bool forOut = false;
  if(output == "map"){
    forOut = true;
  }
  else if(output == "pause"){
    forOut = true;
  }
  else if(output == "enter"){
    forOut = true;
  }
  if(forOut == false){
    cout<<"The correct output was not entered!"<<endl;
    cout<<"Goodbye"<<endl;
    return 1;
  }
   //make the grid
//this pointer initializes the future gen grid based off of the parent grid
Grid* currentGen;

if(input ==  "random")
{
  //this creates a parent grid based off of the dimensions asked for earlier
  currentGen= new Grid(height, width, density,mode);
  //randomizes the order of it
  currentGen->gridPop();
}
else
{
  //if the user chooses to use a file it takes the dimensions from the file
  //to make a parent board
  try{
    currentGen = new Grid(filename, mode);
  }
  catch(runtime_error e){
    cout<<"The program has ended. Come back soon"<<endl;
    cout<<e.what()<<endl;
    return 1;
  }
  //this takes the dimensions from the file and sets them to the same format
  //the random function uses
  height = currentGen->x;
  width = currentGen->y;
}
//this initializes the grid for the new generations
  Grid* newGen;
//this prints out the parent board
  cout<<"This is Generation 0"<<endl;
  string boardStr = currentGen->gridString();
  if(output == "map"){
    //this prints the parent board to the outfile if the user chooses to do so
    std::ofstream outfile ("brinly2.out");
    outfile<<"This is Generation 0"<<endl;
    outfile<< boardStr << endl;
    cout<< boardStr << endl;
  }
  else{
    cout<< boardStr << endl;
  }
  //this is the next generation

// this is out of the loop becasuse this allows to ask the user to press enter
// otherwise it will get stuck in the loop
  getchar();
  while(loop == true){
    //this while loop goes through the game of life until the grid stabilizes or
    //it all dies
    cout<<"This is generation "<< counter <<endl;
    string nextGenStr = currentGen ->nextGen();
    newGen = new Grid(height, width, density, mode);
    newGen->nextGrid(nextGenStr);

    string outGenString = newGen ->gridString();
    cout <<outGenString << endl;
    strArray[counter % 3] = nextGenStr;
    strArray[(counter + 1) % 3] = outGenString;

//this checks to see if the characters in the first and second grid all match up
    for(int i = 0; i < 3; ++i){
      for(int k = 0; k < 3; ++k){
        if(i==k){
          continue;
        }
        //if they match completely, the loop breaks
        if(strArray[i] == strArray[k]){
          loop = false;
          break;
        }
      }
    }
    //if everything is fine then previous grid is relaced by the upcoming grid
    if (outGenString.find('X') || boardStr!= outGenString){
      currentGen -> ~Grid();
      currentGen = newGen;
    }
    //if the user chooses to print out to a file then this happens
    if(output == "map"){
      std::ofstream outfile ("brinly2.out", ofstream::app);
      outfile<<"This is generation "<< counter <<endl;
      outfile <<outGenString << endl;
      outfile.close();
    }
//if the user wants to pause between generations then this allows two second
//pauses between each print
    if(output == "pause"){
      sleep_for(seconds(2));
    }
    //if the user wants to press enter between generations then this allows
    //to press enter for each gen
    if(output == "enter"){
      cout<<"Please press to continue to the next generation"<<endl;
      getchar();
    }
//this counts the different generations
    counter++;
  }
  cout<<"Game Over"<<endl;
  cout<<"Goodbye!"<<endl;
  return 0;
}
