#include "board.h"
#include "block.h"
#include "window.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstring>
using namespace std;

int main (int argc, char *argv[]){
	bool OnlyText = false;
    int seed = 0;
    int startlevel = 0;
    string file = "sequence.txt";
	for (int i = 1; i < argc; ++i){
		if (strcmp(argv[i], "-text") == 0){
			OnlyText = true;
	    }
	    if(strcmp(argv[i], "-startlevel") == 0){
	    	istringstream ss(argv[i+1]);
	    	ss >> startlevel;
	    }
	    if(strcmp(argv[i], "-scriptfile") == 0){
	    	file = argv[i+1];
	    }
        if(strcmp(argv[i], "-seed") == 0){
            istringstream ss(argv[i+1]);
            ss >> seed;
        }
	}
	Board *myboard = new Board(OnlyText, seed, file, startlevel);
	cout << *myboard;
    //used to read in a string from cin
    string s;
    int times = 1;
    int intlength = 0;
    while(cin >> s){
    	//get prex
    	for(int i = 0; i < s.length(); ++i){
            if(s[i] <= '9' && s[i] >= '0'){
            	intlength += 1;
            } else {
            	break;
            }
    	}
        if(intlength == 0){
        	times = 1;
        } else {
    	  string stringtimes = s.substr(0,intlength);
    	  istringstream ss(stringtimes);
    	  ss >> times;
    	}
        //left
    	if(s.substr(intlength,3) == "lef"){
    	   for(int i = 1; i <= times; ++i){
               myboard->left();
               
           }
           cout << *myboard;
    	}
        //right
        else 
    	if(s.substr(intlength,2) == "ri"){
    	   for(int i = 1; i <= times; ++i){
               myboard->right();
               
           }
           cout << *myboard;
    	}
        //down
        else
        if(s.substr(intlength,2) == "do"){
           for(int i = 1; i <= times; ++i){
               myboard->down();
               
           }
           cout << *myboard;
        }
        //clockwise
        else
        if(s.substr(intlength,2) == "cl"){
    		for(int i = 1; i <= times; ++i){
         	   myboard->clockwise();
               
    	    }
            cout << *myboard;
    	}
        //counterclockwise
        else
        if(s.substr(intlength,2) == "co"){
            for(int i = 1; i <= times; ++i){
                myboard->counterclockwise();
                
            }
            cout << *myboard;
        }
        //drop
        else
        if(s.substr(intlength,2) == "dr"){
            for(int i = 1; i <= times; ++i){
                myboard->drop();
                
            }
            if ((myboard->isWon()) || (myboard->isLost())){
                char c;
                cin >> c;
                if(c == 'y'){
                    myboard->restart();
                    myboard->clearwindow();
                    cout << *myboard;
                }else {
                    break;
                }
            }
        }
        //levelup
        else
        if(s.substr(intlength,6) == "levelu"){
            for(int i = 1; i <= times; ++i){
                myboard->levelup();
            }
            cout << *myboard;
        }
        //leveldown
        else
        if(s.substr(intlength,6) == "leveld"){
            for(int i = 1; i <= times; ++i){
                myboard->leveldown();
            }
            cout << *myboard;
        }
        //restart
        else
        if(s.substr(intlength,2) == "re"){
            for(int i = 1; i <= times; ++i){
                myboard->restart();
                
            }
            cout << *myboard;
        }else{
            cout <<"Invalid Command!" << endl;
        }
        times = 1;
        intlength = 0;
    	
    }
    delete myboard;
}
