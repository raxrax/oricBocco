#include <libsedoric.h>

#define CURSOR_START 10 // #26a,10
#define CURSOR_END 3    // #26a,3

#define addr(x, y) ((x) + ((y)*MAX_LEVEL_X))

static unsigned char isColored = 1;

char currentLevelName[25];

void end()
{
    text();
    cls();
    poke(0x26a, CURSOR_END);
}

void init()
{
    int dummy;

    cls();
    paper(0);
    ink(7);
    poke(0x26A, CURSOR_START);

#ifndef USE_TAPE
    hires();
    loadfile("FONT1.BIN", (void *)0x9800, &dummy);
    loadfile("TILESETC.BIN", (void *)0x7800, &dummy);
    loadfile("LORES.BIN", (void *)0x9D00, &dummy);
#endif

    poke(0x26A, CURSOR_START);

    levelData = (void *)0x6f00;
    levelAuthor = (void *)0x77dc;
}

void loadLevel(char *levelName)
{
    int dummy;
    char s1[70];
    memset(s1, 0, 70);
    sprintf(s1, "%s.BIN", levelName);

#ifndef USE_TAPE
    loadfile(s1, (void *)0x6F00, &dummy);
#endif
}

void setColors()
{
    unsigned char color1;
    unsigned char color2;

    if (isColored)
    {
        color1 = COLOR1;
        color2 = COLOR2;
    }
    else
    {
        color1 = 7;
        color2 = 7;
    }

    //for (i = 0; i < MAX_GRID_Y * 12; i += 2) {
    for (i = 0; i < 199; i += 2)
    {
        poke(START_SCREEN_ADDRES - 1 + i * 40, color1);
        poke(START_SCREEN_ADDRES - 1 + 40 + i * 40, color2);
    }
}

void load(void)
{
    int dummy;

    cls();

    //file
    printf("\033CLoad level: ");
    input(currentLevelName, 20);

    if (!strlen(currentLevelName))
        return;

    loadLevel(currentLevelName);
}

void input(char *string, unsigned char len)
{
    unsigned char index;
    char key1;
    index = 0;

    while (key1 != 13)
    {
        key1 = get();
        if (key1 == 20)
        {
            printf("%c", key1);
            continue;
        }
        if (key1 == 127 && index > 0)
        {
            printf("%c", key1);
            index--;
            continue;
        }
        if (key1 == 127)
            continue;
        if (key1 < 32 && key1 > 127)
            continue;
        if (index >= len)
            continue;
        printf("%c", key1);
        string[index] = key1;
        index++;
    }
    index--;
    string[index] = 0;
}
