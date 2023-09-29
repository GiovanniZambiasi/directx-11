#pragma once
#include <chrono>
#include "graphics/Graphics.h"

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game
{
    std::chrono::steady_clock::time_point startTime{};
    
    std::chrono::steady_clock::time_point previousFrameTime{};

    std::unique_ptr<Graphics> graphics{};

    std::shared_ptr<Box> box;
    
public:
    Game() noexcept;

    Game(Game const&) = delete;
    Game& operator= (Game const&) = delete;

    Game(Game&&) = delete;
    Game& operator= (Game&&) = delete;

    void Initialize(HWND window, int width, int height);

    void Update();
    
    std::tuple<int, int> GetDefaultSize() const noexcept { return {1240, 720}; }

};
