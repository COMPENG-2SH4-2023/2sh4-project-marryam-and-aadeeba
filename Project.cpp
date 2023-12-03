#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "objPosArrayList.h"


using namespace std;

#define DELAY_CONST 100000


//////////////////////
// GLOBAL VARIABLES // 
//////////////////////

GameMechs* myGM; // a pointer to a gameMechanics class in the global scope
Player* myPlayer;


void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while((myGM->getExitFlagStatus()) == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    
    /* gameMechanics object on the heap, and 
    initialize its fields accordingly */
    myGM = new GameMechs(26, 13); // makes board that's 26x13
    myPlayer = new Player(myGM);
    myGM->generateFood(myPlayer->getPlayerPos());
}

void GetInput(void)
{
    /*collect the input ASCII character into the corresponding field in
    gameMechanics object using the correct setter method*/  

    myGM->getInput();
      
}

void RunLogic(void)
{
    objPos tempFood;
    objPos tempBody;
    objPos newInsert;
    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    int length = playerBody->getSize();
    myGM->getFoodPos(tempFood);

    myPlayer->updatePlayerDir();  
    myPlayer->movePlayer(); 

    //collision detection with food:
    playerBody->getHeadElement(tempBody);
    if(tempBody.isPosEqual(&tempFood)){
        myGM->incrementScore();
        newInsert.setObjPos(tempBody.x, tempBody.y, '*');
        playerBody->insertHead(newInsert);
        myGM->generateFood(playerBody);
    }
    // collision detection with self:
    if(myPlayer->checkSelfCollision()){
        
    }


    /*access the correct field in the gameMechanics object through the getter method to
    process the input character*/
    
    // choose the correct action - what's this asking for?

    /*clear the input field in gameMechanics to avoid double-
    processing the input*/
    myGM->clearInput();
    
}

void DrawScreen(void)
{
       
    bool drawn;
    objPos tempBody;
    objPos tempFood;
    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    myGM->getFoodPos(tempFood);
    MacUILib_clearScreen(); 
    for(int i = 0; i < myGM->getBoardSizeY(); i++){
        for(int j = 0; j < myGM->getBoardSizeX(); j++){
            
            drawn = false;
            
            for(int k = 0; k < playerBody->getSize(); k++){
                playerBody->getElement(tempBody, k);
                if(j == tempBody.x && i == tempBody.y){
                    MacUILib_printf("%c", tempBody.symbol);
                    drawn = true;
                    break;
                }
            }

            if(drawn) continue;

            if(i == 0 || i == myGM->getBoardSizeY() - 1 || j == 0 || j == myGM->getBoardSizeX() - 1){
                MacUILib_printf("%c", '#');
            }
            else if(j == tempFood.x && i == tempFood.y){
                MacUILib_printf("%c", tempFood.symbol);
            }
            else{
                MacUILib_printf("%c", ' ');
            }
        }
        MacUILib_printf("\n");


    }




    MacUILib_printf("BoardSize: %dx%d\nfood Pos: <%d, %d> + %c\nplayer Pos: <%d, %d> + %c\nScore: %d\n", 
                    myGM->getBoardSizeX(), 
                    myGM->getBoardSizeY(), 
                    tempBody.x, tempBody.y, tempBody.symbol,
                    tempFood.x, tempFood.y, tempFood.symbol,
                    myGM->getScore());
    

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    // all the required end-game actions
    MacUILib_clearScreen();    
  
    MacUILib_uninit();

    // deleting the gameMechanics object from the heap
    // do i do this inside another class or here?? : 
    delete myGM; 
    delete myPlayer;

}
