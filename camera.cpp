#include "Camera.h"
#include "Player.h"
#include "Entity.h"

void UpdateCamera(Camera* camera, Entity* e) {
    // Center the camera on the player
    camera->Size = { 1920, 1080 };
    camera->Position.x = static_cast<int>(e->Movement.Position.x - ((camera->Size.x / 2) - (e->Player.Sprites.Body->BitSize * e->Player.Sprites.Body->Scale) / 2));
    camera->Position.y = static_cast<int>(e->Movement.Position.y - ((camera->Size.y / 2) - (e->Player.Sprites.Body->BitSize * e->Player.Sprites.Body->Scale) / 2));
}
