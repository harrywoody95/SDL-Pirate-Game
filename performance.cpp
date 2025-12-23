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
    
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(850, 90), ImGuiCond_Always);

    ImGui::Begin("Performance", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

    ImGui::BeginChild("StatsColumn", ImVec2(200, 0), false);
    ImGui::Text("Entity Count: %d", game->EntityList.size());
    ImGui::Text("Sprite Count: %d", game->SpriteList.Sprites.size());
    ImGui::Text("Animation Count: %d", game->AnimationList.size());
    ImGui::EndChild();

    ImGui::SameLine();

    ImGui::BeginChild("FPSColumn", ImVec2(300, 0), false);
    ImGui::Text("FPS: %.1f", FpsGraph.Latest());
    ImGui::SameLine();
    ImGui::Text("Average: %.1f", FpsGraph.Average());

    ImGui::PushStyleColor(ImGuiCol_PlotLines, ImVec4(0.2f, 0.9f, 0.2f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.08f, 0.08f, 0.08f, 1.0f));
    ImGui::PlotLines(
        "FPSGraph",
        FpsGraph.fps.data(),
        FpsGraph.filled ? MAXHISTORY : FpsGraph.offset,
        FpsGraph.filled ? FpsGraph.offset : 0,
        nullptr,
        0.0f,
        512.0f,
        ImVec2(-1, 35)
    );
    ImGui::PopStyleColor(2);
    ImGui::EndChild();

    ImGui::SameLine();

    float MemoryInMB = GetMemoryMB();
    MemoryGraph.Add(MemoryInMB);

    ImGui::BeginChild("MemoryColumn", ImVec2(300, 0), false);
    ImGui::Text("Usage: %.1f MB", MemoryInMB);
    ImGui::SameLine();
    ImGui::Text("Average: %.1f MB", MemoryGraph.Average());

    ImGui::PushStyleColor(ImGuiCol_PlotLines, ImVec4(0.1f, 0.1f, 0.8f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.08f, 0.08f, 0.08f, 1.0f));
    ImGui::PlotLines(
        "MemoryGraph",
        MemoryGraph.mem.data(),
        MemoryGraph.filled ? MAXHISTORY : MemoryGraph.offset,
        MemoryGraph.filled ? MemoryGraph.offset : 0,
        nullptr,
        0.0f,
        512.0f,
        ImVec2(-1, 35)
    );
    ImGui::PopStyleColor(2);
    ImGui::EndChild();

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
