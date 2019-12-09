#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>

#include "camera.h"
#include "snowman.h"
#include "sun.h"
#include "scenario.h"
#include "observer.h"
#include "controls-manager.h"
#include "scenario.h"

Camera camera;
Observer observer;
Snowman snowman;
Sun sun;
ControlsManager controlManager;
Scenario scenario;

// Função responsável pela especificação dos parâmetros de iluminação
void setIlumination(void)
{
    static const GLfloat luzAmbiente[4] = {0.2, 0.2, 0.2, 1.0};
    static const GLfloat luzDifusa[4] = {0.8, 0.8, 0.8, 1.0};    // "cor"
    static const GLfloat luzEspecular[4] = {1.0, 1.0, 1.0, 1.0}; // "brilho"
    static const GLfloat posicaoLuz[4] = {-70.0, 75.0, 90.0, 1.0};

    // Capacidade de brilho do material
    static const GLfloat especularidade[4] = {1.0, 1.0, 1.0, 1.0};
    static const GLint especMaterial = 60;

    // Define a refletância do material
    glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
    // Define a concentração do brilho
    glMateriali(GL_FRONT, GL_SHININESS, especMaterial);

    // Ativa o uso da luz ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

    // Define os parâmetros da luz de número 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
}

// Função callback de redesenho da janela de visualização
void displayCallback(void)
{
    // Limpa a janela de visualização com a cor
    // de fundo definida previamente
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Chama a função que especifica os parâmetros de iluminação
    setIlumination();

    snowman.draw();
    // sun.draw();
    scenario.draw();

    glutSwapBuffers(); // Executa os comandos OpenGL
}

// Função usada para especificar a posição do observador virtual
// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
    glMatrixMode(GL_PROJECTION); // Especifica sistema de coordenadas de projeção
    glLoadIdentity(); // Inicializa sistema de coordenadas de projeção

    // Especifica a projeção perspectiva
    // (angulo, aspecto, zMin, zMax)
    gluPerspective(camera.angle, camera.aspect, 0.5, 1000);

    setIlumination();

    // Posiciona e orienta o observador
    glTranslatef(observer.position.x, -observer.position.y, -observer.position.z);
    glRotatef(observer.rotation.x, 1, 0, 0);
    glRotatef(observer.rotation.y, 0, 1, 0);

    glMatrixMode(GL_MODELVIEW); // Especifica sistema de coordenadas do modelo
    glLoadIdentity(); // Inicializa sistema de coordenadas do modelo

    camera.look();

    glutPostRedisplay();
}

// Função callback chamada para gerenciar eventos de teclas normais (ESC)
void keyboardCallback(unsigned char tecla, int x, int y)
{
    controlManager.onKeyDownEvent(tecla, x, y);
    EspecificaParametrosVisualizacao();
    glutPostRedisplay();
}

// Função callback chamada para gerenciar eventos de teclas normais (ESC)
void keyboardUpCallback(unsigned char tecla, int x, int y)
{
    controlManager.onKeyUpEvent(tecla, x, y);
    EspecificaParametrosVisualizacao();
    glutPostRedisplay();
}

// Função callback para tratar eventos de teclas especiais
void specialCallback(int tecla, int x, int y)
{
    controlManager.onSpecialKeyDownEvent(tecla, x, y);
    EspecificaParametrosVisualizacao();
    glutPostRedisplay();
}

// Função callback para tratar eventos de teclas especiais
void specialUpCallback(int tecla, int x, int y)
{
    controlManager.onSpecialKeyUpEvent(tecla, x, y);
    EspecificaParametrosVisualizacao();
    glutPostRedisplay();
}

// Função callback para eventos de botões do mouse
void mouseCallback(int button, int state, int x, int y)
{
    controlManager.onMouseButtonClick(button, state, x, y);
    if (state == GLUT_DOWN) observer.rememberValues();
}

// Função callback para eventos de movimento do mouse
void motionCallback(int x, int y)
{
    controlManager.onMouseMotion(x, y);
    EspecificaParametrosVisualizacao();
    glutPostRedisplay();
}

// Função callback chamada pela GLUT a cada intervalo de tempo
void Anima(int value)
{
    sun.animate();
    snowman.animate();

    glutPostRedisplay();
    glutTimerFunc(34, Anima, 1);
}

// Função callback chamada quando o tamanho da janela é alterado
void reshapeCallback(GLsizei width, GLsizei height)
{
    if (height == 0) // Para previnir uma divisão por zero
        height = 1;

    glViewport(0, 0, width, height); // Especifica as dimensões da viewport

    camera.updateAspect(width, height); // Calcula a correção de aspecto
    EspecificaParametrosVisualizacao();
}

// Função responsável por inicializar parâmetros e variáveis
void setup(void)
{
    /* ---------- CALLBACKS ---------------- */
    glutDisplayFunc(displayCallback); // Registra a função callback de redesenho da janela de visualização
    glutReshapeFunc(reshapeCallback); // Registra a função callback de redimensionamento da janela de visualização
    glutKeyboardFunc(keyboardCallback); // Registra a função callback para tratamento das teclas normais
    glutKeyboardUpFunc(keyboardUpCallback);
    glutSpecialFunc(specialCallback); // Registra a função callback para tratamento das teclas especiais
    glutSpecialUpFunc(specialUpCallback);
    glutMouseFunc(mouseCallback); // Registra a função callback para eventos de botões do mouse
    glutMotionFunc(motionCallback); // Registra a função callback para eventos de movimento do mouse

    /* --------------- OpenGL rendering Options --------------------- */
    // Define a cor de fundo da janela de visualização como branca
    glClearColor(0.4f, 0.0f, 1.0f, 1.0f);

    glEnable(GL_COLOR_MATERIAL); // Habilita a definição da cor do material a partir da cor corrente
    glEnable(GL_LIGHTING); //Habilita o uso de iluminação
    glEnable(GL_LIGHT0); // Habilita a luz de número 0
    glEnable(GL_DEPTH_TEST); // Habilita o depth-buffering

    // Habilita o modelo de colorização de Gouraud
    glShadeModel(GL_SMOOTH);

    controlManager.setObserver(&observer);
    controlManager.setCamera(&camera);
    controlManager.setSnowman(&snowman);
}

// Programa Principal
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Define do modo de operação da GLUT
    glutInitWindowPosition(100, 50); // Especifica a posição inicial da janela GLUT
    glutInitWindowSize(800, 600); // Especifica o tamanho inicial em pixels da janela GLUT
    glutCreateWindow("Jovi - Keystone Kapers");
    setup(); // Chama a função responsável por fazer as inicializações
    glutTimerFunc(60, Anima, 1);
    glutMainLoop(); // Inicia o processamento e aguarda interações do usuário
    return 0;
}
