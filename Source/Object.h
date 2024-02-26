/* =============================== FILE PURPOSE =======================================
* 
*  This file contains the declaration of the Object class, which is used to create
*  an object with a set of vertices and indices. It is also used to draw the object
*  on the screen and to manage the VAO, VBO and EBO. 
* 
==================================================================================== */


#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "Vertex.h"

namespace ProtoEngine 
{

	/// <summary>
	/// This class is used to create an object with a set of vertices and indices.
	/// It is also used to draw the object on the screen and to manage the VAO, VBO and EBO.
	/// </summary>
	class Object
	{
	public:

		/// <summary>
		/// This constructor is used to create an object with a set of vertices and indices.
		/// </summary>
		/// <param name="vertices">- vector of vertices (floats)</param>
		/// <param name="indices">- vector of indices (ints)</param>
		Object(std::vector<Vertex>& vertices, std::vector<int>& indices);

		/// <summary>
		/// Draw the object on the screen.
		/// </summary>
		void Draw();

	private:

		/// <summary>
		/// VAO, VBO and EBO used to draw the object on the screen and manage its vertices and indices.
		/// </summary>
		unsigned int VAO, VBO, EBO;

		/// <summary>
		/// Vector of vertices, which are used to determine object position and shape.
		/// </summary>
		std::vector<Vertex> vertices;

		/// <summary>
		/// Vector of indices, which are used to determine order of vertices that will be drawn.
		/// </summary>
		std::vector<int> indices;
	};

} // namespace ProtoEngine