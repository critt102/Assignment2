#include "classicLife.h"
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char**argv){
  string file_name=argv[1];
  ClassicLife gameone(file_name);
  //gameone.runClassic();
  gameone.runDoughnut();
  return 0;
}
