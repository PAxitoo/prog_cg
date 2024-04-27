#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 velocity;
layout(location = 2) in float life;

out float fragLife;

void main() {
    gl_Position = vec4(position, 1.0);
    fragLife = life;
}
