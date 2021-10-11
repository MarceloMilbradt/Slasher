#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

int main()
{
    //dimencoes da window

    const int windowWidth{520};
    const int windowHeight{520};

    //abrir a window
    InitWindow(windowWidth, windowHeight, "Slasher");

    //-------MAPA------------
    Vector2 mapPos{0, 0};                                                // pos
    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png"); //texture
    const float mapScale = 4.f;

    //---------/MAPA----------

    //-------Personagem-------
    Character knight{
        windowWidth,
        windowHeight,
        LoadTexture("characters/knight_idle_spritesheet.png"),
        LoadTexture("characters/knight_run_spritesheet.png"),
    };
    //-------/Personagem-----

    //-------Prop-------
    Prop props[2]{
        Prop{
            Vector2{600.f, 300.f},
            LoadTexture("nature_tileset/Rock.png"),
        },
        Prop{
            Vector2{400.f, 500.f},
            LoadTexture("nature_tileset/Log.png"),
        },
    };
    //-------/Prop-----

    //ememy
    const int numEnemies = 2; //TODO
    Enemy goblin{
        Vector2{100.f, 200.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png"),
    };
    Enemy slime{
        Vector2{700.f, 500.f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png"),
    };
    Enemy *enemies[numEnemies];
    //for (int i = 0; i < numEnemies; i++)//TODO
    //{

    enemies[0] = &goblin;
    enemies[1] = &slime;
    for (Enemy *enemy : enemies)
    {
        enemy->setTarget(&knight);
    }

    //}

    //seta os frames a 60 fps
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        /* Pega o ∆T(delta T) (tempo desde o ultimo frame)
        *  garante que a aceleração será a mesma a cada frame, independente de framerate
        */
        const float dT = GetFrameTime();

        //começa a renderizar
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);
        //Desenha o mapa
        DrawTextureEx(map, mapPos, 0, mapScale, WHITE);

        //Draw Props
        for (auto prop : props)
        {
            prop.render(knight.getWorldPos());
        }

        knight.tick(dT);

        if (!knight.getAlive())
        {
            DrawText("Game Over!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else
        {
            std::string health = "Health:  ";
            health = health.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(health.c_str(), 55.f, 45.f, 40, RED);
        }

        Vector2 worldPos = knight.getWorldPos();
        //verifica limites do mapa
        if (worldPos.x < 0.f ||
            worldPos.y < 0.f ||
            worldPos.x > map.width * mapScale ||
            worldPos.y > map.height * mapScale)
        {
            knight.undoMovement();
        };

        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.getCollisionRec(worldPos), knight.getCollisionRec()))
            {
                knight.undoMovement();
                break;
            };
        };
        for (Enemy *enemy : enemies)
        {
            enemy->tick(dT);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                bool hit = CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponHitBox());
                enemy->setAlive(!hit);
            }
        }

        //finaliza a renderizacao
        EndDrawing();
    };

    UnloadTexture(map);
    CloseWindow();

    return 0;
}
