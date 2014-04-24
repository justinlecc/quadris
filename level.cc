//
//  level.cc
//  
//
//  Created by Justin and Michael on 13-11-23.
//
//
#include "block.h"
#include "level.h"
#include "boardgraphics.h"
#include <string>
#include <iostream>
#include <cstdlib>
using namespace std;

// module constants

static const int MIN_LEVEL = 0;
static const int MAX_LEVEL = 3;

// Static Member Variables - Initialize Here

int Level::current_level_id = 0;

int Level::seed = 0;

std::string Level::scriptfile = "sequence.txt";

// this can't be initialized to Level0 - Otherwise we will use sequence.txt
// as the scriptfile even if we want to use a different one.
// initialize to NULL instead. An instance of the 
// Level0 class will be created when one of getCurrentLevel
// or getCurrentLevelID is called, unless changeLevel is called
// first.
Level* Level::current_level = 0;



//static methods


// get current_level and current_level_id

int Level::getCurrentLevelID() {
  if (!current_level) {
    current_level = new Level0();
    current_level_id = 0;
    atexit(cleanup);
  }
  return current_level_id;
}

// bit of a singleton pattern here. There's only ever one Level at one time.

Level * Level::getCurrentLevel() {
  if (!current_level) {
    current_level = new Level0();
    atexit(cleanup);
  }
  return current_level;
}

void Level::changeLevel(int level_id) {
  bool initializing = false;
  if (!current_level) {
    initializing = true;
  } else {
    delete current_level;
  }
  switch (level_id) {
    case 0:
      current_level = new Level0();
      current_level_id = 0;
      BoardGraphics::getInstance()->changeLevel();
      break;
    case 1:
      current_level = new Level1();
      current_level_id = 1;
      BoardGraphics::getInstance()->changeLevel();
      break;
    case 2:
      current_level = new Level2();
      current_level_id = 2;
      BoardGraphics::getInstance()->changeLevel();
      break;
    case 3:
      current_level = new Level3();
      current_level_id = 3;
      BoardGraphics::getInstance()->changeLevel();
      break;
    default:
      throw (BadLevelID());
      break;
  }
  if (initializing) {
    atexit(cleanup);
  }
}

void Level::cleanup() {
  delete current_level;
}

// levelUp() and levelDown()

void Level::levelUp() {
  if (current_level_id == MAX_LEVEL) {
    return;
  } else {
    changeLevel(current_level_id+1);
#ifdef DEBUG_LEVEL
    cerr << "levelUp: changing level to " << current_level_id+1 << endl;
#endif
  }
}

void Level::levelDown() {
  if (current_level_id == MIN_LEVEL) {
    return;
  } else {
    changeLevel(current_level_id-1);
#ifdef DEBUG_LEVEL
    cerr << "levelDown: changing level to " << current_level_id-1 << endl;
#endif
  }
}



// Object (non-static) Methods

// Destructor - to avoid warning messages
Level::~Level() {}

// get and change seed:

int Level::getSeed() {
  return seed;
}

void Level::changeSeed(int new_seed) {
  seed = new_seed;
}



// get and change scriptfile:

string Level::getScriptFile() {
  return scriptfile;
}

void Level::changeScriptFile(const string &scriptfile) {
  Level::scriptfile = scriptfile;
}



// createBlock()
// Returns a new block (created using the ifstream).
// caller is responsible for calling delete on the returned Block *.
Block* Level::createBlock() {
  char block_char = newBlockType();
  Block* return_block = new Block(block_char, current_level_id);
  return return_block;
};
