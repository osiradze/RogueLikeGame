#version 300 es
precision highp float;
layout(location = 0) in vec2 a_vertex;
uniform mat4 u_model;
uniform vec2 u_camera;

out vec2 v_uv;

void main() {
    v_uv = a_vertex;
    vec4 worldPos = u_model * vec4(a_vertex, 0.0, 1.0);
    gl_Position = vec4(worldPos.xy - u_camera, worldPos.zw);
}