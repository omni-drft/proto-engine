/* ========================= FILE PURPOSE =========================
*
* This file is used to define the vertex shader for font rendering
* in the application. The vertex shader is used to transform the
* vertices of the font quads to the screen space.
*
================================================================= */

#version 330 core

// Input variables
layout (location = 0) in vec4 vertex;

// Output variables
out vec2 texCoords;

// Uniforms
uniform mat4 projection;

void main()
{
  // Transform the vertex to screen space
  gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);

  // Pass the texture coordinates to the fragment shader
  texCoords = vertex.zw;
}  