#include "vars.h"

#define OBJECTS_MAX 20

#define STATE_CLEAR 0
#define STATE_RUNNING 1
#define STATE_GAMEOVER 2
#define STATE_NEXTLEVEL 3
#define STATE_END 4

#define TRUE 1
#define FALSE 0

#define OBJECT_RND_STATE (rand() % 4)

static struct objectStruct
{
    unsigned char type;
    unsigned char active;
    unsigned char x;
    unsigned char y;

    unsigned char oldx;
    unsigned char oldy;

    unsigned char mapx;
    unsigned char mapy;

    unsigned char halfx;
    unsigned char halfy;

    char direction;
    unsigned char special;
    unsigned char counter;

    unsigned int spaddr;
    unsigned char width;
    unsigned char height;
    unsigned char frames;
    unsigned char state;

    void (*func)();
};

static char key1;
static unsigned char monitorEnable = 0;
static unsigned char objectsCount;
static unsigned char engineState = 0;
static unsigned char currentObject;
static unsigned char newObject;
static unsigned char systemMinLoad = 10;
static unsigned char counter;
static unsigned char bgAndObjectsType = 1;

static struct objectStruct objects[OBJECTS_MAX];

static int multi40[200] = {0, 40, 80, 120, 160, 200, 240, 280, 320, 360, 400, 440, 480, 520, 560, 600, 640, 680, 720, 760, 800, 840, 880, 920, 960, 1000, 1040, 1080, 1120, 1160, 1200, 1240, 1280, 1320, 1360, 1400, 1440, 1480, 1520, 1560, 1600, 1640, 1680, 1720, 1760, 1800, 1840, 1880, 1920, 1960, 2000, 2040, 2080, 2120, 2160, 2200, 2240, 2280, 2320, 2360, 2400, 2440, 2480, 2520, 2560, 2600, 2640, 2680, 2720, 2760, 2800, 2840, 2880, 2920, 2960, 3000, 3040, 3080, 3120, 3160, 3200, 3240, 3280, 3320, 3360, 3400, 3440, 3480, 3520, 3560, 3600, 3640, 3680, 3720, 3760, 3800, 3840, 3880, 3920, 3960, 4000, 4040, 4080, 4120, 4160, 4200, 4240, 4280, 4320, 4360, 4400, 4440, 4480, 4520, 4560, 4600, 4640, 4680, 4720, 4760, 4800, 4840, 4880, 4920, 4960, 5000, 5040, 5080, 5120, 5160, 5200, 5240, 5280, 5320, 5360, 5400, 5440, 5480, 5520, 5560, 5600, 5640, 5680, 5720, 5760, 5800, 5840, 5880, 5920, 5960, 6000, 6040, 6080, 6120, 6160, 6200, 6240, 6280, 6320, 6360, 6400, 6440, 6480, 6520, 6560, 6600, 6640, 6680, 6720, 6760, 6800, 6840, 6880, 6920, 6960, 7000, 7040, 7080, 7120, 7160, 7200, 7240, 7280, 7320, 7360, 7400, 7440, 7480, 7520, 7560, 7600, 7640, 7680, 7720, 7760, 7800, 7840, 7880, 7920, 7960};
static int elementsAddr[180] = {30721U, 30723U, 30725U, 30727U, 30729U, 30731U, 30733U, 30735U, 30737U, 30739U, 30741U, 30743U, 30745U, 30747U, 30749U, 30751U, 30753U, 30755U, 30757U, 30759U, 31201U, 31203U, 31205U, 31207U, 31209U, 31211U, 31213U, 31215U, 31217U, 31219U, 31221U, 31223U, 31225U, 31227U, 31229U, 31231U, 31233U, 31235U, 31237U, 31239U, 31681U, 31683U, 31685U, 31687U, 31689U, 31691U, 31693U, 31695U, 31697U, 31699U, 31701U, 31703U, 31705U, 31707U, 31709U, 31711U, 31713U, 31715U, 31717U, 31719U, 32161U, 32163U, 32165U, 32167U, 32169U, 32171U, 32173U, 32175U, 32177U, 32179U, 32181U, 32183U, 32185U, 32187U, 32189U, 32191U, 32193U, 32195U, 32197U, 32199U, 32641U, 32643U, 32645U, 32647U, 32649U, 32651U, 32653U, 32655U, 32657U, 32659U, 32661U, 32663U, 32665U, 32667U, 32669U, 32671U, 32673U, 32675U, 32677U, 32679U, 33121U, 33123U, 33125U, 33127U, 33129U, 33131U, 33133U, 33135U, 33137U, 33139U, 33141U, 33143U, 33145U, 33147U, 33149U, 33151U, 33153U, 33155U, 33157U, 33159U, 33601U, 33603U, 33605U, 33607U, 33609U, 33611U, 33613U, 33615U, 33617U, 33619U, 33621U, 33623U, 33625U, 33627U, 33629U, 33631U, 33633U, 33635U, 33637U, 33639U, 34081U, 34083U, 34085U, 34087U, 34089U, 34091U, 34093U, 34095U, 34097U, 34099U, 34101U, 34103U, 34105U, 34107U, 34109U, 34111U, 34113U, 34115U, 34117U, 34119U, 34561U, 34563U, 34565U, 34567U, 34569U, 34571U, 34573U, 34575U, 34577U, 34579U, 34581U, 34583U, 34585U, 34587U, 34589U, 34591U, 34593U, 34595U, 34597U, 34599U};

void emptyFunc()
{
    if (objects[currentObject].counter == 0)
    {
        animator();
        objects[currentObject].counter = 2;
    }
    objects[currentObject].counter--;
    return;
}

void animator()
{

    unsigned char curElement, halfY, oldxRoom, oldyRoom, type;
    int x, y, oldx, oldy;

    x = objects[currentObject].x % MAX_GRID_X;
    y = objects[currentObject].y % MAX_GRID_Y;
    oldx = objects[currentObject].oldx;
    oldy = objects[currentObject].oldy;
    oldxRoom = objects[currentObject].oldx % MAX_GRID_X;
    oldyRoom = objects[currentObject].oldy % MAX_GRID_Y;

    type = objects[currentObject].type;

    // reset state
    if (objects[currentObject].state == 0 || objects[currentObject].state > objects[currentObject].frames)
    {
        objects[currentObject].state = objects[currentObject].frames;
    }

    // next state
    objects[currentObject].state--;

    if (type != ID_STATIC)
    {
        des = START_SCREEN_ADDRES + (oldxRoom)*2 + multi40[((oldyRoom)*12)];
        curElement = (unsigned char)levelData[addr(oldx, oldy)];

        //skip enemies and traps
        if (curElement > 160)
            curElement = 0;

        src = elementsAddr[curElement];
        printBGObject(des, src);

        if (objects[currentObject].halfx == 0 || y != oldy || type == ID_PLAYER && x == oldx)
        {
            if (oldxRoom != MAX_GRID_X - 1)
            {
                des = START_SCREEN_ADDRES + (oldxRoom)*2 + 2 + multi40[((oldyRoom)*12)];
                curElement = (unsigned char)levelData[addr(oldx + 1, oldy)];
                if (curElement > 160)
                    curElement = 0;
                src = elementsAddr[curElement];
                printBGObject(des, src);
            }
        }
    }

    des = START_SCREEN_ADDRES + x * 2 + multi40[(y)*12] + objects[currentObject].halfx;
    src = (objects[currentObject].spaddr + (objects[currentObject].state * 2));

    if (bgAndObjectsType && type != ID_STATIC)
    {
        printFGObject(des, src);
    }
    else
    {
        printBGObject(des, src);
    }
}

void printBG()
{
    x = objects[currentObject].x;
    y = objects[currentObject].y;

    src = elementsAddr[(unsigned char)levelData[addr(x, y)]];
    des = START_SCREEN_ADDRES + x % MAX_GRID_X * 2 + multi40[(y % MAX_GRID_Y) * 12];

    printBGObject(des, src);
}

void printBGObjectById(unsigned char x, unsigned char y, unsigned char elementId)
{
    des = START_SCREEN_ADDRES + (x % MAX_GRID_X) * 2 + multi40[((y % MAX_GRID_Y) * 12)];
    src = elementsAddr[elementId];
    printBGObject(des, src);
}

void printBGObject(int des, int src)
{
    int desTmp;
    int srcTmp;
    unsigned char h;

    for (h = 0; h < 12; ++h)
    {
        desTmp = des + multi40[h];
        srcTmp = src + multi40[h];

        poke(desTmp, peek(srcTmp));
        poke(desTmp + 1, peek(1 + srcTmp));
    }
}

void printFGObject(int des, int src)
{
    int desTmp;
    int srcTmp;

    unsigned char h;

    for (h = 0; h < 12; ++h)
    {
        desTmp = des + multi40[h];
        srcTmp = src + multi40[h];

        // if (peek(srcTmp))
        {
            // XOR
            // 	   tmp = peek(des + multi40[h]) & 192;
            //	   poke (desTmp,(peek(desTmp) ^ peek(srcTmp)) | tmp);
            //	   tmp = peek(des + multi40[h]+1) & 192;
            //	   poke (desTmp+1,(peek(1+desTmp) ^ peek(1+srcTmp) | tmp));

            // OR
            /* 		   if (srcTmp+1 & 15!=0)//%001111
                                       poke (srcTmp+1,((peek(1+desTmp)& 192+15) | peek(1+srcTmp)) );
                               else
                                            if(srcTmp+1 & 3!=0)//%000011
                                                    poke (desTmp+1,((peek(1+desTmp)& 192+3) | peek(1+srcTmp)) );
                                            else
                                                    poke (desTmp+1,(peek(1+desTmp) | peek(1+srcTmp)) );
				
				
                               if (srcTmp & 60+192 !=0)//%111100
                                       poke (desTmp,((peek(desTmp)& 192+60) | peek(srcTmp)) );
                               else
                                            if(srcTmp & 192+48!=0)//%110000
                                                    poke (desTmp,((peek(desTmp)& 192+48) | peek(srcTmp)) );
                                            else
                                                    poke (desTmp,(peek(desTmp) | peek(srcTmp)) );
             */

            poke(desTmp, (peek(desTmp) | peek(srcTmp)));
            poke(desTmp + 1, (peek(1 + desTmp) | peek(1 + srcTmp)));
        }
    }
}

void initObjects()
{
    unsigned char i;
    for (i = 0; i < OBJECTS_MAX; ++i)
        objects[i].active = 0;
    memset(collisionMap, 255, MAX_GRID_X * MAX_GRID_Y);
}

void wait(int time)
{
    int now;
    if (time < 0)
        return;
    now = deek(0x276);
    while (now - deek(0x276) < time)
    {
        ;
    }
}

void addObject(
    char type,
    void *func,
    unsigned char x,
    unsigned char y,
    int spaddr,
    unsigned char frames,
    unsigned char special

)
{
    unsigned char i;
    for (i = 0; i < OBJECTS_MAX; i++)
    {
        if (!objects[i].active)
        {
            objects[i].active = 1;
            objects[i].type = type;
            objects[i].x = x;
            objects[i].y = y;
            objects[i].oldx = x;
            objects[i].oldy = y;
            objects[i].halfx = 0;
            objects[i].halfy = 0;
            objects[i].direction = 0;
            objects[i].special = special;
            objects[i].counter = OBJECT_RND_STATE;
            objects[i].spaddr = spaddr;
            objects[i].frames = frames;
            objects[i].state = rand() % frames;
            objects[i].func = func;

            newObject = i;

            return;
        }
    }
}

void objectProcessing()
{
    unsigned char i;
    objectsCount = 0;
    for (i = 0; i < OBJECTS_MAX; ++i)
    {
        switch (objects[i].active)
        {
        case 1:
            currentObject = i;
            ++objectsCount;
            objects[i].func();
            break;
        }
    }
}

void deleteObject(unsigned char objectNumber)
{
    objects[objectNumber].active = 0;
}

void deleteAllObjects(unsigned char objectType)
{
    unsigned char i;
    for (i = 0; i < OBJECTS_MAX; ++i)
        if (1 == objects[i].active && objectType == objects[i].type)
        {
            objects[i].active = 0;
        }
}

void deleteObjectsByPosition(unsigned char x, unsigned char y)
{
    unsigned char i;
    for (i = 0; i < OBJECTS_MAX; ++i)
    {
        if (objects[i].x == x && objects[i].y == y && objects[i].type != ID_PLAYER && objects[i].type != ID_EXPLOSION)
        {
            objects[i].active = 0;
            //collisionMap[objects[i].x][objects[i].y] = 0;
        }
    }
}

void engine()
{
    engineState = STATE_RUNNING;
    while (engineState == STATE_RUNNING)
    {
        key1 = key();
        objectProcessing();
        monitor();
        ++counter;
        if (key1 == keyExit)
            engineState = STATE_END;
    }
}

void monitor()
{
    unsigned int load = 0xffff - deek(0x276);

    wait(systemMinLoad - load);
    load = 0xffff - deek(0x276);
    doke(0x276, 0);

    // if (key1 == '@')
    //     monitorEnable = 1 - monitorEnable;
    // if (monitorEnable == 1)
    // {
    //     sprintf((void *)(0xbf90 + 20), " load:%d obj:%d  ", load, objectsCount);
    // }
}

#define CHARSET_ADDR 0x9800

// void hiresText(unsigned char x, unsigned char y, char *text)
// {
//     unsigned int addr = 0xa000 + x + multi40[y];
//     unsigned char i, l;

//     for (l = 0; l < strlen(text); ++l)
//     {
//         for (i = 0; i < 8; ++i)
//         {
//             poke(addr + l + i * 40, (peek(CHARSET_ADDR + text[l] * 8 + i) | 64));
//         }
//     }
// }

void hiresTextDouble(unsigned char x, unsigned char y, char *text)
{
    unsigned int addr = 0xa000 + x + multi40[y];
    unsigned char i, l;

    for (l = 0; l < strlen(text); ++l)
        for (i = 0; i < 8; ++i)
        {
            poke(addr + l + i * 40 * 2, (peek(CHARSET_ADDR + text[l] * 8 + i) | 64));
            poke(addr + l + i * 40 * 2 + 40, (peek(CHARSET_ADDR + text[l] * 8 + i) | 64));
        }
}
