#ifndef __SCOREBOARD_H__
#define __SCOREBOARD_H__

class ScoreBoard {
  int hi_score;
  int current_score;
  // singleton implementation:
  static ScoreBoard *instance;
  ScoreBoard();
public:
  // getInstance()
  // Returns a pointer to the instance of ScoreBoard, constructing
  // it if neccessary.
  static ScoreBoard* getInstance();
  
  // getCurrentScore()
  // Returns the current score of the game.
  int getCurrentScore() const;
  
  // getHiScore()
  // Returns the hi score.
  int getHiScore() const;
  
  // addPoints(points)
  // Adds points to the current score and updates the hi score if
  // neccessary.
  void addPoints(int points);
  
  // restart()
  // Restarts the scoreboard; sets current_score to 0 and keeps
  // the hi score.
  void restart();
  
  // cleanup()
  // Deletes the instance of the scoreboard.
  static void cleanup();
  
  #ifdef SCOREBOARD_DEBUG
  // printScoreBoard() *For testing only*
  // Prints the current_score and the hi_score.
  // Example:
  // Current score: 10
  // Hi score: 100
  void printScoreBoard();
  #endif
};
#endif