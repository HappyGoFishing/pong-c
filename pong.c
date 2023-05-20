#include <stdio.h>
#include "include/raylib.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_FPS 144.0
#define WINNING_SCORE 5
typedef struct
{
    Vector2 pos;
    float speed;
    float width;
    float height;
    int score;
    char name[10]

} Paddle;

typedef struct
{
    Vector2 pos;
    float radius;
    Vector2 speed;
}Ball;

/*Beginning of code*/

void DrawBall(Ball* ball)
{
    DrawCircle(ball->pos.x, ball->pos.y, ball->radius, WHITE);
}

void UpdateBall(Ball* ball)
{
    ball->pos.x += ball->speed.x;
    ball->pos.y += ball->speed.y;

    if (ball->pos.y + ball->radius >= GetScreenHeight() || ball->pos.y - ball->radius <= 0)
    {
        ball->speed.y *= -1.0;
    }
    if (ball->pos.x  - 200 + ball->radius >= GetScreenHeight() || ball->pos.x - ball->radius <= 0)
    {
        ball->speed.x *= -1.0;
    }
}

void CheckPaddleOutOfBounds(Paddle* paddle)
{
    //Checks if a paddle's position exceeds the window bounds and stops it.
    if (paddle->pos.y < -1.0) paddle->pos.y = 1.0;
            if (paddle->pos.y >= WINDOW_HEIGHT - 80.0) paddle->pos.y = WINDOW_HEIGHT - 80.0;
            if (paddle->pos.y < -1) paddle->pos.y = 1;
}

void CheckBallTouchingPaddle(Ball* ball, Paddle* paddle)
{
    if (CheckCollisionCircleRec((Vector2){ball->pos.x, ball->pos.y}, ball->radius, (Rectangle){paddle->pos.x, paddle->pos.y, paddle->width, paddle->height}))
        {
            ball->speed.x*= -1;
        }
}


int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        printf("program arguemts: %s\n",argv[1]);
    }
    else
    {
        printf("program received no arguments\n");
    }

    Paddle player1 = {WINDOW_WIDTH - 25.0, WINDOW_WIDTH / 2.0 - 150.0, 4.0, 20.0, 90.0, 0, "Player 1"};
    Paddle player2 = {5.0, WINDOW_WIDTH / 2.0 - 150.0, 4.0, 20.0, 90.0, 0, "Player 2"};
    Ball ball1 = { /*Vector2 pos.x*/ WINDOW_WIDTH / 2.0, /*Vector2 pos.y*/ WINDOW_HEIGHT / 2.0, /*float radius*/ 20, /*int speedX*/ 2, /*int speedY*/ 2};

    const char msg[] ="Pong in C (raylib)";
    ;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, msg);
    Font ndsbios = LoadFontEx("assets/fonts/nintendo_ds_bios/Nintendo-DS-BIOS.ttf",36 ,0, 255);
    const int score_font_size = 30;
    SetTargetFPS(WINDOW_FPS);
    while (!WindowShouldClose())
        {
            //Controls for player 1
            if (IsKeyDown(KEY_UP)) player1.pos.y -= player1.speed;
            if (IsKeyDown(KEY_DOWN)) player1.pos.y += player1.speed;
            //Controls for player 2
            if (IsKeyDown(KEY_W)) player2.pos.y -= player2.speed;
            if (IsKeyDown(KEY_S)) player2.pos.y += player2.speed;

            UpdateBall(&ball1);

            CheckPaddleOutOfBounds(&player1);
            CheckPaddleOutOfBounds(&player2);

            CheckBallTouchingPaddle(&ball1, &player1);
            CheckBallTouchingPaddle(&ball1, &player2);

            //UpdateScore(&ball1, &player1);
            //UpdateScore(&ball1, &player2);

            if (ball1.pos.x  - 200 + ball1.radius >= GetScreenHeight())
            {
                    player1.score++;
            }
            if (player1.score >= WINNING_SCORE)
            {
                printf("Player 1 Wins!\n");
                return 0;
            }

            if (ball1.pos.x - ball1.radius <= 0)
            {
                    player2.score++;
            }
            if (player2.score >= WINNING_SCORE)
            {
                printf("Player 2 Wins!\n");
            }


            /*if (CheckCollisionCircleRec((Vector2){ball1.pos.x, ball1.pos.y}, ball1.radius, (Rectangle){player1.pos.x, player1.pos.y, player1.width, player1.height}))
            {
                printf("IT WORKED");
            }*/

            BeginDrawing();

                ClearBackground(BLACK);

                DrawTextEx(ndsbios, TextFormat("%i", player1.score), (Vector2){10.0f, 10.0f},(float)ndsbios.baseSize, 4, GREEN);
                DrawTextEx(ndsbios, TextFormat("%i", player2.score), (Vector2){WINDOW_WIDTH -25, 10.0f},(float)ndsbios.baseSize, 4, BLUE);

                DrawRectangle(player1.pos.x, player1.pos.y, player1.width, player1.height, DARKBLUE);
                DrawRectangle(player2.pos.x, player2.pos.y, player2.width, player2.height, DARKGREEN);

                DrawBall(&ball1);

            EndDrawing();
        }
    CloseWindow();
    return 0;
}
