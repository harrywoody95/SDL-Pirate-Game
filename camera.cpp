#include "Camera.h"
#include "Player.h"

void UpdateCamera(Camera* camera, Player* player) {
    // Center the camera on the player
    camera->Size = { 1920, 1080 };
    camera->Position.x = player->Sprite->Movement.Position.x - camera->Size.x / 2;
    camera->Position.y = player->Sprite->Movement.Position.y - camera->Size.y / 2;
}
