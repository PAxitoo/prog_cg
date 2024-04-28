/*basic.vs*/
#version 330

layout (location = 0) in vec2 vsiPosition;
layout (location = 2) in vec2 vsiTexCoord; // Assurez-vous que l'index de location est correct

out vec2 vsoTexCoord;

void main(void) {
  gl_Position = vec4(vsiPosition, 0.0, 1.0); // Position transformée
  vsoTexCoord = vsiTexCoord; // Passage correct des coordonnées de texture
}

