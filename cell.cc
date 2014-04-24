// cell.cc
//
// Created by Michael Hewson and Justin Leclerc for Quadris

#include "cell.h"
#include "block.h"
#include "board.h"
#include "scoreboard.h"
#include "boardgraphics.h"

#include <iostream>
#include <cassert>
using namespace std;

Cell::Cell(int row, int col) : row(row), col(col){
  block = NULL;
};

// getCharacter
// Returns the character of the block it points to.
// If it doesn't point to a block, returns ' '.
char Cell::getCharacter() {
  if (!block) {
    return ' ';
  } else {
    return block->block_type;
  }
};

// setBlock()
// also draws or undraws the cell graphically
void Cell::setBlock(Block * b) {
  this->block = b;
  if (0 == b) {
    // if block is NULL pointer, cell is empty. undraw.
    undraw();
  } else {
    draw();
  }
};


// getBlock()
// Returns pointer to the Block that the cell is a part of.
Block* Cell::getBlock() const{
  return block;
};


// deleteCell()
void Cell::deleteCell() {
  
  // delete pointer to this
  for (int i = 0; i < BLOCK_SIZE; i++) {
    if (getBlock()->cells[i] == this) {
      getBlock()->cells[i] = 0;
    }
  }
  
  // award points and delete block if deleted
  bool block_empty = true;
  for (int i = 0; i < BLOCK_SIZE; i++) {
    if (getBlock()->cells[i] != 0) {
      block_empty = false;
      break;
    }
  }
  if (block_empty) {
    ScoreBoard::getInstance()->addPoints(getBlock()->level_created + 1);
    Board::getInstance()->removeDroppedBlock(getBlock());
  }
  setBlock(0);
  
}

// draw()
// Draws the cell into the display
void Cell::draw(){
  char block_char = getCharacter();
  assert(block_char != ' ');
  BoardGraphics::getInstance()->drawCell(row,col,block_char);
}

// undraw()
// Erases the cell from the display.
void Cell::undraw(){
  BoardGraphics::getInstance()->undrawCell(row,col);
}