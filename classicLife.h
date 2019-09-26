#include <iostream>
#include <fstream>
using namespace std;

class ClassicLife{
  public:
  ClassicLife();
  ClassicLife(string file_name);
  ~ClassicLife();

  void writeToFile(string out_name);
  void runSimulation();

  bool isEmpty();
  bool isStable();
  bool fullCell(char x);

  int height;
  int width;
  int numvar;
  int loopvalue;
  int currentvalue;
  char cell;
  //ifstream in_file;
  // ofstream out_file;
  char c;
  bool thiscell;
  int sim;
  string line;

  char *inArray;
  char **lifeArray;
  char **newArray;
};
