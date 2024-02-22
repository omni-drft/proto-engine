#version 330 core

layout(location = 0) in vec2 in_position; 

uniform mat4 projection; 

void main() {
    // Transform the vertex position using the projection matrix
    gl_Position = projection * vec4(in_position, 0.0, 1.0);
}