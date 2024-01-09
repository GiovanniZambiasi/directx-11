#pragma once
#include <chrono>
#include <vector>

#include "Controls.h"
#include "IGameContext.h"
#include "graphics/Graphics.h"

class Entity;
class UI;

class Game : public IGameContext
{
    std::chrono::steady_clock::time_point startTime{};
    
    std::chrono::steady_clock::time_point previousFrameTime{};

    std::unique_ptr<Graphics> graphics{};

    std::unique_ptr<UI> ui{};

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

    std::tuple<int, int> GetDefaultSize() const noexcept { return {1240, 720}; }

    IRenderingContext& GetRenderingContext() override { return *graphics.get(); }
    
    Controls& GetControls() { return controls; }
    
    void Initialize(HWND window, int width, int height, int tickRate = 60);

    void Update();

protected:
    std::vector<std::shared_ptr<Entity>>& GetEntities() override { return entities; }
    
private:
    void PreRender();
    
    void UpdateEntities();

    void Render();

};
