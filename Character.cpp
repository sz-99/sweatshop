#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight) : windowWidth(winWidth),
                                                    windowHeight(winHeight)
{
    width = texture.width / maxFrames;
    height = texture.height;
}

Vector2 Character::getScreenPos()
{
    return Vector2{
        static_cast<float>(static_cast<float>(windowWidth) / 2 - scale * 0.5f * static_cast<float>(width)),
        static_cast<float>(static_cast<float>(windowHeight) / 2 - scale * 0.5f * static_cast<float>(height))};
}

void Character::tick(float deltaTime)
{
    if(!getAlive()) return;

    // Vector2 direction{};
    if (IsKeyDown(KEY_D))
        velocity.x += 1.0;
    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0;
    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0;
    if (IsKeyDown(KEY_S))
        velocity.y += 1.0;

    BaseCharacter::tick(deltaTime);

    // origin of sword
    Vector2 origin{};
    Vector2 offset{};
    float rotation{};
    if (rightLeft > 0.f)
    {
        origin = {0.f, weapon.height * scale};
        offset = {55.f, 100.f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale};
        rotation = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? 35.f : 0.f;
    }
    else
    {
        origin = {weapon.width * scale, weapon.height * scale};
        offset = {70.f, 100.f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x - weapon.width * scale,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale};
        rotation = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? -35.f : 0.f;
    }

    // draw sword - source rectangle, dest recrtangle, drawtexturepro
    Rectangle source{0.f, 0.f, static_cast<float>(weapon.width) * rightLeft, static_cast<float>(weapon.height)};
    Rectangle dest{getScreenPos().x + offset.x, getScreenPos().y + offset.y, weapon.width * scale, weapon.height * scale};
    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);
}

void Character::takeDamage(float damage)
{
    health -= damage;
    if (health <=0) setAlive(false);
}