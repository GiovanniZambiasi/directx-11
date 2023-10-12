#pragma once
#include <vector>

#include "Core.h"

class IDrawable;
struct GioTransform;
class TransformationBuffer;
class IndexBuffer;
class IBindable;
class IRenderingContext;

class RenderingComponent
{
    std::vector<std::shared_ptr<IBindable>> bindings{};

    std::vector<std::shared_ptr<IDrawable>> drawables{};
    
public:
    RenderingComponent() = default;
    
    NO_COPY_MOVE(RenderingComponent)

    template <typename TBinding>
    std::enable_if_t<std::is_base_of_v<IBindable, TBinding>>
    AddBinding(const std::shared_ptr<TBinding>& binding)
    {
        assert(binding);

        bindings.push_back(binding);
        
        if(std::is_base_of_v<IDrawable, TBinding>)
        {
            drawables.push_back(std::reinterpret_pointer_cast<IDrawable>(binding));
        }
    }
    
    /**
     * Creates and adds an IBindable of type TBinding
     * \tparam TBinding The the of the bindable. Must be concrete
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
    
};
