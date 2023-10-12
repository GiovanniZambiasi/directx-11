#pragma once
#include <vector>

#include "Core.h"

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
    Drawable() = default;
    
    NO_COPY_MOVE(Drawable)

    template <typename TBinding>
    std::enable_if_t<std::is_base_of_v<IBindable, TBinding>>
    AddBinding(const std::shared_ptr<TBinding>& binding)
    {
        if(std::is_base_of_v<IndexBuffer, TBinding>)
        {
            SetIndexBuffer(std::reinterpret_pointer_cast<IndexBuffer>(binding));
        }
        else if(std::is_base_of_v<TransformationBuffer, TBinding>)
        {
            SetTransformationBuffer(std::reinterpret_pointer_cast<TransformationBuffer>(binding));
        }
        else
        {
            bindings.push_back(binding);
        }
    }
    
    /**
     * Creates and adds an IBindable of type TBinding
     * \tparam TBinding The the of the bindable. Must be concrete
     * \param constructionParams Parameters sent to the constructor of TBinding 
     */
    template <typename TBinding>
    std::enable_if_t<std::is_base_of_v<IBindable, TBinding>, std::shared_ptr<TBinding>>
    CreateBinding(TBinding&& binding)
    {
        std::shared_ptr<TBinding> bindingPtr = std::make_shared<TBinding>(binding);
        AddBinding(bindingPtr);
        return bindingPtr;
    }
    
    void Draw(IRenderingContext& graphics, const GioTransform& inTransform);
    
private:
    void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indices);
    
    void SetTransformationBuffer(const std::shared_ptr<TransformationBuffer>& inBuffer);

};
