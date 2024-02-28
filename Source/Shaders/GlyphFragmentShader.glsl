/* ========================== FILE PURPOSE ==========================
*
* This file is used to modify the text color. It is used in the
* text rendering process. 
*
================================================================== */

#version 330 core

// Interpolated values from the vertex shaders
in vec2 texCoords;

// Output data
out vec4 color;

// Uniforms
uniform sampler2D text;
uniform vec3 textColor;

void main()
{   
  // Sample the color value from the texture
  vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, texCoords).r);

  // Set the output color to the sampled color
  color = vec4(textColor, 1.0) * sampled;
}