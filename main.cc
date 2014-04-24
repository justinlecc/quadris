// main.cc
// mainline for Quadris
// by Michael Hewson and Justin Leclerc
// Copywright (c) 2013. All rights reserved.

#include "command.h"
#include "board.h"
#include "level.h"
#include "boardgraphics.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>

using namespace std;

// global variables, set by command-line options
bool graphical = true;
unsigned int seed = 0;
string scriptfile = "./sequence.txt";
int startlevel = 0;

class BadArguments{};

int main(int argc, char * argv[]) {
  // command-line options
  try {
    for (int i = 1; i < argc; i++) {
      string opt = argv[i];
      if ("-text" == opt) {
        graphical = false;
      } else if ("-seed" == opt) {
        i++;
        if (i < argc) { // to avoid segfault
          seed = atoi(argv[i]);
        }else {
          throw(BadArguments());
        }
      }
      else if ("-scriptfile" == opt) {
        i++;
        if (i < argc) {
          scriptfile = argv[i];
        } else {
          throw(BadArguments());
        }
      }
      else if ("-startlevel" == opt) {
        i++;
        if (i < argc) {
          startlevel = atoi(argv[i]);
        }else {
          throw(BadArguments());
        }
      }
    }
  }
  catch (BadArguments) {
    cerr << "Quadris: Bad Command Line Arguments" << endl;
    exit (1);
  }
  
# ifdef DEBUG_CMD_LINE_OPTIONS
  cout << "graphical: " << graphical << endl;
  cout << "seed: " << seed << endl;
  cout << "scriptfile: " << scriptfile << endl;
  cout << "startlevel: " << startlevel << endl;
# endif

  
  // initialization here
  Level::changeScriptFile(scriptfile);
  Level::changeSeed(seed);
  Level::changeLevel(startlevel);
  if (graphical) {
    BoardGraphics::getInstance()->TurnOnGraphics();
  }
  Board * theboard = Board::getInstance();

  
  while (1) {
    
    // output board's state using Board::drawText()
    theboard->drawText();
    // below was for testing
    //cout << "Current Level: " << Level::getCurrentLevelID() << endl;
    
    
    // use exceptions and a try block to catch EOF and GameOver
    try {
      readCommand();
      // may output to stdout to prompt user, or to stderr if bad command.
    }
    catch (EndOfFile){
      break;
    }
    catch (GameOver) {
      //show gameover screen
      // TODO:
      
      // commenting this out:
      //theboard->drawGameOverText();
      
      // output to stderr so it doesn't mess with evaluation testing.
      cerr << "GAME OVER. Restarting." << endl;
      
      sleep(3);
      
      theboard->restart();
      continue;
      
      /*
      //prompt for restart
      cout << "Game Over. Restart? (Y/n)" << endl;
      { // declaring scope, so as not to cloud namespace
        bool restart = false;
        
        string s;
        // using a string instead of a char, in case they type
        // "drop down", and the drop command causes GameOver.
        // When reading in a char, the program would recognize the 'n' in
        // "down" and end the program.
        
        while (cin >> s) {
          if ("Y" == s || "y" == s) {
            restart = true;
            break;
          } else if ("N" == s || "n" == s) {
            restart = false;
            break;
          }
        }
        if (restart) {
          theboard->restart();
          continue;
        } else {
          break;
        }
      }
      throw; // this should never be reached
      */
    }
  }
  BoardGraphics::getInstance()->TurnOffGraphics();
}
