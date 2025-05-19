#include <stdio.h>
#include <stdlib.h>

#include "object.h"
#include "string.h"

Object *objectInit(char *name, char *desc, uint8_t openable, uint8_t open, uint8_t carryable)
{
    Object* ret = malloc(sizeof(Object));

    ret->name = name;
    ret->desc = desc;
    ret->openable = openable;
    ret->open = open;
    ret->carryable = carryable;

    ret->nextObj = NULL;
    ret->prevObj = NULL;//

    return ret;
}

ObjectContainer *containerInit()
{
    ObjectContainer* ret = malloc(sizeof(ObjectContainer));

    ret->headObject = NULL;
    ret->lastObject = NULL;

    return ret;
}

char *getName_Text(Object *o)
{
    char* buffer = malloc(1024 * sizeof(char)); 
    strcpy(buffer, "a ");
    strcat(buffer, o->name);
    if (o->openable)
    {
        if (o->open)
            strcat(buffer, " (open)");  
        else
            strcat(buffer, " (closed)");
    }
    strcat(buffer, "\n");
    return buffer;
}

char* getDesc_Text(Object* o)
{
    char* buffer = malloc(2048 * sizeof(char)); 
    strcpy(buffer, o->desc);
    if (o->openable)
    {
        if (o->open)
            strcat(buffer, "\n The object is open");  
        else
            strcat(buffer, "\n The object is closed");  
    }
    strcat (buffer, "\n");
    return buffer;
}

void addObject(ObjectContainer* c, Object* o)
{
    if(c->headObject == NULL)
    {
        c->headObject = o;
        c->lastObject = o;
    }
    else
    {
        c->lastObject->nextObj = o;
        o->prevObj = c->lastObject;
        c->lastObject = o;
    }
}

void removeObject(ObjectContainer* c, Object* o)
{
    if (c->headObject == o)
    {
        //set the head to the next object
        c->headObject = c->headObject->nextObj;

        //if new head is null, tail is null too
        if(c->headObject == NULL)
            c->lastObject = NULL;
    }
    else
    {
        Object* next = c->headObject;
        while(next)
        {
            if(next == o)
            {
                next->prevObj->nextObj = next->nextObj;
                next->nextObj->prevObj = next->prevObj;
                next = NULL;
            }
            else
            {
                next = next->nextObj;
            }
        }
    }
}

void printContainer(ObjectContainer* c)
{
    Object* elem = c->headObject;
    while(elem)
    {
        printf("%s", getName_Text(elem));
        printf("%s", getDesc_Text(elem));
        printf("\n\n");
        elem = elem->nextObj;
    }
}