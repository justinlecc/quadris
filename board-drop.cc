#include "board.h"
#include "cell.h"
#include "block.h"
#include "scoreboard.h"
#include "level.h"

#include <cassert>
using namespace std;

// checkForFullLines() - helper for drop
// returns a vector<int>, sorted descending, containing the
// row numbers of full lines. If there are no full lines, the vector<int>
// that is returned will be empty and .size() will be zero.
vector<int> Board::checkForFullLines() {
  vector<int> full_lines;
  
  for (int i = NUM_ROWS-1; i >= 0; i--) {
    bool line_full = true;
    for (int j = 0; j < NUM_COLS; j++) {
      if (0 == cellLookup(i,j)->getBlock()) {
        // if a cell is empty, set line_full to false, and break
        line_full = false;
        break;
      }
    }
    if (line_full) {
      full_lines.push_back(i);
    }
  }
  
  return full_lines;
}

// drop()
void Board::drop() {
  
  // move current_block down until you can't
  while (current_block->moveDown());
  
  // add current_block pointer to dropped_blocks
  dropped_blocks.push_back(current_block);
  
  // set current_block to NULL
  current_block = 0;
  
  // declare int lines_deleted;
  int lines_deleted = 0;
  // start loop here:
  while (1) {
    // look for full lines
    vector<int> full_lines = checkForFullLines();
    
    
    // if there are no full lines, leave loop.
    //cout << "FULL LINES: " << full_lines.size() << endl;
    if (full_lines.size() == 0) {
      //cerr << "no full lines" << endl;
      break;
    }
    //cerr << "we have " << full_lines.size() << " full lines!" << endl;
    
    
    // delete all full lines, incrementing lines_deleted for each line
    //  -> when deleting a full lines, as each cell is deleted, it will check
    //     that cell's block, and if it is completely deleted, adds points to
    //     the scoreboard based on the block's level_created attribute.
    
    
    for (unsigned int i = 0; i < full_lines.size(); i++) {
      int row = full_lines.at(i);
      for (int col = 0; col < NUM_COLS; col++) {
        //cerr << "deleting cell: (" << row << "," << col << ")"<< endl;
        cellLookup(row,col)->deleteCell();
        cellLookup(row,col)->undraw();
      }
      lines_deleted++;
    }
    
    
    // Move lines above the deleted line(s) down 1, starting with the highest line deleted.
    
#ifndef NDEBUG
    {
      // assert that full_lines is sorted the right way
      
      int last_full_line = NUM_ROWS;
      for (unsigned int i = 0; i < full_lines.size(); i++) {
        assert(full_lines.at(i) < last_full_line);
        // assert that it is sorted descending
        
        last_full_line = full_lines.at(i);
      }
    }
#endif
    
    for (unsigned int line = 0; line < full_lines.size(); line++) {
      // full_lines is sorted descending.
      
      int deleted_row = full_lines.at(line);
      
      // TODO:
      // move every cell that is above deleted_row down by one row,
      // starting with the lowest row.
      for (int i = deleted_row + 1; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
          
          Cell * this_cell = cellLookup(i,j);
          Cell * cell_below = cellLookup(i-1,j);
          Block * this_block = this_cell->getBlock();
          // this_block may be null. If it is, we don't have to do anything.
          
          // assert that cell below it is empty
          assert(0 == cell_below->getBlock());
          // TEMPORARY TEST: this assertion should fail when i == deleted_row + 2
          // Test passed.
          
          if (0 == this_block) continue;
          // we don't need to do anything: this_cell is empty.
          // Move on to next cell.
          
          // move cell down one. You have to change the block's cell pointer
          // change the old cell's block pointer to NULL, and change the new cell's
          // block pointer to point at the block
          
          // change block pointer of cell below:
          cell_below->setBlock(this_block);
          
          // change cell pointer of the block that points here:
          // we have to find ourself in the array first
          for (int cell_index = 0; cell_index < BLOCK_SIZE; cell_index++) {
            if (this_block->cells[cell_index] == this_cell) {
              this_block->cells[cell_index] = cell_below;
            }
          }
          
          // set block pointer of this cell to NULL
          this_cell->setBlock(0);
          
        }
      }
    }
    
    
    
    
    // move all blocks down, one row at a time,  until there are no blocks left
    // that can move down.
    bool can_still_move_down = true;
    while (can_still_move_down) {
      can_still_move_down = false;
      for (unsigned int i = 0; i < dropped_blocks.size(); i++) {
        if (dropped_blocks.at(i)->moveDown()) {
          can_still_move_down = true;
        }
      }
    }
    
    // end loop here
  }
  // addPoints() to scoreboard based on (getCurrentLevel() + lines_deleted)^2
  if (lines_deleted > 0) {
    int sqrt_of_points = Level::getCurrentLevelID() + lines_deleted;
    ScoreBoard::getInstance()->addPoints(sqrt_of_points*sqrt_of_points);
    
  }
  
  try {
    moveNextBlockToCurrentBlockAndMakeNewNextBlock();
  }
  catch (NoRoomForBlock) {
    throw (GameOver());
  }
}
