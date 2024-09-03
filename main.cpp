#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

int main()
{
    int windowDimensions[2] {600, 600};
    InitWindow(windowDimensions[0], windowDimensions[1], "intern");

    //background texture
    Texture2D worldMap = LoadTexture("Top-Down_Characters/sweatshop_map.png");
    Vector2 mapPos{};
    float mapScale{4.f};

    Character susan {windowDimensions[0], windowDimensions[1]};

    Prop props[4]{
        Prop {Vector2{1500.f, 300.f}, LoadTexture("Top-Down_Characters/sewing_machine.png")},
        Prop {Vector2{700.f, 400.f}, LoadTexture("Top-Down_Characters/iron.png")},
        Prop {Vector2{900.f, 700.f}, LoadTexture("Top-Down_Characters/sewing_machine.png")},
        Prop {Vector2{350.f, 900.f}, LoadTexture("Top-Down_Characters/iron.png")}
    };

    Enemy ba{
        Vector2{600.f, 300.f},
        LoadTexture("Top-Down_Characters/ecorps_sprites.png"),
        LoadTexture("Top-Down_Characters/ecorps_sprites.png")
    };
    Enemy aw{
        Vector2{500.f, 500.f},
        LoadTexture("Top-Down_Characters/winterter_sprites.png"),
        LoadTexture("Top-Down_Characters/winterter_sprites.png")
    };
    Enemy corp{
        Vector2{1000.f, 800.f},
        LoadTexture("Top-Down_Characters/beebopvillie_sprites.png"),
        LoadTexture("Top-Down_Characters/beebopvillie_sprites.png")
    };

    Enemy* enemies[]{
        &ba,
        &aw,
        &corp
    };
    for (auto enemy: enemies)
    {
        enemy ->setTarget(&susan);
    }

    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(susan.getWorldPos(), -1.f);
        DrawTextureEx(worldMap, mapPos, 0.0, mapScale, WHITE);

        for (auto prop:props)
        {
            prop.render(susan.getWorldPos());
        }
        //check prop collision
        for (auto prop:props)
        {
            if (CheckCollisionRecs(susan.getCollisionRec(), prop.getCollisionRec(susan.getWorldPos())))
            {
                susan.undoMovement();
            }
        }

        //not alive
        if (!susan.getAlive())
        {
            DrawText("GAME OVER!!!", 55.f, 44.f, 40, RED);
        }
        //alive
        else
        {
            std::string susanHealth = "Health";
            susanHealth.append(std::to_string(susan.getHealth()), 0, 5);
            DrawText(susanHealth.c_str(), 55.f, 45.f, 40, RED);
        }

        susan.tick(GetFrameTime());


        if(susan.getWorldPos().x < 0.f ||
            susan.getWorldPos().y < 0.f ||
            susan.getWorldPos().x + windowDimensions[0] > worldMap.width * mapScale ||
            susan.getWorldPos().y + windowDimensions[1] > worldMap.height * mapScale)
            {
                susan.undoMovement();
            }


        //ba.tick(GetFrameTime());
        for (auto enemy: enemies)
        {
            enemy->tick(GetFrameTime());
        }

        //check collision 
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            for (auto enemy: enemies)
            {
                if (CheckCollisionRecs(enemy->getCollisionRec(), susan.getCollisionRec()))
                {
                    enemy->setAlive(false);
                }
            }
        }







        EndDrawing();
    }


}