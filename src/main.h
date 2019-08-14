/* 
 * File:   main.h
 * Author: rax
 *
 * Created on March 4, 2019, 1:04 AM
 */

#ifndef MAIN_H
#define MAIN_H

//main
void findElements(void);
void clearRoom(void);
void printCurrentRoom(void);
void printElement(unsigned char curElement, unsigned char x, unsigned char y);
unsigned char addObjectInEngine(unsigned char objectId, unsigned char x, unsigned char y);
void reverseObject(unsigned int elementAddr);
void game(void);
void loadTitleScreen(void);
void printMenu(void);
void printGameBoard(void);
void printDesigner(void);

//engine
void executeUpdate(void);
void emptyFunc(void);
void animator(void);
void printBG(void);
void printBGObjectById(unsigned char x, unsigned char y, unsigned char elementId);
void printBGObject(int des, int src);
void printFGObject(int des, int src);
void initObjects(void);
void wait(int time);
void addObject(char type, void *func, unsigned char x, unsigned char y, int spaddr, unsigned char frames, unsigned char special);
void objectProcessing(void);
void deleteObject(unsigned char objectNumber);
void deleteAllObjects(unsigned char objectType);
void engine(void);
void monitor(void);
void deleteObjectsByPosition(unsigned char x, unsigned char y);

//common
void end(void);
void init(void);
void loadLevel(char *levelName);
void setColors(void);
void load(void);
void input(char *string, unsigned char len);

// objects
void bombUpdate(void);
void clearNeighbors(void);
void clearPos(unsigned char x, unsigned char y);

void emenyLeftRightUpdate(void);

void explosionUpdate(void);

void playerUpdate(void);
void changeElements(unsigned char src, unsigned char des);
void useBomb(void);
void updateBoard(void);
void openDoor(void);
void useHandle(unsigned char bgElement);
void updateElementOnTheScreen(void);
void help(void);

void enemyUpDownUpdate(void);

//story
void printStory(void);
void printKeysScreen(unsigned char reconfig);
const char *getKeyName(char key1);
void pressAKey(unsigned char useKey);
void changeKey(unsigned char *key1);
void printMenuBoard(void);
void printTorches(void);

#endif /* MAIN_H */
