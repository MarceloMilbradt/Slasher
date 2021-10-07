#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
int main()
{
    //dimencoes da window

    const int windowWidth{520};
    const int windowHeight{520};

    //abrir a window
    InitWindow(windowWidth, windowHeight, "Slasher");

    //-------MAPA------------
    Vector2 mapPos{0, 0};                                       // pos
    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png"); //texture
    const float mapScale = 4.f;

    //---------/MAPA----------

    //-------Personagem-------
    Character knight{
        windowWidth,
        windowHeight,
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

        //verifica limites do mapa
        Vector2 worldPos = knight.getWorldPos();
        if (worldPos.x < 0.f ||
            worldPos.y < 0.f ||
            worldPos.x > map.width * mapScale ||
            worldPos.y > map.height * mapScale)
        {
            knight.undoMovement();
        };

        //finaliza a renderizacao
        EndDrawing();
    };

    UnloadTexture(map);
    CloseWindow();

    return 0;
}
