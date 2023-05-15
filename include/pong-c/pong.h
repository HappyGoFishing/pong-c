typedef struct
{
    bool use_ttf;
    bool use_audio;
} Config;

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
    Vector2 speed;
}Ball;
