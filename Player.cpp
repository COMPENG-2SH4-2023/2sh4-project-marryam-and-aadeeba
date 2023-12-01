#include "Player.h"
#include "objPos.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    // Set up position using objPos
    playerPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '*'); 
    
}


Player::~Player()
{
    // delete any heap members here
    delete mainGameMechsRef;
}

void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos arrray list
    // returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);
    returnPos.setObjPos(playerPos);
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic  
    char input = mainGameMechsRef->getInput();
    switch(input){
        case ' ':
            mainGameMechsRef->setExitTrue();
            break;
        case 'W':
        case 'w':
            if (myDir != DOWN)
            {
                myDir = UP;
            }
            break;
        case 'A':
        case 'a':
            if (myDir != RIGHT)
            {
                myDir = LEFT;
            }
            break;
        case 'S':
        case 's':
            if (myDir != UP)
            {
                myDir = DOWN;
            }
            break;

        case 'D':
        case 'd':
            if (myDir != LEFT)
            {
                myDir = RIGHT;
            }
            break;
        default:
            break;
    }      
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    int boardX = mainGameMechsRef->getBoardSizeX();
    int boardY = mainGameMechsRef->getBoardSizeY();
    // objPos currentPos();
    // getObjPos(&currentPos);

    switch (myDir)
    {
        case UP:
            if (playerPos.y > 1)
            {
                playerPos.y--;
            }
            else
            {
                playerPos.y = boardY - 2; 
            }
            break;

        case RIGHT:
            if (playerPos.x < boardX - 2)
            {
                playerPos.x++;
            }
            else
            {
                playerPos.x = 1;
            }
            break;

        case LEFT:
            if (playerPos.x > 1)
            {
                playerPos.x--;
            }
            else
            {
                playerPos.x = boardX - 2;
            }
            break;

        case DOWN:
            if (playerPos.y < boardY - 2)
            {
                playerPos.y++;
            }
            else
            {
                playerPos.y = 1;
            }
            break;

        default:
            break;
    }
}