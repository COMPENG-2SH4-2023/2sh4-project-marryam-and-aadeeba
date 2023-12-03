#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;


class GameMechs
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    private:
        char input;
        bool exitFlag;
        
        int boardSizeX;
        int boardSizeY;

        // added
        bool loseFlag;
        int score; 
        objPos foodPos; // 2B


    public:
        GameMechs();
        GameMechs(int boardX, int boardY);

        ~GameMechs(); // <- is it needed? this class doesnt have any pointers
        
        bool getExitFlagStatus();
        void setExitTrue();

        char getInput();
        void setInput(char this_input);
        void clearInput();

        int getBoardSizeX();
        int getBoardSizeY();
        
        // added
        bool getLoseFlagStatus(); 
        void setLoseFlag();

        int getScore(); // add const key word
        void incrementScore();

        // 2B
        void generateFood(objPosArrayList *blockOff); 
        void getFoodPos(objPos &returnPos);
      

};

#endif