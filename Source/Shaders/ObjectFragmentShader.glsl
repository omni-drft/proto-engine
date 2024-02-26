/* =========================== FILE PURPOSE ===========================
*  
*  This file is used to define the fragment shader for the triangle.
*  The fragment shader is responsible for determining the color of
*  each pixel in the triangle.
*
===================================================================== */

#version 330 core

uniform vec4 objectColor;

out vec4 finalColor;

void main() 
{
  // Set the color of the pixel to the color of the object
  finalColor = objectColor;
}