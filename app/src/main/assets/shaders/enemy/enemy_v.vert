#version 300 es
layout(location = 0) in vec2 a_position;
layout(location = 1) in vec2 a_velocity;

void main() {
    gl_PointSize = 8.0;
    gl_Position = vec4(a_position, 0.0, 1.0);
}

