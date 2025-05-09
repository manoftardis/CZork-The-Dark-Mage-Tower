#include <stdint.h>

typedef struct object 
{
    char* name;
    char* desc;
    char** adjectives;
    //inserire un array di puntatori di funzioni???
    
    //boolean values
    uint8_t openable;
    uint8_t open;
    uint8_t fixture;
    uint8_t carryable;

} Object;

typedef struct objectContainer
{
    Object* container;

}ObjectContainer;


char* getName(Object o);

char* getDesc(Object o);

void addObject(ObjectContainer c, Object o);

void removeObject(ObjectContainer, char* name ); //oppure passare l'oggetto e controllare l'area di memoria se esiste