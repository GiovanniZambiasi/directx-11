#pragma once

class IRenderingContext;
struct GioTransform;

class TransformUtils
{
public:
    static DirectX::XMMATRIX TransformToMatrix(const GioTransform& transform);

    /**
     * Given an object's world transform, calculates the matrix needed to render it on-screen. This takes into account
     * the camera's projection matrix.
     */
    static DirectX::XMMATRIX CalculateFinalMatrix(IRenderingContext& graphics, const GioTransform& transform);
    
private:
    TransformUtils() = delete;
};
