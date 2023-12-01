#include "GameMechs.h"
#include "MacUILib.h"

#include <cstdlib> // srand() and rand()
#include <time.h> // gives the time
using namespace std;


GameMechs::GameMechs() // default constructor
{
    boardSizeX = 30; // do i follwo week 11 tut vid that 
    boardSizeY = 15; // said 20x10 board size? 

    input = 0; 
    exitFlag = false; // exit if true

    loseFlag = false; // zero means false/player hasn't lost the game
    score = 0; 

    /*initializes food position to be outside board such
    that is it not displayed, this is a common tactic*/ 
    foodPos.setObjPos(-1, -1, 'o'); 

}

GameMechs::GameMechs(int boardX, int boardY)
{
    // out of bound check
    if( boardX <= 0){
		boardX = 30; 
	}
	if (boardY <= 0){
		boardY = 15;
	}

    boardSizeX = boardX;
    boardSizeY = boardY;

    input = 0; // ??
    exitFlag = false; // exit if non-zero

    loseFlag = false; 
    score = 0; 
}

// do you need a destructor? - not yet onlt when u hv data memeber thats on heap
GameMechs::~GameMechs(){
    
}



bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}


char GameMechs::getInput()
{
    if (MacUILib_hasChar())
    {
        input = MacUILib_getChar();
    }

    return input;   
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag() // setLoseTrue??
{
    loseFlag = true;
}


void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0; // does NULL clear the input?
}

int GameMechs::getScore()
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
}
/* FOR ADVANCED FEATURE
You may consider changing incrementScore method to 
allow the score to be increased by numbers other than 1.
*/

void GameMechs::generateFood(objPos blockOff)
{
    // random generate x and y coord (make sure not barder or blockOff pos)
    // generating number betwwen 0 - (cols-2 = 18)
    foodPos.x = (rand() % (boardSizeX - 2)) + 1; // cols, should i use any obj methods? 
    foodPos.y = (rand() % (boardSizeY - 2)) + 1; // rows, should i use any pbj methods? 
    

    // use is position equal in objPos class
    while(foodPos.isPosEqual(&blockOff)) // while the food and blockOff positions are the same keep doing below steps
    {
        foodPos.x = (rand() % (boardSizeX - 2)) + 1; // regenerating x
        foodPos.y = (rand() % (boardSizeX - 2)) + 1; // regenerating y
    }
}

void GameMechs::getFoodPos(objPos &returnFood)
{
    /*Getter method for obtaining the current position of the food.
    Return value is written into the returnPos via pass by reference*/

    returnFood.setObjPos(foodPos);
}
