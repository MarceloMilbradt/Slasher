#include "raylib.h"
#include "Actor.h"
#ifndef CHARACTER_H
#define CHARACTER_H

class Character : public Actor
{
private:
    float windowWidth;
    float windowHeight;

    Texture2D weapon = LoadTexture("characters/weapon_sword.png");
    Rectangle weaponHitBox = {};
    float health = 100.f;
public:
    Character(int winWidth, int winHeight, Texture2D texIdle, Texture2D texRun);
    virtual void tick(float deltaTime) override;
    virtual Vector2 getScreenPos() override;
    Rectangle getWeaponHitBox() const { return weaponHitBox; };
    float getHealth() const { return health; };
    void takeDamage(float damage);

};
#endif