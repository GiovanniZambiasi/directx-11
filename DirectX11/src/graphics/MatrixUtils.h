#pragma once

class IRenderingContext;
struct GioTransform;

class MatrixUtils
{
public:
    static DirectX::XMMATRIX CalculateModelMatrix(const GioTransform& transform);

    /**
     * Given an object's world transform, calculates the matrix needed to render it on-screen. This takes into account
     * the camera's projection matrix.
     */
    static DirectX::XMMATRIX CalculateMVPMatrix(IRenderingContext& graphics, const GioTransform& transform);
    
    static DirectX::XMMATRIX CalculateMVPMatrix(IRenderingContext& graphics, const DirectX::XMMATRIX& modelMatrix);
    
private:
    MatrixUtils() = delete;
};
