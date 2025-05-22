#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "player.h"
#include "room.h"
#include "utility.h"

const char *comb_objects[] = {
    "Black Root",
    "Dried Glimmerleaf",
    "Silverly-Black Hair",
    "Bat Carcass",
    "Wooden Chest",
    "Cylinder"};

Player *playerInit(Room *start, ObjectContainer *inventory)
{
    Player* ret = malloc(sizeof(Player));
    ret->currRoom = start;
    ret->inventory = inventory;
    return ret;
}

void MoveTo(Player *p, char *dest)
{   
    EDirection move = ERROR;

    for(size_t i = 0; i < Direction_Size-1; i++)
    {
        if(!(strcmp(dest, Direction_String[i])))
        {
            move = i;
        }
    }

    if (move == ERROR)
        printf("%s is not a valid direction \n", dest);
    else
    {
        p->currRoom = getRoom_Dir(p->currRoom, move);
        Look(p);
    }
}

void Look(Player* p)
{
    printf("%s\n", getRoomName(p->currRoom));
    printf("%s\n", getRoomDesc(p->currRoom));
}

//check if the object is in the room or in the inventory
//if in the room or in the inventory, print the description
void LookAt(Player* p, char *ObjectName)
{
    Object* obj = getObject(p, ObjectName);
    if(obj != NULL)
    {
        printf("%s\n", getDesc_Text(obj));
    }
    else
    {
        printf("%s is not a valid object \n", ObjectName);
    }
    
}

void Combine(Player *p, char *ObjectName1, char *ObjectName2)
{
    Object* obj1 = getObjectFromContainer(p->inventory, ObjectName1);
    Object* obj2 = getObjectFromContainer(p->inventory, ObjectName2);

    if(obj1 == NULL || obj2 == NULL){
        printf("One of the objects is not in your inventory.\n");
        return;
    }
    
    if((strcmp(obj1->name, "Wooden Chest") == 0 && strcmp(obj2->name, "Cylinder") == 0) || (strcmp(obj2->name, "Wooden Chest") == 0 && strcmp(obj1->name, "Cylinder") == 0))
    {
        printf("You combine the \033[31m%s\033[0m and the \033[31m%s\033[0m. You insert the cylindrical mechanism into the small wooden chest and it fits perfectly."
            "Together they form a \033[31mmusic box\033[0m! This is the princess's music box.\n"
            "You pull the lever to see if it works and the music box plays a sad and melancholic tune."
            "You fear that this music will attract someone or something, but nothing happens.\n"
            "The music ends, and nothing has changed.\n", obj1->name, obj2->name);
        Object* music_box = objectInit("Music Box", "A delicate music box, its brass surface dulled by time. It hums a lullaby long forgotten.", 0, 0, 1, 0);
        removeObject(p->inventory, obj1);
        removeObject(p->inventory, obj2);
        addObject(p->inventory, music_box);

    }
    else if((strcmp(obj1->name, "Black Root") == 0 && strcmp(obj2->name, "Dried Glimmerleaf") == 0) || (strcmp(obj2->name, "Black Root") == 0 && strcmp(obj1->name, "Dried Glimmerleaf") == 0))
    {
        if(strcmp(p->currRoom->name, "The Alchemy Room") != 0)
        {
            printf("You cannot combine %s and %s here.\n", obj1->name, obj2->name);
            return;
        }
        else{
            printf("You combine the \033[31m%s\033[0m and the \033[31m%s\033[0m. At first they resist, then merge with a hiss — becoming a glowing azure mixture.\n"
                "The scent of ozone fills the air.\n"
                "You carefully pour it into the alembic, and the potion begins to bubble and distill.\n"
                "Moments later, a clear vial fills with pale blue liquid, pulsing faintly.\n\n"
                "A \033[31mpotion of shrinking\033[0m is created.\n", obj1->name, obj2->name);
            Object* blue_potion = objectInit("Potion of Shrinking", "A pale blue potion that let you shrink your body.", 0, 0, 1, 1);
            removeObject(p->inventory, obj1);
            removeObject(p->inventory, obj2);
            addObject(p->inventory, blue_potion);
            ObjectUsability* blue_potion_usability = objectUsabilityInit();
            blue_potion_usability->usableRoomCount = 1;
            blue_potion_usability->usableRooms[0] = p->currRoom;
            blue_potion_usability->usedRoomCount = 0;
            blue_potion->usability = blue_potion_usability;
        }
        

    }
    else if((strcmp(obj1->name, "Silvery-black hair") == 0 && strcmp(obj2->name, "Bat Carcass") == 0) || (strcmp(obj2->name, "Silvery-black hair") == 0 && strcmp(obj1->name, "Bat Carcass") == 0))
    {
        if(strcmp(p->currRoom->name, "The Laboratory") != 0)
        {
            printf("You cannot combine %s and %s here.\n", obj1->name, obj2->name);
            return;
        }
        else{
            printf("You combine the \033[31m%s\033[0m and the \033[31m%s\033[0m. — the blend sizzles, turns black, then shifts to a shimmering gold hue.\n"
                "The mixture pulses like a heartbeat.\n""You decant the liquid into the alembic.\n"
                "Steam rises as it distills into a rich, amber-colored potion.\n\n"
                "A \033[31mpotion of shape-changing\033[0m is created.\n", obj1->name, obj2->name);
            Object* amber_potion = objectInit("Potion of Shape-Changing", "An amber-colored potion that makes you change your form.", 0, 0, 1, 1);
            removeObject(p->inventory, obj1);
            removeObject(p->inventory, obj2);
            addObject(p->inventory, amber_potion);
            ObjectUsability* amber_potion_usability = objectUsabilityInit();
            amber_potion_usability->usableRoomCount = 1;
            amber_potion_usability->usableRooms[0] = p->currRoom->north->room_to->east->room_to;
            amber_potion_usability->usedRoomCount = 0;
            amber_potion->usability = amber_potion_usability;
        }
        

    }
    else
    {
        printf("You cannot combine %s and %s.\n", ObjectName1, ObjectName2);
    }
}

void Put(Player *p, char *ObjectName1)
{
    Object* obj = getObjectFromContainer(p->inventory, ObjectName1);
    if(obj != NULL)
    {
        removeObject(p->inventory, obj);
        addObject(p->currRoom->inventory, obj);
        printf("You put the \033[31m%s\n\033[0m", obj->name);

        // --- Check if in the statue room and if the order is correct ---
        if (strcmp(p->currRoom->name, "The Statue Room") == 0) {
            // Define the correct order (these should be the actual pointers, not new objects)
            const char* correctOrder[6] = { "Lens", "Hook", "Shard", "Fang", "Lockpick", "Seal" };
            int count = 0;
            Object* curr = p->currRoom->inventory->headObject;
            while (curr) {
                count++;
                curr = curr->nextObj;
            }
            if (count == 6) {
                if (checkObjectOrder(p->currRoom->inventory, correctOrder, 6)) {
                    printf("\033[34mYou hear a deep, resonant click. The statues' talismans glow, and the obsidian door unlocks!\033[0m\n");
                    // You can add logic here to open the obsidian door, e.g.:
                    if (p->currRoom->north) p->currRoom->north->open = 1;
                } else {
                    printf("Nothing happens. The statues seem to expect a different order.\n");
                }
            }
        }
        // -------------------------------------------------------------

    }
    else
    {
        printf("%s is not a valid object \n", ObjectName1);
    }
}

void Take(Player *p, char *ObjectName1)
{
    Object* obj = getObjectFromContainer(p->currRoom->inventory, ObjectName1);
    if(obj != NULL)
    {
        if(strcmp(obj->name, "Silvery-black hair") == 0)
        {
            if(p->currRoom->inventory->headObject->open == 0)
            {
                printf("The glass cabinet is closed. You need to open it first.\n");
                return;
            }
        }
        removeObject(p->currRoom->inventory, obj);
        addObject(p->inventory, obj);
        printf("You took the \033[31m%s\033[0m\n", obj->name);
    }
    else
    {
        printf("%s is not a valid object \n", ObjectName1);
    }
}

void Inventory(Player *p)
{
    printContainer(p->inventory);
}

// Helper to check if object is usable in current room
int isUsableInRoom(ObjectUsability* usability, Room* room) {
    if (!usability) return 0;
    for (int i = 0; i < usability->usableRoomCount; i++) {
        if (usability->usableRooms[i] == room) return 1;
    }
    return 0;
}

// Helper to check if object was already used in this room
int wasUsedInRoom(ObjectUsability* usability, Room* room) {
    if (!usability) return 0;
    for (int i = 0; i < usability->usedRoomCount; i++) {
        if (usability->usedInRooms[i] == room) return 1;
    }
    return 0;
}

// Helper to mark object as used in this room
void markUsedInRoom(ObjectUsability* usability, Room* room) {
    if (!usability) return;
    if (usability->usedRoomCount < 5) {
        usability->usedInRooms[usability->usedRoomCount++] = room;
    }
}

void Use(Player *p, char *ObjectName1)
{
    Object* obj = getObjectFromContainer(p->inventory, ObjectName1);
    if(obj == NULL) {
        printf("%s is not in your inventory.\n", ObjectName1);
        return;
    }
    if(!obj->usable || obj->usability == NULL) {
        printf("%s cannot be used.\n", ObjectName1);
        return;
    }
    if(!isUsableInRoom(obj->usability, p->currRoom)) {
        printf("You can't use %s here.\n", ObjectName1);
        return;
    }
    if(wasUsedInRoom(obj->usability, p->currRoom)) {
        printf("You have already used %s here.\n", ObjectName1);
        return;
    }
    // Mark as used
    markUsedInRoom(obj->usability, p->currRoom);

    // Perform the actual effect (customize per object/room)
    printf("You used the \033[31m%s\033[0m!\n", obj->name);
    if(strcmp(obj->name, "Crowbar") == 0) {
        if(strcmp(p->currRoom->name, "The Atrium") == 0) {
            printf("You jam the rusty crowbar beneath the boards. "
                "With a loud creak and a shower of splinters, the planks give way, collapsing to the floor.\n"
                "The doorway to the cabin is now open.\n");
            p->currRoom->west->open = 1;
        }
        else if(strcmp(p->currRoom->name, "The Ingredient Storeroom") == 0) {
            printf("You wedge the crowbar into the old hinge and apply pressure. "
                "With a loud snap, the cabinet swings open.\n" 
                "Inside, you retrieve the \033[31msilvery-black hair\033[0m. It's warm to the touch, unnaturally so.\n");
            Object *temp = getObjectFromContainer(p->currRoom->inventory, "Glass Cabinet");
            temp->open = 1;
            }
    }
    else if(strcmp(obj->name, "Key") == 0) {
        if(strcmp(p->currRoom->name, "The Atrium") == 0) {
            printf("You insert the key into the lock. With a satisfying click, the door swings open.\n");
            p->currRoom->north->open = 1;
        }
    }
    else if(strcmp(obj->name, "Vial") == 0) {
        if(strcmp(p->currRoom->name, "The Atrium") == 0) {
            printf("You uncork the vial and carefully pour the corrosive liquid onto the fungal seal."
                "At first, nothing happens. Then the door begins to hiss and sizzle, emitting a noxious green smoke. The mold melts away in bubbling globs, revealing the wooden door beneath.\n\n"
                "Now that the door is open, there is a corridor in front of you that you cannot see the end of. The darkness swallows the warm light of the candles."
                "There is no hope ahead, only the tenacity of those who want to discover the truth. \n"
                "\033[35mThe way south is now open.\033[0m\n");
            p->currRoom->south->open = 1;
            removeObject(p->inventory, obj);
        }
    }
    else {
        printf("You used %s, but nothing happened.\n", obj->name);
    }
}

Object* getObject(Player *p, char *ObjectName)
{
    Object* obj = NULL;
    ObjectContainer* c = p->currRoom->inventory;
    if(c != NULL)
    {
        obj = getObjectFromContainer(c, ObjectName);
    }
    else
    {
        obj = getObjectFromContainer(p->inventory, ObjectName);
    }
    
    return obj;
}

Object* getObjectFromContainer(ObjectContainer* c, char* ObjectName)
{
    Object* obj = c->headObject;
    char objNameUpper[256];
    char searchNameUpper[256];
    
    // Convert ObjectName to uppercase for case-insensitive comparison
    strncpy(searchNameUpper, ObjectName, sizeof(searchNameUpper) - 1);
    searchNameUpper[sizeof(searchNameUpper) - 1] = '\0';
    stringToUpper(searchNameUpper);

    while(obj != NULL)
    {

        // Copy only up to 255 chars from obj->name, ensure null-termination
        strncpy(objNameUpper, obj->name, sizeof(objNameUpper) - 1);
        objNameUpper[sizeof(objNameUpper) - 1] = '\0';
        stringToUpper(objNameUpper);

        if(strcmp(objNameUpper, searchNameUpper) == 0)
        {
            return obj;
        }
        obj = obj->nextObj;
    }
    return NULL;
}

void Help()
{
    printf("Commands:\n");
    printf("MOVETO <direction>\n");
    printf("LOOK to see your surroundings\n");
    printf("LOOKAT <object>\n");
    printf("TAKE <object>\n");
    printf("PUT <object>\n");
    printf("COMBINE <object1> <object2>\n");
    printf("USE <object>\n");
    printf("INVENTORY\n");
    printf("HELP\n");
    printf("\033[33mYellow\033[0m text marks things you can examine.\n");
    printf("\033[31mRed\033[0m text shows items you can interact with or pick up.\n");
    printf("\033[32mGreen\033[0m text highlights available directions.\n");
    printf("\033[34mBlue\033[0m text provides helpful hints or suggestions.\n");
    printf("to interact with objects composed of multiple words, use quotes.\n");
    printf("Example: \"Glass Cabinet\"\n");
    printf("Type 'quit' to quit the game.\n");
    printf("Type 'help' to see this list again.\n");
}