#pragma once
#include <vector>

struct GioTransform;
class TransformationBuffer;
class IndexBuffer;
class IBindable;
class IRenderingContext;

class Drawable
{
    std::vector<std::shared_ptr<IBindable>> bindings{};

    std::shared_ptr<IndexBuffer> indexBuffer{};
    
    std::shared_ptr<TransformationBuffer> transformationBuffer{};

public:
    void AddBinding(const std::shared_ptr<IBindable>& binding);

    void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indices);
    
    void SetTransformationBuffer(const std::shared_ptr<TransformationBuffer>& inBuffer);
    
    void Draw(IRenderingContext& graphics, const GioTransform& inTransform);
};

class IDrawable
{
public:
    virtual ~IDrawable() = default;

    virtual Drawable& GetDrawable() = 0;

    virtual void Draw(IRenderingContext& graphics) = 0;
};