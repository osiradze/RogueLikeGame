#version 300 es
layout(location = 0) in vec2 a_position;
layout(location = 1) in vec2 a_velocity;
uniform vec2 u_camera;

void main() {
    gl_PointSize = 40.0;
    gl_Position = vec4(a_position - u_camera, 0.0, 1.0);
}

