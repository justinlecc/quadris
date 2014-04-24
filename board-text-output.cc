
#include "board.h"
#include "block.h"
#include "cell.h"
#include "scoreboard.h"
#include "level.h"
#include "boardgraphics.h"

#include <iostream>
#include <iomanip>
using namespace std;

// Screen Output

static void printDashedLine() {
  for (int i = 0; i < NUM_COLS; i++) {
    cout << "-";
  }
  cout << endl;
}

// printNextBlock()
// Prints out the block in the 'next' position
void Board::printNextBlock() {
  cout << "Next:" << endl;
  
  // Printing Graphically
  BoardGraphics::getInstance()->changeNextBlock(next_block->block_type);
  
  switch (next_block->block_type) {
    case 'I':
      cout << "IIII" << endl;
      break;
    case 'J':
      cout << "J" << endl << "JJJ" << endl;
      break;
    case 'L':
      cout << "  L" << endl << "LLL" << endl;
      break;
    case 'O':
      cout << "OO" << endl << "OO" << endl;
      break;
    case 'S':
      cout << " SS" << endl << "SS" << endl;
      break;
    case 'Z':
      cout << "ZZ" << endl << " ZZ" << endl;
      break;
    case 'T':
      cout << "TTT" << endl << " T" << endl;
      break;
    default:
      throw (BadBlockType());
      break;
  }
};

void Board::drawText() {
  cout << "Level:" << setw(7) << Level::getCurrentLevelID() << endl;
  cout << "Score:" << setw(7)
  << ScoreBoard::getInstance()->getCurrentScore() << endl;
  cout << "High Score:" << setw(2)
  << ScoreBoard::getInstance()->getHiScore() << endl;
  
  printDashedLine();
  
  for (int i = NUM_ROWS-1; i >= 0; i--) {
    for (int j = 0; j < NUM_COLS; j++) {
      cout << thegrid[i][j]->getCharacter();
    }
    cout << endl;
  }
  printDashedLine();
  printNextBlock();
  
};

// Prints Game Over Screen
void Board::drawGameOverText() {
  
  // copying and pasting from drawText() - being lazy. Hopefully
  // this doesn't bite me in the ass :)
  
  cout << "Level:" << setw(7) << Level::getCurrentLevelID() << endl;
  cout << "Score:" << setw(7)
  << ScoreBoard::getInstance()->getCurrentScore() << endl;
  cout << "High Score:" << setw(2)
  << ScoreBoard::getInstance()->getHiScore() << endl;
  
  printDashedLine();
  
  for (int i = NUM_ROWS-1; i >= 0; i--) {
    for (int j = 0; j < NUM_COLS; j++) {
      cout << thegrid[i][j]->getCharacter();
    }
    cout << endl;
  }
  printDashedLine();
  
  // instead of printNextBlock():
  cout << "GAME OVER" << endl;
}