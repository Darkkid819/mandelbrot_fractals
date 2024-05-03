#version 330 core
out vec4 FragColor;
uniform vec2 center;
uniform float scale;
uniform float aspectRatio;
uniform int maxIterations;

vec3 hsv2rgb(vec3 c) {
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main() {
    vec2 fragCoord = gl_FragCoord.xy;
    vec2 c = (fragCoord - vec2(400.0, 225.0)) * vec2(scale, scale * aspectRatio) + center;
    vec2 z = vec2(0.0, 0.0);
    int i;
    for (i = 0; i < maxIterations && dot(z, z) < 4.0; ++i) {
        z = vec2(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y) + c;
    }
    float t = float(i) / float(maxIterations);
    if (i == maxIterations) {
        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    } else {
        float hue = 0.3 * t; 
        vec3 color = hsv2rgb(vec3(hue, 0.8, 1.0));
        FragColor = vec4(color, 1.0);
    }
}
