#pragma once

struct GioVector
{
    float x{};
    float y{};
    float z{};

    GioVector() = default;
    
    GioVector(float v);

    GioVector(float inX, float inY, float inZ);

    GioVector(const DirectX::XMVECTOR& inVector);

    GioVector operator/(float factor) const;

    GioVector operator+(const GioVector& other) const;

    GioVector operator-(const GioVector& other) const;

    GioVector operator*(float rhs) const;

    GioVector operator-() const;
    
    GioVector& operator+=(const GioVector& other);

    float operator[](int index) const;

    operator DirectX::XMVECTOR() const;

    float Magnitude() const;

    GioVector Normalized() const;

    void Normalize();

    void ClampMagnitude(float maxMagnitude);

    GioVector EulerToRadians() const;

    GioVector RadiansToEuler() const;

    float Dot(const GioVector& other) const;

    std::string ToString() const;

};

struct GioUV
{
    float u{};
    float v{};

    GioUV() = default;
    
    GioUV(float x)
        : u(x), v(x)
    {}

    GioUV(float inU, float inV)
        : u(inU), v(inV)
    {}

    std::string ToString() const;
};
