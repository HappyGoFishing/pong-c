#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_FPS 60.0
#define MAX_SCORE 5

typedef struct {
    bool is_won;
} GameState;

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
