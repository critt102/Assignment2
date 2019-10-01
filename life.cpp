/** life.cpp
 *Source file for game of Life
 *@author Mary Kate Crittenden
 *2278514
 *critt102@mail.chapman.edu
 *CPSC 350-01
 *Assignment 2
 */
#include "life.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
using namespace std;
/**
 * Implements functions as defined in the header, to a default.
 */
Life::Life(){
  width=1;
  height=1;
  numvar=1;
  loopvalue=0;
  currentvalue=0;
  cell='-';
  thiscell=false;
  enter=false;
  sim=0;
  test_equality=false;
  rand_dec=0;
  outputfile='n';
  out_name="";
  gen=0;
  inArray=new char[numvar];
  lifeArray= new char*[width];
  newArray=new char*[width];
  oscilArray=new char*[width];
  for(int k = 0; k < width; ++k){
    lifeArray[k] = new char[height];
    newArray[k] = new char[height];
    oscilArray[k]=new char[height];
  }
}
/**
 * Overloaded constructor implements life functions, asks user questions about how they want the simulation to
 * be run, and defines the sizes of the three life arrays.
 * @param filename a string representing the name of the file containing the starting grid
 */
Life::Life(string filename){
  numvar=0;
  loopvalue=0;
  currentvalue=0;
  cell='-';
  thiscell=false;
  sim=0;
  gen=0;
  test_equality=false;
  rand_dec=0;
  in_file.open(filename, ios::in);
  //program will not run if file entered can not be found
  if(in_file.is_open()==false){
    cout<<"File "<<filename<<" not found."<<endl;
    exit(0);
  }
  cout<<"Do you want to output results to a file? y or n? "<<endl;
  cin>>outputfile;
  if (outputfile=='y' || outputfile== 'Y'){
    cout<<"Enter the name of the file you wish to output to, in the format filename.txt "<<endl;
    cin>>out_name;
    out_file.open(out_name, ios::out);
  }
  else if(outputfile=='n' || outputfile=='N'){
    cout<<"Do you want to press the enter key between generations? y or n? "<<endl;
    cin>>enter_in;
    enter_in=tolower(enter_in);
    if(enter_in=='y' || enter_in=='Y'){
      enter=true;
    }
    else if(enter_in=='n' || enter_in=='N'){
      enter=false;
    }
    else{
      cout<<"Input is not valid. Please enter either n or y."<<endl;
      exit(0);
    }
  }
  else{
    cout<<"Input is not valid. Please enter either n or y."<<endl;
    exit(0);
  }
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

  int help=0;
  while(getline(in_file, line)){
    if(help==0){
      string height_s=line;
      height=stoi(height_s);
      help=1;
    }
    else if(help==1){
      string width_s=line;
      width=stoi(width_s);
      help=2;
    }
    else{
      for(int pp=0; pp<line.size();++pp){
        inArray[loopvalue++]=line[pp];
      }
    }

  }
  //create 2d arrays
  lifeArray= new char*[width];
  newArray=new char*[width];
  oscilArray=new char*[width];
  for(int k = 0; k < width; ++k){
    lifeArray[k] = new char[height];
    newArray[k] = new char[height];
    oscilArray[k]=new char[height];
  }
  //place variables from file intp 2d array
  for(int row=0; row<height; ++row){
    for(int col=0; col<width; ++col){
      lifeArray[row][col]=inArray[currentvalue++];
    }
  }
}
/**
 * Overloaded Constructor also implements life functions, but adds the element of
 * a random grid generation and assignment
 * @param r_height  an int representing the desired height of the random grid
 * @param r_width   an int representing the desired width of the random grid
 * @param r_decimal a double representing the density of the grid
 */
Life::Life(int r_height, int r_width, double r_decimal){
  rand_dec=r_decimal;
  outputfile='n';
  out_name="";
  height=r_height;
  width=r_width;
  numvar=1;
  gen=0;
  loopvalue=0;
  currentvalue=0;
  cell='-';
  thiscell=false;
  sim=0;
  test_equality=false;
  inArray=new char[numvar];
  cout<<"Do you want to output results to a file? y or n? "<<endl;
  cin>>outputfile;
  if (outputfile=='y' || outputfile== 'Y'){
    cout<<"Enter the name of the file you wish to output to, in the format filename.txt "<<endl;
    cin>>out_name;
    out_file.open(out_name, ios::out);
  }
  else if(outputfile=='n' || outputfile=='N'){
    cout<<"Do you want to press the enter key between generations? y or n? "<<endl;
    cin>>enter_in;
    enter_in=tolower(enter_in);
    if(enter_in=='y'|| enter_in=='Y'){
      enter=true;
    }
    else if(enter_in=='n' || enter_in=='N'){
      enter=false;
    }
    else{
      cout<<"Input is not valid. Please enter either n or y."<<endl;
      exit(0);
    }
  }
  else{
    cout<<"Input is not valid. Please enter either n or y."<<endl;
    exit(0);
  }

  //create 2d array
  lifeArray= new char*[width];
  newArray=new char*[width];
  oscilArray=new char*[width];
  for(int k = 0; k < width; ++k){
    lifeArray[k] = new char[height];
    newArray[k] = new char[height];
    oscilArray[k]=new char[height];
  }
  //fill array with '-'
  for(int f=0; f<height; ++f){
    for(int g=0; g<width; ++g){
      lifeArray[f][g]='-';
    }
  }
  //fill grid with 'X' according to density calculation
  int density=(width*height)*rand_dec;
  cout<<"Generating Grid..."<<endl;
  //while grid is not at disired density
  while(density>0){
    srand (time(NULL));
    //generate random position, fill cell
    int q=rand()%height;
    int r=rand()%width;
    if(lifeArray[q][r]!='X'){
      lifeArray[q][r]='X';
      density--;
    }
    //break once grid has reached desired density
    if(density==0){
      cout<<"Grid Generated."<<endl;
      break;
    }
  }
}
//destructor
Life::~Life(){
  delete lifeArray;
  delete newArray;
  delete inArray;
}
/**
 * bool returns true if given grid positions contains a cell, or false if empty
 * @param  x the char at the position in the grid the program is looking at
 * @return   true or false, a bool
 */
bool Life::fullCell(char x){
  if (x=='X'){
    return true;
  }
  else if(x=='-'){
    return false;
  }
  else{
    cout<<"ERROR"<<endl;
  }
}
/**
 * Method runs the simulation in classic mode
 */
void Life::runClassic(){
  if(enter==true){
    getchar();
  }
  //generation number
  if(out_file.is_open())
    out_file<<gen<<endl;
  else
    cout<<gen<<endl;
  for(int row=0; row<height; ++row){
    for(int col=0; col<width; ++col){
      //write to file if user provided one
      if(out_file.is_open())
        out_file<<lifeArray[row][col];
      //write initial grid to console
      else
        cout<<lifeArray[row][col];
    }
    //formatting
    if(out_file.is_open())
      out_file<<endl;
    else
      cout<<endl;
  }
  gen++;
  //formatting
  if(out_file.is_open())
    out_file<<endl;
  else{
    if(enter==true){
      cout<<"Press Enter to continue.";
      getchar();
      cout<<endl;
    }
    else{
      //if user doesn't want to press enter between genreations, have a 2 sec pause between generations
      cout<<endl;
      chrono::seconds time(2);
      this_thread::sleep_for(time);
    }
  }
  //while the world isn't empty or stabilized
  while (test_equality==false){
    //overall map rows
    for(int row_c=0; row_c<height; row_c++){
      //overall maps columns
      for(int col_c=0; col_c<width; col_c++){
        //cell we are focusing on
        cell=lifeArray[row_c][col_c];
        sim=0;
        //check if current cell is full
        thiscell=fullCell(cell);
        for(int a=(row_c-1); a<=(row_c+1); a++){
          for(int b=(col_c-1); b<=(col_c+1); b++){
            if(a>=0 && b>=0 && a<height && b<width){
              thiscell=fullCell(lifeArray[a][b]);
            }
            else{
              thiscell=false;
            }
            if(thiscell==true){
              //total number of full cells
              sim++;
            }
          }
        }
        //do not count current cell in neighbor count
        if (cell=='X'){
          sim--;
        }
        //one or less neighbor
        if(sim<=1){
          newArray[row_c][col_c]='-';
        }
        //two neighbors
        else if(sim==2){
          if (cell=='X'){
            newArray[row_c][col_c]='X';
          }
          else{
            newArray[row_c][col_c]='-';
          }
        }
        //three neighbors
        else if(sim==3){
          newArray[row_c][col_c]='X';
        }
        //four or more neighbors
        else if(sim>=4){
          newArray[row_c][col_c]='-';
        }
      }
    }
    //generation number
    if(out_file.is_open())
      out_file<<gen<<endl;
    else
      cout<<gen<<endl;
    //printing generation to the console or file
    for(int row_new=0; row_new<height; ++row_new){
      for(int col_new=0; col_new<width; ++col_new){
        if(out_file.is_open())
          out_file<<newArray[row_new][col_new];
        else
          cout<<newArray[row_new][col_new];
      }
      //formatting
      if(out_file.is_open())
        out_file<<endl;
      else
        cout<<endl;
    }
    gen++;
    if(out_file.is_open())
      out_file<<endl;
    test_equality=true;
    //test for stabilization of world
    for(int equal=0; equal<height; ++equal){
      for(int ity=0; ity<width; ++ity){
        if(lifeArray[equal][ity]!=newArray[equal][ity]){
          test_equality=false;
        }
      }
    }
    //test for oscillating generations
    if(test_equality==false){
      test_equality=true;
      for(int oscil=0; oscil<height; ++oscil){
        for(int lation=0; lation<width; ++lation){
          if(oscilArray[oscil][lation]!=newArray[oscil][lation]){
            test_equality=false;
          }
        }
      }
    }
    if(out_file.is_open()==false){
      if(enter==true){
        cout<<"Press Enter to continue.";
        getchar();
      }
      else{
        chrono::seconds time(2);
        this_thread::sleep_for(time);
      }
    }
    if (test_equality==true)
      cout<<"World has stabilized"<<endl;
      if(out_file.is_open() && test_equality==true){
        cout<<"Output has been written to file "<<out_name<<endl;
      }
    else if(test_equality==false){
      if(out_file.is_open()==false)
        cout<<endl;
    }
    //copy contents of newArray to lifeArray to prepare for next generation simulation
    if(lifeArray!=newArray){
      for(int copy_h=0; copy_h<height; ++copy_h){
        for(int copy_w=0; copy_w<width; ++copy_w){
          oscilArray[copy_h][copy_w]=lifeArray[copy_h][copy_w];
          lifeArray[copy_h][copy_w]=newArray[copy_h][copy_w];
        }
      }
    }
  }
  if(out_file.is_open())
    out_file.close();
}
/**
 * Runs life similation in doughnut mode
 */
void Life::runDoughnut(){
  if(enter==true){
    getchar();
  }
  //generation count
  if(out_file.is_open())
    out_file<<gen<<endl;
  else
    cout<<gen<<endl;
    //print initial generation
  for(int row=0; row<height; ++row){
    for(int col=0; col<width; ++col){
      if(out_file.is_open())
        out_file<<lifeArray[row][col];
      else
        cout<<lifeArray[row][col];
    }
    //formatting
    if(out_file.is_open())
      out_file<<endl;
    else
      cout<<endl;
  }
  gen++;
  if(out_file.is_open())
    out_file<<endl;
  //press enter or pause between generations
  else{
    if(enter==true){
      cout<<"Press Enter to continue.";
      getchar();
      cout<<endl;
    }
    else{
      cout<<endl;
      chrono::seconds time(2);
      this_thread::sleep_for(time);
    }
  }
  //while world isn't empty or stabilized
  while (test_equality==false){
    //overall map rows
    for(int row_d=0; row_d<height; row_d++){
      //overall maps columns
      for(int col_d=0; col_d<width; col_d++){
        //cell we are focusing on
        cell=lifeArray[row_d][col_d];
        sim=0;
        //check if current cell is full
        thiscell=fullCell(cell);
        //check if world has stabilized
        for(int c=(row_d-1); c<=(row_d+1); c++){
          for(int d=(col_d-1); d<=(col_d+1); d++){
            if(c>=0 &&d>=0 && c<height && d<width){
              thiscell=fullCell(lifeArray[c][d]);
            }
            /*doughnut mode wraps ends into each other, so the following statements
              determine what is contained in locations off the grid
            */
            else if(c<0 && d<width){
              if(d<0)
                thiscell=fullCell(lifeArray[height-1][width-1]);
              else
                thiscell=fullCell(lifeArray[height-1][d]);
            }
            else if(c>=height && d>=0){
              if(d>=width)
                thiscell=fullCell(lifeArray[0][0]);
              else
                thiscell=fullCell(lifeArray[0][d]);
            }
            else if(d<0 && c>=0){
              if(c>=height)
                thiscell=fullCell(lifeArray[0][width-1]);
              else
                thiscell=fullCell(lifeArray[c][width-1]);
            }
            else if(d>=width && c<height){
              if(c<0)
                thiscell=fullCell(lifeArray[height-1][0]);
              else
                thiscell=fullCell(lifeArray[c][0]);
            }
            if(thiscell==true){
              //total number of full cells
              sim++;
            }
          }
        }
        //remove current cell from neightbor count
        if (cell=='X'){
          sim--;
        }
        //one or less neighbor
        if(sim<=1){
          newArray[row_d][col_d]='-';
        }
        //two neighbors
        else if(sim==2){
          if (cell=='X'){
            newArray[row_d][col_d]='X';
          }
          else{
            newArray[row_d][col_d]='-';
          }
        }
        //three neighbors
        else if(sim==3){
          newArray[row_d][col_d]='X';
        }
        //four neighbors
        else if(sim>=4){
          newArray[row_d][col_d]='-';
        }
      }
    }
    //formatting
    if(out_file.is_open())
      out_file<<gen<<endl;
    else
      cout<<gen<<endl;
    //print generation to console or file
    for(int row_new=0; row_new<height; ++row_new){
      for(int col_new=0; col_new<width; ++col_new){
        if(out_file.is_open())
          out_file<<newArray[row_new][col_new];
        else
          cout<<newArray[row_new][col_new];
      }
      //formatting
      if(out_file.is_open())
        out_file<<endl;
      else
        cout<<endl;
    }
    gen++;
    if(out_file.is_open())
      out_file<<endl;
    test_equality=true;
    //test for stabilization
    for(int equal=0; equal<height; ++equal){
      for(int ity=0; ity<width; ++ity){
        if(lifeArray[equal][ity]!=newArray[equal][ity]){
          test_equality=false;
        }
      }
    }
    //test for oscillating generations
    if(test_equality==false){
      test_equality=true;
      for(int oscil=0; oscil<height; ++oscil){
        for(int lation=0; lation<width; ++lation){
          if(oscilArray[oscil][lation]!=newArray[oscil][lation]){
            test_equality=false;
          }
        }
      }
    }
    //press enter or pause between generations
    if(out_file.is_open()==false){
      if(enter==true){
        cout<<"Press Enter to continue.";
        getchar();
      }
      else{
        chrono::seconds time(2);
        this_thread::sleep_for(time);
      }
    }
    if (test_equality==true)
      cout<<"World has stabilized"<<endl;
      if(out_file.is_open()&& test_equality==true){
        cout<<"Output has been written to file "<<out_name<<endl;
      }
    else if(test_equality==false){
      if(out_file.is_open()==false)
        cout<<endl;
    }
    //copy contents of newArray to lifeArray to prepare for next generation simulation
    if(lifeArray!=newArray){
      for(int copy_h=0; copy_h<height; ++copy_h){
        for(int copy_w=0; copy_w<width; ++copy_w){
          lifeArray[copy_h][copy_w]=newArray[copy_h][copy_w];
        }
      }
    }
  }
  if(out_file.is_open())
    out_file.close();
}
/**
 * Method runs life game in Mirror mode
 */
void Life::runMirror(){
  if(enter==true){
    getchar();
  }
  //generation count
  if(out_file.is_open())
    out_file<<gen<<endl;
  else
    cout<<gen<<endl;
  //print initial grid
  for(int row=0; row<height; ++row){
    for(int col=0; col<width; ++col){
      if(out_file.is_open())
        out_file<<lifeArray[row][col];
      else
        cout<<lifeArray[row][col];
    }
    //formatting
    if(out_file.is_open())
      out_file<<endl;
    else
      cout<<endl;
  }
  gen++;
  if(out_file.is_open())
    out_file<<endl;
  //press enter or pause between generations
  else{
    if(enter==true){
      cout<<"Press Enter to continue.";
      getchar();
      cout<<endl;
    }
    else{
      cout<<endl;
      chrono::seconds time(2);
      this_thread::sleep_for(time);
    }
  }
  //while world isn't empty or stabilized
  while (test_equality==false){
    //overall map rows
    for(int row_m=0; row_m<height; row_m++){
      //overall maps columns
      for(int col_m=0; col_m<width; col_m++){
        //cell we are focusing on
        cell=lifeArray[row_m][col_m];
        sim=0;
        //check if current cell is full
        thiscell=fullCell(cell);
        //cout<<"row_d "<<row_d<<" col_d "<<col_d<<endl;
        for(int c=(row_m-1); c<=(row_m+1); c++){
          for(int d=(col_m-1); d<=(col_m+1); d++){
            if(c>=0 &&d>=0 && c<height && d<width){
              thiscell=fullCell(lifeArray[c][d]);
            }
            /*Mirror mode says that locations off the grid are defined by the reflection
            of their exising neightbor. The following statements define which neighbor to refer to.
            */
            else if(c<0 && d<width){
              if(d<0)
                thiscell=fullCell(lifeArray[c+1][d+1]);
              else
                thiscell=fullCell(lifeArray[c+1][d]);
            }
            else if(c>=height && d>=0){
              if(d>=width)
                thiscell=fullCell(lifeArray[c-1][d-1]);
              else
                thiscell=fullCell(lifeArray[c-1][d]);
            }
            else if(d<0 && c>=0){
              if(c>=height)
                thiscell=fullCell(lifeArray[c-1][d+1]);
              else
                thiscell=fullCell(lifeArray[c][d+1]);
            }
            else if(d>=width && c<height){
              if(c<0)
                thiscell=fullCell(lifeArray[c+1][d-1]);
              else
                thiscell=fullCell(lifeArray[c][d-1]);
            }
            if(thiscell==true){
              //total number of full cells
              sim++;
            }
          }
        }
        //don't count current cell in neightbor count
        if (cell=='X'){
          sim--;
        }
        //one or less neighbor
        if(sim<=1){
          newArray[row_m][col_m]='-';
        }
        //two neighbors
        else if(sim==2){
          if (cell=='X'){
            newArray[row_m][col_m]='X';
          }
          else{
            newArray[row_m][col_m]='-';
          }
        }
        //three neighbors
        else if(sim==3){
          newArray[row_m][col_m]='X';
        }
        //four neighbors
        else if(sim>=4){
          newArray[row_m][col_m]='-';
        }
      }
    }
    //formatting
    if(out_file.is_open())
      out_file<<gen<<endl;
    else
      cout<<gen<<endl;
    //print generation to console or file
    for(int row_new=0; row_new<height; ++row_new){
      for(int col_new=0; col_new<width; ++col_new){
        if(out_file.is_open())
          out_file<<newArray[row_new][col_new];
        else
          cout<<newArray[row_new][col_new];
      }
      //formatting
      if(out_file.is_open())
        out_file<<endl;
      else
        cout<<endl;
    }
    gen++;
    if(out_file.is_open())
      out_file<<endl;
    test_equality=true;
    //test for stabilization
    for(int equal=0; equal<height; ++equal){
      for(int ity=0; ity<width; ++ity){
        if(lifeArray[equal][ity]!=newArray[equal][ity]){
          test_equality=false;
        }
      }
    }
    //test for oscillating generations
    if(test_equality==false){
      test_equality=true;
      for(int oscil=0; oscil<height; ++oscil){
        for(int lation=0; lation<width; ++lation){
          if(oscilArray[oscil][lation]!=newArray[oscil][lation]){
            test_equality=false;
          }
        }
      }
    }
    //press enter or pause between generations
    if(out_file.is_open()==false){
      if(enter==true){
        cout<<"Press Enter to continue.";
        getchar();
      }
      else{
        chrono::seconds time(2);
        this_thread::sleep_for(time);
      }
    }
    if (test_equality==true)
      cout<<"World has stabilized"<<endl;
      if(out_file.is_open() && test_equality==true){
        cout<<"Output has been written to file "<<out_name<<endl;
      }
    else if(test_equality==false){
      if(out_file.is_open()==false)
        cout<<endl;
    }
    //copy contents of newArray to lifeArray to prepare for next generation simulation
    if(lifeArray!=newArray){
      for(int copy_h=0; copy_h<height; ++copy_h){
        for(int copy_w=0; copy_w<width; ++copy_w){
          lifeArray[copy_h][copy_w]=newArray[copy_h][copy_w];
        }
      }
    }
  }
  if(out_file.is_open())
    out_file.close();
}
