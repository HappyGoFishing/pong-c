#include <stdio.h>

#include "include/raylib.h"
#include "include/raymath.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_FPS 144

typedef struct
{
    Vector2 pos;
    float speed;
    float width;
    float height;

} Paddle;

typedef struct
{
    Vector2 pos;
    float radius;
    int speedX;
    int speedY;
}Ball;

void DrawBall(Ball* ball)
{
    DrawCircle(ball->pos.x, ball->pos.y, ball->radius, WHITE);
}

void UpdateBall(Ball* ball)
{
    ball->pos.x += ball->speedX;
    ball->pos.y += ball->speedY;

    if (ball->pos.y + ball->radius >= GetScreenHeight() || ball->pos.y - ball->radius <= 0) {
        ball->speedY *= -1;
    }
    if (ball->pos.x  - 200  + ball->radius >= GetScreenHeight() || ball->pos.x - ball->radius <= 0) {
        ball->speedX *= -1;
    }
}

void CheckPaddleOutOfBounds(Paddle* paddle) {
    //Checks if paddle are out of range
    if (paddle->pos.y < -1) paddle->pos.y = 1;
            if (paddle->pos.y >= WINDOW_HEIGHT - 80) paddle->pos.y = WINDOW_HEIGHT - 80;
            if (paddle->pos.y < -1) paddle->pos.y = 1;
}

int main()
{
     //Vector2 pos.x/ /*Vector2 pos.y/ /float speed/ /float width/ /float height/
    Paddle Paddle1 = {WINDOW_WIDTH - 25.0, WINDOW_WIDTH/2.0 - 150, 4, 20, 90};
    Paddle Paddle2 = {5.0, WINDOW_WIDTH/2.0 - 150, 4, 20, 90};

    Ball Ball1 = { /*Vector2 pos.x*/ WINDOW_WIDTH / 2.0, /*Vector2 pos.y*/ WINDOW_HEIGHT / 2.0, /*float radius*/ 20, /*int speedX*/ 2, /*int speedY*/ 2};

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "pong-c");

    SetTargetFPS(144);

    while (!WindowShouldClose())
        {

            //Controls for player 1
            if (IsKeyDown(KEY_UP)) Paddle1.pos.y -= Paddle1.speed;
            if (IsKeyDown(KEY_DOWN)) Paddle1.pos.y += Paddle1.speed;
            //Controls for player 2
            if (IsKeyDown(KEY_W)) Paddle2.pos.y -= Paddle2.speed;
            if (IsKeyDown(KEY_S)) Paddle2.pos.y += Paddle2.speed;


            UpdateBall(&Ball1);
            /*if (CheckCollisionCircleRec(Vector2{Ball1.posX, Ball1.pos.y}, Ball1.radius, Rectangle{Paddle1.pos.x, Paddle1.pos.y, Paddle1.width, Paddle1.height})) {
                    printf("yes");
            }*/

            CheckPaddleOutOfBounds(&Paddle1);
            CheckPaddleOutOfBounds(&Paddle2);

            BeginDrawing();

                ClearBackground(BLACK);
                DrawText("Pong in C",40,20,30,YELLOW);
                DrawRectangle(Paddle1.pos.x, Paddle1.pos.y, Paddle1.width, Paddle1.height, DARKBLUE);
                DrawRectangle(Paddle2.pos.x, Paddle2.pos.y, Paddle2.width, Paddle2.height, DARKGREEN);
                DrawBall(&Ball1);

            EndDrawing();
        }
    CloseWindow();
    printf("Goodbye\n");

}
