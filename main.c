#include <GL4D/gl4du.h>
#include <GL4D/gl4dp.h>
#include <GL4D/gl4dg.h>
#include <GL4D/gl4duw_SDL2.h>
#include <SDL_image.h>
#include <assert.h>
#include <math.h>

/* Prototypes des fonctions statiques */
static void init(void);
static void draw(void);
static void quitter(void);

static GLfloat dernierTemps = 0.0; // Temps du dernier dessin
static GLfloat tempsTotal = 0.0; // Temps total écoulé depuis le début du programme
static GLfloat tempsJulia = 0.0; // Temps écoulé pour l'animation de Julia
static GLfloat parametresJulia[2] = {0.0f, 0.0f}; // Paramètres complexes pour Julia
static GLuint idProgrammeJulia = 0;
static GLuint quad = 0;
static GLuint identifiantsTextures[2] = {0, 0};
static GLuint _sphereId = 0;
static GLuint _pId = 0;
static int largeurFenetre = 800, hauteurFenetre = 600;

int main(int argc, char **argv) {
    if (!gl4duwCreateWindow(argc, argv, "GL4Dummies", 20, 20, largeurFenetre, hauteurFenetre, GL4DW_RESIZABLE | GL4DW_SHOWN))
        return 1;
    init();
    atexit(quitter);
    gl4duwDisplayFunc(draw);
    gl4duwMainLoop();
    return 0;
}

/* Initialisation des paramètres OpenGL et des données. */
static void init(void) {
    quad = gl4dgGenQuadf();
    idProgrammeJulia = gl4duCreateProgram("<vs>shaders/basic.vs", "<fs>shaders/julia.fs", NULL);


    GLuint couleurs[3] = { RGB(0, 0, 255), RGB(0, 255, 0), RGB(255, 255, 255) }; // Bleu, Vert, Blanc
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_1D, identifiantsTextures[1]);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, couleurs);
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    _sphereId = gl4dgGenSpheref(20, 20);
    _pId = gl4duCreateProgram("<vs>shaders/sphere.vs", "<fs>shaders/sphere.fs", NULL);

    gl4duGenMatrix(GL_FLOAT, "modelViewMatrix");
    gl4duGenMatrix(GL_FLOAT, "projectionMatrix");

    gl4duBindMatrix("projectionMatrix");
    gl4duLoadIdentityf();
    gl4duPerspectivef(70.0, 800.0 / 600.0, 1.0, 1000.0);

    gl4duBindMatrix("modelViewMatrix");
}


/* Dessin dans le contexte OpenGL actif. */
static void draw(void) {
    GLfloat tempsEcoule = 0.001f * (GLfloat)(SDL_GetTicks() - dernierTemps);
    dernierTemps = SDL_GetTicks(); // Met à jour le dernier temps
    tempsTotal += tempsEcoule;

    glViewport(0, 0, largeurFenetre, hauteurFenetre);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Activer le mélange pour la transparence
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Continuer à dessiner Julia tant que la sphère n'est pas totalement opaque
    if (tempsTotal < 15.0) { // La sphère atteint son opacité maximale à tempsTotal = 15.0
        tempsJulia += tempsEcoule;
        parametresJulia[0] = 0.7885 * cos(tempsJulia);
        parametresJulia[1] = 0.7885 * sin(tempsJulia);

        glUseProgram(idProgrammeJulia);
        glUniform2fv(glGetUniformLocation(idProgrammeJulia, "c"), 1, parametresJulia);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_1D, identifiantsTextures[1]);
        glUniform1i(glGetUniformLocation(idProgrammeJulia, "tex"), 0);
        gl4dgDraw(quad);
        glBindTexture(GL_TEXTURE_1D, 0);

        glUseProgram(0);
    }

    // Commencer et continuer à dessiner la sphère après 10 secondes
    if (tempsTotal > 10.0) {
        GLfloat opacity = fmin((tempsTotal - 10.0) / 5.0, 1.0);  // Augmenter l'opacité sur 5 secondes jusqu'à 1.0

        glUseProgram(_pId);
        glUniform1f(glGetUniformLocation(_pId, "opacity"), opacity);

        gl4duBindMatrix("modelViewMatrix");
        gl4duLoadIdentityf();
        gl4duTranslatef(0.0f, 0.0f, -2.0f);
        gl4duRotatef(gl4dGetElapsedTime() * 0.1, 0, 1, 0);

        gl4duSendMatrices();
        gl4dgDraw(_sphereId);
        glUseProgram(0);
    }

    glDisable(GL_BLEND);
}


/* Libération des ressources OpenGL à la sortie du programme. */
static void quitter(void) {
    if (identifiantsTextures[0])
        glDeleteTextures(2, identifiantsTextures);
    if (quad)
        glDeleteBuffers(1, &quad);
    glDeleteProgram(idProgrammeJulia);
    gl4duClean(GL4DU_ALL);

    gl4dgDelete(_sphereId);
    glDeleteProgram(_pId);
}
