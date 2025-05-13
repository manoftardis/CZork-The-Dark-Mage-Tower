#ifndef OBJECT_H
#define OBJECT_H

#include <stdint.h>

typedef enum 
{
    LOOKAT,
    PUT,
    TAKE,
    COMBINE,
    USE,

} Action;


// Calling an actions has different results, depending on the function we have different arguments required
// Usually they are the new description of the item if interacting with it, the new room descrpition if it changes it and so on...

typedef struct object 
{
    char* name;
    char* desc;

    //boolean values
    uint8_t openable;
    uint8_t open;
    uint8_t carryable;


    //object reference for a list
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