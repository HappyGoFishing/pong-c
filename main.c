#include <stdio.h>

#include "include/raylib.h"
#include "include/raymath.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

typedef struct
{
    int posX;
    int posY;
    int speed;
    int health;
    int width;
    int height;
} Paddle;

typedef struct
{
    int posX;
    int posY;
    float radius;
    int speedX;
    int speedY;
}Ball;

void DrawBall(Ball* ball)
{
    DrawCircle(ball->posX, ball->posY, ball->radius, WHITE);
}

void UpdateBall(Ball* ball)
{
    ball->posX += ball->speedX;
    ball->posY += ball->speedY;

    if (ball->posY + ball->radius >= GetScreenHeight() || ball->posY - ball->radius <= 0)
    {
        ball->speedY *= -1;
    }
    if (ball->posX  - 200  + ball->radius >= GetScreenHeight() || ball->posX - ball->radius <= 0)
    {
        ball->speedX *= -1;
    }
}

void CheckPaddleOutOfBounds(Paddle* paddle) {
    //Checks if paddle are out of range
    if (paddle->posY < -1) paddle->posY = 1;
            if (paddle->posY >= SCREEN_HEIGHT - 80) paddle->posY = SCREEN_HEIGHT - 80;
            if (paddle->posY < -1) paddle->posY = 1;
}

void CheckBallTouchingPaddle(Ball* ball, Paddle* paddle)
{

}
int main()
{
    Paddle Paddle1 = {SCREEN_WIDTH - 25, SCREEN_WIDTH/2, 6, 3, 20, 80};
    Paddle Paddle2 = {5, SCREEN_WIDTH/2, 6, 3, 20, 80};

    Ball Ball1 = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 20, 4, 4};

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "PongC");
    SetTargetFPS(60);
    while (!WindowShouldClose())
        {

            //Controls for player 1
            if (IsKeyDown(KEY_UP)) Paddle1.posY -= Paddle1.speed;
            if (IsKeyDown(KEY_DOWN)) Paddle1.posY += Paddle1.speed;
            //Controls for player 2
            if (IsKeyDown(KEY_W)) Paddle2.posY -= Paddle2.speed;
            if (IsKeyDown(KEY_S)) Paddle2.posY += Paddle2.speed;

            UpdateBall(&Ball1);
            printf("%d %d\n",Ball1.posX, Ball1.posY);

            CheckPaddleOutOfBounds(&Paddle1);
            CheckPaddleOutOfBounds(&Paddle2);

            BeginDrawing();



                ClearBackground(BLACK);
                DrawText("Kieran's Pong in C",40,20,30,YELLOW);
                //Player 1
                DrawRectangle(Paddle1.posX, Paddle1.posY, Paddle1.width, Paddle1.height, DARKBLUE);
                //Player 2
                DrawRectangle(Paddle2.posX, Paddle2.posY, Paddle2.width, Paddle2.height, DARKGREEN);
                //Ball
                DrawBall(&Ball1);

            EndDrawing();
        }
    CloseWindow();

}
