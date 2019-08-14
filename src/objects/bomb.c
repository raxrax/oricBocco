void bombUpdate()
{
    unsigned char bgDownElement;

    objects[currentObject].counter++;
    if (objects[currentObject].counter % 4 != 0)
    {
        return;
    }

    objects[currentObject].oldx = objects[currentObject].x;
    objects[currentObject].oldy = objects[currentObject].y;

    bgDownElement = levelData[addr(objects[currentObject].x, (objects[currentObject].y + 1))];

    //fallthrough
    if ((bgDownElement == 0 || bgDownElement > 40) && bgDownElement != ID_LADDER && objects[currentObject].y < MAX_LEVEL_Y - 1)
    {
        objects[currentObject].y++;
    }

    animator();

    if (objects[currentObject].state == 0)
    {
        objects[currentObject].active = 0;
        printBG();

        addObject(
            ID_EXPLOSION,
            explosionUpdate,
            objects[currentObject].x,
            objects[currentObject].y,
            SPRITE_EXPLOSION_ADDR,
            SPRITE_EXPLOSION_FRAMES,
            0);
        objects[newObject].state = SPRITE_EXPLOSION_FRAMES;

        sfx(sfxTableExplode);

        clearNeighbors();

        return;
    }
}

void clearNeighbors()
{
    x = objects[currentObject].x;
    y = objects[currentObject].y;

    clearPos(x - 1, y - 1);
    clearPos(x, y - 1);
    clearPos(x + 1, y - 1);

    clearPos(x - 1, y);
    clearPos(x, y);
    clearPos(x + 1, y);

    clearPos(x - 1, y + 1);
    clearPos(x, y + 1);
    clearPos(x + 1, y + 1);
}

void clearPos(unsigned char x, unsigned char y)
{
    unsigned char bgElementAddress = levelData[addr(x, y)];
    //deleteObjectsByPosition(x,y);
    if (bgElementAddress > 19 && bgElementAddress < 28)
    {
        levelData[addr(x, y)] = 0;
        printBGObjectById(x, y, 0);

        addObject(
            ID_EXPLOSION,
            explosionUpdate,
            x,
            y,
            SPRITE_EXPLOSION_ADDR,
            SPRITE_EXPLOSION_FRAMES,
            0);
        objects[newObject].state = SPRITE_EXPLOSION_FRAMES;
    }
}
