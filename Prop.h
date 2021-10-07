#include "raylib.h"
class Prop
{
private:
    Vector2 worldPos{};
    Texture2D texture{};
    Vector2 screenPos{};
    float scale = 4.f;

public:
    Prop(Vector2 pos, Texture2D tex);
    Rectangle getCollisionRec(Vector2 charPos);
    void render(Vector2 charPos);
};
