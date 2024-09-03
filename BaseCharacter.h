#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
#include "raylib.h"

class BaseCharacter
{
    public:
    BaseCharacter();
    Vector2 getWorldPos(){return worldPos;}
    virtual void tick(float deltaTime);
    virtual Vector2 getScreenPos() = 0;
    void undoMovement();
    Rectangle getCollisionRec();
    bool getAlive(){ return alive;}
    void setAlive(bool isAlive){alive = isAlive;}

    protected:
    Texture2D texture {LoadTexture("Top-Down_Characters/susan_idle_spritesheet.png")};
    Texture2D idle {LoadTexture("Top-Down_Characters/susan_idle_spritesheet.png")};
    Texture2D run {LoadTexture("Top-Down_Characters/susan_run_spritesheet.png")};
    //Vector2 screenPos;
    Vector2 worldPos{};
    float rightLeft{1.f};
    float runningTime{};
    int frame{};
    const int maxFrames{6};
    const float updateTime {1.f/12.f};
    float speed{4.f};
    float width{};
    float height{};
    Vector2 worldPosLastFrame{};
    float scale{2.f};
    Vector2 velocity{};

    private:
    bool alive{true};

};

#endif