#version 300 es
precision highp float;
layout(location = 0) in vec2 a_position;
layout(location = 1) in vec2 a_velocity;
layout(location = 2) in vec3 a_color;
layout(location = 3) in float a_is_alive;
uniform vec2 u_camera;
uniform float u_point_size;
uniform float u_ratio;

out vec3 v_color;
out float v_is_alive;

void main() {
    v_is_alive = a_is_alive;
    gl_PointSize = u_point_size;
    vec2 offset = a_position - u_camera;
    gl_Position = vec4(offset.x, offset.y, 0.0, 1.0);
    v_color = vec3(1);
}
