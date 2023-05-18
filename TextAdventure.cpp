#include "TextAdventure.h"
#include "Map.h"

int main()
{
	Game TextAdv = Game();
	return 0;
}

// The constructor for the Game class and Room class
Game::Game()
{
	Map NewMap = Map(this);
	cout << "Welcome to " << GameName << "!\n" << GameMap->EnterRoom(StartRoom);
}

// Removes a substring from a given string, and returns the before and after
void Game::RemoveSubstrings(string& InString, string& Substring)
{
	size_t Index = InString.find(Substring);
	if (Index == -1) return;
	string Before = InString.substr(0, InString.find(Substring));
	string After = InString.substr(InString.find(Substring) + 1);
	InString = Before;
	Substring = After;
}