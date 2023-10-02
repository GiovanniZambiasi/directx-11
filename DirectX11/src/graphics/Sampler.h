#pragma once
#include "IBindable.h"

class IRenderingContext;

class Sampler : public IBindable
{
    Microsoft::WRL::ComPtr<ID3D11SamplerState> sampler{};
    
public:
    Sampler(IRenderingContext& graphics);

    void Bind(IRenderingContext& graphics) override;
};
