#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ILightObject
{
public:
    glm::vec3 lightColor;
    glm::vec3 position;
    float kA, kD, kS;
    bool ShouldRender;

    ILightObject() { position = { 0.0f, 3.0f, 3.0f }; }
    ILightObject(glm::vec3 color, float ka, float kd, float ks, glm::vec3 pos, bool shouldRender) : lightColor(color), kA(ka), kD(kd), kS(ks), position(pos), ShouldRender(shouldRender) {} 

    virtual void Update(double deltaTime) = 0;
    virtual void RenderLight() = 0;
};