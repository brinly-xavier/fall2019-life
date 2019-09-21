/*
Brinly Xavier
2316142
xavier@chapman.edu
CPSC 350 -01
Life Assignment: 02
*/
#include <iostream>

using namespace std;
int main(){
  cout<<"Welcome to the Game of Life";
  string input;
  string filename;
  cout<<"Would you life to provide a file or offer dimensions? Enter 'file' or 'dimensions'";
  cin>>input;
  if(input == "file"){
    cout<<"Enter the file name\n";
    ofstream textfile;
    cin>>filename;
    textfile.open(filename);
    cout<<"Opened file: "<<filename<<"\n";
  }
  else if(input == "dimensions"){

  }
  //make the grid
  Grid board(inp1, inp2);
  grider.gridString();
  grider.makeBoard();
  return 0;
}
