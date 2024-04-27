//basic.fs
#version 330
in  vec2 vsoTexCoord;
/* sortie du frament shader : une couleur */
out vec4 fragColor;

uniform sampler2D tex;
uniform float temps;

void main(void) {
  vec2 d = vsoTexCoord - vec2(0.5);
  float a = atan(d.y, d.x);
  float dist = length(d);
  a += pow(0.0001 * temps, 4.0) / (1.0 + dist);
  vec2 ct = vec2(0.5 + dist * cos(a), 0.5 + dist * sin(a));
  fragColor = texture(tex, ct);
}
