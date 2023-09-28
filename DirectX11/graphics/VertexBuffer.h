#pragma once
#include <vector>

#include "IBindable.h"
#include "ErrorHandling.h"
#include "IRenderingContext.h"

class VertexBuffer : public IBindable
{
    Microsoft::WRL::ComPtr<ID3D11Buffer> buffer{};

    UINT stride{};
    
public:
    template <typename TVertex>
    VertexBuffer(IRenderingContext& graphics, const std::vector<TVertex>& vertices)
        : stride(sizeof(TVertex))
    {
        
        D3D11_BUFFER_DESC desc
        {
            vertices.size() * sizeof(TVertex),
            D3D11_USAGE_DEFAULT,
            D3D11_BIND_VERTEX_BUFFER,
            0,
            0,
            stride
        };
        D3D11_SUBRESOURCE_DATA data{vertices.data()};
        GIO_THROW_IF_FAILED(graphics.GetDevice()->CreateBuffer(&desc, &data, &buffer))
    }
    
    void Bind(IRenderingContext& graphics) override;

    
};
