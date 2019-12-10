#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>

#include "camera.h"
#include "snowman.h"
#include "scenario.h"
#include "observer.h"
#include "controls-manager.h"
#include "scenario.h"
#include "ball.h"
#include "car.h"

Camera camera;
Observer observer;
Snowman snowman;
ControlsManager controlManager;
Scenario scenario;

std::vector<Ball> balls;
std::vector<Car> cars;


void generateBalls()
{
    bool shouldCreateObject = (rand() % 100 > 98) ? true : false;
    if(shouldCreateObject)
    {
        int floorNumber = rand() % 4;
        int direction = rand() % 2;

        balls.push_back(Ball(floorNumber, (direction == 0) ? DIRECTION::LEFT : DIRECTION::RIGHT, 1));
        printf("Generated BALL on FLOOR NUMBER %d\n", floorNumber);
    }
}

void generateCars()
{
    bool shouldCreateObject = (rand() % 100 > 98) ? true : false;
    if(shouldCreateObject)
    {
        int floorNumber = rand() % 4;
        int direction = rand() % 2;

        cars.push_back(Car(floorNumber, (direction == 0) ? DIRECTION::LEFT : DIRECTION::RIGHT, 2));
        printf("Generated CAR on FLOOR NUMBER %d\n", floorNumber);
    }
}


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
    scenario.draw();

    if (balls.size() > 0)
    {
        for (unsigned int i = 0; i < balls.size(); i++)
        {
            balls.at(i).draw();
        }
    }

    if (cars.size() > 0)
    {
        for (unsigned int i = 0; i < cars.size(); i++)
        {
            cars.at(i).draw();
        }
    }

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
    if(focusPlayer)
    {
        gluPerspective(90, camera.aspect, 0.5, 1000);
    }
    else
    {
        gluPerspective(camera.angle, camera.aspect, 0.5, 1000);
    }

    setIlumination();

    if(focusPlayer)
    {
        if(snowman.rotation == 90)
        {
            glTranslatef(0, -(snowman.position.y + 40), (snowman.position.x - 10));
        }
        else
        {
            glTranslatef(0, -(snowman.position.y + 40), -(snowman.position.x + 10));
        }
        // glRotatef(, 1, 0, 0);
        glRotatef(-snowman.rotation, 0, 1, 0);
    }
    else
    {
        // Posiciona e orienta o observador
        glTranslatef(observer.position.x, -observer.position.y, -observer.position.z);
        glRotatef(observer.rotation.x, 1, 0, 0);
        glRotatef(observer.rotation.y, 0, 1, 0);
    }

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
    snowman.animate();
    scenario.interact(&snowman);
    scenario.animate(&snowman);

    generateBalls();
    if(balls.size() > 0)
    {
        for (unsigned int i = 0; i < balls.size(); i++)
        {
            balls.at(i).animate();
            if(balls.at(i).hasCollided(&snowman))
            {
                printf("COLISÃO DETECTADA");
                Sleep(1000);
            }
        }
    }

    generateCars();
    if(cars.size() > 0)
    {
        for (unsigned int i = 0; i < cars.size(); i++)
        {
            cars.at(i).animate();
            if(cars.at(i).hasCollided(&snowman))
            {
                Sleep(1000);
            }
        }
    }

    observer.follow(&snowman);
    EspecificaParametrosVisualizacao();

    glutPostRedisplay();
    glutTimerFunc(34, Anima, 1);
    // glutTimerFunc(90, Anima, 1);
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

    glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
    glutKeyboardFunc(keyboardCallback); // Registra a função callback para tratamento das teclas normais
    glutKeyboardUpFunc(keyboardUpCallback);
    glutSpecialFunc(specialCallback); // Registra a função callback para tratamento das teclas especiais
    glutSpecialUpFunc(specialUpCallback);
    glutMouseFunc(mouseCallback); // Registra a função callback para eventos de botões do mouse
    glutMotionFunc(motionCallback); // Registra a função callback para eventos de movimento do mouse

    /* --------------- OpenGL rendering Options --------------------- */
    // Define a cor de fundo da janela de visualização como branca
    glClearColor(0.6f, 0.6f, 1.0f, 1.0f);

    glEnable(GL_COLOR_MATERIAL); // Habilita a definição da cor do material a partir da cor corrente
    glEnable(GL_LIGHTING); //Habilita o uso de iluminação
    glEnable(GL_LIGHT0); // Habilita a luz de número 0
    glEnable(GL_DEPTH_TEST); // Habilita o depth-buffering

    // Habilita o modelo de colorização de Gouraud
    glShadeModel(GL_SMOOTH);

    focusPlayer = false;

    controlManager.setObserver(&observer);
    controlManager.setCamera(&camera);
    controlManager.setSnowman(&snowman);
}

// Programa Principal
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Define do modo de operação da GLUT
    glutInitWindowPosition(10, 10); // Especifica a posição inicial da janela GLUT
    glutInitWindowSize(1300, 700); // Especifica o tamanho inicial em pixels da janela GLUT
    glutCreateWindow("Jovi - Keystone Kapers");
    setup(); // Chama a função responsável por fazer as inicializações
    glutTimerFunc(60, Anima, 1);
    glutMainLoop(); // Inicia o processamento e aguarda interações do usuário
    return 0;
}
