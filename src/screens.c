void printStory()
{
    text();
    cls();
    poke(0x26A, CURSOR_START);

    printMenuBoard();

    printf("\n\n\n      \033C\033I= > ?\033H\033E STORY \033C\033I\x40 A B ");
    printf("\
\
\033CMy name is Bocco, or rather all my \
\033Cfriends call me that. When I was a \
\033Ckid, with the children on my street,\
\033Cwe often played treasure-hunting.\
\033COn our street, there was an old man \
\033Cwho gathered us in his porch and \
\033Ctold us stories of kinds, missing \
\033Ccivilizations and hidden treasures.\
\033CAfter years later, I realized he was\
\033Can archaelogist. On day, when he was\
\033Con his deathbed, he called me to see\
\033Cme.There was a dusty trunk on the \
\033Ctable that was full of old paper \
\033Cmaps. That was his treasure. This is\
\033Cprecious. Now all old cards are \
\033Cmine. I gathered my luggage and \
\033Cset off on the adventure.\
\
\033CI've been waiting for all my life.");

    pressAKey(1);
}

void printKeysScreen(unsigned char redefine)
{

    text();
    cls();
    poke(0x26A, CURSOR_START);

    printMenuBoard();
    printf("\n\n\n\n\n      \033C\033I= > ?\033H\033E  KEYS \033C\033I\x40 A B h\n\n");

    printf("       \033BLeft..\033C          ");
    if (redefine)
        changeKey((char*)&keyLeft);
    printf("%s\n", getKeyName(keyLeft));
    printf("       \033BRight..\033C         ");
    if (redefine)
        changeKey((char*)&keyRight);
    printf("%s\n", getKeyName(keyRight));
    printf("       \033BUp..\033C            ");
    if (redefine)
        changeKey((char*)&keyUp);
    printf("%s\n", getKeyName(keyUp));
    printf("       \033BDown..\033C          ");
    if (redefine)
        changeKey((char*)&keyDown);
    printf("%s\n", getKeyName(keyDown));
    printf("       \033BUse..\033C           ");
    if (redefine)
        changeKey((char*)&keyUse);
    printf("%s\n", getKeyName(keyUse));
    printf("       \033BBomb..\033C          ");
    if (redefine)
        changeKey((char*)&keyBomb);
    printf("%s\n", getKeyName(keyBomb));
    printf("       \033bGive up..\033C       ");
    if (redefine)
        changeKey((char*)&keyGiveUp);
    printf("%s\n", getKeyName(keyGiveUp));
    printf("       \033BColors..\033C        ");
    if (redefine)
        changeKey((char*)&keyColor);
    printf("%s\n", getKeyName(keyColor));
    printf("       \033BSounds..\033C        ");
    if (redefine)
        changeKey((char*)&keySound);
    printf("%s\n", getKeyName(keySound));
    printf("       \033BDisplay type..\033C  ");
    if (redefine)
        changeKey((char*)&keyDisplayType);
    printf("%s\n", getKeyName(keyDisplayType));
    printf("       \033BLoad level..\033C    ");
    if (redefine)
        changeKey((char*)&keyLoadLevel);
    printf("%s\n", getKeyName(keyLoadLevel));
    printf("       \033bExit..\033C          ");
    if (redefine)
        changeKey((char*)&keyExit);
    printf("%s\n", getKeyName(keyExit));

    printf("\n   \033CYour goal is to collect all\n   \033Ctreasures, and find the exit.");

    pressAKey(1);
}

void changeKey(char *key1)
{
    *key1 = get();
}

const char *getKeyName(char key1)
{
    static char out[10] = {0};
    switch (key1)
    {
    case 8:
        strcpy(out, "Left");
        break;
    case 9:
        strcpy(out, "Right");
        break;
    case 10:
        strcpy(out, "Down");
        break;
    case 11:
        strcpy(out, "Up");
        break;
    case 32:
        strcpy(out, "Space");
        break;
    case 27:
        strcpy(out, "ESC");
        break;
    case 127:
        strcpy(out, "Delete");
        break;
    case 13:
        strcpy(out, "Enter");
        break;
    default:
        sprintf(out, "%c", key1);
        break;
    }

    return out;
}

void titleScreen()
{
    int dummy;
    hires();
    poke(0x26A, CURSOR_START);
    loadfile("TITLE.BIN", (void *)0xa000, &dummy);

    sprintf((void *)(0xbb80 + 0 + 25 * 40), "\004by Rax");

    pressAKey(1);
}

void printAboutGame()
{
    text();
    cls();
    poke(0x26A, CURSOR_START);
    printMenuBoard();
    printf("\n\n\n\n\n\n   \033C\033I= > ?\033H\033E About game \033C\033I\x40 A B h\n\n\n\n");
    printf("     \033CGame code..       \033Frax\n");
    printf("     \033CTitle image..     \033Fgerimm\n");
    printf("     \033CAddtitional code..\033Fiss\n");
    printf("\n\n\n\n\n\n\n\n\n\n\n\033Dcopyright \x60 2019");
    pressAKey(1);
}

void printMenu()
{
    int dummy;
    text();
    cls();
    poke(0x26A, CURSOR_START);

    printMenuBoard();

    printTorches();

    strcpy((void *)(0xbb80 + 18 + 7 * 40), "\006\0119 9\010\005BOCCO'S \006\0119 9");
    strcpy((void *)(0xbb80 + 18 + 8 * 40), "\006\011 9\010\005Adventures\006\0119");
    strcpy((void *)(0xbb80 + 18 + 11 * 40), "\002\010 Play..        P\n\n");
    strcpy((void *)(0xbb80 + 18 + 13 * 40), "\003\010 Story..       S\n\n");
    strcpy((void *)(0xbb80 + 18 + 15 * 40), "\006\010 Instruction.. I\n\n");
    strcpy((void *)(0xbb80 + 18 + 17 * 40), "\004\010 Redefine..    R\n\n");
    strcpy((void *)(0xbb80 + 18 + 19 * 40), "\001\010 About..       A\n\n");

    pressAKey(0);
}

void pressAKey(unsigned char useKey)
{
    wait(100);
    sprintf((void *)(0xbb80 + 22 + 25 * 40), "\001\015C\014Press a key\015D");
    if (useKey == 1)
    {
        key();
        get();
    }
}

void printMenuBoard()
{

    strcpy((void *)(0xbb80 + 1 * 40), "\x09\x02::::::::::::::::::::::::::::::::::::::");
    strcpy((void *)(0xbb80 + 2 * 40), "\x09\0023-.3023232-3332123232-.323223103232.23");

    strcpy((void *)(0xbb80 + 26 * 40), "\x09\002+&,,)+,(,,+%+,*,(&',+,+,%,%&',(,+,%,+");
    strcpy((void *)(0xbb80 + 27 * 40), "\x09\x02:::::::::::::::::::::::::::::::::::::");
}

void printTorches()
{
    printf("\n\n\n\n\n\
\033I\033C #   ## H ## \
\033I\033C### #### ####\
\033I\033C############\
\033I\033C ###5 5#######\
\033I\033C ##5\033A!\033C5####\
\033I\033C  ##5 5#####\
\033I\033C#######5 5###\
\033I\033C #####5\033A!\033C5##\
\033I\033C  #####5 5##\
\033I\033C ##5 5######\
\033I\033C##5\033A!\033C5######\
\033I\033C ##5 5#######\
\033I\033C  ###### ### H\
\033I\033C## ###   ## ##\
");
}

/*

 #   ## H ##  
### #### #####
############
 ###5 5#######
 ##5 ! 5####
  ##5 5#####  
#######5 5###
 #####5 ! 5##
  #####5 5## 
 ##5 5######  
##5 ! 5###### 
 ##5 5#######
  ###### ### H
## ###   ## ## 
*/
