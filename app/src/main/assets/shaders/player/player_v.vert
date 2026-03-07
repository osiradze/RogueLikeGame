#version 300 es
layout(location = 0) in vec2 a_vertex;
uniform mat4 u_model;


void main() {
    gl_Position = u_model * vec4(a_vertex, 0.0, 1.0);
}