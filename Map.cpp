#include "Map.h"

// The constructor for the Map class
Map::Map(Game* InGame)
{
	TextAdv = InGame;
	ParseMap(LoadMap("Map.csv"));
	TextAdv->GameMap = this;
}

// This function loads the csv file with the mpa details into the game
vector<Room> Map::LoadMap(string FilePath)
{
	// Load the map and check if it exists
	ifstream MapFile("Map.csv");
	if (!MapFile) return vector<Room> {Room()};

	// Create a line of data and a vector to store the correlating name, description and exits
	string MapLine;
	vector<Room> MapData;

	// Loop through the CSV file and populate the map vector (ignoring the initial blankspace), by filling a Room struct and add it onto the end
	bool bIsWhitespace = true;
	Room NewRoom = Room();
	int Index = 0;
	while (getline(MapFile, MapLine, ','))
	{
		// Remove blankspace characters before file parsing
		if (bIsWhitespace)
		{
			MapLine.erase(0, 3);
			bIsWhitespace = false;
		}

		// Check the line for a newline character, and split it if it exists
		string NewLine = "\n";
		TextAdv->RemoveSubstrings(MapLine, NewLine);
		NewRoom = CreateRoom(NewRoom, MapLine, Index);
		// Check for the end of the Room
		CheckRoomCreationEnd(MapData, NewRoom, NewLine, Index);

		// Check for the end of the map and return the map vector
		int Rows = sizeof(GameMap) / sizeof(GameMap[0]);
		int Columns = sizeof(GameMap[0]) / sizeof(GameMap[0][0]);
		if (MapData.size() == Rows * Columns)
			return MapData;

	}
	// return the map vector
	return MapData;
}
// Checks if the map data has reached the end of the Room or file
bool Map::CheckRoomCreationEnd(vector<Room>& MapData, Room& InRoom, string InString, int& Index)
{
	Index++;

	// Is the leftover after removing a substring a substantial string?
	if (InString != "\n" && InString != "")
	{
		// Add the room to the map vector
		MapData.push_back(InRoom);

		// Create a new room with the substring's new room name
		Index = 0;
		InRoom = Room();
		InRoom = CreateRoom(InRoom, InString, Index);
		Index++;
		return true;
	}

	// Have we reached the end of a Room?
	if (Index > 2)
	{
		// Add the room to the map vector and initialise a new room
		MapData.push_back(InRoom);
		Index = 0;
		InRoom = Room();
		return true;
	}

	return false;
}
// Enters data into a Room struct at the appropriate variable
Room Map::CreateRoom(Room& InRoom, string InString, int Index)
{
	// Switch on Index to populate the room
	switch (Index)
	{
	case 0:
		InRoom.RoomName = InString;
		return InRoom;
	case 1:
		InRoom.Description = InString;
		return InRoom;
	case 2:
		InRoom.Exits = InString;
		return InRoom;
	default: return InRoom;
	}
}

// This function reads the map vector and converts it into a 2D array to be traversed by the player
void Map::ParseMap(vector<Room> Map)
{
	// First we get the amount of rows and columns there are in our map
	int Rows = sizeof(GameMap) / sizeof(GameMap[0]);
	int Columns = sizeof(GameMap[0]) / sizeof(GameMap[0][0]);

	// Then we create the room for the appropriate grid space by looping through the columns and rows
	for (int MapY = 0; MapY < Columns; MapY++)
	{
		for (int MapX = 0; MapX < Rows; MapX++)
		{
			int Index = MapX * Columns + MapY;
			GameMap[MapX][MapY] = Map.at(Index);
		}
	}
}

// This function returns the name and description of the room, ready to be output to the player
string Map::EnterRoom(int RoomIndex)
{
	// Get the row and column of the required room from the size of the arrays
	int Column = RoomIndex % (sizeof(GameMap[0]) / sizeof(GameMap[0][0]));
	int Row = (RoomIndex - Column) / (sizeof(GameMap) / sizeof(GameMap[0]));

	// Read the appropriate room from the map
	Room EnteredRoom = GameMap[Row][Column];
	return EnteredRoom.ReadRoom();
}
string Room::ReadRoom()
{
	return RoomName + "\n" + Description + "\n";
}
