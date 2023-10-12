#include "pch.h"
#include "BindableTexture.h"

#include "AssetUtils.h"
#include "ErrorHandling.h"
#include "GioTexture.h"
#include "IRenderingContext.h"

BindableTexture::BindableTexture(IRenderingContext& graphics, UINT width, UINT height,
    const std::vector<GioColor32>& pixels)
{
    assert(pixels.size() > 0 && width > 0 && height > 0);
    D3D11_TEXTURE2D_DESC desc{};
    desc.Width = width;
    desc.Height = height;
    desc.ArraySize = 1u;
    desc.MipLevels = 1u;
    desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
    desc.Usage = D3D11_USAGE_IMMUTABLE;
    desc.SampleDesc.Count = 1;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    D3D11_SUBRESOURCE_DATA data{ pixels.data() };
    data.SysMemPitch = desc.Width * sizeof(GioColor32);
    GIO_THROW_IF_FAILED(graphics.GetDevice()->CreateTexture2D(&desc, &data, &texture));
    GIO_THROW_IF_FAILED(graphics.GetDevice()->CreateShaderResourceView(texture.Get(), nullptr, &textureView));
}

void BindableTexture::Bind(IRenderingContext& graphics)
{
    graphics.GetDeviceContext()->PSSetShaderResources(0u, 1u, textureView.GetAddressOf());
}
