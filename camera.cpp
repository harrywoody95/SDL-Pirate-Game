#include "Camera.h"
#include "Player.h"

void UpdateCamera(Camera* camera, Player* player) {
    // Center the camera on the player
    camera->Size = { 1920, 1080 };
    camera->Position.x = static_cast<int>(player->Sprites.Body->Movement.Position.x - ((camera->Size.x / 2) - (player->Sprites.Body->BitSize * player->Sprites.Body->Scale) / 2));
    camera->Position.y = static_cast<int>(player->Sprites.Body->Movement.Position.y - ((camera->Size.y / 2) - (player->Sprites.Body->BitSize * player->Sprites.Body->Scale) / 2));
}
