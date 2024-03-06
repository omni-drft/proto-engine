/* ======================== PURPOSE OF FILE ========================
* 
* This file is the entry point for the application. 
*	It creates a window using GLFW and GLEW, 
* and then enters a loop to render the window.
* 
================================================================== */

#include "Includes.hpp"

struct Character {
	unsigned int TextureID;  // ID handle of the glyph texture
	glm::ivec2   Size;       // Size of glyph
	glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
	unsigned int Advance;    // Offset to advance to next glyph
};

std::map<char, Character> Characters;

void RenderText(ProtoEngine::Shader& s, std::string text, float x, float y, float scale, glm::vec3 color, unsigned int& VAO, unsigned int& VBO);

int main()
{
	// Create a logger
	ProtoEngine::Log::Init();
	// Create a window
	ProtoEngine::Window window(1600, 800, "ProtoEngine");
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// ================ TEXT RENDERING (IN THIS FILE ONLY FOR TESTING) ===================
	// This section is for testing text rendering. It will be moved to a separate file later.

	ProtoEngine::Log::GetLogger()->info("FreeType: Initializing freetype library");

	FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
		ProtoEngine::Log::GetLogger()->critical("FreeType: Could not init freetype library");
		return -1;
	}
	else ProtoEngine::Log::GetLogger()->info("FreeType: Initialized freetype library");

	FT_Face face;
	if (FT_New_Face(ft, "Assets/Fonts/SourceCodePro.ttf", 0, &face))
	{
		ProtoEngine::Log::GetLogger()->critical("FreeType: Failed to load font");
		return -1;
	}
	else ProtoEngine::Log::GetLogger()->info("FreeType: Font loaded succesfully");

	FT_Set_Pixel_Sizes(face, 0, 48);

	if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
	{
		ProtoEngine::Log::GetLogger()->critical("FreeType: Failed to load glyph");
		return -1;
	}
	else ProtoEngine::Log::GetLogger()->info("FreeType: Glyph loaded succesfully");

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

	for (unsigned char c = 0; c < 128; c++)
	{
		// load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			ProtoEngine::Log::GetLogger()->error("FreeType: Failed to load glyph for character {}", c);
			continue;
		}
		// generate texture
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		// set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// now store character for later use
		Character character = {
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				face->glyph->advance.x
		};
		Characters.insert(std::pair<char, Character>(c, character));
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	ProtoEngine::Shader textShader("Source/Shaders/GlyphVertexShader.glsl", "Source/Shaders/GlyphFragmentShader.glsl");
	textShader.Use();
	glm::mat4 projection1{ glm::ortho(0.0f, 1600.0f, 0.0f, 800.0f, -1.0f, 1.0f) };
	textShader.SetMat4("projection", projection1);
	
	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// ===================================================================================



	// Log that the logger has been initialized
	ProtoEngine::Log::GetLogger()->info("Logger: Initialized");
	// Log that the engine is starting
	ProtoEngine::Log::GetLogger()->info("ProtoEngine starting...");

	// Close the console window if in release mode
	#ifdef NDEBUG
	FreeConsole();
	#endif // NDEBUG


	// Initialize the input handler
	ProtoEngine::HandleInput inputHandler(&window);

	// Create shader for objects
	ProtoEngine::Shader objectShader("Source/Shaders/VertexShader.glsl", "Source/Shaders/FragmentShader.glsl");
	objectShader.Use();	
	int currentWidth{}, currentHeight{};
	window.GetDimensions(&currentWidth, &currentHeight);
	glm::mat4 projection{ glm::ortho(0.0f, static_cast<float>(currentWidth), 0.0f, static_cast<float>(currentHeight), -1.0f, 1.0f) };
	objectShader.SetMat4("projection", projection);
	objectShader.SetVec4("objectColor", 1.0f, 0.5f, 0.2f, 1.0f);


	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window.GetWindow()))
	{
		// Clear the window
		window.ClearWindow();

		// Update the window dimensions and viewport
		glViewport(0, 0, currentWidth, currentHeight);
		window.GetDimensions(&currentWidth, &currentHeight);

		// Render text
		RenderText(textShader, "ProtoEngine", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f), VAO, VBO);

		// Swap front and back buffers
		window.SwapBuffers();

		// Poll for and process events
		window.PollEvents();
	}

	return 0;
}


void RenderText(ProtoEngine::Shader& s, std::string text, float x, float y, float scale, glm::vec3 color, unsigned int& VAO, unsigned int& VBO)
{
	// activate corresponding render state	
	s.Use();
	glUniform3f(glGetUniformLocation(s.GetProgramID(), "textColor"), color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	// iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = Characters[*c];

		float xpos = x + ch.Bearing.x * scale;
		float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		float w = ch.Size.x * scale;
		float h = ch.Size.y * scale;
		// update VBO for each character
		float vertices[6][4] = {
				{ xpos,     ypos + h,   0.0f, 0.0f },
				{ xpos,     ypos,       0.0f, 1.0f },
				{ xpos + w, ypos,       1.0f, 1.0f },

				{ xpos,     ypos + h,   0.0f, 0.0f },
				{ xpos + w, ypos,       1.0f, 1.0f },
				{ xpos + w, ypos + h,   1.0f, 0.0f }
		};
		// render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}