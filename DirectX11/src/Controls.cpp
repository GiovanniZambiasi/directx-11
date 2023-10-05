#include "pch.h"
#include "Controls.h"

void Controls::KeyPressed(WPARAM keyCode)
{
    pressedKeys.emplace(keyCode);
}

void Controls::KeyReleased(WPARAM keyCode)
{
    pressedKeys.erase(keyCode);
}

bool Controls::IsDown(WPARAM keyCode) const
{
    return pressedKeys.find(keyCode) != pressedKeys.end();
}

void Controls::Update()
{
    camMoveInput = 0.f;
    
    if(IsDown(0x57))
        camMoveInput += {0.f, 0.f, 1.f};
    else if(IsDown(0x53))
        camMoveInput += {0.f, 0.f, -1.f};

    if(IsDown(0x44))
        camMoveInput += {1.f, 0.f, 0.f};
    else if(IsDown(0x41))
        camMoveInput += {-1.f, 0.f, 0.f};

    camRotateInput = 0.f;
    if(IsDown(0x4C))
        camRotateInput += {0.f, 1.f, 0.f};
    else if(IsDown(0x4A))
        camRotateInput += {0.f, -1.f, 0.f};

}
