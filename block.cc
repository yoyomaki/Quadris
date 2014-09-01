# include "cell.h"
# include "block.h"
# include <iostream>
# include <vector> 
using namespace std;



//constructor
Block::Block(char type, int number, Board *myboard): type(type), number(number), bd(myboard){
   rotationType = 0;
   for(int i= 0; i < 4 ; ++i){
      cellArray[i] = Cell(); 
   }
   if(type == 'I'){
     cellArray[0] = Cell(3,0,type,number);
     cellArray[1] = Cell(3,1,type,number);
     cellArray[2] = Cell(3,2,type,number);
     cellArray[3] = Cell(3,3,type,number);
   } else if(type == 'J'){
     cellArray[0] = Cell(3,0,type,number);
     cellArray[1] = Cell(4,0,type,number);
     cellArray[2] = Cell(4,1,type,number);
     cellArray[3] = Cell(4,2,type,number);
   } else if(type == 'L'){
     cellArray[0] = Cell(3,2,type,number);
     cellArray[1] = Cell(4,0,type,number);
     cellArray[2] = Cell(4,1,type,number);
     cellArray[3] = Cell(4,2,type,number);
   } else if(type == 'O'){
     cellArray[0] = Cell(3,0,type,number);
     cellArray[1] = Cell(3,1,type,number);
     cellArray[2] = Cell(4,0,type,number);
     cellArray[3] = Cell(4,1,type,number);
   } else if(type == 'S'){
     cellArray[0] = Cell(3,1,type,number);
     cellArray[1] = Cell(3,2,type,number);
     cellArray[2] = Cell(4,0,type,number);
     cellArray[3] = Cell(4,1,type,number);
   } else if(type == 'Z'){
     cellArray[0] = Cell(3,0,type,number);
     cellArray[1] = Cell(3,1,type,number);
     cellArray[2] = Cell(4,1,type,number);
     cellArray[3] = Cell(4,2,type,number);
   } else if(type == 'T'){
     cellArray[0] = Cell(3,0,type,number);
     cellArray[1] = Cell(3,1,type,number);
     cellArray[2] = Cell(3,2,type,number);
     cellArray[3] = Cell(4,1,type,number);
   }
}

int Block::getr1(){
   return cellArray[0].getX();
}
int Block::getc1(){
   return cellArray[0].getY();
}
int Block::getr2(){
   return cellArray[1].getX();
}
int Block::getc2(){
   return cellArray[1].getY();
}
int Block::getr3(){
   return cellArray[2].getX();
}
int Block::getc3(){
   return cellArray[2].getY();
}    
int Block::getr4(){
   return cellArray[3].getX();
}
int Block::getc4(){
   return cellArray[3].getY();
}

Cell Block::getcell(int i){
   return cellArray[i];
}


   
char Block::getBlockType(){
   return type;
}   
   
int Block::getRotationType(){
   return rotationType;
}   
   
bool Block::canleft(){
   bool can = true;
   for(int i = 0; i < 4; ++i){
      if((cellArray[i].getY() - 1) < 0){
         can = false;
         break;
      }
      if(bd->getType(cellArray[i].getX(), cellArray[i].getY() - 1) != 32){
         can = false;
         break;
      }
   }
   return can;
}


   
bool Block::canRight(){
   bool can = true;
   for(int i = 0; i < 4; ++i){
      if((cellArray[i].getY() + 1) > 9){
         can = false;
         break;
      }
      if(bd->getType(cellArray[i].getX(), cellArray[i].getY() + 1) != 32){
         can = false;
         break;
      }
   }
   return can;
}
   
bool Block::canDown(){
   bool can = true;
   for(int i = 0; i < 4; ++i){
      if((cellArray[i].getX() + 1) > 17){
         can = false;
         break;
      }
      if(bd->getType(cellArray[i].getX() + 1, cellArray[i].getY()) != 32){
         can = false;
         break;
      }
   }
   return can;
}
   

void Block::left(){
   if(canleft()){
      for(int i =0; i < 4; ++i){
         cellArray[i].decrementY();
      }
   }
}

         
void Block::right(){
   if (canRight()){
      for(int i =0; i < 4; ++i){
         cellArray[i].incrementY();
      }
   }
}


void Block::down(){
   if (canDown()){
      for(int i =0; i < 4; ++i){
         cellArray[i].incrementX();
      }
   }
}

void Block::drop(){
   int plus = 0;
   while (canDown()){
      down();
   }
   for(int i = 0; i < 4; ++i){
     bd->setCell(cellArray[i].getX(), cellArray[i].getY(), type, number);
   }
   int total = 0;
   for(int i = 17; i >= 0; --i){
     if(bd->isFullRow(i)){
        bd->clearRow(i);
        ++i;
        total += 1;
     }
   }
   if(total >= 1){
      plus += (bd->getlevel() + total) * (bd->getlevel() + total);
   }
    for(int i = 0; i < bd->getvcleared().size(); ++i){
        if(bd->getvcleared()[i] == false){
            if(bd->iscleared(i)){
                plus += (bd->getvlevel(i) + 1) * (bd->getvlevel(i) + 1);
                bd->setvcleared(i,true);
            }
            
        }
    }
   bd->scoreplus(plus); 
}



void Block::Clockwise(){
    if(type =='I'){
      if(rotationType == 0){
         if(cellArray[0].getX() - 3 >= 0 &&
            bd->getType(cellArray[0].getX(), cellArray[0].getY()) == 32 &&
            bd->getType(cellArray[0].getX() - 1, cellArray[0].getY()) == 32 &&
            bd->getType(cellArray[0].getX() - 2, cellArray[0].getY()) == 32 &&
            bd->getType(cellArray[0].getX() - 3, cellArray[0].getY()) == 32){
            int r0 = cellArray[0].getX();
            int c0 = cellArray[0].getY();
            cellArray[0].setX(r0-3);
            cellArray[0].setY(c0);
            cellArray[1].setX(r0-2);
            cellArray[1].setY(c0);
            cellArray[2].setX(r0-1);
            cellArray[2].setY(c0);
            cellArray[3].setX(r0);
            cellArray[3].setY(c0);
            rotationType = 1;
         }
      }else {
         if(cellArray[0].getY() + 3 <= 17 &&
            bd->getType(cellArray[4].getX(), cellArray[4].getY()) == 32 &&
            bd->getType(cellArray[4].getX(), cellArray[4].getY()+1) == 32 &&
            bd->getType(cellArray[4].getX(), cellArray[4].getY()+2) == 32 &&
            bd->getType(cellArray[4].getX(), cellArray[4].getY()+3) == 32){
            int r0 = cellArray[0].getX();
            int c0 = cellArray[0].getY();
            cellArray[0].setX(r0+3);
            cellArray[0].setY(c0);
            cellArray[1].setX(r0+3);
            cellArray[1].setY(c0+1);
            cellArray[2].setX(r0+3);
            cellArray[2].setY(c0+2);
            cellArray[3].setX(r0+3);
            cellArray[3].setY(c0+3);
            rotationType = 0;
         }
      }
   } else if(type == 'J'){
      if(rotationType == 0){
         if(cellArray[0].getX() - 1 >= 0 &&
            bd->getType(cellArray[0].getX()- 1, cellArray[0].getY()) == 32 &&
            bd->getType(cellArray[0].getX()- 1, cellArray[0].getY()+1) == 32){
            int r0 = cellArray[0].getX();
            int c0 = cellArray[0].getY();
            cellArray[0].setX(r0-1);
            cellArray[0].setY(c0+1);
            cellArray[1].setX(r0-1);
            cellArray[1].setY(c0);
            cellArray[2].setX(r0);
            cellArray[2].setY(c0);
            cellArray[3].setX(r0+1);
            cellArray[3].setY(c0);
            rotationType = 1;
         }
      }else if(rotationType == 1){
         if(cellArray[0].getY() + 1 <= 9 &&
            bd->getType(cellArray[0].getX()+ 1, cellArray[0].getY()) == 32 &&
            bd->getType(cellArray[0].getX()+ 1, cellArray[0].getY()+1) == 32 &&
            bd->getType(cellArray[0].getX()+ 2, cellArray[0].getY()+1) == 32){
            int r0 = cellArray[0].getX();
            int c0 = cellArray[0].getY();
            cellArray[0].setX(r0+2);
            cellArray[0].setY(c0+1);
            cellArray[1].setX(r0+1);
            cellArray[1].setY(c0+1);
            cellArray[2].setX(r0+1);
            cellArray[2].setY(c0);
            cellArray[3].setX(r0+1);
            cellArray[3].setY(c0-1);
            rotationType = 2;
         }
      }else if(rotationType == 2){
         if(cellArray[0].getX() - 2 >= 0 &&
            bd->getType(cellArray[0].getX(), cellArray[0].getY()-2) == 32 &&
            bd->getType(cellArray[0].getX(), cellArray[0].getY()-1) == 32 &&
            bd->getType(cellArray[0].getX()-2, cellArray[0].getY()-1) == 32){
            int r0 = cellArray[0].getX();
            int c0 = cellArray[0].getY();
            cellArray[0].setX(r0);
            cellArray[0].setY(c0-2);
            cellArray[1].setX(r0);
            cellArray[1].setY(c0-1);
            cellArray[2].setX(r0-1);
            cellArray[2].setY(c0-1);
            cellArray[3].setX(r0-2);
            cellArray[3].setY(c0-1);
            rotationType = 3;
         }
      }else if(rotationType == 3){
         if(cellArray[0].getY() + 2 <= 9 &&
            bd->getType(cellArray[0].getX()-1, cellArray[0].getY()) == 32 &&
            bd->getType(cellArray[0].getX(), cellArray[0].getY()+2) == 32){
            int r0 = cellArray[0].getX();
            int c0 = cellArray[0].getY();
            cellArray[0].setX(r0-1);
            cellArray[0].setY(c0);
            cellArray[1].setX(r0);
            cellArray[1].setY(c0);
            cellArray[2].setX(r0);
            cellArray[2].setY(c0+1);
            cellArray[3].setX(r0);
            cellArray[3].setY(c0+2);
            rotationType = 0;
         }
      }
   }else if(type == 'L'){
      if(rotationType == 0){
         if(cellArray[0].getX() - 1 >= 0 &&
            bd->getType(cellArray[0].getX(), cellArray[0].getY()-2) == 32 &&
            bd->getType(cellArray[0].getX()- 1, cellArray[0].getY()-2) == 32){
            int r0 = cellArray[0].getX();
            int c0 = cellArray[0].getY();
            cellArray[0].setX(r0+1);
            cellArray[0].setY(c0-1);
            cellArray[1].setX(r0+1);
            cellArray[1].setY(c0-2);
            cellArray[2].setX(r0);
            cellArray[2].setY(c0-2);
            cellArray[3].setX(r0-1);
            cellArray[3].setY(c0-2);
            rotationType = 1;
         }
      }else if(rotationType == 1){
         if(cellArray[0].getY() + 1 <= 9 &&
            bd->getType(cellArray[0].getX()- 1, cellArray[0].getY()) == 32 &&
            bd->getType(cellArray[0].getX()- 1, cellArray[0].getY()+1) == 32){
            int r0 = cellArray[0].getX();
            int c0 = cellArray[0].getY();
            cellArray[0].setX(r0);
            cellArray[0].setY(c0-1);
            cellArray[1].setX(r0+1);
            cellArray[1].setY(c0-1);
            cellArray[2].setX(r0+1);
            cellArray[2].setY(c0);
            cellArray[3].setX(r0+1);
            cellArray[3].setY(c0+1);
            rotationType = 2;
         }
      }else if(rotationType == 2){
         if(cellArray[0].getX() - 2 >= 0 &&
            bd->getType(cellArray[0].getX()-2, cellArray[0].getY()) == 32 &&
            bd->getType(cellArray[0].getX()-2, cellArray[0].getY()+1) == 32 &&
            bd->getType(cellArray[0].getX(), cellArray[0].getY()+1) == 32){
            int r0 = cellArray[0].getX();
            int c0 = cellArray[0].getY();
            cellArray[0].setX(r0-2);
            cellArray[0].setY(c0);
            cellArray[1].setX(r0-2);
            cellArray[1].setY(c0+1);
            cellArray[2].setX(r0-1);
            cellArray[2].setY(c0+1);
            cellArray[3].setX(r0);
            cellArray[3].setY(c0+1);
            rotationType = 3;
         }
      }else if(rotationType == 3){
         if(cellArray[0].getY() + 2 <= 9 &&
            bd->getType(cellArray[0].getX()+1, cellArray[0].getY()+2) == 32 &&
            bd->getType(cellArray[0].getX()+2, cellArray[0].getY()+2) == 32 &&
            bd->getType(cellArray[0].getX()+2, cellArray[0].getY()) == 32){
            int r0 = cellArray[0].getX();
            int c0 = cellArray[0].getY();
            cellArray[0].setX(r0+1);
            cellArray[0].setY(c0+2);
            cellArray[1].setX(r0+2);
            cellArray[1].setY(c0+2);
            cellArray[2].setX(r0+2);
            cellArray[2].setY(c0+1);
            cellArray[3].setX(r0+2);
            cellArray[3].setY(c0);
            rotationType = 0;
         }
      }
   } else if(type == 'O'){
      //do nothing
   } else if(type == 'S'){
      if(rotationType == 0){
         if(cellArray[0].getX() - 1 >= 0 &&
            bd->getType(cellArray[0].getX(), cellArray[0].getY()-1) == 32 &&
            bd->getType(cellArray[0].getX() - 1, cellArray[0].getY()-1) == 32){
            int r0 = cellArray[0].getX();
            int c0 = cellArray[0].getY();
            cellArray[1].setX(r0+1);
            cellArray[1].setY(c0);
            cellArray[2].setX(r0-1);
            cellArray[2].setY(c0-1);
            cellArray[3].setX(r0);
            cellArray[3].setY(c0-1);
            rotationType = 1;
         }
      }else {
         if(cellArray[0].getY() + 1 <= 9 &&
            bd->getType(cellArray[0].getX(), cellArray[0].getY()+1) == 32 &&
            bd->getType(cellArray[0].getX() +1, cellArray[0].getY()-1) == 32){
            int r0 = cellArray[0].getX();
            int c0 = cellArray[0].getY();
            cellArray[1].setX(r0);
            cellArray[1].setY(c0+1);
            cellArray[2].setX(r0+1);
            cellArray[2].setY(c0-1);
            cellArray[3].setX(r0+1);
            cellArray[3].setY(c0);
            rotationType = 0;
         }
      }
   } else if(type == 'Z'){
      if(rotationType == 0){
         if(cellArray[0].getX() - 1 >= 0 &&
            bd->getType(cellArray[0].getX()+ 1, cellArray[0].getY()) == 32 &&
            bd->getType(cellArray[0].getX()- 1, cellArray[0].getY()+1) == 32){
            int r0 = cellArray[0].getX();
            int c0 = cellArray[0].getY();
            cellArray[0].setX(r0-1);
            cellArray[0].setY(c0+1);
            cellArray[2].setX(r0);
            cellArray[2].setY(c0);
            cellArray[3].setX(r0+1);
            cellArray[3].setY(c0);
            rotationType = 1;
         }
      }else {
         if(cellArray[0].getY() + 1 <= 9 &&
            bd->getType(cellArray[0].getX()+2, cellArray[0].getY()) == 32 &&
            bd->getType(cellArray[0].getX()+1, cellArray[0].getY()+1) == 32){
            int r0 = cellArray[0].getX();
            int c0 = cellArray[0].getY();
            cellArray[0].setX(r0+1);
            cellArray[0].setY(c0-1);
            cellArray[2].setX(r0+2);
            cellArray[2].setY(c0);
            cellArray[3].setX(r0+2);
            cellArray[3].setY(c0+1);
            rotationType = 0;
         }
      }
   }else if(type == 'T'){
      if(rotationType == 0){
         if(cellArray[0].getX() - 1 >= 0 &&
            bd->getType(cellArray[0].getX()-1, cellArray[0].getY()+1) == 32){
            int r0 = cellArray[0].getX();
            int c0 = cellArray[0].getY();
            cellArray[0].setX(r0-1);
            cellArray[0].setY(c0+1);
            cellArray[2].setX(r0+1);
            cellArray[2].setY(c0+1);
            cellArray[3].setX(r0);
            cellArray[3].setY(c0);
            rotationType = 1;
         }
      }else if(rotationType == 1){
         if(cellArray[0].getY() + 1 <= 9 &&
            bd->getType(cellArray[0].getX()+2, cellArray[0].getY()-1) == 32 &&
            bd->getType(cellArray[0].getX()+2, cellArray[0].getY()+1) == 32){
            int r0 = cellArray[0].getX();
            int c0 = cellArray[0].getY();
            cellArray[0].setX(r0+2);
            cellArray[0].setY(c0-1);
            cellArray[1].setX(r0+2);
            cellArray[1].setY(c0);
            cellArray[2].setX(r0+2);
            cellArray[2].setY(c0+1);
            cellArray[3].setX(r0+1);
            cellArray[3].setY(c0);
            rotationType = 2;
         }
      }else if(rotationType == 2){
         if(cellArray[0].getX() - 2 >= 0 &&
            bd->getType(cellArray[0].getX()-2, cellArray[0].getY()) == 32 &&
            bd->getType(cellArray[0].getX()-1, cellArray[0].getY()) == 32){
            int r0 = cellArray[0].getX();
            int c0 = cellArray[0].getY();
            cellArray[0].setX(r0-2);
            cellArray[0].setY(c0);
            cellArray[1].setX(r0-1);
            cellArray[1].setY(c0);
            cellArray[2].setX(r0);
            cellArray[2].setY(c0);
            cellArray[3].setX(r0-1);
            cellArray[3].setY(c0+1);
            rotationType = 3;
         }
      }else if(rotationType == 3){
         if(cellArray[0].getY() + 2 <= 9 &&
            bd->getType(cellArray[0].getX()+1, cellArray[0].getY()+2) == 32 &&
            bd->getType(cellArray[0].getX()+2, cellArray[0].getY()+1) == 32){
            int r0 = cellArray[0].getX();
            int c0 = cellArray[0].getY();
            cellArray[0].setX(r0+1);
            cellArray[0].setY(c0);
            cellArray[1].setX(r0+1);
            cellArray[1].setY(c0+1);
            cellArray[2].setX(r0+1);
            cellArray[2].setY(c0+2);
            cellArray[3].setX(r0+2);
            cellArray[3].setY(c0+1);
            rotationType = 0;
         }
      }
   }
}




void Block::CounterClockWise(){
    if(type =='I'){
      if(rotationType == 0){
         if(cellArray[0].getX() - 3 >= 0 &&
            bd->getType(cellArray[0].getX(), cellArray[0].getY()) == 32 &&
            bd->getType(cellArray[0].getX() - 1, cellArray[0].getY()) == 32 &&
            bd->getType(cellArray[0].getX() - 2, cellArray[0].getY()) == 32 &&
            bd->getType(cellArray[0].getX() - 3, cellArray[0].getY()) == 32){
            int r0 = cellArray[0].getX();
            int c0 = cellArray[0].getY();
            cellArray[0].setX(r0-3);
            cellArray[0].setY(c0);
            cellArray[1].setX(r0-2);
            cellArray[1].setY(c0);
            cellArray[2].setX(r0-1);
            cellArray[2].setY(c0);
            cellArray[3].setX(r0);
            cellArray[3].setY(c0);
            rotationType = 1;
         }
      }else {
         if(cellArray[0].getY() + 3 <= 17 &&
            bd->getType(cellArray[4].getX(), cellArray[4].getY()) == 32 &&
            bd->getType(cellArray[4].getX(), cellArray[4].getY()+1) == 32 &&
            bd->getType(cellArray[4].getX(), cellArray[4].getY()+2) == 32 &&
            bd->getType(cellArray[4].getX(), cellArray[4].getY()+3) == 32){
            int r0 = cellArray[0].getX();
            int c0 = cellArray[0].getY();
            cellArray[0].setX(r0+3);
            cellArray[0].setY(c0);
            cellArray[1].setX(r0+3);
            cellArray[1].setY(c0+1);
            cellArray[2].setX(r0+3);
            cellArray[2].setY(c0+2);
            cellArray[3].setX(r0+3);
            cellArray[3].setY(c0+3);
            rotationType = 0;
         }
      }
   } else if(type == 'J'){
      if(rotationType == 0){
         if(cellArray[0].getX() - 1 >= 0 &&
            bd->getType(cellArray[0].getX()- 1, cellArray[0].getY()+1) == 32 &&
            bd->getType(cellArray[0].getX(), cellArray[0].getY()+1) == 32){
            int r0 = cellArray[0].getX();
            int c0 = cellArray[0].getY();
            cellArray[0].setX(r0+1);
            cellArray[0].setY(c0);
            cellArray[1].setX(r0+1);
            cellArray[1].setY(c0+1);
            cellArray[2].setX(r0);
            cellArray[2].setY(c0+1);
            cellArray[3].setX(r0-1);
            cellArray[3].setY(c0+1);
            rotationType = 3;
         }
      }else if(rotationType == 1){
         if(cellArray[0].getY() + 1 <= 9 &&
            bd->getType(cellArray[0].getX()+ 2, cellArray[0].getY()) == 32 &&
            bd->getType(cellArray[0].getX()+ 2, cellArray[0].getY()+1) == 32){
            int r0 = cellArray[0].getX();
            int c0 = cellArray[0].getY();
            cellArray[0].setX(r0+1);
            cellArray[0].setY(c0-1);
            cellArray[1].setX(r0+2);
            cellArray[1].setY(c0-1);
            cellArray[2].setX(r0+2);
            cellArray[2].setY(c0);
            cellArray[3].setX(r0+2);
            cellArray[3].setY(c0+1);
            rotationType = 0;
         }
      }else if(rotationType == 2){
         if(cellArray[0].getX() - 2 >= 0 &&
            bd->getType(cellArray[0].getX()-2, cellArray[0].getY()-2) == 32 &&
            bd->getType(cellArray[0].getX()-2, cellArray[0].getY()-1) == 32 &&
            bd->getType(cellArray[0].getX(), cellArray[0].getY()-2) == 32){
            int r0 = cellArray[0].getX();
            int c0 = cellArray[0].getY();
            cellArray[0].setX(r0-2);
            cellArray[0].setY(c0-1);
            cellArray[1].setX(r0-2);
            cellArray[1].setY(c0-2);
            cellArray[2].setX(r0-1);
            cellArray[2].setY(c0-2);
            cellArray[3].setX(r0);
            cellArray[3].setY(c0-2);
            rotationType = 1;
         }
      }else if(rotationType == 3){
         if(cellArray[0].getY() + 2 <= 9 &&
            bd->getType(cellArray[0].getX()-1, cellArray[0].getY()) == 32 &&
            bd->getType(cellArray[0].getX()-1, cellArray[0].getY()+2) == 32 &&
            bd->getType(cellArray[0].getX(), cellArray[0].getY()+2) == 32){
            int r0 = cellArray[0].getX();
            int c0 = cellArray[0].getY();
            cellArray[0].setX(r0);
            cellArray[0].setY(c0+2);
            cellArray[1].setX(r0-1);
            cellArray[1].setY(c0+2);
            cellArray[2].setX(r0-1);
            cellArray[2].setY(c0+1);
            cellArray[3].setX(r0-1);
            cellArray[3].setY(c0);
            rotationType = 2;
         }
      }
   }else if(type == 'L'){
      if(rotationType == 0){
         if(cellArray[0].getX() - 1 >= 0 &&
            bd->getType(cellArray[0].getX(), cellArray[0].getY()-1) == 32 &&
            bd->getType(cellArray[0].getX()- 1, cellArray[0].getY()-1) == 32 &&
            bd->getType(cellArray[0].getX()- 1, cellArray[0].getY()-2) == 32){
            int r0 = cellArray[0].getX();
            int c0 = cellArray[0].getY();
            cellArray[0].setX(r0-1);
            cellArray[0].setY(c0-2);
            cellArray[1].setX(r0-1);
            cellArray[1].setY(c0-1);
            cellArray[2].setX(r0);
            cellArray[2].setY(c0-1);
            cellArray[3].setX(r0+1);
            cellArray[3].setY(c0-1);
            rotationType = 3;
         }
      }else if(rotationType == 1){
         if(cellArray[0].getY() + 1 <= 9 &&
            bd->getType(cellArray[0].getX(), cellArray[0].getY()+1) == 32 &&
            bd->getType(cellArray[0].getX()- 1, cellArray[0].getY()+1) == 32){
            int r0 = cellArray[0].getX();
            int c0 = cellArray[0].getY();
            cellArray[0].setX(r0-1);
            cellArray[0].setY(c0+1);
            cellArray[1].setX(r0);
            cellArray[1].setY(c0+1);
            cellArray[2].setX(r0);
            cellArray[2].setY(c0);
            cellArray[3].setX(r0);
            cellArray[3].setY(c0-1);
            rotationType = 0;
         }
      }else if(rotationType == 2){
         if(cellArray[0].getX() - 2 >= 0 &&
            bd->getType(cellArray[0].getX(), cellArray[0].getY()+1) == 32 &&
            bd->getType(cellArray[0].getX()-2, cellArray[0].getY()) == 32){
            int r0 = cellArray[0].getX();
            int c0 = cellArray[0].getY();
            cellArray[0].setX(r0);
            cellArray[0].setY(c0+1);
            cellArray[1].setX(r0);
            cellArray[1].setY(c0);
            cellArray[2].setX(r0-1);
            cellArray[2].setY(c0);
            cellArray[3].setX(r0-2);
            cellArray[3].setY(c0);
            rotationType = 1;
         }
      }else if(rotationType == 3){
         if(cellArray[0].getY() + 2 <= 9 &&
            bd->getType(cellArray[0].getX()+1, cellArray[0].getY()) == 32 &&
            bd->getType(cellArray[0].getX()+2, cellArray[0].getY()) == 32 &&
            bd->getType(cellArray[0].getX()+1, cellArray[0].getY()+2) == 32){
            int r0 = cellArray[0].getX();
            int c0 = cellArray[0].getY();
            cellArray[0].setX(r0+2);
            cellArray[0].setY(c0);
            cellArray[1].setX(r0+1);
            cellArray[1].setY(c0);
            cellArray[2].setX(r0+1);
            cellArray[2].setY(c0+1);
            cellArray[3].setX(r0+1);
            cellArray[3].setY(c0+2);
            rotationType = 2;
         }
      }
   } else if(type == 'O'){
      //do nothing
   } else if(type == 'S'){
      if(rotationType == 0){
         if(cellArray[0].getX() - 1 >= 0 &&
            bd->getType(cellArray[0].getX(), cellArray[0].getY()-1) == 32 &&
            bd->getType(cellArray[0].getX() - 1, cellArray[0].getY()-1) == 32){
            int r0 = cellArray[0].getX();
            int c0 = cellArray[0].getY();
            cellArray[1].setX(r0+1);
            cellArray[1].setY(c0);
            cellArray[2].setX(r0-1);
            cellArray[2].setY(c0-1);
            cellArray[3].setX(r0);
            cellArray[3].setY(c0-1);
            rotationType = 1;
         }
      }else {
         if(cellArray[0].getY() + 1 <= 9 &&
            bd->getType(cellArray[0].getX(), cellArray[0].getY()+1) == 32 &&
            bd->getType(cellArray[0].getX() +1, cellArray[0].getY()-1) == 32){
            int r0 = cellArray[0].getX();
            int c0 = cellArray[0].getY();
            cellArray[1].setX(r0);
            cellArray[1].setY(c0+1);
            cellArray[2].setX(r0+1);
            cellArray[2].setY(c0-1);
            cellArray[3].setX(r0+1);
            cellArray[3].setY(c0);
            rotationType = 0;
         }
      }
   } else if(type == 'Z'){
      if(rotationType == 0){
         if(cellArray[0].getX() - 1 >= 0 &&
            bd->getType(cellArray[0].getX()+ 1, cellArray[0].getY()) == 32 &&
            bd->getType(cellArray[0].getX()- 1, cellArray[0].getY()+1) == 32){
            int r0 = cellArray[0].getX();
            int c0 = cellArray[0].getY();
            cellArray[0].setX(r0-1);
            cellArray[0].setY(c0+1);
            cellArray[2].setX(r0);
            cellArray[2].setY(c0);
            cellArray[3].setX(r0+1);
            cellArray[3].setY(c0);
            rotationType = 1;
         }
      }else {
         if(cellArray[0].getY() + 1 <= 9 &&
            bd->getType(cellArray[0].getX()+2, cellArray[0].getY()) == 32 &&
            bd->getType(cellArray[0].getX()+1, cellArray[0].getY()+1) == 32){
            int r0 = cellArray[0].getX();
            int c0 = cellArray[0].getY();
            cellArray[0].setX(r0+1);
            cellArray[0].setY(c0-1);
            cellArray[2].setX(r0+2);
            cellArray[2].setY(c0);
            cellArray[3].setX(r0+2);
            cellArray[3].setY(c0+1);
            rotationType = 0;
         }
      }
   }else if(type == 'T'){
      if(rotationType == 0){
         if(cellArray[0].getX() - 1 >= 0 &&
            bd->getType(cellArray[0].getX()-1, cellArray[0].getY()) == 32 &&
            bd->getType(cellArray[0].getX()+1, cellArray[0].getY()) == 32){
            int r0 = cellArray[0].getX();
            int c0 = cellArray[0].getY();
            cellArray[0].setX(r0-1);
            cellArray[0].setY(c0);
            cellArray[1].setX(r0);
            cellArray[1].setY(c0);
            cellArray[2].setX(r0-1);
            cellArray[2].setY(c0);
            cellArray[3].setX(r0);
            cellArray[3].setY(c0+1);
            rotationType = 3;
         }
      }else if(rotationType == 1){
         if(cellArray[0].getY() + 1 <= 9 &&
            bd->getType(cellArray[0].getX()+1, cellArray[0].getY()+1) == 32){
            int r0 = cellArray[0].getX();
            int c0 = cellArray[0].getY();
            cellArray[0].setX(r0+1);
            cellArray[0].setY(c0-1);
            cellArray[1].setX(r0+1);
            cellArray[1].setY(c0);
            cellArray[2].setX(r0+1);
            cellArray[2].setY(c0+1);
            cellArray[3].setX(r0+2);
            cellArray[3].setY(c0);
            rotationType = 0;
         }
      }else if(rotationType == 2){
         if(cellArray[0].getX() - 2 >= 0 &&
            bd->getType(cellArray[0].getX()-1, cellArray[0].getY()) == 32 &&
            bd->getType(cellArray[0].getX()-2, cellArray[0].getY() +1) == 32){
            int r0 = cellArray[0].getX();
            int c0 = cellArray[0].getY();
            cellArray[0].setX(r0-2);
            cellArray[0].setY(c0+1);
            cellArray[1].setX(r0-1);
            cellArray[1].setY(c0+1);
            cellArray[2].setX(r0);
            cellArray[2].setY(c0+1);
            cellArray[3].setX(r0-1);
            cellArray[3].setY(c0);
            rotationType = 1;
         }
      }else if(rotationType == 3){
         if(cellArray[0].getY() + 2 <= 9 &&
            bd->getType(cellArray[0].getX()+2, cellArray[0].getY()+1) == 32 &&
            bd->getType(cellArray[0].getX()+2, cellArray[0].getY()+2) == 32){
            int r0 = cellArray[0].getX();
            int c0 = cellArray[0].getY();
            cellArray[0].setX(r0+2);
            cellArray[0].setY(c0);
            cellArray[1].setX(r0+2);
            cellArray[1].setY(c0+1);
            cellArray[2].setX(r0+2);
            cellArray[2].setY(c0+2);
            cellArray[3].setX(r0+1);
            cellArray[3].setY(c0+1);
            rotationType = 2;
         }
      }
   }
}

ostream &operator<<(ostream &out, Block &block){
    if(block.getBlockType() == 'I'){
        out << "IIII" << endl;
    }else if(block.getBlockType() == 'J'){
        out << "J" << endl;
        out << "JJJ" << endl;
    }else if(block.getBlockType() == 'L'){
        out << "  L" << endl;
        out << "LLL" << endl;
    }else if(block.getBlockType() == 'O'){
        out << "OO" << endl;
        out << "OO" << endl;
    }else if(block.getBlockType() == 'S'){
        out << " SS" << endl;
        out << "SS" << endl;
    }else if(block.getBlockType() == 'Z'){
        out << "ZZ" << endl;
        out << " ZZ" << endl;
    }else if(block.getBlockType() == 'T'){
        out << "TTT" << endl;
        out << " T" << endl;
    }
    return out;
}



void Block::draw(Xwindow *w){
   if(w != 0){
    for(int i = 0; i <4; ++i){
      cellArray[i].draw(w);
    }
   }
}

void Block::undraw(Xwindow *w){
   if(w != 0){
   for(int i = 0; i <4; ++i){
      cellArray[i].undraw(w);
    }
 }
}
