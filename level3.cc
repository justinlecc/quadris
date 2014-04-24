
#include "level.h"

#include <cstdlib>

// Constructor

Level3::Level3() {
  srand(Level::getSeed());
}

// Destructor, to avoid warning messages
Level3::~Level3() {}

char Level3::newBlockType() {
  
  // Probabilities:
  // S and Z Blocks: 2/9
  // others: 1/9
  
  int r = rand() % 9;
  
  return
  r <= 1  ? 'S' :
  r <= 3  ? 'Z' :
  r == 4 ? 'I' :
  r == 5 ? 'J' :
  r == 6 ? 'L' :
  r == 7 ? 'O' :
  'T' ;
  
}