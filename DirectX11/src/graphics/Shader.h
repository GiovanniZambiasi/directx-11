#pragma once
#include <d3dcompiler.h>

#include "ErrorHandling.h"
#include "IBindable.h"

class Drawable;
class IDrawable;

template <typename TShader>
class Shader : public IBindable
{
protected:
    Microsoft::WRL::ComPtr<TShader> shaderInstance{};

    Microsoft::WRL::ComPtr<ID3DBlob> blob{};
    
public:
    Shader(IRenderingContext& graphics, const wchar_t* fileName)
    {
        GIO_THROW_IF_FAILED(D3DReadFileToBlob(fileName, &blob));
    }

    ID3DBlob* GetBlob() const { return blob.Get(); }
};

class VertexShader : public Shader<ID3D11VertexShader>
{
public:
    VertexShader(IRenderingContext& graphics, const wchar_t* fileName);

    void Bind(IRenderingContext& graphics) override;

};

class PixelShader : public Shader<ID3D11PixelShader>
{
public:
    PixelShader(IRenderingContext& graphics, const wchar_t* const fileName);

    void Bind(IRenderingContext& graphics) override;
};

class ShaderUtils
{
public:
    static void BindStandardShaders(IRenderingContext& graphics, Drawable& drawable);
    
    static void BindTexturedShaders(IRenderingContext& graphics, Drawable& drawable);
    
private:
    ShaderUtils() = delete;
};
