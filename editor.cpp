#include "Editor.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_sdl2.h"
#include "imgui/backends/imgui_impl_sdlrenderer2.h"

void Editor::RenderEditor()
{
	ImGui::Begin("test");
	ImGui::Text("hello");
	ImGui::End();
}