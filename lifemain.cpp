#include "classicLife.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char**argv){
  bool valid_in=false;
  string config;
  string mode;
  bool input_o=false;

  while(valid_in==false){
    cout<<"Do you want provide a flat-file configuration, or start with a random configuration?"<<endl;
    cout<<"file or random? "<<endl;
    cin>>config;

    if(config=="random" || config=="Random"){
      valid_in=true;
      double r_decimal;
      int r_height;
      int r_width;
      cout<<"Enter the height of your desired grid size: ";
      cin>>r_height;
      cout<<"Enter the width of your desired grid size: ";
      cin>>r_width;
      cout<<"Enter a decimal value greater than 0 and less than or equal to 1: ";
      cin>>r_decimal;
      ClassicLife gameRand(r_height, r_width, r_decimal);
      while(input_o==false){
        cout<<"What boundry mode do you want to run in?"<<endl;
        cout<<"classic, doughnut, or mirror?"<<endl;
        cin>>mode;
        if(mode=="classic" || mode=="Classic"){
          gameRand.runClassic();
          input_o=true;
        }
        else if(mode=="doughnut" || mode=="Doughnut"){
          gameRand.runDoughnut();
          input_o=true;
        }
        else if(mode=="mirror" || mode=="Mirror"){
          gameRand.runMirror();
          input_o=true;
        }
        else{
          cout<<mode<<" is not a valid input."<<endl;
        }
      }
    }
    else if(config=="file" || config=="File"){
      valid_in=true;
      string file_name;
      cout<<"Enter the name of the file you wish use, in format filename.txt"<<endl;
      cin>>file_name;
      ClassicLife gameOne(file_name);
      while(input_o==false){
        cout<<"What boundry mode do you want to run in?"<<endl;
        cout<<"classic, doughnut, or mirror?"<<endl;
        cin>>mode;
        if(mode=="classic" || mode=="Classic"){
          gameOne.runClassic();
          input_o=true;
        }
        else if(mode=="doughnut" || mode=="Doughnut"){
          gameOne.runDoughnut();
          input_o=true;
        }
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
