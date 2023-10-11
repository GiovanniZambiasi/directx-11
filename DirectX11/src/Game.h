#pragma once
#include <chrono>
#include <vector>

#include "Controls.h"
#include "graphics/Graphics.h"

class Entity;

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game
{
    std::chrono::steady_clock::time_point startTime{};
    
    std::chrono::steady_clock::time_point previousFrameTime{};

    std::unique_ptr<Graphics> graphics{};

    std::vector<std::shared_ptr<Entity>> entities{};

    Controls controls{};
    
    float timeSinceStart{0.f};
    float deltaTime{0.f};
    float minDeltaTime{0.f};
    
public:
    Game() noexcept;

    Game(Game const&) = delete;
    Game& operator= (Game const&) = delete;

    Game(Game&&) = delete;
    Game& operator= (Game&&) = delete;

    void Initialize(HWND window, int width, int height, int tickRate = 60);

    void Update();

    std::tuple<int, int> GetDefaultSize() const noexcept { return {1240, 720}; }

    Controls& GetControls() { return controls; }

    template<typename TEntity>
    std::enable_if_t<std::is_base_of_v<Entity, TEntity>>
    GetEntitiesOfType(std::vector<std::weak_ptr<TEntity>>& outEntities)
    {
        for (std::shared_ptr<Entity>& entity : entities)
        {
            if(std::shared_ptr<TEntity> casted = std::dynamic_pointer_cast<TEntity>(entity))
            {
                outEntities.emplace_back(casted);
            }
        }
    }

private:
    void UpdateEntities();

    void DrawEntities();

};
