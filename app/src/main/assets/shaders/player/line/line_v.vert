#version 300 es
layout(location = 0) in vec2 a_vertex;
uniform vec2 u_camera;
uniform float u_ratio;

void main() {
    vec2 offset = a_vertex - u_camera;
    gl_Position = vec4(offset.x, offset.y, 0.0, 1.0);
}