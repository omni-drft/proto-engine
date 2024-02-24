/* ======================== FILE PURPOSE ========================
*
*  This file is used to define the vertex shader for the triangle.
*  The vertex shader is responsible for transforming the vertices
*  of the triangle from model space to clip space.
* 
=============================================================== */


#version 330 core

// Input vertex position
layout(location = 0) in vec2 inPosition;

// Uniforms
uniform mat4 projection;

// Output
out vec2 fragTexCoord;


void main() 
{
  // Transform the vertex position from model space to clip space
  vec4 transformedPosition = projection * vec4(inPosition, 0.0, 1.0);

  // Pass the texture
  fragTexCoord = inPosition;

  // Set the gl_Position
  gl_Position = transformedPosition;
}