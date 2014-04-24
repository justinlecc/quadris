#ifndef __BLOCK_H__
#define __BLOCK_H__

class Cell;

extern const int BLOCK_SIZE; // should be 4

class BadBlockType{}; 
class NoRoomForBlock{};

class Block {
  bool isValidMove(int row, int col);
public:
  Cell * cells[4]; // BLOCK_SIZE is 4
  const char block_type;
  const int level_created;
  Block(char block_type, int level_created);
  ~Block();
  void putOnBoard();
  
  //obsolete:
  //int const* getStartingCoords();
  
  bool moveDown();
  void moveRight();
  void moveLeft();
  void rotate(bool Clockwise);
  
  
};

#endif