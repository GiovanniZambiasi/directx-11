#include "pch.h"
#include "InputLayout.h"

#include "ErrorHandling.h"
#include "IRenderingContext.h"

InputLayout::InputLayout(IRenderingContext& graphics, const std::vector<D3D11_INPUT_ELEMENT_DESC>& elements, ID3DBlob* blob)
{
    GIO_THROW_IF_FAILED(graphics.GetDevice()->CreateInputLayout(elements.data(),static_cast<UINT>(elements.size()), blob->GetBufferPointer(),
                                            blob->GetBufferSize(), &inputLayout));
    
}

void InputLayout::Bind(IRenderingContext& graphics)
{
    graphics.GetDeviceContext()->IASetInputLayout(inputLayout.Get());
}
