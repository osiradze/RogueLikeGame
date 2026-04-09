#version 300 es
precision highp float;
out vec4 FragColor;
in vec3 v_color;

void main() {
    vec2 coord = gl_PointCoord - vec2(0.5);
    FragColor = vec4(v_color, 1.0);
    if (length(coord) > 0.5)  discard;

}
