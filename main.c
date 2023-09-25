/********************************************************************************************************************
By Kieran Crossland, "finished" 20th May 2023, Licensed GPL3. Written in raylib. [https://github.com/raysan5/raylib]
This is the first real project that I've written and finished in C! ;)
********************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "include/raylib.h"
#include "config.h"
typedef struct {
    Vector2 pos;
    float speed;
    float width;
    float height;
    int score;
} Paddle;

typedef struct {
    Vector2 pos;
    float radius;
    Vector2 speed;
} Ball;

void draw_ball(Ball* ball) {
    DrawCircle(ball->pos.x, ball->pos.y, ball->radius, WHITE);
}

void update_ball_position(Ball* ball) {
    ball->pos.x += ball->speed.x * GetFrameTime();
    ball->pos.y += ball->speed.y * GetFrameTime();
}

void prevent_ball_out_of_bounds(Ball* ball) {
    if (ball->pos.y + ball->radius >= GetScreenHeight() || ball->pos.y - ball->radius <= 0) ball->speed.y *= -1.0;
    if (ball->pos.x  - 200 + ball->radius >= GetScreenHeight() || ball->pos.x - ball->radius <= 0) ball->speed.x *= -1.0;
}

void prevent_paddle_out_of_bounds(Paddle* paddle) {
     //Checks if a paddle's position exceeds the window bounds and stops it.
    if (paddle->pos.y < -1.0) paddle->pos.y = 1.0;
    if (paddle->pos.y >= WINDOW_HEIGHT - 80.0) paddle->pos.y = WINDOW_HEIGHT - 80.0;
}

void check_ball_touching_paddle(Ball* ball, Paddle* paddle) {
    if (CheckCollisionCircleRec((Vector2){ball->pos.x, ball->pos.y}, ball->radius, (Rectangle){paddle->pos.x, paddle->pos.y, paddle->width, paddle->height}))  ball->speed.x*= -1;
}
char* current_time_as_str() {
    time_t mytime = time(NULL);
    char * time_str = ctime(&mytime);
    time_str[strlen(time_str)-1] = '\0';
    return time_str;
}

int append_score_file(const int p1score, const int p2score) {
    char* time_str = current_time_as_str();

    FILE* fp_scorelog = fopen(SCORELOG_FILE, "a");
    if (fp_scorelog == NULL) {
        fprintf(stderr, "NULL file pointer :( \n");
        return 1;
    }
    fseek(fp_scorelog, 0, SEEK_END);
    long size = ftell(fp_scorelog);
    if (0 == size) fprintf(fp_scorelog, "Created on %s\n\n", time_str);

    if (p1score > p2score) fprintf(fp_scorelog, "%s g%i b%i green won\n", time_str, p1score, p2score);
    if (p1score < p2score) fprintf(fp_scorelog, "%s g%i b%i blue won\n", time_str, p1score, p2score);
    fclose(fp_scorelog);
    return 0;
}

void reset_game(Ball* ball, Paddle* paddle1, Paddle* paddle2) {
    ball->pos.x = WINDOW_WIDTH / 2.0;
    ball->pos.y = WINDOW_HEIGHT / 2.0;

    paddle1->pos.x = WINDOW_WIDTH - 25.0;
    paddle1->pos.y = WINDOW_WIDTH / 2.0 - 150.0;
    paddle1->score = 0;

    paddle2->pos.x = 5.0;
    paddle2->pos.y = WINDOW_WIDTH / 2.0 - 150.0;
    paddle2->score = 0;

    printf("Reset game\n");
}

int main(int argc, char** argv) {
    bool game_won = false;
    int winning_score = 3;
    
    if (argc > 1) {
        if (strcmp(argv[1], "--winning-score") == 0) {
        winning_score = atoi(argv[2]);
        }
    }
    printf("winning_score: %i\n", winning_score);

    Paddle player1 = {
        WINDOW_WIDTH - 25.0,
        WINDOW_WIDTH / 2.0 - 150.0,
        512.0,
        20.0,
        90.0,
        0
    };

    Paddle player2 = {
        5.0,
        WINDOW_WIDTH / 2.0 - 150.0,
        512.0,
        20.0,
        90.0,
        0
    };

    Ball ball1 = {
        WINDOW_WIDTH / 2.0,
        WINDOW_HEIGHT / 2.0,
        20,
        300,
        300,
    };

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Kieran's Pong in C (raylib)");
    SetWindowState(FLAG_VSYNC_HINT);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    Font ndsbios = LoadFontEx("assets/fonts/nintendo_ds_bios/Nintendo-DS-BIOS.ttf",36 ,0, 255);


    while (!WindowShouldClose()) {
            //Controls for player 1
            if (IsKeyDown(KEY_UP)) player1.pos.y -= player1.speed * GetFrameTime();
            if (IsKeyDown(KEY_DOWN)) player1.pos.y += player1.speed * GetFrameTime();
            //Controls for player 2
            if (IsKeyDown(KEY_W)) player2.pos.y -= player2.speed * GetFrameTime();
            if (IsKeyDown(KEY_S)) player2.pos.y += player2.speed * GetFrameTime();

            update_ball_position(&ball1);

            prevent_paddle_out_of_bounds(&player1);
            prevent_paddle_out_of_bounds(&player2);
            
            prevent_ball_out_of_bounds(&ball1);
            
            check_ball_touching_paddle(&ball1, &player1);
            check_ball_touching_paddle(&ball1, &player2);

            if (ball1.pos.x  - 200 + ball1.radius >= GetScreenHeight()) player1.score++;

            if (player1.score >= winning_score) {
                printf("Green Wins!\n");
                game_won = true;
                SetWindowTitle("Green Won the last match!");
            }

            if (ball1.pos.x - ball1.radius <= 0) {
                    player2.score++;
            }
            if (player2.score >= winning_score) {
                printf("Blue Wins!\n");
                game_won = true;
                SetWindowTitle("Blue Won the last match!");
            }

            BeginDrawing();
            if (game_won == false) {
                ClearBackground(BLACK);
                DrawTextEx(ndsbios, TextFormat("%i", player1.score), (Vector2){10.0f, 10.0f},(float)ndsbios.baseSize, 4, GREEN);
                DrawTextEx(ndsbios, TextFormat("%i", player2.score), (Vector2){WINDOW_WIDTH -25, 10.0f},(float)ndsbios.baseSize, 4, BLUE);

                DrawRectangle(player1.pos.x, player1.pos.y, player1.width, player1.height, DARKBLUE);
                DrawRectangle(player2.pos.x, player2.pos.y, player2.width, player2.height, DARKGREEN);
                
                draw_ball(&ball1);
            }
            else if (game_won == true) {
                if (append_score_file(player1.score, player2.score) == 1)  fprintf(stderr, "NULL file pointer :( \n");
                reset_game(&ball1, &player1, &player2);
                game_won = false;
            }
            EndDrawing();
        }
    CloseWindow();
    return 0;
}
