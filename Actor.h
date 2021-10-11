#include "raylib.h"
#ifndef ACTOR_H
#define ACTOR_H

class Actor
{
protected:
    Texture2D texture;
    Texture2D textureIdle;
    Texture2D textureRun;
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
    Vector2 velocity{};
    // 1 -> direita -1 -> esquerda
    float rightLeft = 1.f;
    float runningTime = 0.f;
    int frame = 0;
    const int maxFrames = 6;
    const float updateTime = 1.f / 12.f;
    float speed = 4.f;

    float width = 0.f;
    float height = 0.f;
    float scale = 4.0f;

public:
    Actor();
    Vector2 getWorldPos() { return worldPos; };
    virtual Vector2 getScreenPos() = 0;
    virtual void tick(float deltaTime);
    void undoMovement();
    Rectangle getCollisionRec();
    bool getAlive() { return alive; };
    void setAlive(bool isAlive) { alive = isAlive; };

private:
    bool alive = true;
};
#endif