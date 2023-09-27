#pragma once
#include <vector>

#include "Bindable.h"

class IndexBuffer : public Bindable
{
    Microsoft::WRL::ComPtr<ID3D11Buffer> buffer{};
    
public:
    IndexBuffer(Graphics& graphics, const std::vector<USHORT>& indices);
    
    void Bind(Graphics& graphics) override;
};
