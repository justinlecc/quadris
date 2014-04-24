#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <string>

class EndOfFile{};

// readCommand();
// throws exception EndOfFile if end of file, and throws GameOver if the command
// caused the player to lose.
void readCommand();

#endif