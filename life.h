/** life.h
 *Header file for game of life
 *@author Mary Kate Crittenden
 *2278514
 *critt102@mail.chapman.edu
 *CPSC 350-01
 *Assignment 2
 */
#include <iostream>
#include <fstream>
using namespace std;

/**
 * The class Life contains methods for running the game in differnet modes (runClassic, runDoughnut, run Mirror)
 * provides methods isEmpty, isStable, and fullCell, various variables, and 3 char array pointers.
 */
class Life{
  public:
  //constructor
  Life();
  //overloaded constructor
  Life(string file_name);
  //overloaded constructor for random grid assignment
  Life(int r_height, int r_width, double r_decimal);
  //destructor
  ~Life();

  //runs the game in classic mode
  void runClassic();
  //runs game in doughnut mode
  void runDoughnut();
  //runs game in Mirror mode
  void runMirror();

  //checks whether the current position contains a cell
  bool fullCell(char x);

  //height of grid
  int height;
  //width of grid
  int width;
  //represents the total number of variables in a grid
  int numvar;
  //value used to take in values from a file
  int loopvalue;
  //used for looping through array of info from file
  int currentvalue;
  //cell we are currently checking for neighbors
  char cell;
  //true if two cells are equal
  bool test_equality;
  //whether or not the user wants to press enter between generations
  bool enter;
  //input from user for whether they want to press enter
  char enter_in;
  //stream to read in file
  ifstream in_file;
  //stream to write to file
  ofstream out_file;
  //whether or not the current position contains a cell
  bool thiscell;
  //number of neighbors
  int sim;
  //current line from file
  string line;
  //decimal to calcuate density of random life grid
  double rand_dec;
  //hold input of whether user wants to write to an output file
  char outputfile;
  //name of file user wants to output results to
  string out_name;
  //number of generations
  int gen;

  //array of values from input file
  char *inArray;
  //array being looked at in the game
  char **lifeArray;
  //resulting array after generational rules are applied
  char **newArray;
  //array used to check oscillating generation loop
  char **oscilArray;
};
