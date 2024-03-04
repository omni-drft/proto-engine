#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Shader.hpp"
#include "Character.hpp"

namespace ProtoEngine
{

class Text
{
public:
	Text(std::string text);
	void Render(Shader &s, float x, float y, float scale, glm::vec3 color);
	void SetText(std::string t) { text = t; }
	std::string GetText() { return text; }
private:
	unsigned int VAO, VBO;
	std::string text;
};

}

