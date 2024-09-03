#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{
    width = texture.width/maxFrames;
    height = texture.height;
}

void BaseCharacter::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;

    // update animation frame
    runningTime += GetFrameTime();
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames)
            frame = 0;
    }


    // direction not 0 = chracter is moving
    if (Vector2Length(velocity) != 0.0)
    {
        // set worldPos = worldPos + direction
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));

        // facing direction
        velocity.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;

        texture = run;
    }
    // else = chracter is not moving
    else
    {
        texture = idle;
    }
    velocity = {};


    Rectangle source{frame * width, 0.f, rightLeft * width, height};
    Rectangle dest{getScreenPos().x, getScreenPos().y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.0, WHITE);
}

void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame; 
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
        width * scale,
        height * scale
    };
}