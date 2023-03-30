#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "CharMatrix.h"
#include "Space.h"



int main(){  
  // main code.
  printf("\n\n");  
  srand(time(NULL)); 
  space_InitializationScreen();
  Space_t* world = space_newSpaceForBattle(25,40);
  int score = 0;
  // the clock must initializes in one (this cannot be zero).
  int clock = 1;
  int counterToShoot = 0;
  // variable to control the loop of the game. 
  bool playerLose = false;

  // the game continue until the player lose or eliminates the enemies.
  while(!playerLose && space_currentAmountOfEnemies(world)>0){
    system("cls");
    space_displayBattlefield(world);
    printf("    SCORE: %d  ",score);
    space_movementOfEnemiesLasers(world,clock,5);
    space_actualizesTheBattleField(world,clock,&score);
    playerLose = space_movementOfEnemies(world,clock);
    if(kbhit()){
        space_movementOfPlayer(world,getch(),&counterToShoot);
    }
    if(!playerLose){
      playerLose = space_checkPlayerDestruction(world);
    }
    clock++;
    counterToShoot++;
    Sleep(50);
  }
  system("cls");
  space_displayBattlefield(world);
  Sleep(2000);
  system("cls");
  space_FinalizationScreen(world,playerLose,score,clock);
  return 0;    
}


