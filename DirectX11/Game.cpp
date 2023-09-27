#include "pch.h"
#include "Game.h"

#include <chrono>
#include <iostream>
#include "ErrorHandling.h"

extern void ExitGame() noexcept;

using namespace Microsoft;

Game::Game() noexcept
{
    startTime = std::chrono::steady_clock::now();
}

void Game::Initialize(HWND window, int width, int height)
{
    graphics = std::make_unique<Graphics>(window, width, height);
}

void Game::Update()
{
    auto timeNow = std::chrono::steady_clock::now();
    std::chrono::duration<float> timeSinceStart = timeNow - startTime;
    std::chrono::duration<float> deltaTime = timeNow - previousFrameTime;

    graphics->Update(timeSinceStart.count(), deltaTime.count());
    
    previousFrameTime = std::chrono::steady_clock::now();
}
