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
	GameMap = new Map(this);
	PlayerInterface = new Interface(this);

	cout << "Welcome to " << GameName << "!\n" << GameMap->EnterRoom(StartRoom);
	while (!bHasWon) PlayerInterface->PromptPlayer();
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

// This function allows the player to move accross the game map, returning if the movement is valid
string Game::Move(string Direction)
{
	// Parse our direction into an upper case character
	char DirInitial = islower(Direction.at(0)) ? toupper(Direction.at(0)) : Direction.at(0);

	// Is the direction even valid?
	string Dirs = "NESW";
	if (count(Dirs.begin(), Dirs.end(), DirInitial) == 0) return "That doesn't seem like a direction.";
	// Check the exit is valid for the room
	string CurrentExits = GameMap->GetRoom(CurrentRoom).Exits;
	if (count(CurrentExits.begin(), CurrentExits.end(), DirInitial) == 0)
	{
		// Return an invalid movement if we haven't moved
		return "You can't move " + Direction + "\n";
	}

	// Get the new room's index
	int DirectionIndex;
	switch (DirInitial)
	{
	case 'N': DirectionIndex = -static_cast<int>(size(GameMap->GameMap[0])); break;
	case 'E': DirectionIndex = 1; break;
	case 'S': DirectionIndex = static_cast<int>(size(GameMap->GameMap[0])); break;
	case 'W': DirectionIndex = -1; break;
	default: return "That doesn't seem like a direction";
	}

	// Get the new room's details and return them
	CurrentRoom += DirectionIndex;
	return GameMap->EnterRoom(CurrentRoom);

}
// This function allows the player to take an item, returning whether or not it was taken
string Game::Take(string Object)
{
	return "Take\n";
}
// This function opens or unlocks an obstacle, returning the success
string Game::Open(string Object)
{
	return "Open\n";
}