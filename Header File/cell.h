# ifndef __CELL_H__
# define __CELL_H__
# include <iostream>
#include "window.h"

class Cell{
   char cellType; // the type of the cell, represented as capital letter. '0' represented no block here.
   int r, c; // row, column
   int blocknumber;
   int level;
   public:
      Cell();
      Cell(int r, int c, char type, int blocknum);
      void setX(int n);
      void setY(int n);
      void setType(char type);
      int getX() const;
      int getY() const;
      void incrementX();
      void incrementY();
      void decrementY();
      bool getState() ; // return true if there's an active cell.
      char getType() const;
      int getBlockNumber() const;
      void draw(Xwindow *w);
      void undraw(Xwindow *w);
      void setCell(char type, int numblock);
      Cell &operator=(const Cell& old);
      friend std::ostream &operator<<(std::ostream &out, const Cell& c);
   };
   




# endif
