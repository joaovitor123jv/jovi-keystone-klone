#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>

#include "snowman.h"
#include "scenario.h"

// Variáveis para controles de navegação
GLfloat angle, fAspect, angsol;
GLfloat rotX, rotY, rotX_ini, rotY_ini;
GLfloat obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini;
int x_ini, y_ini, bot, dx, dy, dz;

Snowman snowman;

// Função responsável pela especificação dos parâmetros de iluminação
void setIlumination(void)
{
    GLfloat luzAmbiente[4] = {0.2, 0.2, 0.2, 1.0};
    GLfloat luzDifusa[4] = {0.8, 0.8, 0.8, 1.0};    // "cor"
    GLfloat luzEspecular[4] = {1.0, 1.0, 1.0, 1.0}; // "brilho"
    GLfloat posicaoLuz[4] = {-70.0, 75.0, 90.0, 1.0};

    // Capacidade de brilho do material
    GLfloat especularidade[4] = {1.0, 1.0, 1.0, 1.0};
    GLint especMaterial = 60;

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

    glPushMatrix();
        glColor3f(1.0, 1.0, 0.0);
        glTranslatef(-70.0, 80.0, -100.0);
        glRotatef(angsol, 0, 0, 1);
        glutSolidSphere(15, 15, 10);
    glPopMatrix();

    drawScenario();

    // Executa os comandos OpenGL
    glutSwapBuffers();
}

// Função usada para especificar a posição do observador virtual

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
    // Especifica sistema de coordenadas de projeção
    glMatrixMode(GL_PROJECTION);
    // Inicializa sistema de coordenadas de projeção
    glLoadIdentity();

    // Especifica a projeção perspectiva
    // (angulo, aspecto, zMin, zMax)
    gluPerspective(angle, fAspect, 0.5, 1000);

    setIlumination();
    // Posiciona e orienta o observador
    glTranslatef(-obsX, -obsY, -obsZ);
    glRotatef(rotX, 1, 0, 0);
    glRotatef(rotY, 0, 1, 0);

    // Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);
    // Inicializa sistema de coordenadas do modelo
    glLoadIdentity();

    gluLookAt(0 + dx, 0 + dy, 50 + dx, 0 + dx, 10 + dy, 0 + dz, 0, 1, 0);

    glutPostRedisplay();
}

// Função callback chamada para gerenciar eventos de teclas normais (ESC)
void keyboardCallback(unsigned char tecla, int x, int y)
{
    switch (tecla)
    {
    case 27:
        exit(0);
        break;
    case 'a':
        dx++;
        break;
    case 'z':
        dx--;
        break;
    case 's':
        dy++;
        break;
    case 'x':
        dy--;
        break;
    case 'd':
        dz++;
        break;
    case 'c':
        dz--;
        break;
    }

    EspecificaParametrosVisualizacao();
    glutPostRedisplay();
}

// Função callback para tratar eventos de teclas especiais
void specialCallback(int tecla, int x, int y)
{
    switch (tecla)
    {
    case GLUT_KEY_HOME:
        if (angle >= 10)
            angle -= 5;
        break;
    case GLUT_KEY_END:
        if (angle <= 150)
            angle += 5;
        break;
    case GLUT_KEY_F10:
        snowman.toggleRotation();
        break;
    case GLUT_KEY_UP:
        snowman.position.y += 2;
        break;
    case GLUT_KEY_DOWN:
        snowman.position.y -= 2;
        break;
    case GLUT_KEY_LEFT:
        snowman.position.x -= 2;
        break;
    case GLUT_KEY_RIGHT:
        snowman.position.x += 2;
        break;
    case GLUT_KEY_F3:
        snowman.position.z += 2;
        break;
    case GLUT_KEY_F4:
        snowman.position.z -= 2;
        break;
    }
    EspecificaParametrosVisualizacao();
    glutPostRedisplay();
}

// Função callback para eventos de botões do mouse
void mouseCallback(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN)
    {
        // Salva os parâmetros atuais
        x_ini = x;
        y_ini = y;
        obsX_ini = obsX;
        obsY_ini = obsY;
        obsZ_ini = obsZ;
        rotX_ini = rotX;
        rotY_ini = rotY;
        bot = button;
    }
    else
        bot = -1;
}

// Função callback para eventos de movimento do mouse
#define SENS_ROT 5.0
#define SENS_OBS 10.0
#define SENS_TRANSL 10.0
void motionCallback(int x, int y)
{
    // Botão esquerdo ?
    if (bot == GLUT_LEFT_BUTTON)
    {
        // Calcula diferenças
        int deltax = x_ini - x;
        int deltay = y_ini - y;
        // E modifica ângulos
        rotY = rotY_ini - deltax / SENS_ROT;
        rotX = rotX_ini - deltay / SENS_ROT;
    }
    // Botão direito ?
    else if (bot == GLUT_RIGHT_BUTTON)
    {
        // Calcula diferença
        int deltaz = y_ini - y;
        // E modifica distância do observador
        obsZ = obsZ_ini + deltaz / SENS_OBS;
    }
    // Botão do meio ?
    else if (bot == GLUT_MIDDLE_BUTTON)
    {
        // Calcula diferenças
        int deltax = x_ini - x;
        int deltay = y_ini - y;
        // E modifica posições
        obsX = obsX_ini + deltax / SENS_TRANSL;
        obsY = obsY_ini - deltay / SENS_TRANSL;
    }
    EspecificaParametrosVisualizacao();
    glutPostRedisplay();
}

// Função callback chamada pela GLUT a cada intervalo de tempo
void Anima(int value)
{
    // Muda o angulo de rotação, e se chegar a 360, passa para zero
    if (++angsol > 360.0f)
        angsol = 0.0f;

    angsol += 10;
    snowman.animate();

    glutPostRedisplay();
    glutTimerFunc(60, Anima, 1);
}

// Função callback chamada quando o tamanho da janela é alterado
void reshapeCallback(GLsizei w, GLsizei h)
{
    // Para previnir uma divisão por zero
    if (h == 0)
        h = 1;

    // Especifica as dimensões da viewport
    glViewport(0, 0, w, h);

    // Calcula a correção de aspecto
    fAspect = (GLfloat)w / (GLfloat)h;

    EspecificaParametrosVisualizacao();
}

// Função responsável por inicializar parâmetros e variáveis
void setup(void)
{
    // Define a cor de fundo da janela de visualização como branca
    glClearColor(0.4f, 0.0f, 1.0f, 1.0f);

    // Habilita a definição da cor do material a partir da cor corrente
    glEnable(GL_COLOR_MATERIAL);
    //Habilita o uso de iluminação
    glEnable(GL_LIGHTING);
    // Habilita a luz de número 0
    glEnable(GL_LIGHT0);
    // Habilita o depth-buffering
    glEnable(GL_DEPTH_TEST);

    // Habilita o modelo de colorização de Gouraud
    glShadeModel(GL_SMOOTH);

    // Inicializa a variável que especifica o ângulo da projeção
    // perspectiva
    angle = 45;

    // Inicializa as variáveis usadas para alterar a posição do
    // observador virtual
    rotX = 0;
    rotY = 0;
    obsX = obsY = 0;
    obsZ = 150;

    dx = 0;
    dy = 0;
    dz = 0;
}

// Programa Principal
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    // Define do modo de operação da GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // Especifica a posição inicial da janela GLUT
    glutInitWindowPosition(5, 5);

    // Especifica o tamanho inicial em pixels da janela GLUT
    glutInitWindowSize(800, 600);

    // Cria a janela passando como argumento o título da mesma
    glutCreateWindow("Cubo RGB");

    // Registra a função callback de redesenho da janela de visualização
    glutDisplayFunc(displayCallback);

    // Registra a função callback de redimensionamento da janela de visualização
    glutReshapeFunc(reshapeCallback);

    // Registra a função callback para tratamento das teclas normais
    glutKeyboardFunc(keyboardCallback);

    // Registra a função callback para tratamento das teclas especiais
    glutSpecialFunc(specialCallback);

    // Registra a função callback para eventos de botões do mouse
    glutMouseFunc(mouseCallback);

    // Registra a função callback para eventos de movimento do mouse
    glutMotionFunc(motionCallback);

    // Chama a função responsável por fazer as inicializações
    setup();

    glutTimerFunc(60, Anima, 1);

    // Inicia o processamento e aguarda interações do usuário
    glutMainLoop();

    return 0;
}
