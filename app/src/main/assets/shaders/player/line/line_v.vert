#version 300 es
layout(location = 0) in vec2 a_vertex;
uniform vec2 u_camera;

void main() {
    gl_Position = vec4(a_vertex - u_camera, 0.0, 1.0);
}