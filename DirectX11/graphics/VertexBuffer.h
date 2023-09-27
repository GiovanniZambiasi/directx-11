#pragma once
#include <vector>

#include "Bindable.h"

class VertexBuffer : public Bindable
{
    Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer{};
    
public:
    VertexBuffer(Graphics& graphics, const std::vector<UINT>& indices);
    
    void Bind(Graphics& graphics) override;

    
};
