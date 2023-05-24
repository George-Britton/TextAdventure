#include "Interface.h"
#include "TextAdventure.h"

// The constructor for the Interface class
Interface::Interface(Game* InGame)
{
	TextAdv = InGame;
	TextAdv->PlayerInterface = this;
	PopulateCommandArray();
}

// This function populates the CommandMapping array
void Interface::PopulateCommandArray()
{
	// Here we have three commands: move, take, and open. These three commands each have multiple inputs that will call them
	InputMappings.push_back(CommandMapping(&Interface::Move, { "move", "go", "travel" }));
	InputMappings.push_back(CommandMapping(&Interface::Take, { "take", "pickup", "collect" }));
	InputMappings.push_back(CommandMapping(&Interface::Open, { "open", "unlock" }));
}

// This functions asks the player for their next move
void Interface::PromptPlayer()
{
	cout << Prompt;
	string Command = "";
	cin >> Command;
	string Response = ParseInput(Command);
	cout << Response;
}

// This function interprets the player's input into a command for the game, and returns the console text for the output
string Interface::ParseInput(string PlayerCommand)
{
	// First we separate the command from the object/direction
	string Command = PlayerCommand;
	string Object = " ";
	TextAdv->RemoveSubstrings(Command, Object);

	// Then we check to see if the command exists in the command mapping
	for (CommandMapping& CommandMap : InputMappings)
	{
		if (count(CommandMap.Inputs.begin(), CommandMap.Inputs.end(), Command))
		{
			// If it does, we call it with the object/direction
			return (this->*CommandMap.Function)(Object);
		}
	}

	// If it doesn't, we return the invalid command string
	return InvalidCommand;
}