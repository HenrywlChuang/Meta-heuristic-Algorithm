DIR_INC = ./include
DIR_SRC = ./src
DIR_OBJ = ./obj
DIR_BIN = ./bin
DIR_RSL = ./result

SRC = $(wildcard *.cpp ${DIR_SRC}/*.cpp)  
OBJ = $(patsubst %.cpp, ${DIR_OBJ}/%.o, $(notdir ${SRC})) 

TARGET = main

BIN_TARGET = ${DIR_BIN}/${TARGET}

CC = g++
CFLAGS = -g -Wall -I ${DIR_INC} -O3

${BIN_TARGET}: ${OBJ} 
	$(CC) $(OBJ) -o $@

${DIR_OBJ}/%.o: ${DIR_SRC}/%.cpp 
	$(CC) $(CFLAGS)  -c  $< -o $@

${DIR_OBJ}/%.o: %.cpp 
	$(CC) $(CFLAGS)  -c  $< -o $@

.PHONY: clean

clean:
	find ${DIR_OBJ} -name *.o -exec rm -rf {} \;

cleanall:
	find ${DIR_OBJ} -name *.o -exec rm -rf {} \;
	find ${DIR_RSL} -name "*.*" -exec rm -rf {} \;