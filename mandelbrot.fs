#version 330 core
out vec4 FragColor;
uniform vec2 center;
uniform float scale;
uniform float aspectRatio;
uniform int maxIterations;

void main() {
    vec2 fragCoord = gl_FragCoord.xy;
    vec2 c = (fragCoord - vec2(400.0, 225.0)) * vec2(scale, scale * aspectRatio) + center;
    vec2 z = vec2(0.0, 0.0);
    int i;
    for(i = 0; i < maxIterations && dot(z, z) < 4.0; ++i) {
        z = vec2(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y) + c;
    }
    float t = float(i) / float(maxIterations);
    FragColor = vec4(t, t, t, 1.0);
}
