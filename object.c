#include "object.h"

#include "string.h"

char* getName_Text(Object* o)
{
    char* ret = "a ";
    ret = strcat(ret, o->name);
    if (o->openable)
    {
        if (o->open)
            ret = strcat(ret, " (open)");  
        else
            ret = strcat(ret, " (closed)");
    }
    ret = strcat (ret, "\n");
    return ret;
}

char* getDesc_Text(Object* o)
{
    char* ret = o->desc;
    if (o->openable)
    {
        if (o->open)
            ret = strcat(ret, "\n The object is open");  
        else
            ret = strcat(ret, "\n The object is closed");  
    }
    ret = strcat (ret, "\n");
    return ret;
}

void addObject(ObjectContainer* c, Object* o)
{
    c->lastObject->nextObj = o;
    o->prevObj = c->lastObject;
    c->lastObject = o;
}

void removeObject(ObjectContainer* c, Object* o)
{
    if (c->headObject == o)
    {
        c->headObject == c->headObject->nextObj;
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

void destroyObject(Object* o)
{
    free(o);
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