#include "pch.h"
#include "Game.h"

#include <chrono>
#include <iostream>

#include "graphics/Shader.h"
#include "graphics/InputLayout.h"
#include "Box.h"
#include "GioColor.h"
#include "GioVector.h"

extern void ExitGame() noexcept;

using namespace Microsoft;

Game::Game() noexcept
{
    startTime = std::chrono::steady_clock::now();
}

void Game::Initialize(HWND window, int width, int height)
{
    graphics = std::make_unique<Graphics>(window, width, height);
    graphics->Initialize();
    
    box = std::make_shared<Box>(*graphics, GioVector{1.f}, GioTransform{{0.f, 0.f, 5.f}, {0.f}});
    box->GetDrawable().AddBinding(graphics->GetStandardVertexShader());
    box->GetDrawable().AddBinding(graphics->GetStandardPixelShader());
    box->GetDrawable().AddBinding(graphics->GetStandardInputLayout());
}

void Game::Update()
{
    auto timeNow = std::chrono::steady_clock::now();
    std::chrono::duration<float> timeSinceStart = timeNow - startTime;
    std::chrono::duration<float> deltaTime = timeNow - previousFrameTime;

    POINT cursorPos{};
    GetCursorPos(&cursorPos);

    graphics->ClearBuffer({.7f, .9f, 1.f});
    
    std::tuple<UINT, UINT> outputDimensions = graphics->GetOutputDimensions();
    std::tuple<float,float> halfDimensions{std::get<0>(outputDimensions)/2.f, std::get<1>(outputDimensions)/2.f};
    float cursorX = cursorPos.x/ std::get<0>(halfDimensions) -1.f;
    float cursorY = 1-(cursorPos.y/std::get<1>(halfDimensions) - 1.f);

    auto& boxTransform = box->GetTransform();
    boxTransform.position = GioVector{cursorX, cursorY, boxTransform.position.z};
    boxTransform.rotation = GioVector{boxTransform.rotation.x, timeSinceStart.count(), timeSinceStart.count()};
    box->Draw(*graphics);

    graphics->SwapBuffers();
    
    previousFrameTime = std::chrono::steady_clock::now();
}
