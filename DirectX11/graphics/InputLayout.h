#pragma once
#include <vector>

#include "IBindable.h"

class InputLayout : public IBindable
{
    Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout{};
    
public:
    InputLayout(Graphics& graphics, const std::vector<D3D11_INPUT_ELEMENT_DESC>& elements, ID3DBlob* blob);

    void Bind(Graphics& graphics) override;
};
