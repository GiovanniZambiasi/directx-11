#pragma once
#include <vector>

#include "IBindable.h"

class IndexBuffer : public IBindable
{
    Microsoft::WRL::ComPtr<ID3D11Buffer> buffer{};
    
public:
    IndexBuffer(Graphics& graphics, const std::vector<USHORT>& indices);
    
    void Bind(Graphics& graphics) override;
};
