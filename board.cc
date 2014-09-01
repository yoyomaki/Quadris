#include "board.h"
#include "window.h"
#include "block.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>
using namespace std;


int Board::HighScore = 0;
bool Board::seeded = false;

void Board::scoreplus(int n){
    if(window != 0){
  ostringstream s1;
  s1 << score;
  window->drawString(100,25,s1.str(),Xwindow::White);
  score+=n;
  ostringstream s2;
  s2 << score;
  window->drawString(100,25,s2.str(),Xwindow::Brown);  
  if(score > HighScore){
     ostringstream s3;
     s3 << HighScore;
     window->drawString(120,40,s1.str(),Xwindow::White);
     HighScore = score;
     ostringstream s4;
     s4 << score;
     window->drawString(120,40,s2.str(),Xwindow::Brown);  
     HighScore = score;
  }
    }else {
        score += n;
        if(score > HighScore){
            HighScore = score;
        }
    }
}

Board::~Board(){
    for (int i = 0; i < 18; ++i){
	delete [] theboard[i];
    }
    delete [] theboard;
    delete window;
    delete currentBlock;
    delete nextBlock;
}

int Board::getlevel(){
  return level;
}

void Board::clearRow(int n){
  for(int i = n; i >= 4; --i){
    for(int j = 0; j < 10; ++j){
       theboard[i][j] = theboard[i-1][j];
       theboard[i][j].incrementX();
       }
    }
  
  for(int i = 0; i < 4; ++i){
    for(int j = 0; j < 10; ++j){
       theboard[i][j] = Cell(i,j,32,0);
    }
  }
}


//generate next block
Block * Board::genNextBlock(){
  char c;
  int RandomNum;
  numblock += 1;
  Block* next = 0;
  if(level == 0){
  	ff >> c;
  	next = new Block(c,numblock,this);
  } else if (level == 1){
  	if(!seeded){
  		srand(seed);
        seeded = true;
    }
    RandomNum = 1 + (rand() % 12);
    if(RandomNum <= 2){
    	next = new Block('I',numblock,this);
    } else if(RandomNum <= 4){
    	next = new Block('J',numblock,this);
    } else if(RandomNum <= 6){
    	next = new Block('L',numblock,this);
    } else if(RandomNum <= 8){
    	next = new Block('O',numblock,this);
    } else if(RandomNum <= 9){
    	next = new Block('S',numblock,this);
    } else if(RandomNum <= 10){
    	next = new Block('Z',numblock,this);
    } else if(RandomNum <= 12){
    	next = new Block('T',numblock,this);
    }
  } else if(level == 2){
  	if(!seeded){
  		srand(seed);
        seeded = true;
    }
    RandomNum = 1 + (rand() % 7);
    if(RandomNum <= 1){
      next = new Block('I',numblock,this);
    } else if(RandomNum <= 2){
      next = new Block('J',numblock,this);
    } else if(RandomNum <= 3){
      next = new Block('L',numblock,this);
    } else if(RandomNum <= 4){
      next = new Block('O',numblock,this);
    } else if(RandomNum <= 5){
      next = new Block('S',numblock,this);
    } else if(RandomNum <= 6){
      next = new Block('Z',numblock,this);
    } else if(RandomNum <= 7){
      next = new Block('T',numblock,this);
    }
  } else if(level == 3){
  	if(!seeded){
  		srand(seed);
        seeded = true;
    }
    RandomNum = 1 + (rand() % 7);
    if(RandomNum <= 1){
      next = new Block('I',numblock,this);
    } else if(RandomNum <= 2){
      next = new Block('J',numblock,this);
    } else if(RandomNum <= 3){
      next = new Block('L',numblock,this);
    } else if(RandomNum <= 4){
      next = new Block('O',numblock,this);
    } else if(RandomNum <= 6){
      next = new Block('S',numblock,this);
    } else if(RandomNum <= 8){
      next = new Block('Z',numblock,this);
    } else if(RandomNum <= 9){
      next = new Block('T',numblock,this);
    }
  }
    vlevel.push_back(level);
    vcleared.push_back(false);
  return next;
}



//constructor
Board::Board(bool OnlyText, int seed, string file, int startlevel): gameStart(false),seed(seed),ff(file.c_str()), level(startlevel){
   theboard = new Cell* [18];
   numblock = 0;
   for (int n = 0; n < 18 ;n++){
      Cell* theCell = new Cell[10];
      for (int j = 0; j < 10; ++j){
         theCell[j].setX(n);
         theCell[j].setY(j);
         }
      theboard[n] = theCell;
      }
	if(OnlyText == true){
		window = 0;
	} else {
    window = new Xwindow(500,1300);
	}
	currentBlock = genNextBlock();
 
  nextBlock = genNextBlock();
}

//set level
void Board::SetLevel(int n){
   level = n;
   }

void Board::clearCell(int r, int c){
   theboard[r][c].setType(32);
}
void Board::setCell(int r, int c, char type, int numblock){
   theboard[r][c].setCell(type, numblock);
}

bool Board::getState(int r, int c){
   return this->theboard[r][c].getState();
   }
Block* Board::returnNextBlock(){
   return nextBlock;
   }  
   
bool Board::isFullRow(int n){
   bool result = true;
   for (int i = 0; i < 10; ++i){
      if (theboard[n][i].getType() == 32){
         result = false;
         break;
      }
    }
   return result;
}

bool Board::isWon(){
    bool won = true;
    for (int i = 0; i < 18 ; ++i){
       for(int j = 0; j < 10; ++j){
          if (theboard[i][j].getState()){
             won = false;
             }
          }
       }
    return won;
}

bool Board::isLost(){
   bool lost = false;
   // check if there's space for the next block.
   if (nextBlock->getBlockType() == 'I'){
      if (theboard[3][0].getType() != 32 || theboard[3][1].getType() != 32 || 
          theboard[3][2].getType() != 32 || theboard[3][3].getType() != 32){
           lost = true;
      }
   }
   else if (nextBlock->getBlockType() == 'J'){
      if (theboard[3][0].getType() != 32 || theboard[4][0].getType() != 32 || 
          theboard[4][1].getType() != 32 || theboard[4][2].getType() != 32){
           lost = true;
      } 
   }    
   else if (nextBlock->getBlockType() == 'L'){
      if (theboard[3][2].getType() != 32 || theboard[4][0].getType() != 32 || 
          theboard[4][1].getType() != 32 || theboard[4][2].getType() != 32){
           lost = true;
      }  
   }   
   else if (nextBlock->getBlockType() == 'O'){
      if (theboard[3][0].getType() != 32 || theboard[3][1].getType() != 32 || 
          theboard[4][0].getType() != 32 || theboard[4][1].getType() != 32){
           lost = true;
      }   
   }   
   else if (nextBlock->getBlockType() == 'S'){
      if (theboard[3][1].getType() != 32 || theboard[3][2].getType() != 32 || 
          theboard[4][0].getType() != 32 || theboard[4][1].getType() != 32){
           lost = true;
      }   
   }   
   else if (nextBlock->getBlockType() == 'Z'){
      if (theboard[3][0].getType() != 32 || theboard[3][1].getType() != 32 || 
          theboard[4][1].getType() != 32 || theboard[4][2].getType() != 32){
           lost = true;
      }   
   }   
   else if (nextBlock->getBlockType() == 'T'){
      if (theboard[3][0].getType() != 32 || theboard[3][1].getType() != 32 || 
          theboard[3][2].getType() != 32 || theboard[4][1].getType() != 32){
           lost = true;
      }  
   }
   return lost;
}



void Board::left(){
    currentBlock->undraw(window);
    currentBlock->left();
    currentBlock->draw(window);
}

void Board::right(){
    currentBlock->undraw(window);
    currentBlock->right();
    currentBlock->draw(window);
}
void Board::down(){
    currentBlock->undraw(window);
    currentBlock->down();
    currentBlock->draw(window);
}

void Board::clockwise(){
    currentBlock->undraw(window);
    currentBlock->Clockwise();
    currentBlock->draw(window);
}

void Board::counterclockwise(){
    currentBlock->undraw(window);
    currentBlock->CounterClockWise();
    currentBlock->draw(window);
}

void Board::drop(){
    clearwindow();
    currentBlock->drop();
    delete currentBlock;
    currentBlock = nextBlock;
    nextBlock = genNextBlock();
    cout << *this;
    if(isLost()){
      delete currentBlock;
      delete nextBlock;
      cout << "Oh dear! You lose." << endl;
      cout << "Restart?(y/n)" << endl;
      
      if(window != 0){
        window->fillRectangle(0,700,500,500,Xwindow::White);
        window->drawString(40, 720, "NO MORE NEXT! YOU LOSE!", Xwindow::Brown);
        window->drawString(40, 750, "Restart?(y/n)", Xwindow::Brown);
      }

    }
   if(isWon()){
      delete currentBlock;
      delete nextBlock;
      cout << "You Won!" << endl;
      cout << "Restart?(y/n)" << endl;
      if(window != 0){
        window->fillRectangle(0,700,500,500,Xwindow::White);
        window->drawString(40, 720, "HAHAHAHA YOU WON!", Xwindow::Brown);
        window->drawString(40, 750, "Restart?(y/n)", Xwindow::Brown);
      }

    }      
      
}
void Board::clearwindow(){
  if(window != 0){
    window->fillRectangle(0,0,2000,2000,Xwindow::White);
  }
}

void Board::levelup(){
    if(level == 3){
        cout << "CANNOT LEVEL UP ANYMORE!" << endl;
    }else {
        if(window!=0){
        ostringstream s1;
        s1 << level;
        window->drawString(100,10,s1.str(),Xwindow::White);
        level += 1;
        ostringstream s2;
        s2 << level;
        window->drawString(100,10,s2.str(),Xwindow::Brown);
        }else {
            level+=1;
        }
    }
}

void Board::leveldown(){
    if(level == 0){
        cout << "CANNOT LEVEL DOWN ANYMORE!" << endl;
    }else {
        if(window !=0){
        ostringstream s1;
        s1 << level;
        window->drawString(100,10,s1.str(),Xwindow::White);
        level -= 1;
        ostringstream s2;
        s2 << level;
        window->drawString(100,10,s2.str(),Xwindow::Brown);
        }else {
            level -=1;
        }
    }
}

void Board::restart(){
    if(score > HighScore) HighScore = score;
    score = 0;
    numblock = 0;
    for(int i = 0; i < 18; ++i){
        for(int j = 0; j < 10; ++j){
            theboard[i][j].setType(32); 
        }
    }
    clearwindow();
    vlevel.clear();
    vcleared.clear();
    currentBlock = genNextBlock();
    nextBlock = genNextBlock();
}

ostream &operator<<(ostream &out, const Board &bd){
    out << "Level:      " << bd.level << endl;
    out << "Score:      " << bd.score << endl;
    out << "Hi Score:   " << bd.HighScore << endl;
    out << "----------" << endl;
    for(int i = 0; i < 18; ++i){
        for(int j = 0; j < 10; ++j){
          if(i == bd.currentBlock->getr1() && j == bd.currentBlock->getc1()){
            out << bd.currentBlock->getBlockType();
          }
          else if(i == bd.currentBlock->getr2() && j == bd.currentBlock->getc2()){
            out << bd.currentBlock->getBlockType();
          }
          else if(i == bd.currentBlock->getr3() && j == bd.currentBlock->getc3()){
            out << bd.currentBlock->getBlockType();
          }
          else if(i == bd.currentBlock->getr4() && j == bd.currentBlock->getc4()){
            out << bd.currentBlock->getBlockType();
          }
          else {
            out << bd.theboard[i][j].getType();
          }
        }
        out << endl;
    }
    out << "----------" << endl;
    out << "Next:" << endl;
    out << *(bd.nextBlock);

    if(bd.window != 0){
       ostringstream s1;
       s1 << bd.level;
       ostringstream s2;
       s2 << bd.score;
       ostringstream s3;
       s3 << bd.HighScore;
       bd.window->drawString(40, 10, "Level:", Xwindow::Brown);
       bd.window->drawString(100, 10, s1.str(), Xwindow::Brown);
       bd.window->drawString(40, 25, "Score:", Xwindow::Brown);
       bd.window->drawString(100, 25, s2.str(), Xwindow::Brown);
       bd.window->drawString(40, 38, "Hi Score:", Xwindow::Brown);
       bd.window->drawString(120, 40, s3.str(), Xwindow::Brown);
       bd.window->drawString(40, 45, "----------------------------------------------------------", Xwindow::Brown);
       
        
        
       for(int i = 0; i < 18; ++i){
        for(int j = 0; j < 10; ++j){
          bd.theboard[i][j].draw(bd.window);
        }
      }

      bd.currentBlock->draw(bd.window);

       bd.window->drawString(40, 680, "----------------------------------------------------------", Xwindow::Brown);
       bd.window->drawString(40,695, "Next:" ,Xwindow::Brown);
       if(bd.nextBlock->getBlockType() == 'I'){
          bd.window->fillRectangle(40, 710, 140,35, Xwindow::Red);
       }else if(bd.nextBlock->getBlockType() == 'J'){
          bd.window->fillRectangle(40, 710, 35,35, Xwindow::Yellow);
          bd.window->fillRectangle(40, 745, 105,35, Xwindow::Yellow);
       }else if(bd.nextBlock->getBlockType() == 'L'){
          bd.window->fillRectangle(110, 710, 35,35, Xwindow::Green);
          bd.window->fillRectangle(40, 745, 105,35, Xwindow::Green);
       }else if(bd.nextBlock->getBlockType() == 'O'){
          bd.window->fillRectangle(40, 710, 70,70, Xwindow::Blue);
       }else if(bd.nextBlock->getBlockType() == 'S'){
          bd.window->fillRectangle(75, 710, 70,35, Xwindow::Orange);
          bd.window->fillRectangle(40, 745, 70,35, Xwindow::Orange);
       }else if(bd.nextBlock->getBlockType() == 'Z'){
          bd.window->fillRectangle(40, 710, 70,35, Xwindow::Cyan);
          bd.window->fillRectangle(75, 745, 70,35, Xwindow::Cyan);
       }else if(bd.nextBlock->getBlockType() == 'T'){
          bd.window->fillRectangle(40, 710, 105,35, Xwindow::Magenta);
          bd.window->fillRectangle(75, 745, 35,35, Xwindow::Magenta);
       }

    }

    return out;
}



char Board::getType(int r, int c){
  return theboard[r][c].getType();
}


bool Board::iscleared(int i){
  bool result = true;
  for(int r = 0; r < 18; ++r){
     for(int c = 0; c < 10; ++c){
      if(theboard[r][c].getBlockNumber() == i){
        result = false;
      }
     }
  }
  return result;
}


vector<bool> Board::getvcleared(){
  return vcleared;
}

int Board::getvlevel(int i){
  return vlevel[i];
}

void Board::setvcleared(int i,bool result){
  vcleared[i] = result;
}


