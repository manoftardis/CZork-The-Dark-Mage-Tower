#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "room.h"
#include "object.h"
#include "player.h"


void start(void);
void createRooms(void);
void spawnPlayer(void);
PAction getInput();

char InputBuffer[256];

Room startRoom;
ObjectContainer inventory;
Player player;

int main() 
{
    start();
}


void start()
{
    createRooms();
    spawnPlayer();
}

void createRooms()
{
    Room startRoom = {
        .desc = "This is the starting room",
        .name = "Start",
        .enterFunc = NULL,
        .exitFunc = NULL,
        .visited = 0,
        .north = NULL,
        .east = NULL,
        .south = NULL,
        .west = NULL,
    };

    Room floor1 = {
        .desc = "The room is the first floor",
        .name = "Floor1",
        .enterFunc = NULL,
        .exitFunc = NULL,
        .visited = 0,
        .north = NULL,
        .east = NULL,
        .south = NULL,
        .west = NULL,
    };

    Room cabin = {
        .desc = "This is the Cabin",
        .name = "Cabin",
        .enterFunc = NULL,
        .exitFunc = NULL,
        .visited = 0,
        .north = NULL,
        .east = NULL,
        .south = NULL,
        .west = NULL,
    };

    Room storage = {
        .desc = "This is the Storage Room",
        .name = "Storage Room",
        .enterFunc = NULL,
        .exitFunc = NULL,
        .visited = 0,
        .north = NULL,
        .east = NULL,
        .south = NULL,
        .west = NULL,
    };

    Room secret1 = {
        .desc = "This is the Secret Room",
        .name = "Secret1",
        .enterFunc = NULL,
        .exitFunc = NULL,
        .visited = 0,
        .north = NULL,
        .east = NULL,
        .south = NULL,
        .west = NULL,
    };

    //connect the rooms
    startRoom.north = &floor1;
    floor1.south = &startRoom;

    floor1.west = &cabin;
    cabin.east = &floor1;

    floor1.east = &storage;
    storage.west = &floor1;

    storage.south = &secret1;
    secret1.north = &storage;

    Room floor2 = {
        .desc = "This is the second floor",
        .name = "Floor2",
        .enterFunc = NULL,
        .exitFunc = NULL,
        .visited = 0,
        .north = NULL,
        .east = NULL,
        .south = NULL,
        .west = NULL,
    };

    //connect the rooms
    floor1.north = &floor2;
    floor2.south = &floor1;

    Room floor3 = {
        .desc = "This is the third floor",
        .name = "Floor3",
        .enterFunc = NULL,
        .exitFunc = NULL,
        .visited = 0,
        .north = NULL,
        .east = NULL,
        .south = NULL,
        .west = NULL,
    };

    Room potion = {
        .desc = "This is the potion closet",
        .name = "Potion closet",
        .enterFunc = NULL,
        .exitFunc = NULL,
        .visited = 0,
        .north = NULL,
        .east = NULL,
        .south = NULL,
        .west = NULL,
    };

    //connect the rooms
    floor2.north = &floor3;
    floor3.south = &floor2;

    floor3.west = &potion;
    potion.east = &floor3;

    Room floor4 = {
        .desc = "This is the fourth floor",
        .name = "Floor4",
        .enterFunc = NULL,
        .exitFunc = NULL,
        .visited = 0,
        .north = NULL,
        .east = NULL,
        .south = NULL,
        .west = NULL,
    };

    Room secret2 = {
        .desc = "This is the second secret room",
        .name = "Secret2",
        .enterFunc = NULL,
        .exitFunc = NULL,
        .visited = 0,
        .north = NULL,
        .east = NULL,
        .south = NULL,
        .west = NULL,
    };

    Room secret3 = {
        .desc = "This is the third secret room",
        .name = "Secret3",
        .enterFunc = NULL,
        .exitFunc = NULL,
        .visited = 0,
        .north = NULL,
        .east = NULL,
        .south = NULL,
        .west = NULL,
    };

    //connect the rooms
    floor3.north = &floor4;
    floor4.south = &floor3;

    floor4.west = &secret2;
    secret2.east = &floor4;

    secret2.south = &secret3;
    secret3.north = &secret2;

    Room boss = {
        .desc = "This is the boss room",
        .name = "Boss",
        .enterFunc = NULL,
        .exitFunc = NULL,
        .visited = 0,
        .north = NULL,
        .east = NULL,
        .south = NULL,
        .west = NULL,
    };

    //connects the rooms
    floor4.north = &boss;

    //create the objects
    Object potionI1 = {
        .name = "Potion Ingredient 1",
        .desc = "A potion ingredient",
        .openable = 0,
        .open = 0,
        .carryable = 1,
        .nextObj = NULL,
        .prevObj = NULL,
    };

    Object key1 = {
        .name = "Key",
        .desc = "A key",
        .openable = 0,
        .open = 0,
        .carryable = 1,
        .nextObj = NULL,
        .prevObj = NULL,
    };

    Object crowbar = {
        .name = "Crowbar",
        .desc = "A crowbar",
        .openable = 0,
        .open = 0,
        .carryable = 1,
        .nextObj = NULL,
        .prevObj = NULL,
    };

    Object acidPotion = {
        .name = "Acid Potion",
        .desc = "A strange green potion",
        .openable = 0,
        .open = 0,
        .carryable = 1,
        .nextObj = NULL,
        .prevObj = NULL,
    };

    Object potionI2 = {
        .name = "Potion Ingredient 2",
        .desc = "A potion ingredient",
        .openable = 0,
        .open = 0,
        .carryable = 1,
        .nextObj = NULL,
        .prevObj = NULL,
    };

    Object potionI3 = {
        .name = "Potion Ingredient 3",
        .desc = "A potion ingredient",
        .openable = 0,
        .open = 0,
        .carryable = 1,
        .nextObj = NULL,
        .prevObj = NULL,
    };

    Object potionI4 = {
        .name = "Potion Ingredient 4",
        .desc = "A potion ingredient",
        .openable = 0,
        .open = 0,
        .carryable = 1,
        .nextObj = NULL,
        .prevObj = NULL,
    };

    Object mirror = {
        .name = "Mirror",
        .desc = "A mirror",
        .openable = 0,
        .open = 0,
        .carryable = 0,
        .nextObj = NULL,
        .prevObj = NULL,
    };

    Object darkBook = {
        .name = "Dark Magic Book",
        .desc = "A mysterious book",
        .openable = 0,
        .open = 0,
        .carryable = 1,
        .nextObj = NULL,
        .prevObj = NULL,
    };

    Object diary = {
        .name = "The Prince Diary",
        .desc = "A diary",
        .openable = 0,
        .open = 0,
        .carryable = 1,
        .nextObj = NULL,
        .prevObj = NULL,
    };

    //fill the rooms with the objects
}

void spawnPlayer(void)
{
    inventory = (ObjectContainer){
        .headObject = NULL,
        .lastObject = NULL,
    };

    player = (Player){
        .currRoom = &startRoom,
        .inventory = &inventory,
    };
}

PAction getInput()
{
    int c;
    char tmp[256];
    char* command = "";
    char* arg1 = "";
    char* arg2 = "";

    char* result = fgets(InputBuffer, 256, stdin);
    if (result != NULL)
    {
        //handle the input
        if(*result != '\0' && *result != EOF && *result != '\n')
        {
            while(isspace(*result))
            {
                result++;
            }
            //handle command
            int i;
            for(i = 0; i < 254 && *result != '\0' && !(isspace(*result))  && *result != EOF && *result != '\n'; i++, result++)
            {
                tmp[i] = result; 
            }
            tmp[i+1] = '\0';
            strncpy(command, tmp, i);

            for(i = 0; i < 255 && *result != '\0' && !(isspace(*result))  && *result != EOF && *result != '\n'; i++, result++)
            {
                tmp[i] = result; 
            }
            tmp[i+1] = '\0';
            strncpy(arg1, tmp, i);

            for(i = 0; i < 255 && *result != '\0' && !(isspace(*result))  && *result != EOF && *result != '\n'; i++, result++)
            {
                tmp[i] = result; 
            }
            tmp[i+1] = '\0';
            strncpy(arg2, tmp, i);
        }
    }
    if(strcmp(command, "MOVETO") == 0)
    {
        MoveTo(&player, arg1);
    }
    else if(strcmp(command, "LOOK") == 0)
    {
        Look(&player);
    }
    else if(strcmp(command, "LOOKAT") == 0)
    {
        LookAt(arg1);
    }
    else if(strcmp(command, "TAKE") == 0)
    {
        Take(&player, arg1);
    }
    else if(strcmp(command, "COMBINE") == 0)
    {
        Combine(&player, arg1, arg2);
    }
    else if(strcmp(command, "PUT") == 0)
    {
        Put(&player, arg1);
    }
    else if(strcmp(command, "USE") == 0)
    {
        Use(&player, arg1);
    }
    else if(strcmp(command, "INVENTORY") == 0)
    {
        Inventory(&player);
    }
    else
    {
        //default case (command doesn't exist)
    }
}