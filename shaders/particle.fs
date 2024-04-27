#version 330 core
in float fragLife;
out vec4 FragColor;

void main() {
    float alpha = fragLife / 10.0; // Assume max life is 10 seconds
    FragColor = vec4(1.0, 0.5, 0.0, alpha); // Orange color with fading alpha
}
