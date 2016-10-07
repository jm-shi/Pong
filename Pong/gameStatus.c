//
//  gameStatus.c
//  Pong
//

#include "gameStatus.h"

void moveBall(GameState *game) {
    
    int speedX = game->gameBall.speedX;
    int speedY = game->gameBall.speedY;
    
    wallCollision(game);
    paddleCollision(game);
    
    game->gameBall.x += speedX*game->gameBall.directionX;
    game->gameBall.y += speedY*game->gameBall.directionY;
    
}

void compMove(GameState *game) {
    
    if (game->gameBall.y >= game->player2.y) {
        if (game->player2.y + PADDLE_HEIGHT + 5 <= SCREEN_HEIGHT)
            game->player2.y += 5;
    }
    else {
        if (game->player2.y - 5 >= 0)
            game->player2.y -= 5;
    }
}

void wallCollision(GameState *game) {
    int ballY = game->gameBall.y;
    if (ballY <= 0 || ballY+BALL_SIZE >= SCREEN_HEIGHT)
        game->gameBall.directionY *= -1;
}

void paddleCollision(GameState *game) {
    int paddle1X = game->player1.x;
    int paddle1Y = game->player1.y;
    int paddle2X = game->player2.x;
    int paddle2Y = game->player2.y;
    int ballX = game->gameBall.x;
    int ballY = game->gameBall.y;
    
    if (ballX <= paddle1X+PADDLE_WIDTH && ballX >= paddle1X) {
        if (ballY + BALL_SIZE >= paddle1Y && ballY <= paddle1Y+PADDLE_HEIGHT) {
            game->gameBall.directionX *= -1;
        }
    }
    
    if (ballX >= paddle2X-PADDLE_WIDTH && ballX <= paddle2X) {
        if (ballY + BALL_SIZE >= paddle2Y && ballY <= paddle2Y+PADDLE_HEIGHT) {
            game->gameBall.directionX *= -1;
        }
    }
}

int outOfBounds(GameState *game) {
    int ballX = game->gameBall.x;
    
    if (ballX <= -SCREEN_WIDTH/2) {
        game->gameScore.player2Score += 1;
        game->previousWinner = PLAYER_TWO;
        return 1;
    }
    if (ballX >= 3*SCREEN_WIDTH/2) {
        game->gameScore.player1Score += 1;
        game->previousWinner = PLAYER_ONE;
        return 1;
    }
    
    return 0;
}
