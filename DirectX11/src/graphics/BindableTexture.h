#pragma once
#include <vector>

#include "IBindable.h"

struct GioTexture;

class BindableTexture : public IBindable
{
    Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> textureView;
    
public:
    BindableTexture(IRenderingContext& graphics, const std::wstring& path);

    BindableTexture(IRenderingContext& graphics, const GioTexture& inTexture);
    
    void Bind(IRenderingContext& graphics) override;
};
