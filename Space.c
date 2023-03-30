#include <windows.h>
#include "Space.h"

/**
 * @brief creation of the new space of the specified size with the enemies and the player.
 * The recomended sizes are between rows(23-25) columns(40-44) for the well function of game.
 * M = normal enemies.
 * W = shield enemies.
 * v = enemies laser.
 * A = player.
 * ^ = player laser.
 * 
 * @param rows 
 * @param columns 
 * @return Space_t* 
 */
Space_t* space_newSpaceForBattle(int rows,int columns){
    Space_t* newSpace = (Space_t*)malloc(sizeof(Space_t));
    newSpace->battleSpace = charMatrix_New(rows,columns);
    newSpace->normalEnemyToken = 'M';
    newSpace->shieldEnemyToken = 'W';
    newSpace->enemyLaserToken = 'v';  
    newSpace->totalAmountOfEnemies = 0;
    newSpace->currentAmountOfEnemies = 0;
    newSpace->directionEnemyRight = true;
    newSpace->playerToken = 'A';
    newSpace->playerLaser = '^';
    newSpace->explosion = 'X'; 

    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            if(i%2!=0 && j%2==0 && i<7 && j>=5 && j<=columns-5){
                charMatrix_set(newSpace->battleSpace,i,j,newSpace->normalEnemyToken);
                newSpace->currentAmountOfEnemies++;
                newSpace->totalAmountOfEnemies++;
            }
            else{
                if(i%2!=0 && j%2==0 && i>=7 && i<9 && j>=5 && j<=columns-5){
                    charMatrix_set(newSpace->battleSpace,i,j,newSpace->shieldEnemyToken);
                    newSpace->currentAmountOfEnemies++;
                    newSpace->totalAmountOfEnemies++;
                }
                else{
                    charMatrix_set(newSpace->battleSpace,i,j,' ');
                }
            }
        }
    }
    charMatrix_exchange(newSpace->battleSpace,rows-1,columns/2,newSpace->playerToken);
    return newSpace;
}

/**
 * @brief diplay the current state of the space.
 * 
 * @param space 
 */
void space_displayBattlefield(Space_t* space){
    for(int i=0;i<charMatrix_getRows(space->battleSpace);i++){
        printf("|");
        for(int j=0;j<charMatrix_getColumns(space->battleSpace);j++){
            printf("%c",charMatrix_get(space->battleSpace,i,j));
        }
        printf("|\n");
    }
}

/**
 * @brief control the movement of the enemies on the board.
 * Return true if the enemies down to earth (that means the player lose) and false otherwise.
 * 
 * @param space 
 * @param clock 
 * @return true 
 * @return false 
 */
bool space_movementOfEnemies(Space_t* space,int clock){
    space->speedOfEnemies = 1 + 10 * space->currentAmountOfEnemies/space->totalAmountOfEnemies ;
    bool enemiesDownToEarth = false;
    bool goDown = false;
    int i=0;
    while(i<charMatrix_getRows(space->battleSpace) && charMatrix_get(space->battleSpace,i,0)!=space->normalEnemyToken
    && charMatrix_get(space->battleSpace,i,0)!=space->shieldEnemyToken){
        i++;
    }
    if(i<charMatrix_getRows(space->battleSpace)){
        space->directionEnemyRight = true;
        goDown = true;
    }
    i=0; 
    while(i<charMatrix_getRows(space->battleSpace) && charMatrix_get(space->battleSpace,i,charMatrix_getColumns(space->battleSpace)-1)!=space->normalEnemyToken
    && charMatrix_get(space->battleSpace,i,charMatrix_getColumns(space->battleSpace)-1) != space->shieldEnemyToken){
        i++;
    }
    if(i<charMatrix_getRows(space->battleSpace)){
        space->directionEnemyRight = false;
        goDown = true;
    }
    
    if(clock%space->speedOfEnemies == 0){
        if(space->directionEnemyRight){
            for(int j=charMatrix_getColumns(space->battleSpace);j>0;j--){
                for(int i=charMatrix_getRows(space->battleSpace)-1;i>0;i--){
                    if(goDown && (charMatrix_get(space->battleSpace,i-1,j-1)==space->normalEnemyToken
                    || charMatrix_get(space->battleSpace,i-1,j-1)==space->shieldEnemyToken)){
                        charMatrix_exchange(space->battleSpace,i,j,charMatrix_get(space->battleSpace,i-1,j-1));
                        charMatrix_exchange(space->battleSpace,i-1,j-1,' ');
                    }
                    else{
                        if(!goDown && (charMatrix_get(space->battleSpace,i,j-1)==space->normalEnemyToken
                        || charMatrix_get(space->battleSpace,i,j-1)==space->shieldEnemyToken)){
                            charMatrix_exchange(space->battleSpace,i,j,charMatrix_get(space->battleSpace,i,j-1));
                            charMatrix_exchange(space->battleSpace,i,j-1,' ');
                        }
                    }
                }

            }
        }
        else{
            for (int j = 0; j<charMatrix_getColumns(space->battleSpace)-1; j++) {
                for (int i = 1; i<charMatrix_getRows(space->battleSpace); i++) {
                    if (goDown && (charMatrix_get(space->battleSpace,i-1,j+1) == space->normalEnemyToken
                    || charMatrix_get(space->battleSpace,i-1,j+1) == space->shieldEnemyToken)){
                        charMatrix_exchange(space->battleSpace,i,j,charMatrix_get(space->battleSpace,i-1,j+1));
                        charMatrix_exchange(space->battleSpace,i-1,j+1,' ');
                    }
                    else{
                        if (!goDown && (charMatrix_get(space->battleSpace,i,j+1)== space->normalEnemyToken
                        || charMatrix_get(space->battleSpace,i,j+1) == space->shieldEnemyToken)) {
                            charMatrix_exchange(space->battleSpace,i,j,charMatrix_get(space->battleSpace,i,j+1));
                            charMatrix_exchange(space->battleSpace,i,j+1,' ');
                        }
                    } 
                }
            }
        }
        for (int j=0; j<charMatrix_getColumns(space->battleSpace); j++) {
            if (charMatrix_get(space->battleSpace,charMatrix_getRows(space->battleSpace)-1,j)==space->normalEnemyToken
            || charMatrix_get(space->battleSpace,charMatrix_getRows(space->battleSpace)-1,j)==space->shieldEnemyToken){
                enemiesDownToEarth = true;
            }
        }
    }
    return enemiesDownToEarth;
}

/**
 * @brief control the movement of the enemies lasers.
 * 
 * @param space 
 * @param clock the clock is a conuter for the bucle of game.
 * @param ratioOfEnemiesShoots how often the enemies shoot.the smaller the ratio more often the enemies shoot.
 * (this ratio must be a positive number higher tha zero). 
 */
void space_movementOfEnemiesLasers(Space_t* space,int clock,int ratioOfEnemiesShoots){
    bool enemiesReadyToshoot = false;
    for(int j=0;j<charMatrix_getColumns(space->battleSpace);j++){
        for(int i=charMatrix_getRows(space->battleSpace)-1;i>=0;i--){
            if(clock%2==0 && i<charMatrix_getRows(space->battleSpace)-1 && charMatrix_get(space->battleSpace,i,j)==space->enemyLaserToken
            && (charMatrix_get(space->battleSpace,i+1,j)!=space->normalEnemyToken
            && charMatrix_get(space->battleSpace,i+1,j)!=space->shieldEnemyToken)){
                charMatrix_exchange(space->battleSpace,i+1,j,space->enemyLaserToken);
                charMatrix_exchange(space->battleSpace,i,j,' ');
            }
            else{
                if(clock%2==0 && i<charMatrix_getRows(space->battleSpace)-1 && charMatrix_get(space->battleSpace,i,j)==space->enemyLaserToken &&
                (charMatrix_get(space->battleSpace,i+1,j)==space->normalEnemyToken
                || charMatrix_get(space->battleSpace,i+1,j)==space->shieldEnemyToken)){
                    charMatrix_exchange(space->battleSpace,i,j,' ');
                }
                else{
                    if((clock+1)%2==0 && i==charMatrix_getRows(space->battleSpace)-1 && charMatrix_get(space->battleSpace,i,j)==space->enemyLaserToken){
                        charMatrix_exchange(space->battleSpace,i,j,' ');
                    }
                }
            }
        }
    }
    
    for(int j=0;j<charMatrix_getColumns(space->battleSpace);j++){
        for(int i=0;i<charMatrix_getRows(space->battleSpace);i++){
            if(clock%ratioOfEnemiesShoots==0 && (charMatrix_get(space->battleSpace,i,j)==space->normalEnemyToken
            || charMatrix_get(space->battleSpace,i,j)==space->shieldEnemyToken) && (rand()%15)>13 &&
            charMatrix_get(space->battleSpace,i+1,j)!=space->playerLaser){
                int k = i+1;
                while(k<charMatrix_getRows(space->battleSpace) && (charMatrix_get(space->battleSpace,k,j)!=space->normalEnemyToken
                && charMatrix_get(space->battleSpace,k,j)!=space->shieldEnemyToken)){
                    k++;
                }
                if(k == charMatrix_getRows(space->battleSpace)){
                    enemiesReadyToshoot = true;
                }
                if(enemiesReadyToshoot){
                    charMatrix_exchange(space->battleSpace,i+1,j,space->enemyLaserToken);
                }
            }

        }
    }
}

/**
 * @brief actualizes the space. This means the enemies that are drestroyed, the advance of the player´s
 * lasers or eventual collitions of lasers.
 * 
 * @param space 
 * @param clock 
 * @param score 
 */
void space_actualizesTheBattleField(Space_t* space,int clock,int* score){
    for(int j=0;j<charMatrix_getColumns(space->battleSpace);j++){
        for(int i=0;i<charMatrix_getRows(space->battleSpace);i++){
            if (i>0 &&charMatrix_get(space->battleSpace,i,j)==space->playerLaser && 
            charMatrix_get(space->battleSpace,i-1,j)==space->normalEnemyToken){
                charMatrix_exchange(space->battleSpace,i,j,' ');
                charMatrix_exchange(space->battleSpace,i-1,j,space->explosion);
                space->currentAmountOfEnemies--;
                *score += 50;
            }
            else if (i>0 && charMatrix_get(space->battleSpace,i,j)==space->playerLaser && 
                 charMatrix_get(space->battleSpace,i-1,j)==space->shieldEnemyToken) {
                     charMatrix_exchange(space->battleSpace,i,j,' ');
                     charMatrix_exchange(space->battleSpace,i-1,j,space->normalEnemyToken);
                     *score += 70;
                 }
                 else if (i>0 && charMatrix_get(space->battleSpace,i,j)==space->playerLaser && 
                      charMatrix_get(space->battleSpace,i-1,j)==space->enemyLaserToken) {
                          charMatrix_exchange(space->battleSpace,i,j,' ');
                      }
                       else if (charMatrix_get(space->battleSpace,i,j)==space->explosion) {
                               charMatrix_exchange(space->battleSpace,i,j,' ');
                           }
                            else if (i>0 && charMatrix_get(space->battleSpace,i,j)==space->playerLaser && 
                                     charMatrix_get(space->battleSpace,i-1,j)!=space->enemyLaserToken) {
                                         charMatrix_exchange(space->battleSpace,i,j,' ');
                                         charMatrix_exchange(space->battleSpace,i-1,j,space->playerLaser);
                                }
                                else if(i==0 && charMatrix_get(space->battleSpace,i,j)==space->playerLaser){
                                        charMatrix_exchange(space->battleSpace,i,j,' ');
                                    }
                                
        }
    }
}

/**
 * @brief control the player movement (left, rigth or shoot).
 * 
 * @param space 
 * @param command '4' for left '6' for right and 's' for shoot.
 * @param counterToShoot is a counter same as the clock.
 */
void space_movementOfPlayer(Space_t* space,char command,int* counterToShoot){
    if(command == '4'){
        for(int j=0;j<charMatrix_getColumns(space->battleSpace)-1;j++){
            if(charMatrix_get(space->battleSpace,charMatrix_getRows(space->battleSpace)-1,j+1)==space->playerToken){
                charMatrix_exchange(space->battleSpace,charMatrix_getRows(space->battleSpace)-1,j,space->playerToken);
                charMatrix_exchange(space->battleSpace,charMatrix_getRows(space->battleSpace)-1,j+1,' ');
            }
        }
    }
    else{
        if(command == '6'){
            for(int j=charMatrix_getColumns(space->battleSpace)-1;j>0;j--){
                if(charMatrix_get(space->battleSpace,charMatrix_getRows(space->battleSpace)-1,j-1)==space->playerToken){
                    charMatrix_exchange(space->battleSpace,charMatrix_getRows(space->battleSpace)-1,j,space->playerToken);
                    charMatrix_exchange(space->battleSpace,charMatrix_getRows(space->battleSpace)-1,j-1,' ');
                }
            }
        }
        else{
            if(command == 's' && *counterToShoot>=3){
                for(int j=0;j<charMatrix_getColumns(space->battleSpace);j++){
                    if(charMatrix_get(space->battleSpace,charMatrix_getRows(space->battleSpace)-1,j)==space->playerToken){
                        charMatrix_exchange(space->battleSpace,charMatrix_getRows(space->battleSpace)-2,j,space->playerLaser);
                        *counterToShoot = 0;
                    }
                }                                
            }
        }
    }
}

/**
 * @brief return the current amount of enemies.
 * 
 * @param space 
 * @return int 
 */
int space_currentAmountOfEnemies(Space_t* space){
    return space->currentAmountOfEnemies;
}

/**
 * @brief initialization screen. Is a preentation for the game.
 * 
 */
void space_InitializationScreen(void){
    printf("\n\n                Welcome soldier! \n \n \n \n");
    Sleep(1000);
    printf("Brave the COMMAND PROMPT INVADERS and come back a hero. \n \n \n \n");
    Sleep(2500);
    printf("       The operating system is depending upon you. \n \n \n \n");
    Sleep(2500);
    printf("                      Good luck.\n\n\n\n");
    Sleep(1000);
    printf("                Press any key to start.");
    getch();
}

/**
 * @brief finalization screen. Message for the end of the game. Depend if the player lose or win.
 * 
 * @param space 
 * @param playerLose 
 * @param score 
 * @param clock 
 */
void space_FinalizationScreen(Space_t* space,bool playerLose,int score,int clock){
  if(!playerLose){
    printf("\n \n \n \n \n \n               CONGRATULATIONS! \n \n \n \n \n");
    Sleep(1000);
    printf("\n \n               Score: %d", score);
    Sleep(1000);
    int bonus = space_currentAmountOfEnemies(space)*20 - clock;
    printf("\n \n               Bonus: %d", bonus);
    Sleep(1000);
    printf("\n \n               Total Score: %d", score + bonus);
    printf("\n \n \n \n               Good job");
    Sleep(1000);
    printf(", Savior of Earth.");
    Sleep(1000);
    getch();
  }
  else{
    printf("\n \n \n \n \n \n                You have failed.");
    Sleep(1000);
    printf("\n \n \n \n \n \n              The world is doomed.");
    Sleep(1000);
    printf("\n \n               Final Score: %d", score);
    getch();
  }
}

/**
 * @brief check if the player was destroy.Return true if was destroyed and false otherwise.
 * 
 * @param space 
 * @return true 
 * @return false 
 */
bool space_checkPlayerDestruction(Space_t* space){
    bool playerLose = false;
    for(int j=0;j<charMatrix_getColumns(space->battleSpace);j++){
        if(charMatrix_get(space->battleSpace,charMatrix_getRows(space->battleSpace)-2,j)==space->enemyLaserToken
        && charMatrix_get(space->battleSpace,charMatrix_getRows(space->battleSpace)-1,j)==space->playerToken){
            playerLose = true;
        }
    }
    return playerLose;
}