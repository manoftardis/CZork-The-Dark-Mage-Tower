#include "player.h"
#include "room.h"

void MoveTo(Player* p, EDirection dest)
{   
    p->currRoom = getRoom_Dir(p->currRoom, dest);
}