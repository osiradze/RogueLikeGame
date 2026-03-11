#version 300 es
precision mediump float;
out vec4 FragColor;

void main() {
    vec2 coord = gl_PointCoord - vec2(0.5);
    if (length(coord) > 0.5) discard;
    if (length(coord) < 0.45) discard;
    FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}

