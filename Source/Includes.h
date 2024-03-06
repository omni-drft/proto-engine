/* ============================ FILE PURPOSE ===============================
*	 
*  This file is used to include all the necessary libraries and classes for
*  the project. This is done to avoid having to include all the libraries
*  int the main file.
* 
========================================================================== */

// Link OpenGL Extension Wrangler
#include <GL/glew.h>

// Link GLFW for window creation and input handling
#include <GLFW/glfw3.h>

// Link GLM for algebra
#include <glm/glm.hpp>

//#include <ft2build.h>
//#include FT_FREETYPE_H

// Link standard libraries
#include <iostream>
#include <Windows.h>
#include <vector>
#include <map>

// Link custom classes
#include "HandleInput.h"
#include "Shader.h"
#include "Window.h"
#include "Object.h"
#include "Vertex.h"
#include "Log.h"