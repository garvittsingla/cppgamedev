#include <raylib.h>
#include <cmath>
#include <iostream>
#include <imgui.h>
#include <rlImGui.h>
#include <gameMain.h>
#include <asserts.h>

int main() {


    InitWindow(800, 600, "Fractal Canopy - Raylib");
    SetTargetFPS(240);
    if (!initGame()) {
        std::cout << "Failed to initialize!" << std::endl;
        return 0;
    }
    rlImGuiSetup(true);
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.FontGlobalScale = 2;
    ImGui::StyleColorsClassic();
    std::cout << "working";

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        rlImGuiBegin();
        ImGui::PushStyleColor(ImGuiCol_WindowBg,{});
        ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg,{});
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
        ImGui::PopStyleColor(2);

        if (!updateGame()) {
            CloseWindow();
        }

        rlImGuiEnd();

        EndDrawing();

    }
    rlImGuiShutdown();

    CloseWindow();
    closeGame();
}