/* =========================== FILE PURPOSE ===========================
*  
*  This file is used to define the fragment shader for the triangle.
*  The fragment shader is responsible for determining the color of
*  each pixel in the triangle.
*
===================================================================== */

#version 330 core

out vec4 fragColor;

void main() {
    fragColor = vec4(1.0, 0.0, 0.0, 1.0); // Red color
}