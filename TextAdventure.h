#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Map.h"
using namespace std;

// This class is the leading force behind all the logic in the game.
// It contains the map, game controls and commands, and the file-manipulation
class Game
{
public:
	Game();
	~Game() {};

	// A flag for when the player has won the game
	bool bHasWon = false;

	// This is the title of your game - make it cool!
	string GameName = "Text Adventure";

	// This is a reference to the map that holds the game world
	friend class Map;
	Map* GameMap = nullptr;
	// This is the index of the map that we start at
	int StartRoom = 4;

private:
	// Removes a substring from a given string, and returns the before and after
	void RemoveSubstrings(string& InString, string& Substring);
};