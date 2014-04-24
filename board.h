#ifndef __BOARD_H__
#define __BOARD_H__

// board.h
//
// By Michael Hewson and Justin Leclerc
//
// Part of Quadris

#include <vector>
class Block;
class Cell;

class GameOver {};

extern const int NUM_ROWS;
extern const int NUM_COLS;

class Board {
  // static attributes
  static Board * instance;
  
  // object attributes
  Block * current_block;
  Block * next_block;
  std::vector <Block *> dropped_blocks;
  Cell * thegrid[15][10];
  // NUM_ROWS should equal 15, NUM_COLS should equal 18.
  
  // private static methods
  static void cleanup();
  
  // private object methods
  void printNextBlock();
  Board();
  ~Board();
  std::vector<int> checkForFullLines();
  
public:
  
  // public static methods
  static Board * getInstance();
  
  // returns pointer to next block
  Block* getNextBlock();
  
  // public object methods
  void down();
  void right();
  void left();
  void clockwise();
  void counterClockwise();
  void drop();
  void restart();
  void drawGameOverText();
  
  // cellLookup()
  // Returns a point to the specified cell
  Cell* cellLookup(int row, int col) const;
  
  void removeDroppedBlock(Block * b);
  
  void moveNextBlockToCurrentBlockAndMakeNewNextBlock();
  
  // drawText(): outputs the board's state to stdout
  void drawText();
};

#endif