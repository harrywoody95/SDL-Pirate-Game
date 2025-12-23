#pragma once
#include <array>
#include "SDL.h"
#include "imgui/imgui.h"
#include <windows.h>
#include <psapi.h>
#pragma comment(lib, "Psapi.lib")
struct Game;
float GetMemoryMB();

static const int MAXHISTORY = 120;
struct ImGuiFPSGraph
{
    std::array<float, MAXHISTORY> fps;
    int offset = 0;
    bool filled = false;
    float Average();

    void Add(float value)
    {
        fps[offset] = value;
        offset = (offset + 1) % MAXHISTORY;
        if (offset == 0)
            filled = true;
    }

    float Latest() const
    {
        int idx = offset - 1;
        if (idx < 0) idx += MAXHISTORY;
        return fps[idx];
    }
};

struct ImGuiMemoryGraph {
    std::array<float, MAXHISTORY> mem = { 0 };
    int offset = 0;
    bool filled = false;

    void Add(float value) {
        mem[offset] = value;
        offset = (offset + 1) % MAXHISTORY;
        if (offset == 0) filled = true;
    }

    float Latest() const {
        return mem[(offset + MAXHISTORY - 1) % MAXHISTORY];
    }

    float Average() const {
        int count = filled ? MAXHISTORY : offset;
        if (count == 0) return 0.0f;
        float sum = 0.0f;
        for (int i = 0; i < count; ++i)
            sum += mem[i];
        return sum / count;
    }
};

struct Performance
{
    ImGuiFPSGraph FpsGraph;
    ImGuiMemoryGraph MemoryGraph;
    Uint64 PerfFreq = SDL_GetPerformanceFrequency();
    Uint64 LastCounter = SDL_GetPerformanceCounter();
    float Fps;

    void Update();
    void RenderPerformance(Game* game);
};
