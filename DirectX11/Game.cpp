#include "pch.h"
#include "Game.h"

#include <chrono>
#include <iostream>

#include "graphics/Shader.h"
#include "graphics/InputLayout.h"
#include "Box.h"
#include "GioColor.h"
#include "GioVector.h"
#include "Monkey.h"

extern void ExitGame() noexcept;

using namespace Microsoft;

Game::Game() noexcept
{
    startTime = std::chrono::steady_clock::now();
}

void Game::Initialize(HWND window, int width, int height, int tickRate)
{
    graphics = std::make_unique<Graphics>(window, width, height);
    graphics->Initialize();

    entities =
        {
        std::make_shared<Box>(*graphics, GioVector{1.f}, GioTransform{{0.f, 0.f, 5.f}, {0.f}}),
        std::make_shared<Box>(*graphics, GioVector{1.f}, GioTransform{{-2.f, 0.f, 5.f}, {0.f}}),
        std::make_shared<Monkey>(*graphics, GioTransform{ {2.f, 0.f, 5.f}, {0.f} })
    };
    
    minDeltaTime = 1.f/static_cast<float>(tickRate);
}

void Game::Update()
{
    auto timeNow = std::chrono::steady_clock::now();
    std::chrono::duration<float> timeSinceStart = timeNow - startTime;
    std::chrono::duration<float> deltaTime = timeNow - previousFrameTime;

    if(deltaTime.count() < minDeltaTime)
    {
        return;
    }
    
    POINT cursorPos{};
    GetCursorPos(&cursorPos);

    graphics->ClearBuffer({.7f, .9f, 1.f});
    
    float positionOffset{0.f};
    float rotationOffset{0.f};
    
    float change{1.f};
    for (std::shared_ptr<Entity>& entity : entities)
    {
        positionOffset = std::sin(timeSinceStart.count() + change);
        change += 2.f;

        rotationOffset = 180.f + std::sin(timeSinceStart.count() * .8f) * 45.f;

        auto& transform = entity->GetTransform();
        transform.position = GioVector{transform.position.x, positionOffset, transform.position.z};
        transform.rotationEuler = GioVector{transform.rotationEuler.x, rotationOffset, transform.rotationEuler.z};
        entity->Draw(*graphics);
    }

    graphics->GetCameraTransform().position = GioVector{positionOffset, 0.f, 0.f};

    rotationOffset = std::sin(timeSinceStart.count()) * 25.f;
    std::cout << rotationOffset << std::endl;
    graphics->GetCameraTransform().rotationEuler = GioVector{rotationOffset, 0.f, 0.f};
    
    graphics->UpdateCameraMatrix();
    
    graphics->SwapBuffers();
    
    previousFrameTime = std::chrono::steady_clock::now();
}
