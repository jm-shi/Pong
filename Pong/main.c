//
//  main.c
//  Pong
//

#include <stdio.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include "main.h"
#include "gameStatus.h"

void initializeGame(GameState *game) {
    game->player1.x = 20;
    game->player1.y = SCREEN_HEIGHT/2 - PADDLE_HEIGHT/2;
    
    game->player2.x = SCREEN_WIDTH-40;
    game->player2.y = SCREEN_HEIGHT/2 - PADDLE_HEIGHT/2;
    
    game->gameBall.x = SCREEN_WIDTH/2 - SCREEN_WIDTH/3;
    game->gameBall.y = SCREEN_HEIGHT/2 - BALL_SIZE/2;
    game->gameBall.speedX = 15;
    game->gameBall.speedY = 7;
    game->gameBall.directionX = 1;
    game->gameBall.directionY = 1;
    game->gameBall.size = BALL_SIZE;
    
    game->gameScore.player1Score = 0;
    game->gameScore.player2Score = 0;
    
    game->font = TTF_OpenFont("OpenSans-Regular.ttf", 50);
}

void resetBall(GameState *game) {
    game->gameBall.x = SCREEN_WIDTH/2 - game->previousWinner*SCREEN_WIDTH/3;
    game->gameBall.y = SCREEN_HEIGHT/2 - BALL_SIZE/2;
    game->gameBall.speedX = 15;
    game->gameBall.speedY = 7;
    game->gameBall.directionX = game->previousWinner;
    game->gameBall.directionY = 1;
    game->gameBall.size = BALL_SIZE;
}

void drawScore(SDL_Renderer *renderer, GameState *game) {
    SDL_Surface *leftScoreSurface;
    SDL_Color white = {255,255,255};
    
    SDL_Rect rect1;
    rect1.x = SCREEN_WIDTH/2 - 80 - SCREEN_WIDTH/16;
    rect1.y = 0;
    rect1.w = SCREEN_WIDTH/16;
    rect1.h = SCREEN_HEIGHT/6;
    
    char text[20];
    sprintf(text, "%02d", game->gameScore.player1Score);
    
    leftScoreSurface = TTF_RenderText_Solid(game->font, text, white);
    SDL_Texture *leftScoreTexture = SDL_CreateTextureFromSurface(renderer, leftScoreSurface);
    SDL_RenderCopy(renderer, leftScoreTexture, NULL, &rect1);
    
    SDL_Surface *rightScoreSurface;
    SDL_Rect rect2;
    rect2.x = SCREEN_WIDTH/2 + 80;
    rect2.y = 0;
    rect2.w = SCREEN_WIDTH/16;
    rect2.h = SCREEN_HEIGHT/6;
    
    sprintf(text, "%02d", game->gameScore.player2Score);
    rightScoreSurface = TTF_RenderText_Solid(game->font, text, white);
    SDL_Texture *rightScoreTexture = SDL_CreateTextureFromSurface(renderer, rightScoreSurface);
    SDL_RenderCopy(renderer, rightScoreTexture, NULL, &rect2);
    
    
    SDL_DestroyTexture(leftScoreTexture);
    SDL_FreeSurface(leftScoreSurface);
    SDL_DestroyTexture(rightScoreTexture);
    SDL_FreeSurface(rightScoreSurface);
}


void render(SDL_Renderer *renderer, GameState *game)
{
    // Set background color to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    // Create red paddle for player 1
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect paddle1 = {
        game->player1.x,
        game->player1.y,
        PADDLE_WIDTH,
        PADDLE_HEIGHT
    };
    SDL_RenderFillRect(renderer, &paddle1);
    
    // Create yellow paddle for player 2
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_Rect paddle2 = {
        game->player2.x,
        game->player2.y,
        PADDLE_WIDTH,
        PADDLE_HEIGHT
    };
    SDL_RenderFillRect(renderer, &paddle2);
    
    // Create white ball
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect ball = {
        game->gameBall.x,
        game->gameBall.y,
        BALL_SIZE,
        BALL_SIZE
    };
    SDL_RenderFillRect(renderer, &ball);
    
    drawScore(renderer, game);
    
    // Draw white line in middle
    SDL_RenderDrawLine(renderer, SCREEN_WIDTH/2, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT);
    
}

int processEvents(SDL_Renderer *renderer, SDL_Window *window, GameState *game) {
    
    SDL_Event event;
    int running = 1;
    
    while (SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                running = 0;
                break;
            default:
                break;
        }
    }
    
    if (outOfBounds(game)) 
        resetBall(game);
    moveBall(game);
    compMove(game);
    
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_UP]) {
        if (game->player1.y-5 >= 0)
            game->player1.y -= 5;
    }
    else if(state[SDL_SCANCODE_DOWN]) {
        if (game->player1.y + PADDLE_HEIGHT + 5 <= SCREEN_HEIGHT)
            game->player1.y += 5;
    }
    
    return running;
}

int main(int argc, const char * argv[]) {
    
    GameState gameState;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    
    window = SDL_CreateWindow("Pong",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_OPENGL);
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    gameState.renderer = renderer;
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    initializeGame(&gameState);
    
    int running = 1;
    while (running) {
        running = processEvents(renderer, window, &gameState);
        render(renderer, &gameState);
        SDL_RenderPresent(renderer);
        SDL_Delay(25);
    }
    
    // Close and destroy the window
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    
    SDL_Quit();
    return 0;
    
}
