#include "TextAdventure.h"
#include "Map.h"
#include "Interface.h"

int main()
{
	Game TextAdv = Game();
	return 0;
}

// The constructor for the Game class
Game::Game()
{
	Map NewMap = Map(this);
	cout << "Welcome to " << GameName << "!\n" << GameMap->EnterRoom(StartRoom);
}

// Removes a substring from a given string, and returns the before and after
void Game::RemoveSubstrings(string& InString, string& Substring)
{
	// First we find out if the substring exists, and if it doesn't, we return out of the function
	size_t Index = InString.find(Substring);
	if (Index == -1) return;

	// We then separate the prefix and suffix from the instring, and set the InString to the prefix, and the Substring to the suffix
	string Before = InString.substr(0, InString.find(Substring));
	string After = InString.substr(InString.find(Substring) + 1);
	InString = Before;
	Substring = After;
}