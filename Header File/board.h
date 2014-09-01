#ifndef __BOARD_H__
#define __BOARD_H__
#include "cell.h"
#include "block.h"
#include <iostream>
#include <fstream>
#include "window.h"
#include <vector>


class Block;

class Board{
    static bool seeded;
    static int HighScore;
    
    Cell **theboard;// 18 * 10
    bool gameStart;
    int level;
    int score;
    int seed;
    int numblock;
    std::ifstream ff;
    std::vector<int> vlevel;
    std::vector<bool> vcleared;
    
    Block *currentBlock;
    Block *nextBlock;
    Xwindow* window;
    
    public:
       ~Board();
       Board(bool OnlyText = false, int seed = 10, std::string file = "sequence.txt", int startlevel = 0);
       Block* genNextBlock();
       //determine whether nth row is a full row
       bool isFullRow(int n);
       //clear a full row and drop down all rows above it
       void clearRow(int n);
       //determine whether I win
       bool isWon();
       //determine whether I lose
       bool isLost();
       //
       Block *returnNextBlock();
       //
       void SetLevel(int n);
       //   
       int getlevel ();
       void clearCell(int r, int c);
       void setCell(int r, int c, char type, int numblock);
       bool getState(int r, int c);
       friend std::ostream &operator<<(std::ostream &out, const Board &bd);
       void scoreplus(int n);
       void left();
       void right();
       void down();
       void clockwise();
       void counterclockwise();
       void drop();
       void levelup();
       void leveldown();
       void restart();
        
       char getType(int r, int c);
       bool iscleared(int i);
       std::vector<bool> getvcleared();
       int getvlevel(int i);
       void setvcleared(int i,bool result);
  
  void clearwindow();
};
# endif
