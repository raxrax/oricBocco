#include <compat.h>
#include <libsedoric.h>
#include <libgraphics.h>

//#define START_SCREEN_ADDRES  0xA001 + (0 * 40)

#include "main_editor.h"

#include "vars.h"
#include "common.c"
#include "engine.c"

#define MAX_ELEMENTS 178

// tileset address
#define taddr(x, y) x + ((currentRoomX)*MAX_GRID_X) + y *MAX_LEVEL_X + ((currentRoomY)*MAX_LEVEL_X * MAX_GRID_Y)

unsigned char element = 1;

static char key1;

void main()
{
    init();
    bgElementAddress = 0;
    fillScreen();
    setColors();
    clearLevel();
    printRoom();

    editor();
    end();
}

void editor(void)
{
    board();
    while (key1 != '!')
    {

        key1 = get();
        blink(0);
        keys();

        board();
        blink(1);
    }
}

void keys(void)
{

    switch (key1)
    {
    case 8:
        if (x > 0)
            x--;
        break;
    case 9:
        if (x < MAX_GRID_X - 1)
            x++;
        break;
    case 11:
        if (y > 0)
            y--;
        break;
    case 10:
        if (y < MAX_GRID_Y - 1)
            y++;
        break;
    case '.':
        if (element < MAX_ELEMENTS)
            element++;
        break;
    case ',':
        if (element > 0)
            element--;
        break;
    case ' ':
        levelData[taddr(x, y)] = element;
        break;
    case 127:
        levelData[taddr(x, y)] = 0;
        break;
    case 'C':
        element = levelData[taddr(x, y)];
        break;

    case 'J':
        if (currentRoomX > 0)
        {
            currentRoomX--;
            printRoom();
        }
        break;

    case 'K':
        if (currentRoomX < MAX_ROOMS_X)
        {
            currentRoomX++;
            printRoom();
        }
        break;

    case 'I':
        if (currentRoomY > 0)
        {
            currentRoomY--;
            printRoom();
        }
        break;

    case 'M':
        if (currentRoomY < MAX_ROOMS_Y)
        {
            currentRoomY++;
            printRoom();
        }
        break;

    case 'S':
        save();
        break;

    case 'L':
        load();
        currentRoomX = 0;
        currentRoomY = 0;
        printRoom();
        break;

    case '?':
        help();
        fillScreen();
        setColors();
        printRoom();
        break;
    }
}

void board(void)
{
    cls();
    printf("pos :%dx%d  el:%d bgEl:%d   ?-Help\n", x, y, element, levelData[taddr(x, y)]);
    printf("room:%dx%d     \n", currentRoomX, currentRoomY);
}

void blink(unsigned char isElement)
{
    int des, src, offset, curElement;
    static unsigned char update;
    update++;

    if (isElement)
    {
        curElement = element;
    }
    else
    {
        curElement = (unsigned char)levelData[taddr(x, y)];
    }

    offset = curElement / 20;

    {
        des = START_SCREEN_ADDRES + (x * 2) + (y * 40 * 12);

        src = 1 + TILESET_ADDRESS + curElement * 2 + offset * 40 * 11;
        printBGObject(des, src);
    }
}

void printRoom(void)
{
    cls();

    printf("Please wait...");

    for (y = 0; y < MAX_GRID_Y; y++)
    {
        for (x = 0; x < MAX_GRID_X; x++)
        {
            blink(0);
        }
    }

    x = 0;
    y = 0;
}

void save(void)
{
    char s1[60];
    char filename[35];
    cls();

    //author
    printf("Author (30 chars): ");
    input(filename, 30);
    strcpy(levelAuthor, filename);

    cls();

    //save
    printf("Save level: ");
    input(filename, 20);
    //sprintf(s1, "SAVEO \"%s.COM\",A#6F00,E#77FF,N", filename);
    sprintf(s1, "%s.BIN", filename);

    if (!strlen(filename))
        return;

    cls();
    printf("%s", s1);
    //bang(s1);
    savefile(s1, (void *)0x6F00, 0x7800 - 0x6F00);
}

void help(void)
{
    text();
    printf("HELP\n\n\n");
    printf("ARROWS - Move cursor\n\n");
    printf("< > - Change element\n\n");
    printf("I J K M - Change room\n\n");
    printf("SPACE - Put element\n\n");
    printf("DEL - Delete element\n\n");
    printf("C - Copy element\n\n");
    printf("S - Save level\n\n");
    printf("L - Load level\n\n");

    get();
    hires();
}

void fillScreen(void)
{
    // for (i = 0xa000; i < 0xbfdf - 120; i++) {
    //     poke(i, 63);
    // }
}

void clearLevel(void)
{
    memset(levelData, 0, MAX_LEVEL_X * MAX_LEVEL_Y);
}
