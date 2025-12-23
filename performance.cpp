#include "Performance.h"
#include "Game.h"

float ImGuiFPSGraph::Average()
{
    int Count = filled ? MAXHISTORY : offset;
    if (Count == 0)
    {
        return 0.0f;
    }

    float Sum = 0.0f;
    for (int i = 0; i < Count; ++i)
        Sum += fps[i];

    return Sum / Count;
}

void Performance::RenderPerformance(Game* game)
{
    ImGui::SetNextWindowSize(ImVec2(500, 500), ImGuiCond_Always);

    ImGui::Begin("Performance");
    ImGui::Text("FPS: %.1f", FpsGraph.Latest());
    ImGui::Text("Avg: %.1f", FpsGraph.Average());

    ImGui::PushStyleColor(ImGuiCol_PlotLines, ImVec4(0.2f, 0.9f, 0.2f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.08f, 0.08f, 0.08f, 1.0f));

    ImGui::PlotLines(
        "##FPS",
        FpsGraph.fps.data(),
        FpsGraph.filled ? MAXHISTORY : FpsGraph.offset,
        FpsGraph.filled ? FpsGraph.offset : 0,
        nullptr,
        0.0f,
        144.0f,
        ImVec2(-1, 150)
    );

    ImGui::PopStyleColor(2);

    float memMB = GetMemoryMB();
    MemoryGraph.Add(memMB);

    ImGui::Text("Memory: %.1f MB", memMB);
    ImGui::Text("Avg: %.1f MB", MemoryGraph.Average());

    ImGui::PushStyleColor(ImGuiCol_PlotLines, ImVec4(0.9f, 0.2f, 0.2f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.08f, 0.08f, 0.08f, 1.0f));

    ImGui::PlotLines(
        "##Memory",
        MemoryGraph.mem.data(),
        MemoryGraph.filled ? MAXHISTORY : MemoryGraph.offset,
        MemoryGraph.filled ? MemoryGraph.offset : 0,
        nullptr,
        0.0f,
        512.0f, // max memory scale (adjust as needed)
        ImVec2(-1, 150)
    );
    ImGui::Text("Entity Count: %d", game->EntityList.size());
    ImGui::Text("Sprite Count: %d", game->SpriteList.Sprites.size());
    ImGui::Text("Animation Count: %d", game->AnimationList.size());
    ImGui::PopStyleColor(2);

    ImGui::End();
}

void Performance::Update() 
{

    Uint64 currentCounter = SDL_GetPerformanceCounter();
    double deltaTime = (double)(currentCounter - LastCounter) / (double)PerfFreq;
    LastCounter = currentCounter;

    Fps = (deltaTime > 0.0) ? (float)(1.0 / deltaTime) : 0.0f;
    FpsGraph.Add(Fps);
};

float GetMemoryMB()
{
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
        return pmc.WorkingSetSize / (1024.0f * 1024.0f);
    }
    return 0.0f;
}
