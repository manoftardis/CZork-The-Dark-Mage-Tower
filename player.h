#ifndef PLAYER_H
#define PLAYER_H

#include "room.h"
#include "object.h"

typedef struct Player
{
    Room* currRoom;
    ObjectContainer* inventory;

}Player;

//Move the player from the current room to dest room if they are directly connected
void MoveTo(Player* p, Room* dest);

//print the current room name and description
void Look(Player* p);

//take the object if present in the room
void Take(Player* p, Object* o);

//Print the player inventory
void Inventory(Player* p);

//Open the object if openable and closed and present
void Open(Player* p, Object* o);

//Close the object if openable and open and present
void Close(Player* p, Object* o);

//maybe move this function in the main file or rooms????
void Win();

//same as win maybe
void Start();

#endif