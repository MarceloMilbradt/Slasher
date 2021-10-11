#include "Enemy.h"
#include "raylib.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D texIdle, Texture2D texRun)
{
    worldPos = (pos);
    texture = (texIdle);
    textureIdle = (texIdle);
    textureRun = (texRun);
    width = (float)texture.width / (float)maxFrames;
    height = (float)texture.height;
    speed = 3.0f;
}
void Enemy::tick(float deltaTime)
{
    if (!getAlive())
        return;

    //get target
    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
    if (Vector2Length(velocity) < radius)
        velocity = {};
    Actor::tick(deltaTime);

    if (CheckCollisionRecs(getCollisionRec(), target->getCollisionRec()))
    {
        target->takeDamage(getDamage() * deltaTime);
    }
}
void Enemy::setTarget(Character *t)
{
    target = t;
};
Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(worldPos, target->getWorldPos());
}
