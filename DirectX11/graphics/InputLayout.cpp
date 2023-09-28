#include "pch.h"
#include "InputLayout.h"

#include "ErrorHandling.h"
#include "Graphics.h"

InputLayout::InputLayout(Graphics& graphics, const std::vector<D3D11_INPUT_ELEMENT_DESC>& elements, ID3DBlob* blob)
{
    GIO_THROW_IF_FAILED(graphics.GetDevice()->CreateInputLayout(elements.data(), elements.size(), blob->GetBufferPointer(),
                                            blob->GetBufferSize(), &inputLayout));
    
}

void InputLayout::Bind(Graphics& graphics)
{
    graphics.GetDeviceContext()->IASetInputLayout(inputLayout.Get());
}
