//
//  level0.cpp
//  
//
//  Created by Justin and Michael on 13-11-23.
//
//

#include "level.h"
#include "block.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

// static definitions
static vector<char> script_chars;

// module scope global constant
//static int num_chars = 0;
static bool initialized = false;

// Constructor.
Level0::Level0(){
  if (!initialized) {
    ifstream input;
    input.open(getScriptFile().c_str());
    if (!input) {
      throw (BadScriptFile());
    }
    char c;
    for(int i = 0; input >> c; i++){
      script_chars.push_back(c);
      //num_chars++;
    }
    initialized=true;
    input.close();
  } 
};

// Destructor, to avoid warning messages.
Level0::~Level0() {}

// newBlockType()
// Returns the next block type character.
char Level0::newBlockType() {
  static int index = 0; // will overflow if scriptfile contains several billion chars
  char retChar;
  if (script_chars.size() != 0){
    retChar = script_chars.at(index % script_chars.size());
    index++;
    return retChar;
  } else {
    return '\0';
  }
};
