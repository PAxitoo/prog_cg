#version 330 core
out vec4 fragColor;

uniform float time; // Temps pour permettre une animation ou transition
uniform int iter;  // Nombre d'itérations pour contrôler la densité de la fractale

void main() {
    vec2 z = vec2(0.0, 0.0);  // Point initial
    for (int i = 0; i < iter; i++) {
        float r = rand(z);  // Générer un nombre aléatoire basé sur z pour la sélection de la transformation
        if (r < 0.85) {
            z = 0.85 * z + 0.04 * vec2(z.y, -z.x) + vec2(0.0, 1.6);
        } else if (r < 0.92) {
            z = 0.2 * z - 0.26 * vec2(-z.y, z.x) + vec2(0.0, 1.6);
        } else if (r < 0.99) {
            z = -0.15 * z + 0.28 * vec2(z.y, -z.x) + vec2(0.0, 0.44);
        } else {
            z = 0.0 * z + vec2(0.0, 0.4);
        }
    }
    fragColor = vec4(z, 0.0, 1.0);  // Colorier le point selon sa position
}
