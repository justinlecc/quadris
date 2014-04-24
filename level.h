//
//  level.h
//  
//
//  Created by Justin Leclerc on 13-11-23.
//
//

#ifndef __LEVEL_H__
#define __LEVEL_H__
#include <string>

class Block;

class BadScriptFile{};
class BadLevelID{};

class Level {
  // static private members
  static int current_level_id;
  static Level* current_level;
  static int seed;
  static void cleanup();
  static std::string scriptfile;

  virtual char newBlockType()=0;
protected:
  static std::string getScriptFile();
public:
  static int getCurrentLevelID();
  static Level* getCurrentLevel();
  
  virtual ~Level();
  
  Block* createBlock();
  static void levelUp();
  static void levelDown();
  static void changeLevel(int level_id);
  static void changeScriptFile(const std::string & scriptfile);
  static int getSeed();
  static void changeSeed(int new_seed);
};

class Level0: public Level{
  char newBlockType(); // will need to become private
public:
  Level0();
  ~Level0();
};

class Level1: public Level{
  char newBlockType();
public:
  Level1();
  ~Level1();
};

class Level2: public Level{
  char newBlockType();
public:
  Level2();
  ~Level2();
};

class Level3: public Level{
  char newBlockType();
public:
  Level3();
  ~Level3();
};


#endif
