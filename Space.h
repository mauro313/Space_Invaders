#ifndef SPACE_H_INCLUDED
#define SPACE_H_INCLUDED
#include "CharMatrix.h"

typedef struct _space{
    // battlefield;
    CharMatrix_t* battleSpace;
    
    // enemies variables.
    char normalEnemyToken;
    char shieldEnemyToken;
    char enemyLaserToken;
    int totalAmountOfEnemies; 
    int currentAmountOfEnemies; 
    int speedOfEnemies;
    bool directionEnemyRight;
    
    //player variables.
    char playerToken;
    char playerLaser;

    //generic variable
    char explosion;
}Space_t;

Space_t* space_newSpaceForBattle(int rows,int columns);

void space_displayBattlefield(Space_t* space);

bool space_movementOfEnemies(Space_t* space,int clock);

void space_movementOfEnemiesLasers(Space_t* space,int clock,int ratioOfEnemiesShoots);

void space_actualizesTheBattleField(Space_t* space,int clock,int* score);

void space_movementOfPlayer(Space_t* space,char command,int* counterToShoot);

int space_currentAmountOfEnemies(Space_t* space);

bool space_checkPlayerDestruction(Space_t* space);

void space_InitializationScreen(void);

void space_FinalizationScreen(Space_t* space,bool playerLose,int score,int clock);


#include "Space.c"

#endif //SPACE_H_INCLUDED