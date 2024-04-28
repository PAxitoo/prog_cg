/*sphere.vs*/
#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

out vec3 vNormal;
out vec3 vEye;

void main() {
    vNormal = mat3(transpose(inverse(modelViewMatrix))) * normal;
    vec4 eye = modelViewMatrix * vec4(position, 1.0);
    vEye = eye.xyz;
    gl_Position = projectionMatrix * eye;
}
