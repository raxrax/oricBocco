//object.direction 0 - down; 1 - up
//special 0-normal 1-spider
void enemyUpDownUpdate()
{
    unsigned char bgDownElement, bgUpElement;
    unsigned char xid, yid; // x,y integer division

    if (objects[currentObject].counter != 0)
    {
        --objects[currentObject].counter;
        return;
    }
    objects[currentObject].counter = 3;

    x = objects[currentObject].x;
    y = objects[currentObject].y;
    objects[currentObject].oldx = x;
    objects[currentObject].oldy = y;

    xid = x % MAX_GRID_X;
    yid = y % MAX_GRID_Y;

    collisionMap[xid][yid] = 0;

    bgElementAddress = addr(x, y);
    bgDownElement = levelData[addr(x, (y + 1))];
    bgUpElement = levelData[addr(x, (y - 1))];

    if (objects[currentObject].direction == 0)
    {
        if (yid > 0 && (bgUpElement == 0 || bgUpElement > 40))
        {
            objects[currentObject].y--;
        }
        else
        {
            objects[currentObject].direction = 1;
        }
    }
    else
    {
        if (yid < MAX_GRID_Y - 1 && (bgDownElement == 0 || bgDownElement > 40) && bgDownElement != ID_LADDER)
        {
            objects[currentObject].y++;
        }
        else
        {
            objects[currentObject].direction = 0;
        }
    }

    animator();

    if (objects[currentObject].direction == 1 && objects[currentObject].special == 1 && y != objects[currentObject].y)
    {
        printBGObjectById(x, y, ID_SPIDERWEB);
    }

    collisionMap[objects[currentObject].x % MAX_GRID_X][objects[currentObject].y % MAX_GRID_Y] = objects[currentObject].type;
}