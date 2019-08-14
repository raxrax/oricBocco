#ifndef __MAIN_EDITOR_H__
#define __MAIN_EDITOR_H__

void animator(void);
void printBGObject(int des, int src);
void printFGObject(int des, int src);
void engine(void);
void monitor(void);


void printRoom(void);
void fillScreen(void);
void clearLevel(void);
void help(void);
void load(void);
void save(void);
void blink(unsigned char isElement);
void board(void);
void keys(void);
void editor(void);
void input(char *string, unsigned char len);

#endif /* __MAIN_EDITOR_H__ */

