#include "raylib.h"
#include "Actor.h"
#include "Character.h"

class Enemy : public Actor
{
private:
    Character *target;
    float dps = 10.f;
    float radius = 25.f;
public:
    Enemy(Vector2 pos, Texture2D texIdle, Texture2D texRun);
    virtual void tick(float deltaTime) override;
    void setTarget(Character *target);
    float getDamage(){return dps;};
    virtual Vector2 getScreenPos() override;
};