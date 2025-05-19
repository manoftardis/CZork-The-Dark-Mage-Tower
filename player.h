#ifndef PLAYER_H
#define PLAYER_H

#include "room.h"
#include "object.h"

typedef enum PAction
{
    LOOK,
    LOOKAT,
    TAKE,
    MOVETO,
    COMBINE,
    PUT,
    USE,
    INVENTORY,

} PAction;



typedef struct Player
{
    Room* currRoom;
    ObjectContainer* inventory;

}Player;

Player* playerInit(Room* start, ObjectContainer* inventory);

//Move the player from the current room to dest room if they are directly connected
void MoveTo(Player* p, char* dest);

//print the current room name and description
void Look(Player* p);

//print the description of an object in the player inventory or room
void LookAt(char* ObjectName);

//combines two items in a new one if possible
void Combine(Player *p, char* ObjectName1, char* ObjectName2);

//insert an item from the player inventory inside the room inventory
void Put(Player *p, char* ObjectName1);

//take the object if present in the room
void Take(Player* p, char* ObjectName1);

//Print the player inventory
void Inventory(Player* p);

//Use the item from the player inventory??
void Use(Player* p, char* ObjectName1);

//maybe move this function in the main file or rooms????
void Win();

//same as win maybe
void Start();

#endif