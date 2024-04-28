// julia.fs
#version 330
in vec2 vsoTexCoord;
out vec4 fragColor;

uniform sampler1D tex;
uniform vec2 c;

void main(void) {
    vec2 z = vec2(vsoTexCoord.x * 3.0 - 1.5, vsoTexCoord.y * 2.0 - 1.0);
    int maxIter = 300;
    for(int i = 0; i < maxIter; i++) {
        if(length(z) > 2.0) {
            float colorIndex = float(i) / float(maxIter - 1);
            fragColor = texture(tex, colorIndex);
            return;
        }
        z = vec2(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y) + c;
    }
    fragColor = vec4(1.0, 1.0, 1.0, 1.0); 
}
