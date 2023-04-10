#include <stdio.h>
#include "../include/raylib.h"
#include "../include/raymath.h"
#define VERSION "development"
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
    int centreX;
    int centreY;
    float radius;
    int speedX;
    int speedY;
}Ball;


void DrawBall(Ball* ball)
{
    DrawCircle(ball->centreX, ball->centreY, ball->radius, WHITE);
}
void UpdateBall(Ball* ball)
{
    ball->centreX += ball->speedX;
    ball->centreY += ball->speedY;

    if (ball->centreY + ball->radius >= GetScreenHeight() || ball->centreY - ball->radius <= 0)
    {
        ball->speedY *= -1;
    }
    if (ball->centreX  - 200  + ball->radius >= GetScreenHeight() || ball->centreX - ball->radius <= 0)
    {
        ball->speedX *= -1;
    }
}

void CheckPaddleOutOfBounds(Paddle* paddle) {
    //Checks if paddle are out of range. !DO NOT TOUCH, THIS BREAKS EASILY.
    if (paddle->posY < -1) paddle->posY = 1;
            if (paddle->posY >= SCREEN_HEIGHT - 80) paddle->posY = SCREEN_HEIGHT - 80;

            if (paddle->posY < -1) paddle->posY = 1;
            if (paddle->posY >= SCREEN_HEIGHT - 80) paddle->posY = SCREEN_HEIGHT - 80;
}
int main()
{

    //format: Paddle ExamplePaddle = { xPosition, yPosition, speed, health, width, height }
    Paddle Paddle1 = {SCREEN_WIDTH - 25, SCREEN_WIDTH/2, 6, 3, 20, 80};
    Paddle Paddle2 = {5, SCREEN_WIDTH/2, 6, 3, 20, 80};
    //format: Ball ExampleBall = { xCentre, yCentre, radius, speedX, speedY};
    Ball Ball1 = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 20, 4, 4};


    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "PongC");
    SetTargetFPS(60);


    while (!WindowShouldClose())
        {


            //Controls for player 1
            if (IsKeyDown(KEY_UP)) Paddle1.posY -= Paddle1.speed;
            if (IsKeyDown(KEY_DOWN)) Paddle1.posY += Paddle1.speed;
            //Controls for player2
            if (IsKeyDown(KEY_W)) Paddle2.posY -= Paddle2.speed;
            if (IsKeyDown(KEY_S)) Paddle2.posY += Paddle2.speed;


            UpdateBall(&Ball1);

            CheckPaddleOutOfBounds(&Paddle1);

            CheckPaddleOutOfBounds(&Paddle2);



            BeginDrawing();

                DrawFPS(SCREEN_WIDTH - 100, 20);

                ClearBackground(BLACK);
                DrawText("Kieran's Pong in C",20,20,30,WHITE);
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






























/*
int BallMoveRightX(Ball* ball)
{
    ball->speed = 2;

    if (ball->direction_is_left == false) {
            printf("BallMoveRight\n");
            ball->centreX += ball->speed;
            if (ball->centreX >= SCREEN_WIDTH - 40) {
                ball->direction_is_left = true;
            }
    }
}
int BallMoveLeftX(Ball* ball)
{
    ball->speed = 1;

    if (ball->direction_is_left == true) {
            printf("BallMoveLeft\n");
            ball->centreX -= ball->speed;
            if (ball->centreX -= ball->speed) {
                if (ball->centreX <=  40) {
                    ball->direction_is_left = false;
                }
            }
    }
}
*/
