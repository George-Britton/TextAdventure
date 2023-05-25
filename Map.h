#pragma once
#include "TextAdventure.h"
using namespace std;
class Game;

// This struct is used to create a new room in the game.
// When we load in a .csv file, we create a Room, and populate it with our content
struct Room
{
public:
	// Here we store the name, description, and possible exits of the room.
	string RoomName;
	string Description;
	// The exits can be stored as initials of the direction (North, East, South, West), and we compare it later to the player input.
	string Exits;

	// This function returns the name and description of the room, ready to be output to the player
	string ReadRoom();
};

// This class holds the data for the world map
class Map
{
public:
	Map(Game* InGame);
	~Map() {};

	// The parent game this class belongs to
	Game* TextAdv = nullptr;

	// This is a two-dimensional array containing all the room names of your map, in order.
	// If we were to look at a world-map of your game, this is how it would be laid out.
	// Feel free to change the sizes of the arrays to change the size of your map. Its co-ordinates are in the [X][Y] format.
	Room GameMap[3][3];

	// Finds the appropriate room on the mpa and prints its details
	Room GetRoom(int RoomIndex);
	string EnterRoom(int RoomIndex);
private:
	// Load the map and populate the GameMap which structs
	vector<Room> LoadMap(string FilePath);
	// Sets the appropriate Map line to the generating room
	bool AddMapLineToRoom(string& Line, int& Index, Room& CurrentRoom, vector<Room>& MapData);
	// Checks if the map data has reached the end of the Room or file
	bool CheckRoomCreationEnd(vector<Room>& MapData, Room& InRoom, string InString, int& Index);
	// Enters data into a Room struct at the appropriate variable
	Room CreateRoom(Room& InRoom, string InString, int Index);
	// This function reads the map vector and converts it into a 2D array to be traversed by the player
	void ParseMap(vector<Room> Map);
};