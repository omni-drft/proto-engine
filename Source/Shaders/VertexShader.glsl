/* ======================== FILE PURPOSE ========================
*
*  This file is used to define the vertex shader for the triangle.
*  The vertex shader is responsible for transforming the vertices
*  of the triangle from model space to clip space.
* 
=============================================================== */


#version 330 core

layout(location = 0) in vec2 in_position;

void main() {
    gl_Position = vec4(in_position, 0.0, 1.0);
}