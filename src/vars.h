/*
screen 240x200 / 12 = 20 x 16.6

screen  18 x 14 = 252 bytes

rooms 3x3 = 9

level 9 x 252 = 2268 / #8dc bytes

#6f00 - #77db level (rooms data)
#77dc - #77FF author name 35 bytes

#7800 - #9800 tileset 

#9800 - #9FFF chars

#A000 - #BFDF hires

game - #503-#6eff (69ff - 27,135 bytes)

 */

#ifndef VARS_H
#define VARS_H

#define MAX_ROOMS_X 2 //(3 elements 0,1,2)
#define MAX_ROOMS_Y 2 //(3 elements 0,1,2)

#define MAX_GRID_X 18 //(18 elements 0-17)
#define MAX_GRID_Y 14 //(14 elements 0-13)

#define MAX_LEVEL_X (MAX_GRID_X * (MAX_ROOMS_X + 1))
#define MAX_LEVEL_Y (MAX_GRID_Y * (MAX_ROOMS_Y + 1))

#define COLOR1 6
#define COLOR2 3

#define TILESET_ADDRESS 0x7800

//#define SPRITE_xxxxx_ADDR TILESET_ADDRESSS+(12*12*40)+21,
//#define SPRITE_xxxxx_WIDTH 2
//#define SPRITE_xxxxx_HEIGHT 14
//#define SPRITE_xxxxx_FRAMES X
//#define SPRITE_xxxxx_STATE 0

#define SPRITE_WIDTH 2
#define SPRITE_HEIGHT 12
#define SPRITE_STATE_DEFAULT 0

#define SPRITE_COIN_ADDR TILESET_ADDRESS + (9 * 12 * 40) + 0 * 2 + 1
#define SPRITE_COIN_FRAMES 6

//(?2key)

#define SPRITE_EXPLOSION_ADDR TILESET_ADDRESS + (9 * 12 * 40) + 6 * 2 + 1
#define SPRITE_EXPLOSION_FRAMES 3

#define SPRITE_SNAKEMINLEFT_ADDR TILESET_ADDRESS + (9 * 12 * 40) + 9 * 2 + 1
#define SPRITE_SNAKEMINLEFT_FRAMES 2

#define SPRITE_SNAKEMINRIGHT_ADDR TILESET_ADDRESS + (9 * 12 * 40) + 11 * 2 + 1
#define SPRITE_SNAKEMINRIGHT_FRAMES 2

#define SPRITE_SPIDERLEFTRIGHT_ADDR TILESET_ADDRESS + (9 * 12 * 40) + 13 * 2 + 1
#define SPRITE_SPIDERLEFTRIGHT_FRAMES 4

#define SPRITE_FIREMANLEFT_ADDR TILESET_ADDRESS + (10 * 12 * 40) + 0 * 2 + 1
#define SPRITE_FIREMANLEFT_FRAMES 4

#define SPRITE_FIREMANRIGHT_ADDR TILESET_ADDRESS + (10 * 12 * 40) + 4 * 2 + 1
#define SPRITE_FIREMANRIGHT_FRAMES 4

#define SPRITE_BATLEFT_ADDR TILESET_ADDRESS + (10 * 12 * 40) + 8 * 2 + 1
#define SPRITE_BATLEFT_FRAMES 2

#define SPRITE_BATRIGHT_ADDR TILESET_ADDRESS + (10 * 12 * 40) + 10 * 2 + 1
#define SPRITE_BATRIGHT_FRAMES 2

#define SPRITE_SPIDERUPDOWN_ADDR TILESET_ADDRESS + (10 * 12 * 40) + 12 * 2 + 1
#define SPRITE_SPIDERUPDOWN_FRAMES 2

#define SPRITE_CANAL_ADDR TILESET_ADDRESS + (10 * 12 * 40) + 16 * 2 + 1
#define SPRITE_CANAL_FRAMES 3

#define SPRITE_ARROW_LEFT_ADDR TILESET_ADDRESS + (11 * 12 * 40) + 6 * 2 + 1
#define SPRITE_ARROW_RIGHT_ADDR TILESET_ADDRESS + (11 * 12 * 40) + 4 * 2 + 1
#define SPRITE_ARROW_UP_ADDR TILESET_ADDRESS + (11 * 12 * 40) + 0 * 2 + 1
#define SPRITE_ARROW_DOWN_ADDR TILESET_ADDRESS + (11 * 12 * 40) + 2 * 2 + 1
#define SPRITE_ARROW_FRAMES 2

#define SPRITE_ROBOT_ADDR TILESET_ADDRESS + (11 * 12 * 40) + 8 * 2 + 1
#define SPRITE_ROBOT_FRAMES 4

#define SPRITE_ROBOBAT_ADDR TILESET_ADDRESS + (11 * 12 * 40) + 12 * 2 + 1
#define SPRITE_ROBOBAT_FRAMES 4

#define SPRITE_GHOSTLEFT_ADDR TILESET_ADDRESS + (12 * 12 * 40) + 12 * 2 + 1
#define SPRITE_GHOSTLEFT_FRAMES 2

#define SPRITE_GHOSTRIGHT_ADDR TILESET_ADDRESS + (12 * 12 * 40) + 14 * 2 + 1
#define SPRITE_GHOSTRIGHT_FRAMES 2

#define SPRITE_TORCH_ADDR TILESET_ADDRESS + (12 * 12 * 40) + 0 * 2 + 1
#define SPRITE_TORCH_FRAMES 3

#define SPRITE_OOZE_ADDR TILESET_ADDRESS + (12 * 12 * 40) + 5 * 2 + 1
#define SPRITE_OOZE_FRAMES 4

#define SPRITE_OOZE2_ADDR TILESET_ADDRESS + (12 * 12 * 40) + 3 * 2 + 1
#define SPRITE_OOZE2_FRAMES 2

////#define SPRITE_BULLETLEFT_ADDR TILESET_ADDRESS+(y*12*40)+x*2+1
////#define SPRITE_BULLETLEFT_FRAMES 2

////#define SPRITE_BULLETRIGHT_ADDR TILESET_ADDRESS+(y*12*40)+x*2+1
////#define SPRITE_BULLETRIGHT_FRAMES 2

//(?3fire)

//(?2robobat)

#define SPRITE_SNAKEBIGLEFT_ADDR TILESET_ADDRESS + (13 * 12 * 40) + 2 * 2 + 1
#define SPRITE_SNAKEBIGLEFT_FRAMES 2

#define SPRITE_SNAKEBIGRIGHT_ADDR TILESET_ADDRESS + (13 * 12 * 40) + 0 * 2 + 1
#define SPRITE_SNAKEBIGRIGHT_FRAMES 2

//#define SPRITE_SNAKEBIGUPDOWN_ADDR TILESET_ADDRESS+(13*12*40)+4*2+1
//#define SPRITE_SNAKEBIGUPDOWN_FRAMES 2

#define SPRITE_HEROLEFT_ADDR TILESET_ADDRESS + (13 * 12 * 40) + 10 * 2 + 1
#define SPRITE_HEROLEFT_FRAMES 4

#define SPRITE_HEROIDLERIGHT_ADDR TILESET_ADDRESS + (14 * 12 * 40) + 16 * 2 + 1
#define SPRITE_HEROIDLERIGHT_FRAMES 2

#define SPRITE_HEROIDLELEFT_ADDR TILESET_ADDRESS + (9 * 12 * 40) + 17 * 2 + 1
#define SPRITE_HEROIDLELEFT_FRAMES 2

#define SPRITE_HERORIGHT_ADDR TILESET_ADDRESS + (13 * 12 * 40) + 6 * 2 + 1
#define SPRITE_HERORIGHT_FRAMES 4

#define SPRITE_HEROUPDOWN_ADDR TILESET_ADDRESS + (13 * 12 * 40) + 14 * 2 + 1
#define SPRITE_HEROUPDOWN_FRAMES 4

#define SPRITE_SKELETONLEFT_ADDR TILESET_ADDRESS + (14 * 12 * 40) + 0 * 2 + 1
#define SPRITE_SKELETONLEFT_FRAMES 3

#define SPRITE_SKELETONRIGHT_ADDR TILESET_ADDRESS + (14 * 12 * 40) + 3 * 2 + 1
#define SPRITE_SKELETONRIGHT_FRAMES 3

#define SPRITE_BOMB_ADDR TILESET_ADDRESS + (14 * 12 * 40) + 6 * 2 + 1
#define SPRITE_BOMB_FRAMES 6

#define SPRITE_NUMBERS_ADDR TILESET_ADDRESS + (15 * 12 * 40) + 1 * 2 + 1
#define SPRITE_X_ADDR TILESET_ADDRESS + (15 * 12 * 40) + 0 * 2 + 1

//#define SPRITE_WIZARDLEFT_ADDR TILESET_ADDRESS+(14*12*40)+12*2+1
//#define SPRITE_WIZARDLEFT_FRAMES 2

//#define SPRITE_WIZARDRIGHT_ADDR TILESET_ADDRESS+(14*12*40)+14*2+1
//#define SPRITE_WIZARDRIGHT_FRAMES 2

//OBJECTS ID

#define ID_SPACE 0
#define ID_PLAYER 158
#define ID_LADDER 146
#define ID_COIN 142
#define ID_ARROW_LEFT 157
#define ID_ARROW_RIGHT 156
#define ID_ARROW_UP 154
#define ID_ARROW_DOWN 155
#define ID_CANAL 144

#define ID_SPIDERLEFTRIGHT 169
#define ID_ROBOT 174
#define ID_SNAKEMIN 170
#define ID_BAT 171     // 10x8 10x10
#define ID_FIREMAN 173 // 10x0 10x4
#define ID_ROBORAT 172
#define ID_GHOST 175
#define ID_OOZE 177
#define ID_OOZE2 176
#define ID_SNAKEBIG 178
#define ID_SPIDERUPDOWN 168
#define ID_SKELETON 166
//#define ID_WIZARD 167
#define ID_BOMBACTIVATED 148
#define ID_BOMB 143
#define ID_EXPLOSION 186

#define ID_SPIDERWEB 62

#define ID_SWITCHON 150
#define ID_SWITCHOFF 153
#define ID_BRICK 36
#define ID_HOLE 145

#define ID_KEY 147
#define ID_CHEST 148
#define ID_CHEST2 149

#define ID_CLOSEDDOOR 37
#define ID_OPENDOOR 151

#define ID_DYNAMIC 1
#define ID_STATIC 2

#define ID_EXITCLOSED 138
#define ID_EXITOPEN 137

#define ID_TORCH 152

#define ID_BROKENGRAVE 140
#define ID_GRAVE 141

#define ID_INVISIBLEBRICK 38

#define BOARD_ITEM1 3
#define BOARD_ITEM2 11

//###################

#define START_SCREEN_ADDRES 0xA002 + (0 * 40)

//###################

unsigned char x, y;

static int i;

static int src, des;

static unsigned char *levelData;
static char *levelAuthor;

static unsigned char collisionMap[MAX_GRID_X][MAX_GRID_Y];
static unsigned char collisionMapHalfX[MAX_GRID_X][MAX_GRID_Y];

static unsigned char currentRoomX = 0;
static unsigned char currentRoomY = 0;

static unsigned int bgElementAddress;

static unsigned char level = 0;
unsigned char maxLevel = 10;
char *copyright = "rax@Sofia2019";

// KEYS
static char keyUp = 11;
static char keyDown = 10;
static char keyLeft = 8;
static char keyRight = 9;
static char keyUse = ' ';
static char keyBomb = 'B';
static char keyColor = 'C';
static char keyGiveUp = 'G';
static char keyLoadLevel = '0';
static char keyDisplayType = 'T';
static char keyExit = '!';
static char keySound = 'S';

#endif /* VARS_H */
