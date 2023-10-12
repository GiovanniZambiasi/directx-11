#pragma once
#include <vector>

#include "GioColor.h"
#include "IBindable.h"

class GioTexture;

class BindableTexture : public IBindable
{
    Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> textureView;
    
public:
    BindableTexture(IRenderingContext& graphics, UINT width, UINT height, const std::vector<GioColor32>& pixels);
    
    void Bind(IRenderingContext& graphics) override;
};
