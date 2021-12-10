CC = g++
CFLAGS = -std=c++11 -Ofast
HEADERS = headers.h parser.h 
SOURCE = main.cpp parser.cpp 
OBJECTS = main.o parser.o 
TARGET = ../bin/cell_move_router
$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)
main.o : $(SOURCE) $(HEADERS)
	$(CC) $(CFLAGS) -c main.cpp
parser.o : $(SOURCE) $(HEADERS)
	$(CC) $(CFLAGS) -c parser.cpp
clean :
	rm $(TARGET) $(OBJECTS)