#include "Editor.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_sdl2.h"
#include "imgui/backends/imgui_impl_sdlrenderer2.h"
#include <vector>
#include "MapTile.h"
#include "Game.h"

//

void MapEditor::RenderEditor(Game* game)
{
    int w, h;
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    SDL_GetRendererOutputSize(game->Renderer.MainRenderer, &w, &h);
    ImGui::SetNextWindowSize(ImVec2((float)w, (float)h), ImGuiCond_Always);
    ImGui::Begin("Map Editor");
    ImGui::End();
}




