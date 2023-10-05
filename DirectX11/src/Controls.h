#pragma once
#include <set>
#include <unordered_map>

#include "GioVector.h"

class Controls
{
    std::set<WPARAM> pressedKeys{};

    GioVector camMoveInput{};
    GioVector camRotateInput{};
    
public:
    void KeyPressed(WPARAM keyCode);

    void KeyReleased(WPARAM keyCode);

    bool IsDown(WPARAM keyCode) const;

    GioVector GetCamMoveInput() const { return camMoveInput; }
    
    GioVector GetCamRotateInput() const { return camRotateInput; }
    
    void Update();
};
