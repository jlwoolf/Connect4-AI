OBJS	= main.o Board.o Game.o
SOURCE	= main.cpp Board.cpp Game.cpp
HEADER	= Board.h Game.h
OUT	= minimax
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 

Board.o: Board.cpp
	$(CC) $(FLAGS) Board.cpp 

Game.o: Game.cpp
	$(CC) $(FLAGS) Game.cpp 


clean:
	rm -f $(OBJS) $(OUT)