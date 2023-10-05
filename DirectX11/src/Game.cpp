#include "pch.h"
#include "Game.h"

#include <chrono>
#include <iostream>

#include "graphics/Shader.h"
#include "graphics/InputLayout.h"
#include "Box.h"
#include "GioColor.h"
#include "GioVector.h"
#include "Logger.h"
#include "Monkey.h"

extern void ExitGame() noexcept;

using namespace Microsoft;

Game::Game() noexcept
{
    startTime = std::chrono::steady_clock::now();
    previousFrameTime = startTime;
}

void Game::Initialize(HWND window, int width, int height, int tickRate)
{
    graphics = std::make_unique<Graphics>(window, width, height);
    graphics->Initialize();
    graphics->GetCameraTransform() = { { .0f, .0f, -5.f} };

    entities =
        {
        std::make_shared<Box>(*graphics, GioTransform{{2.f, -1.f, 0.f}, {0.f, 180.f, 0.f}, {.5f}}),
        std::make_shared<Box>(*graphics, GioTransform{{-2.f, -1.f, 0.f}, {0.f, 180.f, 0.f}, {.25f}}),
        std::make_shared<Monkey>(*graphics, GioTransform{ {0.f, 0.f, 1.f}, {0.f, 180.f, 0.f } }),
        // std::make_shared<Box>(*graphics, GioTransform{{25.f, 0.f, 0.f}, {0.f, 180.f, 0.f}, {1.f, 25.f, 25.f}}),
        // std::make_shared<Box>(*graphics, GioTransform{{-25.f, 0.f, 0.f}, {0.f, 180.f, 0.f}, {1.f, 25.f, 25.f}}),
    };
    
    minDeltaTime = 1.f/static_cast<float>(tickRate);
}

void Game::Update()
{
    auto timeNow = std::chrono::steady_clock::now();
    timeSinceStart = std::chrono::duration<float>{timeNow - startTime}.count();
    deltaTime = std::chrono::duration<float>{timeNow - previousFrameTime}.count();

    if(deltaTime < minDeltaTime)
    {
        return;
    }
    
    POINT cursorPos{};
    GetCursorPos(&cursorPos);

    UpdateEntities();
    
    DrawEntities();
    
    previousFrameTime = std::chrono::steady_clock::now();
}

void Game::UpdateEntities()
{
    controls.Update();
    
    float change{1.f};
    
    for (std::shared_ptr<Entity>& entity : entities)
    {
        float positionOffset = std::sin(timeSinceStart + change);
        change += 2.f;

        auto& transform = entity->GetTransform();
        transform.position = GioVector{transform.position.x, positionOffset, transform.position.z};
        transform.Rotate({0.f, deltaTime * 25.f, 0.f});
        entity->Update(deltaTime);
    }

    GioTransform& camTransform = graphics->GetCameraTransform();
    camTransform.Translate(controls.GetCamMoveInput() * deltaTime * 10.f);
    camTransform.Rotate(controls.GetCamRotateInput() * deltaTime * 45.f);
}

void Game::DrawEntities()
{
    graphics->ClearBuffer({.7f, .9f, 1.f});

    graphics->UpdateCameraMatrix();
    
    for (std::shared_ptr<Entity>& entity : entities)
    {
        entity->Draw(*graphics);
    }
 
    graphics->SwapBuffers();
}
