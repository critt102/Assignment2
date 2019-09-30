/** lifemain.cpp
 *main file for Life game
 *@author Mary Kate Crittenden
 *2278514
 *critt102@mail.chapman.edu
 *CPSC 350-01
 *Assignment 2
 */
#include "life.h"
#include <iostream>
#include <fstream>
using namespace std;

/**
 * main method, implemetns and runs life.cpp
 * @param  argc numer of arguments
 * @param  argv command lines arguments
 * @return      0 to end main call
 */
int main(int argc, char**argv){
  //tests user input for config
  bool valid_in=false;
  //stores grid configuration (from file or random)
  string config;
  //tests user input for mode
  bool input_o=false;
  //stores desired boundary mode
  string mode;

  //loop will keep asking for input until a valid input is recieved
  while(valid_in==false){
    cout<<"Do you want provide a flat-file configuration, or start with a random configuration?"<<endl;
    cout<<"file or random? "<<endl;
    cin>>config;
    //create a random grid
    if(config=="random" || config=="Random"){
      valid_in=true;
      //store density input
      double r_decimal;
      //store height input
      int r_height;
      //store width input
      int r_width;
      cout<<"Enter the height of your desired grid size: ";
      cin>>r_height;
      cout<<"Enter the width of your desired grid size: ";
      cin>>r_width;
      cout<<"Enter a decimal value greater than 0 and less than or equal to 1: ";
      cin>>r_decimal;
      //initialize life game with random grid
      Life gameRand(r_height, r_width, r_decimal);
      //keeps asking for input until valid input is recieved
      while(input_o==false){
        cout<<"What boundry mode do you want to run in?"<<endl;
        cout<<"classic, doughnut, or mirror?"<<endl;
        cin>>mode;
        //classic mode
        if(mode=="classic" || mode=="Classic"){
          gameRand.runClassic();
          input_o=true;
        }
        //doughnut mode
        else if(mode=="doughnut" || mode=="Doughnut"){
          gameRand.runDoughnut();
          input_o=true;
        }
        //mirror mode
        else if(mode=="mirror" || mode=="Mirror"){
          gameRand.runMirror();
          input_o=true;
        }
        else{
          cout<<mode<<" is not a valid input."<<endl;
        }
      }
    }
    //read a file to get initial grid
    else if(config=="file" || config=="File"){
      valid_in=true;
      //stores name of file input
      string file_name;
      cout<<"Enter the name of the file you wish use, in format filename.txt"<<endl;
      cin>>file_name;
      //initialize life game with file grid
      Life gameOne(file_name);
      //keeps asking for input until valid input is recieved
      while(input_o==false){
        cout<<"What boundry mode do you want to run in?"<<endl;
        cout<<"classic, doughnut, or mirror?"<<endl;
        cin>>mode;
        //classic mode
        if(mode=="classic" || mode=="Classic"){
          gameOne.runClassic();
          input_o=true;
        }
        //doughnut mode
        else if(mode=="doughnut" || mode=="Doughnut"){
          gameOne.runDoughnut();
          input_o=true;
        }
        //mirror mode
        else if(mode=="mirror" || mode=="Mirror"){
          gameOne.runMirror();
          input_o=true;
        }
        else{
          cout<<mode<<" is not a valid input."<<endl;
        }
      }
    }
    else{
      cout<<config<<" is not a valid input."<<endl;
    }
  }
  return 0;
}
