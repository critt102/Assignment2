#include "classicLife.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
using namespace std;

ClassicLife::ClassicLife(){
  width=1;
  height=1;
  numvar=1;
  loopvalue=0;
  currentvalue=2;
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
  gen=0;
  test_equality=false;
  rand_dec=0;
  in_file.open(filename, ios::in);
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
  else{
    cout<<"Do you want to press the enter key between generations? y or n? "<<endl;
    cin>>enter_in;
    enter_in=tolower(enter_in);
    if(enter_in=='y'){
      enter=true;
    }
    else{
      enter=false;
    }
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
    }
  }
}

ClassicLife::ClassicLife(int r_height, int r_width, double r_decimal){
  rand_dec=r_decimal;
  outputfile='n';
  out_name="";
  height=r_height;
  width=r_width;
  numvar=1;
  gen=0;
  loopvalue=0;
  currentvalue=2;
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
  else{
    cout<<"Do you want to press the enter key between generations? y or n? "<<endl;
    cin>>enter_in;
    enter_in=tolower(enter_in);
    if(enter_in=='y'){
      enter=true;
    }
    else{
      enter=false;
    }
  }

  //create 2d array
  lifeArray= new char*[width];
  newArray=new char*[width];
  for(int k = 0; k < width; ++k){
    lifeArray[k] = new char[height];
    newArray[k] = new char[height];
  }
  //fill array with '-'
  for(int f=0; f<height; ++f){
    for(int g=0; g<width; ++g){
      lifeArray[f][g]='-';
    }
  }
  //fill with 'X' according to density calculation
  double density= (width*height)*rand_dec;
  while(density>0){
    srand (time(NULL));
    for(int q=0; q<height; ++q){
      if(density==0){
        break;
      }
      for(int r=0; r<width; ++r){
        if(density==0){
          break;
        }
        int num_a=rand()%2;
        if(num_a==1){
          lifeArray[q][r]='X';
          density--;
        }
      }
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
  else if(x=='-'){
    return false;
  }
  else{
    cout<<"ERROR"<<endl;
  }
}

void ClassicLife::runClassic(){
  if(enter==true){
    getchar();
  }
  if(out_file.is_open())
    out_file<<gen<<endl;
  else
    cout<<gen<<endl;
  for(int row=0; row<height; ++row){
    for(int col=0; col<width; ++col){
      if(out_file.is_open())
        out_file<<lifeArray[row][col];
      else
        cout<<lifeArray[row][col];
    }
    if(out_file.is_open())
      out_file<<endl;
    else
      cout<<endl;
  }
  gen++;
  if(out_file.is_open())
    out_file<<endl;
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
              //  if(c>=0 &&d>=0 && c<height && d<width)
              thiscell=fullCell(lifeArray[a][b]);
            }
            else{
              thiscell=false;
            }
            if(thiscell==true){
              sim++;
            }
          }
        }
        if (cell=='X'){
          sim--;
        }
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

    if(out_file.is_open())
      out_file<<gen<<endl;
    else
      cout<<gen<<endl;
    for(int row_new=0; row_new<height; ++row_new){
      for(int col_new=0; col_new<width; ++col_new){
        if(out_file.is_open())
          out_file<<newArray[row_new][col_new];
        else
          cout<<newArray[row_new][col_new];
      }

      if(out_file.is_open())
        out_file<<endl;
      else
        cout<<endl;
    }
    gen++;
    if(out_file.is_open())
      out_file<<endl;
    test_equality=true;
    for(int equal=0; equal<height; ++equal){
      for(int ity=0; ity<width; ++ity){
        if(lifeArray[equal][ity]!=newArray[equal][ity]){
          test_equality=false;
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

void ClassicLife::runDoughnut(){
  if(enter==true){
    getchar();
  }

  if(out_file.is_open())
    out_file<<gen<<endl;
  else
    cout<<gen<<endl;
  for(int row=0; row<height; ++row){
    for(int col=0; col<width; ++col){
      if(out_file.is_open())
        out_file<<lifeArray[row][col];
      else
        cout<<lifeArray[row][col];
    }
    if(out_file.is_open())
      out_file<<endl;
    else
      cout<<endl;
  }
  gen++;
  if(out_file.is_open())
    out_file<<endl;
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
        //cout<<"row_d "<<row_d<<" col_d "<<col_d<<endl;
        for(int c=(row_d-1); c<=(row_d+1); c++){
          for(int d=(col_d-1); d<=(col_d+1); d++){
            if(c>=0 &&d>=0 && c<height && d<width){
              thiscell=fullCell(lifeArray[c][d]);
            }
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
              sim++;
            }
            else{
            }
          }
        }
        if (cell=='X'){
          sim--;
        }
        if(sim<=1){
          newArray[row_d][col_d]='-';
        }
        else if(sim==2){
          if (cell=='X'){
            newArray[row_d][col_d]='X';
          }
          else{
            newArray[row_d][col_d]='-';
          }
        }
        else if(sim==3){
          newArray[row_d][col_d]='X';
        }
        else if(sim>=4){
          newArray[row_d][col_d]='-';
        }
      }
    }

    if(out_file.is_open())
      out_file<<gen<<endl;
    else
      cout<<gen<<endl;
    for(int row_new=0; row_new<height; ++row_new){
      for(int col_new=0; col_new<width; ++col_new){
        if(out_file.is_open())
          out_file<<newArray[row_new][col_new];
        else
          cout<<newArray[row_new][col_new];
      }
      if(out_file.is_open())
        out_file<<endl;
      else
        cout<<endl;
    }
    gen++;
    if(out_file.is_open())
      out_file<<endl;
    test_equality=true;
    for(int equal=0; equal<height; ++equal){
      for(int ity=0; ity<width; ++ity){
        if(lifeArray[equal][ity]!=newArray[equal][ity]){
          test_equality=false;
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
      if(out_file.is_open()&& test_equality==true){
        cout<<"Output has been written to file "<<out_name<<endl;
      }
    else if(test_equality==false){
      if(out_file.is_open()==false)
        cout<<endl;
    }
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

void ClassicLife::runMirror(){
  if(enter==true){
    getchar();
  }
  if(out_file.is_open())
    out_file<<gen<<endl;
  else
    cout<<gen<<endl;
  for(int row=0; row<height; ++row){
    for(int col=0; col<width; ++col){
      if(out_file.is_open())
        out_file<<lifeArray[row][col];
      else
        cout<<lifeArray[row][col];
    }
    if(out_file.is_open())
      out_file<<endl;
    else
      cout<<endl;
  }
  gen++;
  if(out_file.is_open())
    out_file<<endl;
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
              sim++;
            }
            else{
            }
          }
        }
        if (cell=='X'){
          sim--;
        }
        if(sim<=1){
          newArray[row_m][col_m]='-';
        }
        else if(sim==2){
          if (cell=='X'){
            newArray[row_m][col_m]='X';
          }
          else{
            newArray[row_m][col_m]='-';
          }
        }
        else if(sim==3){
          newArray[row_m][col_m]='X';
        }
        else if(sim>=4){
          newArray[row_m][col_m]='-';
        }
      }
    }
    if(out_file.is_open())
      out_file<<gen<<endl;
    else
      cout<<gen<<endl;
    for(int row_new=0; row_new<height; ++row_new){
      for(int col_new=0; col_new<width; ++col_new){
        if(out_file.is_open())
          out_file<<newArray[row_new][col_new];
        else
          cout<<newArray[row_new][col_new];
      }
      if(out_file.is_open())
        out_file<<endl;
      else
        cout<<endl;
    }
    gen++;
    if(out_file.is_open())
      out_file<<endl;
    test_equality=true;
    for(int equal=0; equal<height; ++equal){
      for(int ity=0; ity<width; ++ity){
        if(lifeArray[equal][ity]!=newArray[equal][ity]){
          test_equality=false;
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

bool ClassicLife::isEmpty(){
  return false;
}
bool ClassicLife::isStable(){
  return true;
}
//this has changed
