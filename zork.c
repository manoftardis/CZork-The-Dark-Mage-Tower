#include "room.h"
#include "object.h"
#include "player.h"

void start();

int main() 
{
    start();
}


void start()
{
    Room startRoom = {
        .desc = "This is the starting room",
        .name = "Start",
        .enterFunc = NULL,
        .exitFunc = NULL,
        .visited = 0,
    };

    Room floor1 = {
        .desc = "The room is the first floor",
        .name = "Floor1",
        .enterFunc = NULL,
        .exitFunc = NULL,
        .visited = 0,
    };

    Room cabin = {
        .desc = "This is the Cabin",
        .name = "Cabin",
        .enterFunc = NULL,
        .exitFunc = NULL,
        .visited = 0,
    };

    Room storage = {
        .desc = "This is the Storage Room",
        .name = "Storage Room",
        .enterFunc = NULL,
        .exitFunc = NULL,
        .visited = 0,
    };

    Room secret = {
        .desc = "This is the Secret Room",
        .name = "Secret1",
        .enterFunc = NULL,
        .exitFunc = NULL,
        .visited = 0,
    };

    Room floor2 = {
        .desc = "This is the the second floor",
        .name = "Floor2",
        .enterFunc = NULL,
        .exitFunc = NULL,
        .visited = 0,
    };

    //connect the rooms
    startRoom.north = &floor1;
    floor1.south = &startRoom;

    floor1.west = &cabin;
    cabin.east = &floor1;

    floor1.east = &storage;
    storage.west = &floor1;

    storage.south = &secret;
    secret.north = &storage;
}