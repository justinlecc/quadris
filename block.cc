// block.cc
//
// By Michael Hewson and Justin Leclerc

#include "block.h"
#include "cell.h"
#include "board.h"
//#define NULL 0
#include <iostream>
using namespace std;

const int BLOCK_SIZE = 4;

// moveDown()
// Moves the Block down one position in Board::thegrid.
// Returns true if move executed, false if the move was invalid.
bool Block::moveDown(){
  for (int i = 0; i < BLOCK_SIZE; i++){
    if (cells[i]) { // only operates on non-NULL cells incase
    int r = cells[i]->row; // cells have been deleted.
    int c = cells[i]->col;
    if (!isValidMove(r-1,c)){ // move down 1 space -> r - 1
      //cerr << "moveDown returning false" << endl;
      return false;
    }
    }
  }
  for (int i = 0; i < BLOCK_SIZE; i++){
    if (!cells[i]) { // only operates on non-NULL cells (as above)
      continue;
    }
    int r = cells[i]->row;
    int c = cells[i]->col;
    
    // undraw the cell from the display
    //cells[i]->undraw();
    
    cells[i]->setBlock(NULL);
    // sets that Cell::Block * to NULL
    
    cells[i] = Board::getInstance()->cellLookup(r-1,c);
    // if that cell currently points at this block, it still works,
    // because another element of cells still points at that cell.
    
    cells[i]->setBlock(this);
    //if (!isValidMove(r-1,c)){ // move down 1 space -> r - 1
    //  return false;
  }
  //change the cells
  this->putOnBoard();
  return true;
};

// moveRight()
// Moves Block one position to the right.
void Block::moveRight(){
  for (int i = 0; i < BLOCK_SIZE; i++){
    if (cells[i]) { // only operates on non-NULL cells incase
      int r = cells[i]->row; // cells have been deleted.
      int c = cells[i]->col;
      if (!isValidMove(r,c+1)){ // move right 1 space -> c + 1
        return;
      }
    }
  }
  for (int i = 0; i < BLOCK_SIZE; i++){
    if (!cells[i]) { // only operates on non-NULL cells (as above)
      break;
    }
    int r = cells[i]->row;
    int c = cells[i]->col;
    
    // undraw the cell from the display
    //cells[i]->undraw();
    
    cells[i]->setBlock(NULL);
    // sets that Cell::Block * to NULL
    
    cells[i] = Board::getInstance()->cellLookup(r,c+1);
    // if that cell currently points at this block, it still works,
    // because another element of cells still points at that cell.
    
    cells[i]->setBlock(this);
    //if (!isValidMove(r,c+1)){ // move down 1 space -> r - 1
    //  return false;
  }
  //change the cells
  this->putOnBoard();
  return;
}

// moveLeft()
// Moves the Block one position to the left.
void Block::moveLeft(){
  for (int i = 0; i < BLOCK_SIZE; i++){
    if (cells[i]) { // only operates on non-NULL cells incase
      int r = cells[i]->row; // cells have been deleted.
      int c = cells[i]->col;
      if (!isValidMove(r,c-1)){ // move right 1 space -> c + 1
        return;
      }
    }
  }
  for (int i = 0; i < BLOCK_SIZE; i++){
    if (!cells[i]) { // only operates on non-NULL cells (as above)
      break;
    }
    int r = cells[i]->row;
    int c = cells[i]->col;
    
    // undraw the cell from the display
    cells[i]->undraw();
    
    cells[i]->setBlock(NULL);
    // sets that Cell::Block * to NULL
    
    cells[i] = Board::getInstance()->cellLookup(r,c-1);
    // if that cell currently points at this block, it still works,
    // because another element of cells still points at that cell.
    
    cells[i]->setBlock(this);
    //if (!isValidMove(r,c+1)){ // move down 1 space -> r - 1
    //  return false;
  }
  //change the cells
  this->putOnBoard();
  return;

}

//void Block::rotate(bool clockwise) {}

// Constructor
Block::Block(char block_type, int level_created)
: block_type(block_type), level_created(level_created) {

  Board *the_board = Board::getInstance();
  switch (block_type) {
    case 'I':
      cells[0] = the_board->cellLookup(11,0);
      cells[1] = the_board->cellLookup(11,1);
      cells[2] = the_board->cellLookup(11,2);
      cells[3] = the_board->cellLookup(11,3);
      break;
    case 'J':
      cells[0] = the_board->cellLookup(11,0);
      cells[1] = the_board->cellLookup(11,1);
      cells[2] = the_board->cellLookup(11,2);
      cells[3] = the_board->cellLookup(12,0);
      // break statement was missing
      break;
    case 'L':
      cells[0] = the_board->cellLookup(11,0);
      
      // changed this line from 12,0 to 12,2
      cells[1] = the_board->cellLookup(12,2);
      
      cells[2] = the_board->cellLookup(11,1);
      cells[3] = the_board->cellLookup(11,2);
      break;
    case 'O':
      cells[0] = the_board->cellLookup(11,0);
      cells[1] = the_board->cellLookup(12,0);
      cells[2] = the_board->cellLookup(11,1);
      cells[3] = the_board->cellLookup(12,1);
      break;
    case 'S':
      cells[0] = the_board->cellLookup(11,0);
      cells[1] = the_board->cellLookup(11,1);
      cells[2] = the_board->cellLookup(12,1);
      cells[3] = the_board->cellLookup(12,2);
      break;
    case 'Z':
      cells[0] = the_board->cellLookup(11,1);
      cells[1] = the_board->cellLookup(11,2);
      cells[2] = the_board->cellLookup(12,1);
      cells[3] = the_board->cellLookup(12,0);
      break;
    case 'T':
      cells[0] = the_board->cellLookup(11,1);
      cells[1] = the_board->cellLookup(12,0);
      cells[2] = the_board->cellLookup(12,1);
      cells[3] = the_board->cellLookup(12,2);
      break;
    default:
      throw(BadBlockType());
      break;
  }
};

// Destructor
Block::~Block(){};

// putOnBoard()
// Points all the cells in Block::cells[] back to the block.
void Block::putOnBoard() {
  for (int i = 0; i < BLOCK_SIZE; i++) {
    if (cells[i] == NULL) continue;
    if (cells[i]->getBlock() &&
        cells[i]->getBlock() != this) {
      throw (NoRoomForBlock());
    }
    cells[i]->setBlock(this);
    
    // drawing cell graphically
    //cells[i]->draw();
  }
}

// isValidMove(row,col)
// Returns true if moving to the position (row,col) is valid.
bool Block::isValidMove(int row, int col){
  if ( row >= NUM_ROWS || row < 0 ||
      col >=  NUM_COLS || col < 0  ){
    return false;
  } else {
    Board* cur_board = Board::getInstance();
    Cell* cur_cell = cur_board->cellLookup(row, col);
    const Block* cur_block = cur_cell->getBlock();
    if (cur_block == NULL || cur_block == this){
      return true;
    } else {
      return false;
    }
  }
};