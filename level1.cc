
#include "level.h"
// change this to #include "level.h" later

//const int seed = 0; // this will be replaced by Level::seed

#include <cstdlib>


// Constructor

Level1::Level1() {
  srand(Level::getSeed());
}

// Destructor, to avoid warning messages
Level1::~Level1() {}

char Level1::newBlockType() {
  
  // Probabilities:
  // S and Z: 1/12 for each
  // others: 1/6
  
  int r = rand() % 12;
  
  return
  r == 0 ? 'S' :
  r == 6 ? 'Z' :
  r%6 == 1 ? 'I' :
  r%6 == 2 ? 'J' :
  r%6 == 3 ? 'L' :
  r%6 == 4 ? 'O' :
  'T' ;
  
}