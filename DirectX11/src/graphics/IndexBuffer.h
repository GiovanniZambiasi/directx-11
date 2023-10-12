#pragma once
#include <vector>

#include "IBindable.h"

class IndexBuffer : public IBindable
{
    Microsoft::WRL::ComPtr<ID3D11Buffer> buffer{};

    UINT indexCount{0};
    
public:
    IndexBuffer(IRenderingContext& graphics, const std::vector<UINT>& indices);

    void Bind(IRenderingContext& graphics) override;

    UINT GetIndexCount() const { return indexCount; }
};
