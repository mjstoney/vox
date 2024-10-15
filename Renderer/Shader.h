#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "PointLight.h"

class Shader
{
public:
	unsigned int ID;
	Shader();
	Shader(const char* vertexPath, const char* fragmentPath);
	void Use();
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec2(const std::string& name, const glm::vec2 &value) const;
	void setVec3(const std::string& name, const glm::vec3 &value) const;
	void setMat4(const std::string& name, const glm::mat4 &value) const;
    void setPointLight(const std::string &name, ILightObject *pointLight);

private:
	void checkCompileErrors(unsigned int shader, std::string type);

};