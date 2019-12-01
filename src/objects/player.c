static unsigned char keys = 0;
static unsigned char bombs = 0;
static unsigned char treasures = 0;

void playerUpdate()
{
    static unsigned char idleTimer = 0, xid, yid;
    unsigned char tmpElement;
    unsigned char bgElement;
    unsigned char bgElementLeft;
    unsigned char bgElementRight;

    objects[currentObject].oldx = objects[currentObject].x;
    objects[currentObject].oldy = objects[currentObject].y;

    x = objects[currentObject].x;
    y = objects[currentObject].y;

    xid = x % MAX_GRID_X;
    yid = y % MAX_GRID_Y;

    bgElementAddress = addr(x, y);
    bgElement = levelData[bgElementAddress];
    bgElementLeft = levelData[bgElementAddress - 1];
    bgElementRight = levelData[bgElementAddress + 1];

    //left
    if (key1 == keyLeft)
    {
        if (x == 0 && objects[currentObject].halfx == 0 )
            return;
            
        if (objects[currentObject].halfx == 0 && bgElementLeft < 40 && bgElementLeft > 0)
        {
            return;
        }

        if (objects[currentObject].halfx == 0)
        {
            objects[currentObject].x--;
            objects[currentObject].halfx = 1;
        }
        else
        {
            objects[currentObject].halfx = 0;
        }

        sfx(sfxTableStep);

        objects[currentObject].spaddr = SPRITE_HEROLEFT_ADDR;
        objects[currentObject].frames = SPRITE_HEROLEFT_FRAMES;

        //new room
        if (xid == 0 && objects[currentObject].halfx == 1)
        {
            --currentRoomX;
            objects[currentObject].halfx = 0;
            objects[currentObject].oldx = objects[currentObject].x;
            objects[currentObject].oldy = objects[currentObject].y;
            printCurrentRoom();
        }
    }
    //right
    else if (key1 == keyRight)
    {
        if (x == MAX_LEVEL_X-1)
        {
            return;
        }

        if (levelData[bgElementAddress + 1] < 40 && levelData[bgElementAddress + 1] > 0)
        {
            return;
        }

        if (objects[currentObject].halfx == 1)
        {
            ++objects[currentObject].x;
            objects[currentObject].halfx = 0;
        }
        else
        {
            objects[currentObject].halfx = 1;
        }

        sfx(sfxTableStep);

        objects[currentObject].spaddr = SPRITE_HERORIGHT_ADDR;
        objects[currentObject].frames = SPRITE_HERORIGHT_FRAMES;

        //new room
        if (xid == MAX_GRID_X - 1 && objects[currentObject].halfx == 1)
        {
            ++currentRoomX;
            ++objects[currentObject].x;
            objects[currentObject].oldx = objects[currentObject].x;
            objects[currentObject].oldy = objects[currentObject].y;
            objects[currentObject].halfx = 0;
            printCurrentRoom();
        }
    }
    //up
    else if (key1 == keyUp)
    {
        if (y == 0)
            return;
        if (bgElement != ID_LADDER || objects[currentObject].halfx)
            return;
        if (levelData[addr(x, (y - 1))] > ID_SPACE && levelData[addr(x, (y - 1))] < 40)
            return;

        sfx(sfxTableStep);

        objects[currentObject].y--;
        objects[currentObject].spaddr = SPRITE_HEROUPDOWN_ADDR;
        objects[currentObject].frames = SPRITE_HEROUPDOWN_FRAMES;

        if (yid == 0)
        {
            currentRoomY--;
            printCurrentRoom();
            objects[currentObject].oldx = objects[currentObject].x;
            objects[currentObject].oldy = objects[currentObject].y;
        }
    }
    //down
    else if (key1 == keyDown)
    {
        if (y == MAX_LEVEL_Y)
        {
            engineState = STATE_GAMEOVER;
            return;
        }
        tmpElement = levelData[addr(x, (y + 1))];
        if (tmpElement != ID_LADDER && tmpElement != ID_SPACE || objects[currentObject].halfx)
        {
            return;
        }

        sfx(sfxTableStep);
        ++objects[currentObject].y;
        objects[currentObject].spaddr = SPRITE_HEROUPDOWN_ADDR;
        objects[currentObject].frames = SPRITE_HEROUPDOWN_FRAMES;

        //next room
        if (yid == MAX_GRID_Y - 1)
        {
            ++currentRoomY;
            printCurrentRoom();
            objects[currentObject].oldx = objects[currentObject].x;
            objects[currentObject].oldy = objects[currentObject].y;
        }
    }

    else if (key1 == keyColor)
    {
        isColored = 1 - isColored;
        setColors();
    }

    else if (key1 == keyDisplayType)
    { // display type
        bgAndObjectsType = bgAndObjectsType ? 0 : 1;
    }

    else if (key1 == keyBomb)
    {
        useBomb();
    }

    else if (key1 == keyUse)
    {
        useHandle(bgElement);
        openDoor();
    }

    else if (key1 == keyGiveUp)
    {
        engineState = STATE_GAMEOVER;
        return;
    }

    else if (key1 == keySound)
    {
        isSoundDisabled = 1 - isSoundDisabled;
        return;
    }

    else if (key1 == keyLoadLevel)
    {
        load();
        engineState = STATE_GAMEOVER;
        return;
    }

    // else if (key1 == '6')
    // {
    //     memcpy(0xa000,0x07800,0x2000-200);
    //     get(); get();
    //     return;
    // }

    if (!key1)
    {
        switch (objects[currentObject].spaddr)
        {
        case SPRITE_HERORIGHT_ADDR:
            objects[currentObject].spaddr = SPRITE_HEROIDLERIGHT_ADDR;
            objects[currentObject].frames = SPRITE_HEROIDLERIGHT_FRAMES;
            objects[currentObject].direction = 1;
            break;
        case SPRITE_HEROLEFT_ADDR:
            objects[currentObject].spaddr = SPRITE_HEROIDLELEFT_ADDR;
            objects[currentObject].frames = SPRITE_HEROIDLELEFT_FRAMES;
            objects[currentObject].direction = -1;
            break;
        }
    }
    else
    {
        idleTimer = 0;
        animator();
    }

    ++idleTimer;
    if (idleTimer == 7)
    {
        idleTimer = 0;
        animator();
    }

    //items
    switch (bgElement)
    {
    case ID_BOMB:
        ++bombs;
        levelData[bgElementAddress] = 0;
        updateBoard();
        sfx(sfxTableGetItem);
        break;

    case ID_KEY:
        ++keys;
        levelData[bgElementAddress] = 0;
        updateBoard();
        sfx(sfxTableGetItem);
        break;

    case ID_COIN:
        deleteObjectsByPosition(x, y);
    case ID_CHEST:
    case ID_CHEST2:
        --treasures;
        levelData[bgElementAddress] = 0;
        printBGObjectById(x, y, 0);
        animator();
        updateBoard();
        sfx(sfxTableGetItem);

        //if level complete
        if (treasures == 0)
        {
            changeElements(ID_EXITCLOSED, ID_EXITOPEN);
            changeElements(ID_GRAVE, ID_BROKENGRAVE);
            updateElementOnTheScreen(TRUE);
            sfx(sfxTableGetAllItems);
        }

        break;
    case ID_EXITOPEN:
        cls();
        sfx(sfxTableGetAllItems);
        engineState = STATE_NEXTLEVEL;
        return;
        break;
    }

    //collision
    if (collisionMap[xid][yid] != 0)
    {
        engineState = STATE_GAMEOVER;
    }

    // trap elements
    if (bgElement > 159 && bgElement < 166)
    {
        objects[currentObject].x = objects[currentObject].oldx;
        objects[currentObject].y = objects[currentObject].oldy;
        engineState = STATE_GAMEOVER;
    }

    //fallthrough
    tmpElement = levelData[addr(objects[currentObject].x, objects[currentObject].y + 1)];
    if ((tmpElement > 39 || tmpElement == 0) && tmpElement != ID_LADDER && bgElement != ID_LADDER)
    {
        tmpElement = levelData[addr(objects[currentObject].x, objects[currentObject].y) + MAX_LEVEL_X + 1];
        if (objects[currentObject].halfx == 0 || (tmpElement > 39 || tmpElement == 0) && tmpElement != ID_LADDER && bgElementRight != ID_LADDER)
        {

            objects[currentObject].oldy = objects[currentObject].y;
            objects[currentObject].oldx = objects[currentObject].x;
            ++objects[currentObject].y;

            if (objects[currentObject].y % MAX_GRID_Y){
                animator();
            }

            bgElement = levelData[addr(objects[currentObject].x, objects[currentObject].y)];
            // trap elements
            if (bgElement > 159 && bgElement < 166)
            {
                objects[currentObject].x = objects[currentObject].oldx;
                objects[currentObject].y = objects[currentObject].oldy;
                engineState = STATE_GAMEOVER;
                return;
            }

            // die
            if (objects[currentObject].y >= MAX_LEVEL_Y)
            {
                engineState = STATE_GAMEOVER;
                return;
            }

            //next room || objects[currentObject].y % MAX_GRID_Y == 0
            if (objects[currentObject].y % MAX_GRID_Y == MAX_GRID_Y - 1 || objects[currentObject].y % MAX_GRID_Y == 0)
            {
                ++currentRoomY;
                ++objects[currentObject].y;

                objects[currentObject].oldx = objects[currentObject].x;
                objects[currentObject].oldy = objects[currentObject].y;
                printCurrentRoom();
            }

        }
    }
}

void updateBoard()
{
    //bombs
    printBGObject(START_SCREEN_ADDRES + (BOARD_ITEM2 + 2) * 2 + multi40[15 * 12], SPRITE_X_ADDR + 2 + (bombs / 10) * 2);
    printBGObject(START_SCREEN_ADDRES + (BOARD_ITEM2 + 3) * 2 + multi40[15 * 12], SPRITE_X_ADDR + 2 + (bombs % 10) * 2);

    //keys
    printBGObject(START_SCREEN_ADDRES + (BOARD_ITEM1 + 2) * 2 + multi40[15 * 12], SPRITE_X_ADDR + 2 + (keys / 10) * 2);
    printBGObject(START_SCREEN_ADDRES + (BOARD_ITEM1 + 3) * 2 + multi40[15 * 12], SPRITE_X_ADDR + 2 + (keys % 10) * 2);
}

void changeElements(unsigned char src, unsigned char des)
{
    unsigned int levelAddress;
    for (levelAddress = 0x6f00; levelAddress < 0x77ff; ++levelAddress)
    {
        if (peek(levelAddress) == src)
        {
            poke(levelAddress, des);
        }
    }
}

void useHandle(unsigned char bgElement)
{
    switch (bgElement)
    {
    case ID_SWITCHOFF:
        sfx(sfxTableHandle);
        changeElements(ID_BRICK, ID_HOLE);
        changeElements(ID_SWITCHOFF, ID_SWITCHON);
        updateElementOnTheScreen(FALSE);

        break;

    case ID_SWITCHON:
        sfx(sfxTableHandle);
        changeElements(ID_HOLE, ID_BRICK);
        changeElements(ID_SWITCHON, ID_SWITCHOFF);
        updateElementOnTheScreen(FALSE);
        break;
    }
}

void useBomb()
{
    unsigned char bgForwardElement;
    bgForwardElement = levelData[addr(x + (objects[currentObject].direction == 1 ? 1 : -1), y)];
    if (bombs > 0 && (bgForwardElement > 40 || bgForwardElement == 0))
    {
        addObject(
            ID_BOMBACTIVATED,
            bombUpdate,
            objects[currentObject].x + (objects[currentObject].direction == 1 ? 1 : -1),
            objects[currentObject].y,
            SPRITE_BOMB_ADDR,
            SPRITE_BOMB_FRAMES,
            0);

        objects[newObject].state = SPRITE_BOMB_FRAMES;
        bombs--;
        updateBoard();
    }
}

void openDoor()
{
    unsigned int bgFrontElementAddr;
    bgFrontElementAddr = addr(x + (objects[currentObject].direction == 1 ? 1 : -1), y);
    if (levelData[bgFrontElementAddr] == ID_CLOSEDDOOR && keys > 0)
    {
        keys--;
        levelData[bgFrontElementAddr] = ID_OPENDOOR;
        printBGObjectById(objects[currentObject].x + (objects[currentObject].direction == 1 ? 1 : -1), objects[currentObject].y, ID_OPENDOOR);
        updateBoard();
        sfx(sfxTableOpenDoor);
    }
}

void updateElementOnTheScreen(unsigned char addObjects)
{
    unsigned char element;
    for (y = MAX_GRID_Y * currentRoomY; y < MAX_GRID_Y * currentRoomY + MAX_GRID_Y; ++y)
    {
        for (x = MAX_GRID_X * currentRoomX; x < MAX_GRID_X * currentRoomX + MAX_GRID_X; ++x)
        {
            element = levelData[addr(x, y)];

            switch (element)
            {
            case ID_CLOSEDDOOR:
            case ID_OPENDOOR:
            case ID_SWITCHON:
            case ID_SWITCHOFF:
            case ID_BRICK:
            case ID_HOLE:
                printElement(element, x, y);
                break;
            }

            if (addObjects == TRUE)
            {
                switch (element)
                {
                case ID_BROKENGRAVE:
                    addObjectInEngine(element, x, y);
                    break;
                }
            }
        }
    }
}
