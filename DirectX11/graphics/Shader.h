﻿#pragma once
#include <d3dcompiler.h>

#include "ErrorHandling.h"
#include "IBindable.h"

template <typename TShader>
class Shader : public IBindable
{
protected:
    Microsoft::WRL::ComPtr<TShader> shaderInstance{};

    Microsoft::WRL::ComPtr<ID3DBlob> blob{};
    
public:
    Shader(Graphics& graphics, const wchar_t* fileName)
    {
        GIO_THROW_IF_FAILED(D3DReadFileToBlob(fileName, &blob));
    }

    ID3DBlob* GetBlob() const { return blob.Get(); }
};

class VertexShader : public Shader<ID3D11VertexShader>
{
public:
    VertexShader(Graphics& graphics, const wchar_t* fileName);

    void Bind(Graphics& graphics) override;

};

class PixelShader : public Shader<ID3D11PixelShader>
{
public:
    PixelShader(Graphics& graphics, const wchar_t* const fileName);

    void Bind(Graphics& graphics) override;
};
