#include <GL4D/gl4du.h>
#include <GL4D/gl4dp.h>
#include <GL4D/gl4dg.h>
#include <GL4D/gl4duw_SDL2.h>
#include <SDL_image.h>
#include <assert.h>
#include <math.h>

/* Prototypes des fonctions statiques */
static void initialiser(void);
static void dessiner(void);
static void quitter(void);

static GLfloat temps = 0.0;
static GLfloat parametresJulia[2] = {0.0f, 0.0f}; // Paramètres complexes pour Julia
static GLuint idProgrammeJulia = 0;
static GLuint quad = 0;
static GLuint identifiantsTextures[2] = {0, 0};
static int largeurFenetre = 800, hauteurFenetre = 600;

int main(int argc, char **argv) {
    if (!gl4duwCreateWindow(argc, argv, "GL4Dummies", 20, 20, largeurFenetre, hauteurFenetre, GL4DW_RESIZABLE | GL4DW_SHOWN))
        return 1;
    initialiser();
    atexit(quitter);
    gl4duwDisplayFunc(dessiner);
    gl4duwMainLoop();
    return 0;
}

/* Initialisation des paramètres OpenGL et des données. */
static void initialiser(void) {
    quad = gl4dgGenQuadf();
    idProgrammeJulia = gl4duCreateProgram("<vs>shaders/basic.vs", "<fs>shaders/julia.fs", NULL);

    glGenTextures(2, identifiantsTextures);
    glBindTexture(GL_TEXTURE_2D, identifiantsTextures[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, 1024, 1024, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);

    GLuint couleurs[3] = { RGB(0, 0, 255), RGB(0, 255, 0), RGB(255, 255, 255) }; // Bleu, Vert, Blanc
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_1D, identifiantsTextures[1]);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, couleurs);
}

/* Dessin dans le contexte OpenGL actif. */
static void dessiner(void) {
    // Arrête l'animation de Julia après 10 secondes
    if (temps >= 10.0) {
        return; 
    }
    
    temps += 0.01;
    parametresJulia[0] = 0.7885 * cos(temps);
    parametresJulia[1] = 0.7885 * sin(temps);
    glViewport(0, 0, largeurFenetre, hauteurFenetre);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(idProgrammeJulia);
    glUniform2fv(glGetUniformLocation(idProgrammeJulia, "c"), 1, parametresJulia); // Animation de Julia

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_1D, identifiantsTextures[1]);
    glUniform1i(glGetUniformLocation(idProgrammeJulia, "tex"), 0);
    gl4dgDraw(quad);
    glBindTexture(GL_TEXTURE_1D, 0);

    glUseProgram(0);
}


/* Libération des ressources OpenGL à la sortie du programme. */
static void quitter(void) {
    if (identifiantsTextures[0])
        glDeleteTextures(2, identifiantsTextures);
    if (quad)
        glDeleteBuffers(1, &quad);
    glDeleteProgram(idProgrammeJulia);
    gl4duClean(GL4DU_ALL);
}
