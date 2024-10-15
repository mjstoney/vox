#pragma once

class GameObject
{
public:

    virtual void Translate(glm::mat4 translation) = 0;
    virtual void Rotate(glm::mat4 rotation) = 0;
    virtual void Scale(glm::mat4 scale) = 0;
    virtual void Render(const std::vector<ILightObject*> &lightObjects) = 0;
    virtual void Update(double deltaTime) = 0;

};