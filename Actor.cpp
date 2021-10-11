#include "Actor.h"
#include "raymath.h"
#include "raylib.h"
#include "raymath.h"

Actor::Actor()
{
}
void Actor::tick(float deltaTime)
{
    if (!getAlive())
        return;
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
    Rectangle dest{getScreenPos().x, getScreenPos().y, scale * width, scale * height};

    if (Vector2Length(velocity) != 0.0)
    {
        Vector2 newPos = Vector2Normalize(velocity);
        newPos = Vector2Scale(newPos, speed);
        //set worldPos = worldPos + direction
        worldPos = Vector2Add(worldPos, newPos);

        rightLeft = velocity.x < 0.f ? -1.f : 1.f;
        texture = textureRun;
    }
    else
    {
        texture = textureIdle;
    }
    velocity = {};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}
void Actor::undoMovement()
{
    worldPos = worldPosLastFrame;
}
Rectangle Actor::getCollisionRec()
{
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
        width * scale,
        height * scale};
}
