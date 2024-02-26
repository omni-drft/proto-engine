#pragma once 

#include <iostream>
#include <glm/glm.hpp>

namespace ProtoEngine
{
	struct Character
	{
		unsigned int textureID;
		glm::ivec2 size;
		glm::ivec2 bearing;
		unsigned int advance;
	};
} // namespace ProtoEngine