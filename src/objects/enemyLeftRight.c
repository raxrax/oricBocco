//object.direction 0 - left; 1 - right
//special 0-ground 1-air

#define ENEMYLEFTRIGHTSPEED 3
void emenyLeftRightUpdate()
{
    unsigned char bgDownElement;
    unsigned char bgDownElementForward;
    unsigned char xid, yid; // x,y integer division

    if (objects[currentObject].counter != 0)
    {
        objects[currentObject].counter--;
        return;
    }

    objects[currentObject].counter = ENEMYLEFTRIGHTSPEED;

    x = objects[currentObject].x;
    y = objects[currentObject].y;

    xid = x % MAX_GRID_X;
    yid = y % MAX_GRID_Y;

    collisionMap[xid][yid] = 0;

    objects[currentObject].oldx = x;
    objects[currentObject].oldy = y;

    bgElementAddress = addr(x, y);
    bgDownElement = levelData[addr(x, (y + 1))];
    bgDownElementForward = objects[currentObject].direction == 0 ? levelData[addr(x - 1, (y + 1))] : levelData[addr(x + 1, (y + 1))];

    // change direction
    if (objects[currentObject].special == 2 && objects[currentObject].halfx == 0 && (bgDownElementForward == 0 || bgDownElementForward > 40) && bgDownElementForward != ID_LADDER)
    {
        objects[currentObject].direction = objects[currentObject].direction == 0 ? 1 : 0;
        reverseObject(objects[currentObject].spaddr);
    }
    else
    { //fallthrough
        if (objects[currentObject].halfx == 0 && objects[currentObject].special == 0 && (bgDownElement == 0 || bgDownElement > 40) && bgDownElement != ID_LADDER && objects[currentObject].y < MAX_LEVEL_Y - 1)
        { // fallthrough
            ++objects[currentObject].y;
        }
    }

    if (objects[currentObject].y == objects[currentObject].oldy)
    { //left - right
        if (objects[currentObject].direction == 0)
        {
            if (xid > 0 && (objects[currentObject].halfx == 1 || levelData[bgElementAddress - 1] == 0 || levelData[bgElementAddress - 1] > 40))
            {
                if (objects[currentObject].halfx == 0)
                {
                    objects[currentObject].x--;
                    objects[currentObject].halfx = 1;
                }
                else
                {
                    objects[currentObject].halfx = 0;
                }
            }
            else
            {
                objects[currentObject].direction = 1;
                reverseObject(objects[currentObject].spaddr);
            }
        }
        else
        {
            if (xid < MAX_GRID_X - 1 && (levelData[bgElementAddress + 1] == 0 || levelData[bgElementAddress + 1] > 40))
            {
                if (objects[currentObject].halfx == 1)
                {
                    ++objects[currentObject].x;
                    objects[currentObject].halfx = 0;
                }
                else
                {
                    objects[currentObject].halfx = 1;
                }
            }
            else
            {

                objects[currentObject].direction = 0;
                reverseObject(objects[currentObject].spaddr);
            }
        }
    }

    collisionMap[objects[currentObject].x % MAX_GRID_X][objects[currentObject].y % MAX_GRID_Y] = objects[currentObject].type;

    animator();
}