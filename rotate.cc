#include "block.h"
#include <cassert>
#include <limits>
#include <iostream>
#include "board.h"
#include "cell.h"
using namespace std;

static int array_min (int arr[], int len) {
  int min = std::numeric_limits<int>().max();
  for (int i = 0; i < len; i++) {
    if (arr[i] < min) {
      min = arr[i];
    }
  }
  return min;
}

void Block::rotate(bool clockwise) {
  
  //
  
  // find bottom-left corner of smallest enclosing
  // rectangle
  int origin_row = NUM_ROWS; // these are out of range
  int origin_col = NUM_COLS;
  for (int i = 0; i < BLOCK_SIZE; i++) {
    assert(cells[i] != 0);
    
    if (cells[i]->row < origin_row) {
      origin_row = cells[i]->row;
    }
    
    if (cells[i]->col < origin_col) {
      origin_col = cells[i]->col;
    }
  }
  // origin_row should now be the lowest row that any of
  // the cells occupy, and origin_col should be the lowest 
  // column that any of the cells occupy.
  assert(origin_row < NUM_ROWS);
  assert(origin_col < NUM_COLS);
  
  
  // keeping track of coordinates in arrays
  int coords_rows [BLOCK_SIZE];
  int coords_cols [BLOCK_SIZE];
  
  for (int i = 0; i < BLOCK_SIZE; i++) {
    
    
    int row = cells[i]->row - origin_row;
    assert(row>=0);
    
    int col = cells[i]->col - origin_col;
    assert(col>=0);
    
    // clockwise:         row,col -> -col,row 
    // counterclockwise:  row,col -> col,-row
    if (clockwise) {
      coords_rows[i] = -1*col;
      coords_cols[i] = row;
    } else {
      coords_rows[i] = col;
      coords_cols[i] = -1*row;
    }
  }
  
  // put coordinates back in the first quadrant
  
  int row_displacement = array_min(coords_rows, BLOCK_SIZE);
  assert(row_displacement <= 0);
  /*
  int min_row = 0;
  for (int i = 0; i < BLOCK_SIZE; i++) {
    if (coords_rows[i] < min_row) {
      min_row
    }
  }
  */
  int col_displacement = array_min(coords_cols, BLOCK_SIZE);
  assert(col_displacement <= 0);
  
  
  for (int i = 0; i < BLOCK_SIZE; i++) {
    // move coordinates back into first quadrant
    coords_rows[i] -= row_displacement;
    assert(coords_rows[i] >= 0);
    
    coords_cols[i] -= col_displacement;
    assert(coords_cols[i] >= 0);
    
    // add origin_row and origin_col to coordinates
    coords_rows[i] += origin_row;
    assert(0 <= coords_rows[i]);
    assert(coords_rows[i] < NUM_ROWS);
    coords_cols[i] += origin_col;
    assert(0 <= coords_cols[i]);
    assert(coords_cols[i] < NUM_ROWS);
  }
  
  // check if move is valid:
  for (int i = 0; i < BLOCK_SIZE; i++) {
    if (!isValidMove(coords_rows[i], coords_cols[i])) {
      return;
    }
  }
  
  // undraw the cells
  //for (int i = 0; i < BLOCK_SIZE; i++) {
    //cells[i]->undraw();
  //}
  
  // point block to cells and point cells to blocks and print their new positions
  
  for (int i = 0; i < BLOCK_SIZE; i++) {
    // delete the cell's reference to us
    cells[i]->setBlock(0);
    
    // point to the new cell
    cells[i] = Board::getInstance()->cellLookup(coords_rows[i], coords_cols[i]);
  }
  
  for (int i = 0; i < BLOCK_SIZE; i++) {
    // assert that the new cells don't point at a block yet
    assert(cells[i]->getBlock() == 0);
    
    // point the cells back to us
    cells[i]->setBlock(this);
    
    // draw the cell
    ///cells[i]->draw();
  }
  
}
