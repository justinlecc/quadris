
// command.cc
// implementation of command interpreter for Quadris
// defines function readCommand
// By Michael Hewson and Justin Leclerc


#include "command.h"
#include "board.h"
#include "level.h"
#include <iostream>
//include <stdexcept>
#include <string>
using namespace std;


static const int NUM_COMMANDS = 9;

enum {Left = 0, Right, Down, Clockwise, CounterClockwise, Drop, LevelUp, LevelDown, Restart};

static string command_list[] = {
  "left",
  "right",
  "down",
  "clockwise",
  "counterclockwise",
  "drop",
  "levelup",
  "leveldown",
  "restart"
};

static bool str_match(string input_cmd, string full_cmd) {
  for (unsigned int i = 0; i < input_cmd.length(); i++) {
    if (input_cmd[i] != full_cmd[i]) {
      // possible segfault if input_cmd is longer than full_cmd
      return false;
    }
  }
  return true;
}

static void execute(int cmd_id) {
  //cout << command_list[cmd_id] << endl;
  // above is to check that it works
  
  Board * theboard = Board::getInstance();
  
  switch (cmd_id) {
    case Left:
      //cout << "left" << endl;
      theboard->left();
      break;
    case Right:
      //cout << "right" << endl;
      theboard->right();
      break;
    case Down:
      //cout << "down" << endl;
      theboard->down();
      break;
    case Clockwise:
      //cout << "clockwise" << endl;
      theboard->clockwise();
      break;
    case CounterClockwise:
      //cout << "counterclockwise" << endl;
      theboard->counterClockwise();
      break;
    case Drop:
      //cout << "drop" << endl;
      theboard->drop();
      break;
    case LevelUp:
      //cout << "levelup" << endl;
      Level::levelUp();
      break;
    case LevelDown:
      //cout << "leveldown" << endl;
      Level::levelDown();
      break;
    case Restart:
      //cout << "restart" << endl;
      theboard->restart();
      break;
  }
}


void readCommand() {
  
  // prompt user for command:
  //cout << "Enter a command." << endl;;
  // we can add: ", or help for a list of commands and descriptions."
  // if we implement a help command.
  
  
  while (1) {
    
    // check for multiplier:
    int multiplier;
    cin >> multiplier;
    if (cin.fail()) {
      if (cin.eof()) {
        throw(EndOfFile());
      } else {
        cin.clear();
        multiplier = 1;
      }
    }
    
    string cmd;
    
    cin >> cmd;
    
    if (cin.fail()) {
      throw(EndOfFile());
    }
    
    
    
    // evaluate cmd for match to possible commands.
    
    // implementation that doesn't use <regex>:
    // create helper function str_match that returns true if every character in cmd matches
    // the character with the same index in full_cmd; and false otherwise.
    // then call str_match on cmd with every command in the list of possible commands, and if cmd
    // matches exactly one command in the list, execute that command.
    
    int which_command_matches = -1;
    // -1 means that either no commands match
    // -2 means more than one command matches
    //
    
    for (int i = 0; i < NUM_COMMANDS; i++) {
      if (str_match(cmd, command_list[i])) {
        if (which_command_matches != -1) {
          which_command_matches = -2;
          break;
          // leave for loop so that it stays at -1
        } else {
          which_command_matches = i;
        }
      }
    }
    if (which_command_matches >= 0) {
      // do the command multiplier times, but only once if it's restart.
      
      
      if (which_command_matches == Restart) {
        multiplier = 1;
      }
      
      
      for (int i = 0; i < multiplier; i++) {
        execute(which_command_matches);
      }
      
      break;
      
    }
    else {
      cerr << "Command '" << cmd << "' is not recognized or is ambiguous." << endl;
      // can add "type 'help' for a list of commands"
      continue;
    }
  }
}