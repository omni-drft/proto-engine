#pragma once 

#include <iostream>
#include <glm/glm.hpp>
#include <map>

namespace ProtoEngine
{
	struct Character
	{
		unsigned int textureID;
		glm::ivec2 size;
		glm::ivec2 bearing;
		unsigned int advance;
	};

	// Create map of character glyphs
	extern std::map<char, Character> characters;
} // namespace ProtoEngine