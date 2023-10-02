#pragma once
#include <vector>

#include "IBindable.h"

struct GioMesh;

class IndexBuffer : public IBindable
{
    Microsoft::WRL::ComPtr<ID3D11Buffer> buffer{};

    UINT indexCount{0};
    
public:
    IndexBuffer(IRenderingContext& graphics, const std::vector<UINT>& indices);

    IndexBuffer(IRenderingContext& graphics, const GioMesh& mesh);
    
    void Bind(IRenderingContext& graphics) override;

    UINT GetIndexCount() const { return indexCount; }
};
