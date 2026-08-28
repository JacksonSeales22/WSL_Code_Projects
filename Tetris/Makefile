CXX = g++
CXXFLAGS = -std=c++17 -Wall -g $(shell pkg-config --cflags sdl2)
LDFLAGS = $(shell pkg-config --libs sdl2)
TARGET = tetris

tetris: tetris.cpp board.h pieces.h gameplay.h display.h
	$(CXX) $(CXXFLAGS) tetris.cpp -o $(TARGET) $(LDFLAGS)

run: tetris
	./tetris

clean:
	rm -f $(TARGET)