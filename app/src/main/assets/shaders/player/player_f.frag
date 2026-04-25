#version 300 es
precision mediump float;

in vec2 v_uv;
uniform float u_time;
uniform float u_alpha;
uniform int u_glow;

out vec4 FragColor;

void main() {
    /**if (length(v_uv) > 0.5) discard;
    FragColor = vec4(1.0);*/


    vec2 p = v_uv * 2.0 - 1.0;
    float d = length(p);

    // circle mask
    float circle = smoothstep(1.0, 0.96, d);

    // soft outer glow
    float glowPulse = 0.5 + 0.5 * sin(u_time * 2.5 + 1.0);
    float glow = exp(-d * mix(4.0, 2.0, glowPulse)) * smoothstep(1.0, 0.4, d);

    // animated organic edge
    float wave = u_glow == 1 ? 0.0 : sin(atan(p.y, p.x) * 10.0 + u_time * 3.0) * 0.025;
    float edge = smoothstep(1.0 + wave, 0.92 + wave, d);

    vec3 coreColor  = vec3(1.0, 0.3, 0.05);  // deep molten orange
    vec3 innerColor = vec3(1.0, 0.95, 0.4);  // white-hot yellow core

    float pulse = 0.5 + 0.5 * sin(u_time * 2.5);
    float innerRadius = mix(0.5, 0.95, pulse);
    vec3 color = mix(coreColor, innerColor, smoothstep(innerRadius, 0.0, d));
    color = mix(color, coreColor, smoothstep(0.7, 1.0, d));

    color += coreColor * glow * 0.8;

    float alpha = max(edge, glow * 0.35);

    FragColor = vec4(color, alpha * u_alpha);
}