# include <iostream>
# include "cell.h"
using namespace std;

Cell &Cell::operator=(const Cell& old){
   cellType = old.cellType;
   r = old.r;
   c = old.c;
   blocknumber = old.blocknumber;
   return *this;
}

int Cell::getBlockNumber() const{
  return blocknumber;
}

Cell::Cell(){
    r = 0;
    c = 0;
    cellType = 32;
    blocknumber = 0;
}

Cell::Cell(int r, int c, char type, int blocknumber):r(r),c(c),cellType(type), blocknumber(blocknumber){}




int Cell::getX() const{
   return r;
   }
int Cell::getY() const{
   return c;
   }

void Cell::setX(int n){
   r = n;
   }

void Cell::setY(int n){
   c = n;
   }
   

   
bool Cell::getState(){
   if (cellType == 32){
      return false;
      }
   return true;
   }
   
char Cell::getType() const{
   return cellType;
   }


   
void Cell::setCell(char type, int numblock){
   cellType = type;
   blocknumber = numblock;
}

void Cell::incrementX(){
   r++;
   }
void Cell::incrementY(){
   c++; 
   }
void Cell::decrementY(){
   c--;
   }

ostream &operator<<(ostream &out, Cell& c){
    out << c.getType();
    return out;
}

void Cell::setType(char type){
  cellType = type;
}


 void Cell::draw(Xwindow *w){
  if(cellType == 32){
    w->fillRectangle(40+35*c, 45+35*r,35, 35, Xwindow::White);
  }else if(cellType == 'I'){
    w->fillRectangle(40+35*c, 45+35*r,35, 35, Xwindow::Red);
  }else if(cellType == 'J'){
    w->fillRectangle(40+35*c, 45+35*r,35, 35, Xwindow::Yellow);
  }else if(cellType == 'O'){
    w->fillRectangle(40+35*c, 45+35*r,35, 35, Xwindow::Blue);
  }else if(cellType == 'L'){
    w->fillRectangle(40+35*c, 45+35*r,35, 35, Xwindow::Green);
  }else if(cellType == 'S'){
    w->fillRectangle(40+35*c, 45+35*r,35, 35, Xwindow::Orange);
  }else if(cellType == 'T'){
    w->fillRectangle(40+35*c, 45+35*r,35, 35, Xwindow::Magenta);
  }else if(cellType == 'Z'){
    w->fillRectangle(40+35*c, 45+35*r,35, 35, Xwindow::Cyan);
  } 
}

void Cell::undraw(Xwindow *w){
   
  w->fillRectangle(40+35*c, 45+35*r,35, 35, Xwindow::White);
}
