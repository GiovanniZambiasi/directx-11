#include "pch.h"
#include "RenderingComponent.h"

#include "IRenderingContext.h"
#include "RenderingResources.h"
#include "graphics/IDrawable.h"
#include "graphics/cbuffers/TransformationBuffer.h"

void RenderingComponent::Draw(IRenderingContext& graphics, const GioTransform& inTransform)
{
    std::shared_ptr<TransformationBuffer> transformBuffer =
        graphics.GetSharedResources().transformationBuffer;
    transformBuffer->Update(graphics, inTransform);
    transformBuffer->Bind(graphics);

    for (std::shared_ptr<IBindable>& bindable : bindings)
    {
        assert(bindable);
        bindable->Bind(graphics);
    }

    for (auto &drawable : drawables)
    {
        assert(drawable);
        drawable->Draw(graphics);
    }    
}

