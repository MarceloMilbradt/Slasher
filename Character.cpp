#include "Character.h"
#include "raymath.h"
#include "raylib.h"

Character::Character(int winWidth, int winHeight, Texture2D texIdle, Texture2D texRun) : windowWidth(winWidth),
                                                                                         windowHeight(winHeight)
{

    texture = (texIdle);
    textureIdle = (texIdle);
    textureRun = (texRun);

    width = (float)texture.width / (float)maxFrames;
    height = (float)texture.height;
}
void Character::tick(float deltaTime)
{

    if (!getAlive())
        return;

    worldPosLastFrame = worldPos;

    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0;
    if (IsKeyDown(KEY_D))
        velocity.x += 1.0;
    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0;
    if (IsKeyDown(KEY_S))
        velocity.y += 1.0;

    Actor::tick(deltaTime);
    Vector2 origing{};
    Vector2 offset{};

    float rotation = 0;
    if (rightLeft > 0.f)
    {
        origing.x = 0.f;
        origing.y = weapon.height * scale;
        offset.x = 45.f;
        offset.y = 55.f;

        weaponHitBox.x = getScreenPos().x + offset.x;
        weaponHitBox.y = getScreenPos().y + offset.y - weapon.height * scale;

        weaponHitBox.height = weapon.height * scale;
        weaponHitBox.width = weapon.width * scale;

        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? 35.f : 0.f;
    }
    else
    {
        origing.x = weapon.width * scale;
        origing.y = weapon.height * scale;
        offset.x = 15.f;
        offset.y = 55.f;

        weaponHitBox.x = getScreenPos().x + offset.x - weapon.width * scale;
        weaponHitBox.y = getScreenPos().y + offset.y - weapon.height * scale;

        weaponHitBox.height = weapon.height * scale;
        weaponHitBox.width = weapon.width * scale;

        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? -35.f : 0.f;
    }

    //desenha a espada
    Rectangle source{0.f, 0.f, weapon.width * rightLeft, static_cast<float>(weapon.height)};
    Rectangle destination{getScreenPos().x + offset.x, getScreenPos().y + offset.y, weapon.width * scale, weapon.height * scale};
    DrawTexturePro(weapon, source, destination, origing, rotation, WHITE);

    DrawRectangleLines(
        weaponHitBox.x,
        weaponHitBox.y,
        weaponHitBox.width,
        weaponHitBox.height,
        RED);
}
Vector2 Character::getScreenPos()
{
    return Vector2{
        windowWidth / 2.0f - scale * (0.5f * width),
        windowHeight / 2.0f - scale * (0.5f * height),
    };
}

void Character::takeDamage(float damage)
{
    health -= damage;
    if (health <= 0.f)
    {
        setAlive(false);
    }
}