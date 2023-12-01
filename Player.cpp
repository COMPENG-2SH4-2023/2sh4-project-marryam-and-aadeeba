#include "Player.h"
#include "objPos.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    // Set up position using objPos
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '*'); 
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);
}


Player::~Player()
{
    // delete any heap members here
    delete mainGameMechsRef;
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos arrray list
    return playerPosList;
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
    
    objPos newHead;
    objPos currentHead;
    playerPosList->getHeadElement(currentHead);

    switch (myDir)
    {
        case UP:
            if (currentHead.y > 1)
            {
                currentHead.y--;
            }
            else
            {
                currentHead.y = boardY - 2; 
            }
            break;

        case RIGHT:
            if (currentHead.x < boardX - 2)
            {
                currentHead.x++;
            }
            else
            {
                currentHead.x = 1;
            }
            break;

        case LEFT:
            if (currentHead.x > 1)
            {
                currentHead.x--;
            }
            else
            {
                currentHead.x = boardX - 2;
            }
            break;

        case DOWN:
            if (currentHead.y < boardY - 2)
            {
                currentHead.y++;
            }
            else
            {
                currentHead.y = 1;
            }
            break;

        default:
            break;
    }

    playerPosList->insertHead(currentHead);
    playerPosList->removeTail();

}
