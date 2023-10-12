#include "pch.h"
#include "Drawable.h"

#include "IndexBuffer.h"
#include "IRenderingContext.h"
#include "cbuffers/TransformationBuffer.h"

void Drawable::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indices)
{
    indexBuffer = indices;
}

void Drawable::SetTransformationBuffer(const std::shared_ptr<TransformationBuffer>& inBuffer)
{
    transformationBuffer = inBuffer;
}

void Drawable::Draw(IRenderingContext& graphics, const GioTransform& inTransform)
{
    assert(indexBuffer);
    assert(transformationBuffer);
    
    indexBuffer->Bind(graphics);

    transformationBuffer->Update(graphics, inTransform);

    transformationBuffer->Bind(graphics);

    for (std::shared_ptr<IBindable>& bindable : bindings)
    {
        bindable->Bind(graphics);
    }

    graphics.GetDeviceContext()->DrawIndexed(indexBuffer->GetIndexCount(), 0u, 0u);
}

