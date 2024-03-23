#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <map>

class Character
{
public:
	Character();
	std::map<char, Character> GetCharacters();

private:

	unsigned int TextureID;  // ID handle of the glyph texture
	glm::ivec2   Size;       // Size of glyph
	glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
	unsigned int Advance;    // Offset to advance to next glyph

	static std::map<char, Character> Characters;
};

