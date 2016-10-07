//
//  main.h
//  Pong
//

#ifndef main_h
#define main_h

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define PADDLE_WIDTH 20
#define PADDLE_HEIGHT 120
#define BALL_SIZE 20

#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

typedef enum {
    PLAYER_ONE = -1,
    PLAYER_TWO = 1
} PreviousWinner;

typedef struct {
    int x, y;
} Paddle;

typedef struct {
    int x, y;
    int speedX, speedY;
    int directionX, directionY;
    int size;
} Ball;

typedef struct {
    int player1Score;
    int player2Score;
} Score;

typedef struct {
    Paddle player1, player2;
    Ball gameBall;
    Score gameScore;
    TTF_Font *font;
    SDL_Renderer *renderer;
    int previousWinner;
} GameState;

#endif /* main_h */
