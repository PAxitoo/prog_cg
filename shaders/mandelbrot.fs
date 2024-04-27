//mandelbrot.fs
#version 330
in  vec2 vsoTexCoord;
/* sortie du frament shader : une couleur */
out vec4 fragColor;

uniform sampler1D tex;

void main(void) {
  vec2 z = vec2(0); // z0 = 0
  vec2 c = vec2(vsoTexCoord.x * 2.5 - 2.0, vsoTexCoord.y * 2.5 - 1.25);
  // calculs successifs de z
  for(int i = 0; i < 100; i++) {
    vec2 oz = z;
    float m;
    z.x = oz.x * oz.x - oz.y * oz.y + c.x;
    z.y = 2.0 * oz.x * oz.y + c.y;
    if(i > 10 && (m = length(z)) < 4.0) {
      fragColor = vec4(1.0) * texture(tex, float(int(m * 20.0)) / 20.0);
      return;
    }
  }
  fragColor = vec4(1.0, 1.0, 0.8, 1.0);
}
