#version 430 core


layout(location = 0) in vec3 vertexPosition;


void main() {
    gl_Position.xyz = vertexPosition;
    gl_Position.w = 1;
}
