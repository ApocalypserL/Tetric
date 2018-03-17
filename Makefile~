CC	:= g++
SRC	:= $(wildcard *.cpp)

TARGET	:= Friends

all	: $(SRC)
	$(CC) -o $(TARGET) $(SRC) -g
.PHONY: clean
clean	:
	-rm -f *.o $(TARGET)
