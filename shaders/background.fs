#version 330 core
out vec4 FragColor;
uniform float time;

void main() {
    float r = 0.5 + 0.5 * sin(time * 0.5);
    float g = 0.5 + 0.5 * sin(time * 0.7);
    float b = 0.5 + 0.5 * sin(time * 0.9);
    FragColor = vec4(r, g, b, 1.0);
}
