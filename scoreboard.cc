//
//  scoreboard.cpp
//  
//
//  Created by Justin Leclerc on 13-11-22.
//
//

#include "scoreboard.h"
#include "boardgraphics.h"
#include <iostream>
#include <cstdlib>
#ifndef NULL
#define NULL (0)
#endif
using namespace std;

// instance of the scoreboard
ScoreBoard* ScoreBoard::instance = NULL;

// ScoreBoard constructor
ScoreBoard::ScoreBoard(): hi_score(0), current_score(0) {};

// getInstance()
// Returns a pointer to the instance of ScoreBoard, constructing it if neccessary.
ScoreBoard* ScoreBoard::getInstance(){
  if (ScoreBoard::instance == NULL){
    ScoreBoard::instance = new ScoreBoard();
    
    // *MICHAEL* adding this to avoid memory leak:
    atexit(cleanup);
  }
  return instance;
};

// getCurrentScore()
// Returns the current score of the game.
int ScoreBoard::getCurrentScore() const{
  return current_score;
};

// getHiScore()
// Returns the hi score.
int ScoreBoard::getHiScore() const{
  return hi_score;
};

// addPoints(points)
// Adds points to the current score and updates the hi score if neccessary.
void ScoreBoard::addPoints(int points){
  current_score += points;
  BoardGraphics::getInstance()->changeScore();
  if (current_score > hi_score){
    hi_score = current_score;
    BoardGraphics::getInstance()->changeHiScore();
  }
};

// restart()
// Restarts the scoreboard; sets current_score to 0 and keeps the hi score.
void ScoreBoard::restart(){
  current_score = 0;
  BoardGraphics::getInstance()->changeScore();
};

// cleanup()
// Deletes the instance of the scoreboard
void ScoreBoard::cleanup(){
  delete instance;
};

#ifdef SCOREBOARD_DEBUG
// printScoreBoard()
// Prints the current_score and the hi_score.
// Example:
// Current score: 10
// Hi score: 100
void ScoreBoard::printScoreBoard(){
  cout << "Current score: " << getCurrentScore() << endl;
  cout << "Hi score: " << getHiScore() << endl;
};
#endif
