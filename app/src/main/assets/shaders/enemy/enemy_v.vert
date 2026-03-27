#version 300 es
precision highp float;
layout(location = 0) in vec2 a_position;
layout(location = 1) in vec2 a_velocity;
uniform vec2 u_camera;
uniform float u_point_size;

void main() {
    gl_PointSize = u_point_size;
    gl_Position = vec4(a_position - u_camera, 0.0, 1.0);
}

