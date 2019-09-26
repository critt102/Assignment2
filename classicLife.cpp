#include "classicLife.h"
#include <iostream>
#include <fstream>
using namespace std;

ClassicLife::ClassicLife(){
  width=1;
  height=1;
  numvar=1;
  loopvalue=0;
  currentvalue=2;
  cell='-';
  thiscell=false;
  sim=0;
  inArray=new char[numvar];
  lifeArray= new char*[width];
  newArray=new char*[width];
  //ifstream in_file;
  for(int k = 0; k < width; ++k){
    lifeArray[k] = new char[height];
    newArray[k] = new char[height];
  }
}
ClassicLife::ClassicLife(string filename){
  numvar=0;
  loopvalue=0;
  currentvalue=2;
  cell='-';
  thiscell=false;
  sim=0;
  ifstream in_file;
  in_file.open(filename, ios::in);
  if(in_file.is_open()){
    //counting chars
    while(getline(in_file, line)){
      //count variables
      for(int i=0; i<line.size();++i){
        numvar++;
      }
    }
  }
  in_file.close();
  //make array of to fit all chars
  inArray=new char[numvar];
  in_file.open(filename, ios::in);
  //take in all chars and put them in one array
  while(getline(in_file, line)){
    for(int pp=0; pp<line.size();++pp){
        inArray[loopvalue++]=line[pp];
    }
  }
  //turn width and height into ints
  height=inArray[0]-'0';
  width=inArray[1]-'0';
  //create 2d array
  lifeArray= new char*[width];
  newArray=new char*[width];
  for(int k = 0; k < width; ++k){
    lifeArray[k] = new char[height];
    newArray[k] = new char[height];
  }
  for(int row=0; row<height; ++row){
    for(int col=0; col<width; ++col){
      lifeArray[row][col]=inArray[currentvalue++];
      // cout<<"row "<<row;
      // cout<<" col "<<col<<" ";
      // cout<<inArray[currentvalue++]<<endl;
    }
  }
}

ClassicLife::~ClassicLife(){
  delete lifeArray;
  delete newArray;
  delete inArray;
}
bool ClassicLife::fullCell(char x){
  if (x=='X'){
    return true;
  }
  else{
    return false;
  }
}
void ClassicLife::writeToFile(string out_name){
  cout<<"Write to file"<<endl;
}
void ClassicLife::runSimulation(){
  int numruns=0;
  //overall map rows
  for(int row_c=0; row_c<height; row_c++){
    //overall maps columns
    for(int col_c=0; col_c<width; col_c++){
      //cell we are focusing on
      cell=lifeArray[row_c][col_c];
      sim=0;
      numruns++;
      //check if current cell is full
      thiscell=fullCell(cell);
      for(int a=(row_c-1); a<=(row_c+1); a++){
        for(int b=(col_c-1); b<=(col_c+1); b++){
          if(a>=0 &&b>=0){
            thiscell=fullCell(lifeArray[a][b]);
          }
          else{
            thiscell=false;
          }
          if(thiscell==true){
            sim++;
          }
          else{
          }
        }
      }
      if (cell=='X'){
        sim--;
      }
      //cout<<lifeArray[0][0]<<endl;
      //cout<<sim<<endl;
      if(sim<=1){
        newArray[row_c][col_c]='-';
      }
      else if(sim==2){
        if (cell=='X'){
          newArray[row_c][col_c]='X';
        }
        else{
          newArray[row_c][col_c]='-';
        }
      }
      else if(sim==3){
        newArray[row_c][col_c]='X';
      }
      else if(sim>=4){
        newArray[row_c][col_c]='-';
      }
    }
  }
  for(int row_new=0; row_new<height; ++row_new){
    for(int col_new=0; col_new<width; ++col_new){
      cout<<newArray[row_new][col_new];
    }
    cout<<endl;
  }
}
bool ClassicLife::isEmpty(){
  return false;
}
bool ClassicLife::isStable(){
  return true;
}
//this has changed
