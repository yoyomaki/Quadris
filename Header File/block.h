#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "cell.h"
#include "board.h"


class Board;

class Block{
    
   
      int rotationType; // this is use to determine the position of each cell in the rotationArray.
	   Cell cellArray[4]; // A block is consist of 4 cells.
	   // record the topleft corner of a 4*4 matrix. (2D array)
      char type;
      int number;
      Board *bd; // pointer to the Board. The board is an observer for each block.
   public:
 
    int getr1();
    int getc1();

    int getr2();
    int getc2();
    
    int getr3();
    int getc3();
    
    int getr4();
    int getc4();
    Cell getcell(int i);
    Block(char type, int number, Board *myboard);
     char getBlockType();
	   
	   bool canleft();
	   bool canRight();
	   bool canDown();
      void left();
      void right();
      int getRotationType();
      void Clockwise(); //rotation type + 1
      void CounterClockWise(); // rotation type -1
      void down();
      void drop();
      void draw(Xwindow *w);
      void undraw(Xwindow *w);
      friend std::ostream &operator<<(std::ostream &out, Block &block);
};

# endif
