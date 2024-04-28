//sphere.fs
#version 330 core
uniform float opacity;
in vec3 vNormal;
in vec3 vEye;

out vec4 fragColor;

void main() {
    vec3 N = normalize(vNormal);
    vec3 L = normalize(-vEye);
    vec3 V = normalize(vEye);
    
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 objectColor = vec3(0.5, 0.8, 1.0);
    
    // Ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    
    // Diffuse
    float diff = max(dot(N, L), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // Specular
    float specularStrength = 0.5;
    float shininess = 32.0;
    vec3 viewDir = normalize(-vEye);
    vec3 reflectDir = reflect(-L, N);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specularStrength * spec * lightColor;  

    vec3 result = (ambient + diffuse + specular) * objectColor;
    
    fragColor = vec4(result, opacity);
}

