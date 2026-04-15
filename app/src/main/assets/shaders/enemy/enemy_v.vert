#version 300 es
precision highp float;
layout(location = 0) in vec2 a_position;
layout(location = 1) in vec2 a_velocity;
layout(location = 2) in vec3 a_color;
uniform vec2 u_camera;
uniform float u_point_size;
uniform float u_time;
uniform float u_ratio;

out vec3 v_color;

void main() {
    gl_PointSize = u_point_size;
    vec2 pos = a_position;
    pos.y += sin(a_position.x * 12.0 + u_time * 2.5) * 0.005;
    pos.x += cos(a_position.y * 12.0 + u_time * 2.0) * 0.008;
    vec2 offset = pos - u_camera;
    gl_Position = vec4(offset.x, offset.y, 0.0, 1.0);
    v_color = a_color;
}
