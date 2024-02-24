/* ================================ FILE PURPOSE =========================================
* 
* This file contains the implementation of the Object class. The Object class
* is used to represent a drawable object in the software. It contains the vertices
* and indices of the object, as well as the VAO, VBO, and EBO used to draw the object.
* 
======================================================================================= */


#include "Object.h"

ProtoEngine::Object::Object(std::vector<float>& vertices, std::vector<int>& indices)
	: vertices(vertices), indices(indices)
{
	// Generate VAO, VBO, and EBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind VAO
	glBindVertexArray(VAO);

	// Bind and set up vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

	// Bind and set up element buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);

	// Set vertex attribute pointers
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Unbind VAO
	glBindVertexArray(0);

}

void ProtoEngine::Object::Draw()
{
	// Bind VAO before drawing
	glBindVertexArray(VAO);

	// Draw the rectangle
	glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);

	// Unbind VAO after drawing
	glBindVertexArray(0);
}
