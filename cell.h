#ifndef __CELL_H__
#define __CELL_H__

// cell.h
//
// Created by Michael Hewson and Justin Leclerc

class Block;

class Cell {
  Block * block;
  
public:
  
  const int row;
  const int col;
  
  Cell(int row, int col);
  
  char getCharacter();
  Block* getBlock() const;
  
  
  // You may also pass it a NULL to remove the block from the cell
  void setBlock(Block * b);
  
  // graphical
  void draw();
  void undraw();
  
  void deleteCell();
  
};


#endif