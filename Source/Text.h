#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class Text
{
public:
	unsigned int TextureID;  // ID handle of the glyph texture
	glm::ivec2   Size;       // Size of glyph
	glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
	unsigned int Advance;    // Offset to advance to next glyph

	void Init();
};

