//
//  gameStatus.h
//  Pong
//

#ifndef gameStatus_h
#define gameStatus_h

#include <stdio.h>
#include "main.h"

void moveBall(GameState *game);
void compMove(GameState *game);

void wallCollision(GameState *game);
void paddleCollision(GameState *game);

int outOfBounds(GameState *game);

#endif /* gameStatus_h */
