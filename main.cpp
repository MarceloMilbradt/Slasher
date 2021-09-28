#include "raylib.h"
#include "raymath.h"

struct AnimData //struct que representa um objeto animavel
{
    Rectangle source; //hitbox da animacao
    Rectangle dest;
    Vector2 pos;       //posicao da hitbox
    int frame;         //frame da animacao
    float updateTime;  //intervalo de atualizacao da animacao (s)
    float runningTime; //tempo que a animacao esta rodando
    float maxFrames;   //maximos de frames da animacao
};

AnimData updateAnimation(AnimData data, float deltaT)
{
    //atualiza o running time
    data.runningTime += deltaT;
    if (data.runningTime >= data.updateTime)
    {
        data.runningTime = 0.0;
        //atualiza o frame de animacao
        data.source.x = data.frame * data.source.width;
        data.frame++;
        if (data.frame > data.maxFrames)
        {
            data.frame = 0;
        }
    }
    return data;
};

int main()
{
    //dimencoes da window
    const int windowDimensions[2] = {
        526, //width
        526, //height
    };
    //abrir a window
    InitWindow(windowDimensions[0], windowDimensions[1], "Slasher");

    //-------MAPA------------
    Vector2 mapPos{0, 0};                                       // pos
    const float mapSacale = 4.0f;                               // scale
    Texture2D map = LoadTexture("nature_tileset/main-map.png"); //texture
    //---------/MAPA----------

    //--------PERSONAGEM---------
    const float speed = 5.0f;
    Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png"); //texture
    Vector2 knightPos{
        (float)windowDimensions[0] / 2.0f - mapSacale * (0.5f * (float)knight.width / 6.0f),
        (float)windowDimensions[1] / 2.0f - mapSacale * (0.5f * (float)knight.height),
    };
    AnimData knightData{
        {
            //rectangle(hitbox)
            0.0f,                     // x
            0.0f,                     // y
            (float)knight.width / 6.0f, // width
            (float)knight.height     // height
        },
        {},
        {
            //vector2(posicao)
            (float)windowDimensions[0] / 2.0f - mapSacale * (0.5f * (float)knight.width / 6.0f),
            (float)windowDimensions[1] / 2.0f - mapSacale * (0.5f * (float)knight.height),

        },
        0,        // frame
        1.0f / 10.0f, //updateTime
        0.0f,        // running time
        6.0f,        //maximo de frames
    };

    //---------/PERSONAGEM-------

    //seta os frames a 60 fps
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        /* Pega o ∆T(delta T) (tempo desde o ultimo frame)
        *  garante que a aceleração será a mesma a cada frame, independente de framerate
        */
        //const float dT = GetFrameTime();

        //começa a renderizar
        BeginDrawing();
        ClearBackground(WHITE);

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
            //set mapPos = mapPos - direction
            mapPos = Vector2Subtract(mapPos, newPos);
        }

        DrawTextureEx(map, mapPos, 0, mapSacale, WHITE);

        //finaliza a renderizacao
        EndDrawing();
    }
    UnloadTexture(map);
    CloseWindow();

    return 0;
}
