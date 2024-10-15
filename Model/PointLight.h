#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ILightObject.h"

class PointLight : public ILightObject
{
public:

    PointLight() :ILightObject(glm::vec3(1.0f, 1.0f, 1.0f), 0.2f, 0.8f, 1.0f, glm::vec3(0.0f,-10.0f, 0.0f), false) {}
    PointLight(glm::vec3 color, float ka, float kd, float ks, glm::vec3 pos, bool shouldRender) : ILightObject(color, ka, kd, ks, pos, shouldRender) {} 
    void Update(double deltaTime) override;
    void RenderLight() override;
};
