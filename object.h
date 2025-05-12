#ifndef OBJECT_H
#define OBJECT_H

#include <stdint.h>

typedef enum 
{
    LOOKAT,
    LOOKUNDER,
    TAKE,
    OPEN,
    PULL,
    PUSH,

} Action;


// Calling an actions has different results, depending on the function we have different arguments required
// Usually they are the new description of the item if interacting with it, the new room descrpition if it changes it and so on...

typedef struct object 
{
    char* name;
    char* desc;
    //maybe we don't want this since the name will have the adjective
    char** adjectives;

    // Possible actions for the function array are 
    // LOOK AT
    // LOOK UNDER
    // TAKE
    // OPEN
    // PULL
    // PUSH
    void (*actions[sizeof(Action)])();


    //boolean values
    uint8_t openable;
    uint8_t open;
    uint8_t fixture;
    uint8_t carryable;

    Object* prevObj;
    Object* nextObj;

} Object;

typedef struct objectContainer
{
    Object* headObject;
    Object* lastObject;

}ObjectContainer;


char* getName_Text(Object* o);

char* getDesc_Text(Object* o);

void addObject(ObjectContainer* c, Object* o);

void removeObject(ObjectContainer* c, Object* o);

void destroyObject(Object* o);

void printContainer(ObjectContainer* c);

//Open the obeject if it can be opened
void openObject(Object* o);

#endif