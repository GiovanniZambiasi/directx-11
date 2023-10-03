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
    previousFrameTime = startTime;
}

void Game::Initialize(HWND window, int width, int height, int tickRate)
{
    graphics = std::make_unique<Graphics>(window, width, height);
    graphics->Initialize();

    entities =
        {
        std::make_shared<Box>(*graphics, GioTransform{{2.f, -1.f, 5.f}, {0.f}, {.5f}}),
        std::make_shared<Box>(*graphics, GioTransform{{-2.f, -1.f, 5.f}, {0.f}, {.25f}}),
        std::make_shared<Monkey>(*graphics, GioTransform{ {0.f, 0.f, 5.f}, {0.f} })
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
    float positionOffset{0.f};
    float rotationOffset{0.f};
    
    float change{1.f};
    
    for (std::shared_ptr<Entity>& entity : entities)
    {
        positionOffset = std::sin(timeSinceStart + change);
        change += 2.f;

        rotationOffset = 180.f + std::sin(timeSinceStart * .8f) * 45.f;

        auto& transform = entity->GetTransform();
        // transform.position = GioVector{transform.position.x, positionOffset, transform.position.z};
        //transform.rotationEuler = GioVector{transform.rotationEuler.x, deltaTime * 25.f, transform.rotationEuler.z};
        float dt = deltaTime * 25.f;
        std::cout << dt << std::endl;
        transform.Rotate({0.f, dt, 0.f});
        entity->Update(deltaTime);
    }

    positionOffset = std::sin(timeSinceStart);
    graphics->GetCameraTransform().position = GioVector{positionOffset, 0.f, 0.f};
    
    rotationOffset = std::sin(timeSinceStart) * 25.f;
    graphics->GetCameraTransform().rotationEuler = GioVector{rotationOffset, 0.f, 0.f};
}

void Game::DrawEntities()
{
    graphics->ClearBuffer({.7f, .9f, 1.f});

    for (std::shared_ptr<Entity>& entity : entities)
    {
        entity->Draw(*graphics);
    }
 
    graphics->UpdateCameraMatrix();
    
    graphics->SwapBuffers();
}
