
#include "boardgraphics.h"
#include "window.h"
#include "level.h"
#include "scoreboard.h"
#include "board.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
using namespace std;

// ENABLES TEXTDISPLAY
static bool GRAPHICS_ON;
                                           
//DISPLAY DIMENSIONS                             
int WINDOW_HEIGHT = 600; // initialized height
int PIXEL_SIZE = 30;
int X_START = 400;
int Y_START = 75;
int GRID_HEIGHT;      
int GRID_WIDTH;                             
int WINDOW_WIDTH;
int BORDER;


struct BoardGraphicsImpl {
  Xwindow* win;
};


// Singleton Pattern:

BoardGraphics * BoardGraphics::instance = 0;

// TurnOnGraphics()
// If GRAPHICS_ON: do nothing.
// Else: set up BoardGraphics
void BoardGraphics::TurnOnGraphics() {
  if (!GRAPHICS_ON){
    GRAPHICS_ON = true;
    
    // calculate neccessary dimensions
    GRID_HEIGHT = (WINDOW_HEIGHT * 2) / 4;
    GRID_WIDTH = WINDOW_HEIGHT / 2;
    BORDER = GRID_WIDTH / 4;
    WINDOW_WIDTH  = GRID_WIDTH + (BORDER * 2) + (GRID_WIDTH / 2) + (GRID_WIDTH / 2);
    
    // initialize the pImpl
    pImpl = new BoardGraphicsImpl;
    
    // Initializes a window; we won't need a window stored in Board.
    pImpl->win = new Xwindow(WINDOW_WIDTH, WINDOW_HEIGHT);
    
    // Print the background
    pImpl->win->fillRectangle(0,0,750, 600, 1);
    
    // Print the grid
    pImpl->win->fillRectangle(400,75,300, 450, 0);

    // prints out the score, hi-score, level
    changeLevel();
    changeScore();
    changeHiScore();
    //changeNextBlock(); // taken out and put into Board::printNextBlock
  }
}

// initializer
BoardGraphics::BoardGraphics() {}

// cleanup()
void BoardGraphics::cleanup() {
  delete instance;
}

BoardGraphics * BoardGraphics::getInstance() {
  if (!instance) {
    instance = new BoardGraphics;
    atexit(cleanup);
  }
  return instance;
}

BoardGraphics::~BoardGraphics(){}


// Other Public Methods

// Turns graphics off
void BoardGraphics::TurnOffGraphics() {
  if (GRAPHICS_ON){
    delete instance->pImpl->win;
    delete instance->pImpl;
  }
    GRAPHICS_ON = false;
}



// changeLevel()
// Changes the level on display
void BoardGraphics::changeLevel() {
  if (GRAPHICS_ON){
    int level_num = Level::getCurrentLevelID();
    string str_level_num;//string which will contain the result
    stringstream convert; // stringstream used for the conversion
    convert << level_num;//add the value of Number to the characters in the stream
    str_level_num = convert.str();//set Result to the content of the stream
    string level_msg = "Level: " + str_level_num;
    // fill background
    pImpl->win->fillRectangle(180,70,120,45, 1);
    // print new numbers
    pImpl->win->drawBigString(30, 110, level_msg, 0);
  }
}

// changeScore()
// Changes the score on display
void BoardGraphics::changeScore() {
  if (GRAPHICS_ON){
    ScoreBoard* SB = ScoreBoard::getInstance();
    int score = SB->getCurrentScore();
    string score_str;//string which will contain the result
    stringstream convert; // stringstream used for the conversion
    convert << score;//add the value of Number to the characters in the stream
    score_str = convert.str();//set Result to the content of the stream
    string score_msg = "Score: " + score_str;
    
    // fill background
    pImpl->win->fillRectangle(190,115,165,40, 1);
    
    // print new numbers
    pImpl->win->drawBigString(30, 150, score_msg, 0);
  }
}

// changeHiScore()
// Changes the high score on display
void BoardGraphics::changeHiScore() {
  if (GRAPHICS_ON){
    ScoreBoard* SB = ScoreBoard::getInstance();
    int score = SB->getHiScore();
    string score_str;//string which will contain the result
    stringstream convert; // stringstream used for the conversion
    convert << score;//add the value of Number to the characters in the stream
    score_str = convert.str();//set Result to the content of the stream
    string score_msg = "Hi-Score: " + score_str;
    
    // fill background
    pImpl->win->fillRectangle(260,160,115,40, 1);
    
    // print new numbers
    pImpl->win->drawBigString(30, 190, score_msg, 0);
  }
}

// colours
// {"white", "black", "red", "green", "blue", "cyan", "yellow", "magenta", "orange", "brown"};

// colourSelect(type)
int colourSelect(char type){
  switch (type) {
    case 'I':
      return 3;
      break;
    case 'J':
      return 4;
      break;
    case 'L':
      return 5;
      break;
    case 'O':
      return 6;
      break;
    case 'S':
      return 7;
      break;
    case 'Z':
      return 8;
      break;
    case 'T':
      return 9;
      break;
    default:
      cerr << "Invalid block type in BoardGraphics.cc in colourSelect() helper" << endl;
      return -1;
  }
  
}

// changeNextBlock(block_type)
// Changes the next block
void BoardGraphics::changeNextBlock(char block_type) {
  if (GRAPHICS_ON){
    string next_msg = "Next block: ";
    pImpl->win->drawBigString(30, 400, next_msg, 0);
    
    // cover old block
    pImpl->win->fillRectangle(95,410,200,100, 1); // adjust coords
    // block colour
    int block_colour = colourSelect(block_type);
    
    // print block
    switch (block_type) {
      case 'I':
        pImpl->win->fillRectangle(100,450,PIXEL_SIZE*4,PIXEL_SIZE, block_colour);
        break;
      case 'J':
        pImpl->win->fillRectangle(100,450-PIXEL_SIZE,PIXEL_SIZE,PIXEL_SIZE, block_colour);
        pImpl->win->fillRectangle(100,450,PIXEL_SIZE*3,PIXEL_SIZE, block_colour);
        break;
      case 'L':
        pImpl->win->fillRectangle(100+(PIXEL_SIZE*2),450-PIXEL_SIZE,PIXEL_SIZE,PIXEL_SIZE, block_colour);
        pImpl->win->fillRectangle(100,450,PIXEL_SIZE*3,PIXEL_SIZE, block_colour);
        break;
      case 'O':
        pImpl->win->fillRectangle(100,450-PIXEL_SIZE,PIXEL_SIZE*2,PIXEL_SIZE, block_colour);
        pImpl->win->fillRectangle(100,450,PIXEL_SIZE*2,PIXEL_SIZE, block_colour);
        break;
      case 'S':
        pImpl->win->fillRectangle(100+PIXEL_SIZE,450-PIXEL_SIZE,PIXEL_SIZE*2,PIXEL_SIZE, block_colour);
        pImpl->win->fillRectangle(100,450,PIXEL_SIZE*2,PIXEL_SIZE, block_colour);
        break;
      case 'Z':
        pImpl->win->fillRectangle(100,450-PIXEL_SIZE,PIXEL_SIZE*2,PIXEL_SIZE, block_colour);
        pImpl->win->fillRectangle(100+PIXEL_SIZE,450,PIXEL_SIZE*2,PIXEL_SIZE, block_colour);
        break;
      case 'T':
        pImpl->win->fillRectangle(100+PIXEL_SIZE,450-PIXEL_SIZE,PIXEL_SIZE,PIXEL_SIZE, block_colour);
        pImpl->win->fillRectangle(100,450,PIXEL_SIZE*3,PIXEL_SIZE, block_colour);
        break;
      default:
        break;
    }
  }
}

// drawCell(row,col,block_type)
// Draws the cell at r,c with color corresponding to block_type
void BoardGraphics::drawCell(int row, int col, char block_type) {
  if (GRAPHICS_ON){
    int r_converted = ((row-7)*-1) + 7;     // converting from row to x
    int c_converted = col;                  // the same
    int y = (r_converted*PIXEL_SIZE) + Y_START;
    int x = (c_converted*PIXEL_SIZE) + X_START;
  
  // colour number
    int colour = colourSelect(block_type);
  
  // print correct type of block
    pImpl->win->fillRectangle(x,y,PIXEL_SIZE,PIXEL_SIZE, colour);
  }
}

// undrawCell(r,c)
void BoardGraphics::undrawCell(int row, int col) {
  if (GRAPHICS_ON){
    int r_converted = ((row-7)*-1) + 7;     // converting from row to x
    int c_converted = col;                  // the same
    int y = (r_converted*PIXEL_SIZE) + Y_START;
    int x = (c_converted*PIXEL_SIZE) + X_START;
  
  // prints white
    pImpl->win->fillRectangle(x,y,PIXEL_SIZE,PIXEL_SIZE, 0);
  }
}
void BoardGraphics::gameOver() {}
void BoardGraphics::restart() {}