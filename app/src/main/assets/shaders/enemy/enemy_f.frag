#version 300 es
precision mediump float;
out vec4 FragColor;

void main() {
    vec2 coord = gl_PointCoord - vec2(0.5);
    FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    if (length(coord) > 0.5)  discard;
    if (length(coord) < 0.45) FragColor = vec4(0.0, 0.0, 0.0, 1.0);

}

