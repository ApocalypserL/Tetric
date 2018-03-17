CC	:= g++
SRC	:= $(wildcard *.cpp)

TARGET	:= Tetric

all	: $(SRC)
	$(CC) -o $(TARGET) $(SRC) -lglut -lGL -lGLU
.PHONY: clean
clean	:
	-rm -f *.o $(TARGET)
