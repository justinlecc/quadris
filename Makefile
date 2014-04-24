CXX = g++ # compiler
CXXFLAGS = -g -Wall -MMD -I /opt/X11/include  ${DEBUGFLAGS} # compiler flags
GRAPHICS_FILE = boardgraphics.o
OBJECTS = main.o command.o level.o level0.o level1.o level2.o level3.o scoreboard.o board.o board-drop.o board-text-output.o cell.o block.o rotate.o ${GRAPHICS_FILE} window-v2.o
DEPENDS = ${OBJECTS:.o=.d} # substitute “.o” with “.d”
EXEC = quadris # executable name

${EXEC} : ${OBJECTS} # link step
	${CXX} ${OBJECTS} -o ${EXEC} -I/opt/X11/include -L/opt/X11/lib -lX11

-include ${DEPENDS} # copies .d files (if exists)

.PHONY : clean # not a file name
clean : # remove files that can be regenerated
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}