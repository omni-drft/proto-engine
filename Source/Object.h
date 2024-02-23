#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

namespace ProtoEngine 
{

class Object
{
public:
	Object();

	void Draw();

private:
	unsigned int VAO, VBO, EBO;
	std::vector<float> vertices;
	std::vector<int> indices;
};

} // namespace ProtoEngine