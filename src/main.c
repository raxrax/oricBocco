#include <compat.h>

#include "vars.h"
#include "main.h"

#include "sfxTables.c"
#include "sounds.c"
#include "common.c"
#include "engine.c"
#include "objects.c"
#include "screens.c"

unsigned char playerStartX = 0;
unsigned char playerStartY = 0;

char string[50];

unsigned char isSetPlayer = 0;

void main()
{
    char key1 = 0;

    //  poke(0x24e,1);
    //  poke(0x24f,1);

    init();

    titleScreen();

    printMenu();
    while (key1 != keyExit)
    {

        key1 = get();
        switch (key1)
        {
        case 'P':
            hires();
            poke(0x26A, CURSOR_START);
            game();
            printMenu();
            break;

        case 'S':
            printStory();
            printMenu();
            break;

        case 'I':
            printKeysScreen(0);
            printMenu();
            break;

        case 'R':
            printKeysScreen(1);
            printMenu();
            break;

        case 'A':
            printAboutGame();
            printMenu();
            break;

        default:
            break;
        }
    }

    cls();
}

void game()
{

    level = 0;

    // modify invisible brick (makes it invisible)
    doke(elementsAddr[ID_INVISIBLEBRICK],0);

    //clear level name
    memset(currentLevelName, 0, sizeof(currentLevelName));

    //set level name
    sprintf(currentLevelName, "LEVEL%d", level);

    // game board
    setColors();
    printGameBoard();

    engineState = STATE_CLEAR;

    while (engineState != STATE_END)
    {

        keys = 0;
        bombs = 0;
        treasures = 0;
        isSetPlayer = 0;

        initObjects();

        loadLevel(currentLevelName);

        changeElements(ID_EXITOPEN, ID_EXITCLOSED);

        setColors();

        findElements();

        printCurrentRoom();

        printDesigner();

        engine();

        if (engineState == STATE_NEXTLEVEL)
        {
            hiresTextDouble(12, 80, " Level complete ");
            if (level < maxLevel)
            {
                ++level;
            }else{
                level = 0;
            }
            memset(currentLevelName, 0, sizeof(currentLevelName));
            sprintf(currentLevelName, "LEVEL%d", level);
        }

        if (engineState == STATE_GAMEOVER)
        {
            sfx(sfxTableDying);
            hiresTextDouble(14, 80, " GAME OVER ");
        }

        if (engineState != STATE_END)
        {
            wait(100);
        }
    }
}

void printGameBoard()
{
    for (i = 0; i < MAX_GRID_X; i++)
    {
        printBGObject(START_SCREEN_ADDRES + 40 * 14 * 12 + 6 * 40 + i * 2, elementsAddr[22]); //123
        printBGObject(START_SCREEN_ADDRES + 40 * 15 * 12 + 6 * 40 + i * 2, elementsAddr[22]); //24
    }

    printBGObject(START_SCREEN_ADDRES + 40 * 15 * 12 + (BOARD_ITEM1 + 5) * 2, elementsAddr[73]);
    printBGObject(START_SCREEN_ADDRES + 40 * 15 * 12 + (BOARD_ITEM2 + 5) * 2, elementsAddr[73]);

    printBGObject(START_SCREEN_ADDRES + 40 * 15 * 12 + (BOARD_ITEM1 - 2) * 2, elementsAddr[72]);
    printBGObject(START_SCREEN_ADDRES + 40 * 15 * 12 + (BOARD_ITEM2 - 2) * 2, elementsAddr[72]);

    printBGObject(START_SCREEN_ADDRES + 40 * 15 * 12 + (BOARD_ITEM2 - 1) * 2, elementsAddr[0]);
    printBGObject(START_SCREEN_ADDRES + 40 * 15 * 12 + (BOARD_ITEM2 + 2) * 2, SPRITE_X_ADDR + 2);
    printBGObject(START_SCREEN_ADDRES + 40 * 15 * 12 + (BOARD_ITEM2 + 3) * 2, SPRITE_X_ADDR + 2);
    printBGObject(START_SCREEN_ADDRES + 40 * 15 * 12 + (BOARD_ITEM2 + 4) * 2, elementsAddr[0]);
    printBGObject(START_SCREEN_ADDRES + 40 * 15 * 12 + (BOARD_ITEM1 - 1) * 2, elementsAddr[0]);
    printBGObject(START_SCREEN_ADDRES + 40 * 15 * 12 + (BOARD_ITEM1 + 2) * 2, SPRITE_X_ADDR + 2);
    printBGObject(START_SCREEN_ADDRES + 40 * 15 * 12 + (BOARD_ITEM1 + 3) * 2, SPRITE_X_ADDR + 2);
    printBGObject(START_SCREEN_ADDRES + 40 * 15 * 12 + (BOARD_ITEM1 + 4) * 2, elementsAddr[0]);

    //items
    printBGObject(START_SCREEN_ADDRES + 40 * 15 * 12 + BOARD_ITEM1 * 2, elementsAddr[ID_KEY]);
    printBGObject(START_SCREEN_ADDRES + 40 * 15 * 12 + (BOARD_ITEM1 + 1) * 2, SPRITE_X_ADDR);
    printBGObject(START_SCREEN_ADDRES + 40 * 15 * 12 + BOARD_ITEM2 * 2, elementsAddr[ID_BOMB]);
    printBGObject(START_SCREEN_ADDRES + 40 * 15 * 12 + (BOARD_ITEM2 + 1) * 2, SPRITE_X_ADDR);
}

void findElements()
{

    for (y = 0; y < MAX_LEVEL_X; ++y)
        for (x = 0; x < MAX_LEVEL_X; ++x)
        {

            switch (levelData[addr(x, y)])
            {
            case ID_PLAYER:
                playerStartX = x;
                playerStartY = y;
                currentRoomX = x / MAX_GRID_X;
                currentRoomY = y / MAX_GRID_Y;
                break;

            case ID_CHEST:
            case ID_CHEST2:
            case ID_COIN:
                treasures++;
                break;
            }
        }
}

void clearRoom()
{

    for (x = 0; x < OBJECTS_MAX; ++x)
    {
        if (objects[x].type != ID_PLAYER)
        {
            objects[x].active = 0;
        }
    }
}

void printCurrentRoom()
{
    int curElement;
    unsigned char k = 0, x1, y1;
    x = 0;
    y = 0;
    k = 0;

    clearRoom();

    for (k = 0; k <= MAX_GRID_X + MAX_GRID_Y - 2; ++k)
    {
        for (x = 0; x <= k; ++x)
        {
            y = k - x;
            if (y < MAX_GRID_Y && x < MAX_GRID_X)
            {

                if (x > MAX_GRID_X || y > MAX_GRID_Y)
                    continue;

                x1 = x + MAX_GRID_X * currentRoomX;
                y1 = y + MAX_GRID_Y * currentRoomY;

                //clear map
                collisionMap[x][y] = 0;

                curElement = (unsigned char)levelData[addr((x1), (y1))];

                printBGObjectById(x1, y1, addObjectInEngine(curElement, x1, y1));
            }
        }
    }
    updateBoard();
    key();
}

void printElement(unsigned char curElement, unsigned char x, unsigned char y)
{
    static int des, src;

    src = elementsAddr[curElement];
    des = START_SCREEN_ADDRES + x % MAX_GRID_X * 2 + multi40[(y % MAX_GRID_Y) * 12];

    printBGObject(des, src);
}

unsigned char addObjectInEngine(unsigned char objectId, unsigned char x, unsigned char y)
{
    switch (objectId)
    {
    case ID_PLAYER: //player
        levelData[addr(x, y)] = 0;
        if (!isSetPlayer)
        {
            addObject(
                ID_PLAYER,
                playerUpdate,
                x,
                y,
                SPRITE_HERORIGHT_ADDR,
                SPRITE_HERORIGHT_FRAMES,
                0);
            isSetPlayer = 1;
        }
        else
        {
            objectId = 0;
        }
        break;

    case ID_COIN:
        addObject(
            ID_STATIC,
            emptyFunc,
            x,
            y,
            SPRITE_COIN_ADDR,
            SPRITE_COIN_FRAMES,
            0);
        objectId = 0;
        break;

    case ID_TORCH:
        addObject(
            ID_STATIC,
            emptyFunc,
            x,
            y,
            SPRITE_TORCH_ADDR,
            SPRITE_TORCH_FRAMES,
            0);
        break;

    case ID_ARROW_LEFT:
        addObject(
            ID_STATIC,
            emptyFunc,
            x,
            y,
            SPRITE_ARROW_LEFT_ADDR,
            SPRITE_ARROW_FRAMES,
            0);
        objectId = 0;
        break;

    case ID_ARROW_RIGHT:
        addObject(
            ID_STATIC,
            emptyFunc,
            x,
            y,
            SPRITE_ARROW_RIGHT_ADDR,
            SPRITE_ARROW_FRAMES,
            0);
        objectId = 0;
        break;

    case ID_ARROW_UP:
        addObject(
            ID_STATIC,
            emptyFunc,
            x,
            y,
            SPRITE_ARROW_UP_ADDR,
            SPRITE_ARROW_FRAMES,
            0);
        objectId = 0;
        break;

    case ID_ARROW_DOWN:
        addObject(
            ID_STATIC,
            emptyFunc,
            x,
            y,
            SPRITE_ARROW_DOWN_ADDR,
            SPRITE_ARROW_FRAMES,
            0);
        objectId = 0;
        break;

    case ID_CANAL:
        addObject(
            ID_STATIC,
            emptyFunc,
            x,
            y + 1,
            SPRITE_CANAL_ADDR,
            SPRITE_CANAL_FRAMES,
            0);
        break;

    case ID_SPIDERLEFTRIGHT:
        addObject(
            ID_SPIDERLEFTRIGHT,
            emenyLeftRightUpdate,
            x,
            y,
            SPRITE_SPIDERLEFTRIGHT_ADDR,
            SPRITE_SPIDERLEFTRIGHT_FRAMES,
            2);
        objectId = 0;
        break;

    case ID_ROBOT:
        addObject(
            ID_ROBOT,
            emenyLeftRightUpdate,
            x,
            y,
            SPRITE_ROBOT_ADDR,
            SPRITE_ROBOT_FRAMES,
            2);
        objectId = 0;
        break;

    case ID_SNAKEMIN:
        addObject(
            ID_SNAKEMIN,
            emenyLeftRightUpdate,
            x,
            y,
            SPRITE_SNAKEMINLEFT_ADDR,
            SPRITE_SNAKEMINLEFT_FRAMES,
            0);
        objectId = 0;
        break;

    case ID_BAT:
        addObject(
            ID_BAT,
            emenyLeftRightUpdate,
            x,
            y,
            SPRITE_BATLEFT_ADDR,
            SPRITE_BATLEFT_FRAMES,
            1);
        objectId = 0;
        break;

    case ID_FIREMAN:
        addObject(
            ID_FIREMAN,
            emenyLeftRightUpdate,
            x,
            y,
            SPRITE_FIREMANLEFT_ADDR,
            SPRITE_FIREMANLEFT_FRAMES,
            2);
        objectId = 0;
        break;

    case ID_GHOST:
        addObject(
            ID_GHOST,
            emenyLeftRightUpdate,
            x,
            y,
            SPRITE_GHOSTLEFT_ADDR,
            SPRITE_GHOSTLEFT_FRAMES,
            1);
        objectId = 0;
        break;

    case ID_OOZE:
        addObject(
            ID_OOZE,
            emenyLeftRightUpdate,
            x,
            y,
            SPRITE_OOZE_ADDR,
            SPRITE_OOZE_FRAMES,
            0);
        objectId = 0;
        break;

    case ID_OOZE2:
        addObject(
            ID_OOZE2,
            emenyLeftRightUpdate,
            x,
            y,
            SPRITE_OOZE2_ADDR,
            SPRITE_OOZE2_FRAMES,
            0);
        objectId = 0;
        break;

    case ID_SKELETON:
        addObject(
            ID_SKELETON,
            emenyLeftRightUpdate,
            x,
            y,
            SPRITE_SKELETONLEFT_ADDR,
            SPRITE_SKELETONLEFT_FRAMES,
            2);
        objectId = 0;
        break;

    case ID_BROKENGRAVE:
        addObject(
            ID_SKELETON,
            emenyLeftRightUpdate,
            x,
            y,
            SPRITE_SKELETONLEFT_ADDR,
            SPRITE_SKELETONLEFT_FRAMES,
            2);
        objectId = ID_BROKENGRAVE;
        break;

    case ID_SPIDERUPDOWN:
        addObject(
            ID_SPIDERUPDOWN,
            enemyUpDownUpdate,
            x,
            y,
            SPRITE_SPIDERUPDOWN_ADDR,
            SPRITE_SPIDERUPDOWN_FRAMES,
            1);
        objectId = 0;
        break;

    case ID_ROBORAT:
        addObject(
            ID_ROBORAT,
            enemyUpDownUpdate,
            x,
            y,
            SPRITE_ROBOBAT_ADDR,
            SPRITE_ROBOBAT_FRAMES,
            0);
        objectId = 0;
        break;

    case ID_SNAKEBIG:
        addObject(
            ID_SNAKEBIG,
            emenyLeftRightUpdate,
            x,
            y,
            SPRITE_SNAKEBIGRIGHT_ADDR,
            SPRITE_SNAKEBIGRIGHT_FRAMES,
            2);
        objectId = 0;
        break;
    }

    return objectId;
}

void reverseObject(unsigned int elementAddr)
{
    unsigned int reverseElementAddr = 0;

    switch (elementAddr)
    {
    case SPRITE_SNAKEMINLEFT_ADDR:
        reverseElementAddr = SPRITE_SNAKEMINRIGHT_ADDR;
        break;
    case SPRITE_SNAKEMINRIGHT_ADDR:
        reverseElementAddr = SPRITE_SNAKEMINLEFT_ADDR;
        break;

    case SPRITE_BATLEFT_ADDR:
        reverseElementAddr = SPRITE_BATRIGHT_ADDR;
        break;
    case SPRITE_BATRIGHT_ADDR:
        reverseElementAddr = SPRITE_BATLEFT_ADDR;
        break;

    case SPRITE_FIREMANLEFT_ADDR:
        reverseElementAddr = SPRITE_FIREMANRIGHT_ADDR;
        break;
    case SPRITE_FIREMANRIGHT_ADDR:
        reverseElementAddr = SPRITE_FIREMANLEFT_ADDR;
        break;

    case SPRITE_GHOSTLEFT_ADDR:
        reverseElementAddr = SPRITE_GHOSTRIGHT_ADDR;
        break;
    case SPRITE_GHOSTRIGHT_ADDR:
        reverseElementAddr = SPRITE_GHOSTLEFT_ADDR;
        break;

    case SPRITE_SKELETONLEFT_ADDR:
        reverseElementAddr = SPRITE_SKELETONRIGHT_ADDR;
        break;
    case SPRITE_SKELETONRIGHT_ADDR:
        reverseElementAddr = SPRITE_SKELETONLEFT_ADDR;
        break;

    case SPRITE_SNAKEBIGLEFT_ADDR:
        reverseElementAddr = SPRITE_SNAKEBIGRIGHT_ADDR;
        break;
    case SPRITE_SNAKEBIGRIGHT_ADDR:
        reverseElementAddr = SPRITE_SNAKEBIGLEFT_ADDR;
        break;
    }

    if (reverseElementAddr)
    {
        objects[currentObject].spaddr = reverseElementAddr;
    }
}

void printDesigner()
{
    memset((void *)(0xbb80 + 25 * 40), '#', 118);
    memset((void *)(0xbb80 + 25 * 40 + 43), ' ', 32);

    ((unsigned int *)(0xbb80 + 38 + 25 * 40))[0] = 32 * 256 + 32;
    ((unsigned int *)(0xbb80 + 38 + 26 * 40))[0] = 32 * 256 + 32;

    ((unsigned int *)(0xbb80 + 0 + 25 * 40))[0] = 9 * 256 + 6;
    ((unsigned int *)(0xbb80 + 0 + 26 * 40))[0] = 9 * 256 + 6;
    ((unsigned int *)(0xbb80 + 0 + 27 * 40))[0] = 9 * 256 + 6;

    memcpy((void *)(0xbb8B + 25 * 40), (char *)"\010\003Level designer\006\011", 18);
    sprintf((void *)(0xbb80 + 26 * 40 + (18 - strlen(levelAuthor) / 2)), "\003\010%s\011", levelAuthor);

    ((unsigned char *)(0xbb80 + 36 + 26 * 40))[0] = 6;
    ((unsigned char *)(0xbb80 + 37 + 26 * 40))[0] = '#';

    key();
    get();
    cls();
}