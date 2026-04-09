#version 300 es
precision highp float;
layout(location = 0) in vec2 a_position;
layout(location = 1) in vec2 a_velocity;
layout(location = 2) in vec3 a_color;
uniform vec2 u_camera;
uniform float u_point_size;

out vec3 v_color;
out float v_is_alive;

void main() {
    gl_PointSize = u_point_size;
    gl_Position = vec4(a_position - u_camera, 0.0, 1.0);
    v_color = vec3(a_color);
}
