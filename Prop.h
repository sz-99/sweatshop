#include "raylib.h"

class Prop
{
    public:
    Prop(Vector2 pos, Texture2D tex);
    void render(Vector2 playerPos);
    Rectangle getCollisionRec (Vector2 playerPos);

    private:
    Vector2 worldPos{};
    Texture2D texture{};
    float scale{1.0f};
};