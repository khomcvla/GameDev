BINARY = ./engine
DOC = doc
RM = rm -rf
SRC = src/Bonus.cpp src/Character.cpp src/Collider.cpp src/Collision.cpp src/EndGame.cpp src/Enemy.cpp src/Game.cpp src/Gem.cpp src/Health.cpp src/HealthBar.cpp src/Inventory.cpp src/Knife.cpp src/main.cpp src/Map.cpp src/Menu.cpp src/Object.cpp src/Player.cpp src/Sword.cpp src/Texture.cpp src/Weapon.cpp src/Description.cpp

CXX =g++
CXXFLAGS = -std=c++14 -Wall -pedantic -Wno-long-long -O0 -ggdb 
SDL = `sdl2-config --cflags --libs` -lSDL2 -lSDL2_image


all: compile doc

# Compile
compile: 
	$(CXX) $(CXXFLAGS) $(SRC) -o $(BINARY) $(SDL)

# Run the program
run:
	$(BINARY)

# Delete binary and documentation
clean:
	rm -rf $(BINARY)
	rm -rf $(DOC)

# Create documentation
doc: 
	doxygen
	mv doc/html/* doc/
	rm -r doc/html
