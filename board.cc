//board.cc

#include "board.h"
#include "scoreboard.h"
#include "level.h"
#include "cell.h"
#include "block.h"

#include <cstdlib>
#include <cassert>

//#include <iostream>
//using namespace std;

// GLOBAL CONSTANTS
// if you change any of these constants, you will also have to change
// values in board.h
const int NUM_COLS = 10;
const int NUM_ROWS = 15;
const int STARTING_ROW = 11;


// Static Attributes - initialized here
Board * Board::instance = 0;



// Methods for Singleton Pattern:

// static, private
void Board::cleanup() {
  delete instance;
}

// static, public
Board * Board::getInstance() {
  if (0 == instance) {
    instance = new Board;
    
    getInstance()->next_block = Level::getCurrentLevel()->createBlock();
    
    getInstance()->moveNextBlockToCurrentBlockAndMakeNewNextBlock();
    
    atexit(cleanup);
  }
  return instance;
}

// Private Constructor
Board::Board() {
  
  // Initialize Cell Grid with Row and Column Values.
  for (int i = 0; i < NUM_ROWS; i++) {
    for (int j = 0; j < NUM_COLS; j++) {
      thegrid[i][j] = new Cell(i,j);
    }
  }
  
  // set these to NULL, just in case
  next_block = 0;
  current_block = 0;
  
}

// Private Destructor
Board::~Board() {
  for (int i = 0; i < NUM_ROWS; i++) {
    for (int j = 0; j < NUM_COLS; j++) {
      delete thegrid[i][j];
    }
  }
  
  delete next_block;
  delete current_block;
  
  // Note: dropped_blocks is a vector object, and will delete itself. But we still need to
  //       delete its Block * 's
  for (unsigned int i = 0; i < dropped_blocks.size(); i++) {
    delete dropped_blocks[i]; // [i] instead of .at(i) to avoid exceptions
  }
}





// Public Command Methods

// left()
void Board::left() {
  current_block->moveLeft();
}

// right()
void Board::right(){
  current_block->moveRight();
}

// down()
void Board::down(){
  current_block->moveDown();
}

// clockwise()
void Board::clockwise() {
  current_block->rotate(true); // true for clockwise
}


// Note: checkForFullLines() and drop() are now implemented in board-drop.cc

// counterClockwise()
void Board::counterClockwise() {
  current_block->rotate(false); // false for counterclockwise
}

// getNextBlock()
// Returns a pointer to the next_block
Block* Board::getNextBlock(){
  return next_block;
}

// restart()
void Board::restart() {
  // delete all cells without deleting the actual grid of cells
  for (int i = 0; i < NUM_ROWS; i++) {
    for (int j = 0; j < NUM_COLS; j++) {
      thegrid[i][j]->setBlock(0);
      
      // erase blocks
      thegrid[i][j]->undraw();
    }
  }
  // delete dropped_blocks - also have to delete each block
  for (unsigned int i = 0; i < dropped_blocks.size(); i++) {
    delete dropped_blocks.at(i);
  }
  dropped_blocks.clear();
  
  // delete current_block and next_block and set to null
  delete current_block;
  current_block = 0;
  
  delete next_block;
  next_block = 0;
  
  // level should start with the same sequence as during startup
  Level::changeLevel(Level::getCurrentLevelID());
  
  // make new next_block
  next_block = Level::getCurrentLevel()->createBlock();
  
  // self explanatory
  moveNextBlockToCurrentBlockAndMakeNewNextBlock();
  
  // reset score but not hiscore
  ScoreBoard::getInstance()->restart();
  
  
}



// cellLookup()
// Returns a point to the specified cell
Cell* Board::cellLookup(int row, int col) const{
  assert (row < NUM_ROWS);
  assert (col < NUM_COLS);
  return thegrid[row][col];
};

// removeDroppedBlock()
void Board::removeDroppedBlock(Block * b) {
  for (unsigned int i = 0; i < dropped_blocks.size(); i++) {
    if (dropped_blocks.at(i) == b) {
      dropped_blocks.erase(dropped_blocks.begin() + i);
    }
  }
}



void Board::moveNextBlockToCurrentBlockAndMakeNewNextBlock() {
  try {
    next_block->putOnBoard();
  }
  catch (NoRoomForBlock) {
    throw;
  }
  current_block = next_block;
  next_block = Level::getCurrentLevel()->createBlock();
}




