#include "raylib.h"

class Character
{
private:
    Texture2D texture = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D textureIdle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D textureRun = LoadTexture("characters/knight_run_spritesheet.png");
    Vector2 screenPos{};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
    // 1 -> direita -1 -> esquerda
    float rightLeft = 1.f;
    float runningTime = 0.f;
    int frame = 0;
    const int maxFrames = 6;
    const float updateTime = 1.f / 12.f;
    const float speed = 4.f;
    
    float width=0.f;
    float height=0.f;
    float scale=4.0f;
public:
    Character(int winWidth, int winHeight);
    Vector2 getWorldPos()
    {
        return worldPos;
    };
    void tick(float deltaTime);
    void undoMovement();
};