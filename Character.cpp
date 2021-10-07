#include "Character.h"
#include "raymath.h"
#include "raylib.h"

Character::Character(int winWidth, int winHeight)
{

    screenPos = {
        static_cast<float>(winWidth) / 2.0f - scale * (0.5f * width),
        static_cast<float>(winHeight)  / 2.0f - scale * (0.5f * height),
    };

    width = (float)texture.width / (float)maxFrames;
    height = (float)texture.height;
}
void Character::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;

    Vector2 direction{0, 0};
    if (IsKeyDown(KEY_A))
        direction.x -= 1.0;
    if (IsKeyDown(KEY_D))
        direction.x += 1.0;
    if (IsKeyDown(KEY_W))
        direction.y -= 1.0;
    if (IsKeyDown(KEY_S))
        direction.y += 1.0;

    if (Vector2Length(direction) != 0.0)
    {
        Vector2 newPos = Vector2Normalize(direction);
        newPos = Vector2Scale(newPos, speed);
        //set worldPos = worldPos + direction
        worldPos = Vector2Add(worldPos, newPos);

        rightLeft = direction.x < 0.f ? -1.f : 1.f;
        texture = textureRun;
    }
    else
    {
        texture = textureIdle;
    }

    //Update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames)
            frame = 0;
    }

    Rectangle source{width * frame, 0.f, rightLeft * width, height};
    Rectangle dest{screenPos.x, screenPos.y, scale * width, scale * height};

    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}
void Character::undoMovement()
{
    worldPos = worldPosLastFrame;
}