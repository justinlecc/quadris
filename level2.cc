
#include "level.h"

#include <cstdlib>

// Constructor

Level2::Level2() {
  srand(Level::getSeed());
}

// Destructor, to avoid warning messages
Level2::~Level2() {}

char Level2::newBlockType() {
  
  // Probabilities:
  // all blocks: 1/7
  
  int r = rand() % 7;
  
  return
  r == 0 ? 'S' :
  r == 1 ? 'Z' :
  r == 2 ? 'I' :
  r == 3 ? 'J' :
  r == 4 ? 'L' :
  r == 5 ? 'O' :
  'T' ;
  
}