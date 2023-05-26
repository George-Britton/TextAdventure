#include "Inventory.h"

// The constructor for the Intventory class
Inventory::Inventory()
{
	// In here we populate the list of items in our game
	InventoryList.push_back(Item("key", 3, false, false));
}

// This function collects the item from the room if possible
bool Inventory::CollectItem(string ItemName, int RoomIndex)
{
	// Loop through the inventory array and see if the item...
	for (Item& InvItem : InventoryList)
	{
		// ...exists, is in the room, and hasn't already been collected
		if (InvItem.Name == ItemName && InvItem.Location == RoomIndex && !InvItem.bCollected)
		{
			// Collect the item and return a success if it is
			InvItem.bCollected = true;
			return true;
		}
	}

	// Otherwise return that the take command was invalid
	return false;
}

// This function consumes an item if possible
void Inventory::ConsumeItem(string ItemName)
{
	// Loop through the inventory array and see if the item...
	for (Item& InvItem : InventoryList)
	{
		// ...exists, and has been collected
		if (InvItem.Name == ItemName && InvItem.bCollected)
		{
			// Consume the item and return
			InvItem.bConsumed = true;
			return;
		}
	}
}

// This function checks if the player has an item
bool Inventory::HasItem(string ItemName)
{
	// Loop through the inventory array and see if the item...
	for (Item& InvItem : InventoryList)
	{
		// ...exists, and hasn't been consumed
		if (InvItem.Name == ItemName && !InvItem.bConsumed)
		{
			// Return the acknowledgment that the player has the item
			return true;
		}
	}

	// Otherwise inform teh player that they don't have the item
	return false;
}

// This function prints out all the items the player has collected
string Inventory::PrintInventory()
{
	bool InventoryEmpty = true;
	string InventoryString = "Your inventory contains:\n";;
	// Loop through the inventory array and see if the item...
	for (Item& InvItem : InventoryList)
	{
		// ... has been collected
		if (InvItem.bCollected)
		{
			// Appends the name of the item
			InventoryString += InvItem.Name + "\n";
			InventoryEmpty = false;
		}
	}

	// Return the final output, but announce it's empty if no items were found
	if (InventoryEmpty) return "It looks like your inventory is empty";
	return InventoryString;
}