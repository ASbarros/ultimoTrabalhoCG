//*****************************************************
//
// Exemplo3DPiramide.cpp
// Um programa OpenGL que abre uma janela GLUT e desenha
// o wireframe de uma pir�mide.
//
// Navega��o via bot�es do mouse + movimento:
// - bot�o esquerdo: rotaciona objeto
// - bot�o direito:  aproxima/afasta
// - bot�o do meio:  translada objeto
//
// Teclas Home e End fazem zoom in/zoom out
//
// Marcelo Cohen e Isabel H. Manssour
// Este c�digo acompanha o livro
// "OpenGL - Uma Abordagem Pr�tica e Objetiva"
//
//*****************************************************

#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

// Vari�veis para controles de navega��o
GLfloat angle, fAspect;
GLfloat rotX, rotY, rotX_ini, rotY_ini;
GLfloat obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini;
int x_ini,y_ini,bot;

// Define um v�rtice
struct VERT
{
    float x,y,z;	// posi��o no espa�o
};

// Define uma face
struct FACE
{
    int total;	// total de v�rtices
    int ind[4];	// �ndices para o vetor de v�rtices
};

// Define um objeto 3D
struct OBJ
{
    VERT *vertices;		// aponta para os v�rtices
    FACE *faces;		// aponta para as faces
    int total_faces;	// total de faces no objeto
};

// Defini��o dos v�rtices
VERT vertices[] =
{
    { 0, 0, 0 },	// v1 canto inf esquerdo diant.
    { 0, 10, 0 },	// v5 canto sup esquerdo diant.
    { 10, 0, 0 },	// v2 canfo inf direito  diant.
    { 10, 10, 0 },	// v6 canfo sup direito  diant.
};

// Defini��o das faces
FACE faces[] =
{

    { 4, { 1,0,2,3}},	// lado dianteiro

};

// Finalmente, define o objeto pir�mide
OBJ faceParede =
{
    vertices, faces, 1
};

// Desenha um objeto em wireframe
void DesenhaObjetoWireframe(OBJ *objeto)
{

    // Percorre todas as faces
    for(int f=0; f < objeto->total_faces; f++)
    {
        glBegin(GL_QUADS);
        // Percorre todos os v�rtices da face
        for(int v=0; v < objeto->faces[f].total; v++)
            glVertex3f(objeto->vertices[objeto->faces[f].ind[v]].x,
                       objeto->vertices[objeto->faces[f].ind[v]].y,
                       objeto->vertices[objeto->faces[f].ind[v]].z);
        glEnd();
    }
}

// Fun��o callback de redesenho da janela de visualiza��o
void Desenha(void)
{
    // Limpa a janela de visualiza��o com a cor
    // de fundo definida previamente
    glClear(GL_COLOR_BUFFER_BIT);

    // Altera a cor do desenho para preto
    glColor3f(0.0f, 0.0f, 0.0f);

    //glutWireCube(30);
    //glutWireTeapot(30);
    //glutWireCone(10,30, 50, 50);
    //glutWireSphere(5,35,5);
    //glutWireTorus(20, 40, 20, 20);
    //glutWireTetrahedron();
    //glutWireOctahedron();
    //glutWireDodecahedron();
    //glutWireIcosahedron();


    //Desenha o objeto definido anteriormente: uma pir�mide
    //PAREDES
    DesenhaObjetoWireframe(&faceParede);
    //2
    glPushMatrix();
    glTranslated(10, 0, 0);
    DesenhaObjetoWireframe(&faceParede);
    glPopMatrix();

    //3
    glPushMatrix();
    glTranslated(20, 0, 0);
    DesenhaObjetoWireframe(&faceParede);
    glPopMatrix();

    //4
    glPushMatrix();
    glTranslated(30, 0, 0);
    DesenhaObjetoWireframe(&faceParede);
    glPopMatrix();

    //5
    glPushMatrix();
    glTranslated(40, 0, 0);
    DesenhaObjetoWireframe(&faceParede);
    glPopMatrix();

    //6
    glPushMatrix();
    glTranslated(50, 0, 0);
    glRotated(-90, 0, 1, 0);
    DesenhaObjetoWireframe(&faceParede);
    glPopMatrix();

    //7
    glPushMatrix();
    glTranslated(50, 0, 10);
    DesenhaObjetoWireframe(&faceParede);
    glPopMatrix();

    //8
    glPushMatrix();
    glTranslated(60, 0, 10);
    DesenhaObjetoWireframe(&faceParede);
    glPopMatrix();

    //9
    glPushMatrix();
    glTranslated(70, 0, 10);
    glRotated(-90, 0, 1, 0);
    DesenhaObjetoWireframe(&faceParede);
    glPopMatrix();

    //10
    glPushMatrix();
    glTranslated(70, 0, 20);
    glRotated(-90, 0, 1, 0);
    DesenhaObjetoWireframe(&faceParede);
    glPopMatrix();

    //11
    glPushMatrix();
    glTranslated(50, 0, 30);
    DesenhaObjetoWireframe(&faceParede);
    glPopMatrix();

    //12
    glPushMatrix();
    glTranslated(60, 0, 30);
    DesenhaObjetoWireframe(&faceParede);
    glPopMatrix();

    //13
    glPushMatrix();
    glTranslated(50, 0, 30);
    glRotated(-90, 0, 1, 0);
    DesenhaObjetoWireframe(&faceParede);
    glPopMatrix();

    //14
    glPushMatrix();
    glTranslated(50, 0, 40);
    glRotated(-90, 0, 1, 0);
    DesenhaObjetoWireframe(&faceParede);
    glPopMatrix();

    //15
    glPushMatrix();
    glTranslated(40, 0, 50);
    DesenhaObjetoWireframe(&faceParede);
    glPopMatrix();

    //16
    glPushMatrix();
    glTranslated(50, 0, 40);
    glRotated(-90, 0, 1, 0);
    DesenhaObjetoWireframe(&faceParede);
    glPopMatrix();

    //17
    glPushMatrix();
    glTranslated(30, 0, 50);
    DesenhaObjetoWireframe(&faceParede);
    glPopMatrix();

    //18
    glPushMatrix();
    glTranslated(30, 0, 50);
    glRotated(90, 0, 1, 0);
    DesenhaObjetoWireframe(&faceParede);
    glPopMatrix();

    //19
    glPushMatrix();
    glTranslated(20, 0, 40);
    DesenhaObjetoWireframe(&faceParede);
    glPopMatrix();

    //20
    glPushMatrix();
    glTranslated(10, 0, 40);
    DesenhaObjetoWireframe(&faceParede);
    glPopMatrix();

    //21
    glPushMatrix();
    glTranslated(10, 0, 40);
    glRotated(-90, 0, 1, 0);
    DesenhaObjetoWireframe(&faceParede);
    glPopMatrix();

    //22
    glPushMatrix();
    glTranslated(0, 0, 50);
    DesenhaObjetoWireframe(&faceParede);
    glPopMatrix();

    //23
    glPushMatrix();
    glTranslated(0, 0, 50);
    glRotated(90, 0, 1, 0);
    DesenhaObjetoWireframe(&faceParede);
    glPopMatrix();

    //24
    glPushMatrix();
    glTranslated(0, 0, 40);
    glRotated(90, 0, 1, 0);
    DesenhaObjetoWireframe(&faceParede);
    glPopMatrix();

    //25
    glPushMatrix();
    glTranslated(0, 0, 30);
    glRotated(90, 0, 1, 0);
    DesenhaObjetoWireframe(&faceParede);
    glPopMatrix();

    //26
    glPushMatrix();
    glTranslated(0, 0, 20);
    glRotated(90, 0, 1, 0);
    DesenhaObjetoWireframe(&faceParede);
    glPopMatrix();

    //27
    glPushMatrix();
    glTranslated(0, 0, 10);
    glRotated(90, 0, 1, 0);
    DesenhaObjetoWireframe(&faceParede);
    glPopMatrix();

    //CHAO
    glColor3f(0.5f, 0.25f, 0.0f);

    //28 AT� 32
    for(int i = 0; i < 50; i = i + 10) {
        glPushMatrix();
        glTranslated(i, 0, 0);
        glRotated(90, 1, 0, 0);
        DesenhaObjetoWireframe(&faceParede);
        glPopMatrix();
    }
    //33 AT� 39
    for(int i = 0; i < 70; i = i + 10) {
        glPushMatrix();
        glTranslated(i, 0, 10);
        glRotated(90, 1, 0, 0);
        DesenhaObjetoWireframe(&faceParede);
        glPopMatrix();
    }

    //40 AT� 46
    for(int i = 0; i < 70; i = i + 10) {
        glPushMatrix();
        glTranslated(i, 0, 20);
        glRotated(90, 1, 0, 0);
        DesenhaObjetoWireframe(&faceParede);
        glPopMatrix();
    }

    //47 AT� 51
    for(int i = 0; i < 50; i = i + 10) {
        glPushMatrix();
        glTranslated(i, 0, 30);
        glRotated(90, 1, 0, 0);
        DesenhaObjetoWireframe(&faceParede);
        glPopMatrix();
    }

    //52
    glPushMatrix();
    glTranslated(0, 0, 40);
    glRotated(90, 1, 0, 0);
    DesenhaObjetoWireframe(&faceParede);
    glPopMatrix();

    //53
    glPushMatrix();
    glTranslated(30, 0, 40);
    glRotated(90, 1, 0, 0);
    DesenhaObjetoWireframe(&faceParede);
    glPopMatrix();

    //54
    glPushMatrix();
    glTranslated(40, 0, 40);
    glRotated(90, 1, 0, 0);
    DesenhaObjetoWireframe(&faceParede);
    glPopMatrix();


    //TETO
    glColor3f(0.0f, 0.0f, 1.0f);

    //55 AT� 59
    for(int i = 0; i < 50; i = i + 10) {
        glPushMatrix();
        glTranslated(i, 10, 0);
        glRotated(90, 1, 0, 0);
        DesenhaObjetoWireframe(&faceParede);
        glPopMatrix();
    }
    //60 AT� 66
    for(int i = 0; i < 70; i = i + 10) {
        glPushMatrix();
        glTranslated(i, 10, 10);
        glRotated(90, 1, 0, 0);
        DesenhaObjetoWireframe(&faceParede);
        glPopMatrix();
    }

    //67 AT� 73
    for(int i = 0; i < 70; i = i + 10) {
        glPushMatrix();
        glTranslated(i, 10, 20);
        glRotated(90, 1, 0, 0);
        DesenhaObjetoWireframe(&faceParede);
        glPopMatrix();
    }

    //74 AT� 78
    for(int i = 0; i < 50; i = i + 10) {
        glPushMatrix();
        glTranslated(i, 10, 30);
        glRotated(90, 1, 0, 0);
        DesenhaObjetoWireframe(&faceParede);
        glPopMatrix();
    }

    //79
    glPushMatrix();
    glTranslated(0, 10, 40);
    glRotated(90, 1, 0, 0);
    DesenhaObjetoWireframe(&faceParede);
    glPopMatrix();

    //80
    glPushMatrix();
    glTranslated(30, 10, 40);
    glRotated(90, 1, 0, 0);
    DesenhaObjetoWireframe(&faceParede);
    glPopMatrix();

    //81
    glPushMatrix();
    glTranslated(40, 10, 40);
    glRotated(90, 1, 0, 0);
    DesenhaObjetoWireframe(&faceParede);
    glPopMatrix();
    // Executa os comandos OpenGL
    glutSwapBuffers();
}

// Fun��o usada para especificar a posi��o do observador virtual
void PosicionaObservador(void)
{
    // Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);
    // Inicializa sistema de coordenadas do modelo
    glLoadIdentity();
    // Posiciona e orienta o observador
    glTranslatef(-obsX,-obsY,-obsZ);
    glRotatef(rotX,1,0,0);
    glRotatef(rotY,0,1,0);
}

// Fun��o usada para especificar o volume de visualiza��o
void EspecificaParametrosVisualizacao(void)
{
    // Especifica sistema de coordenadas de proje��o
    glMatrixMode(GL_PROJECTION);
    // Inicializa sistema de coordenadas de proje��o
    glLoadIdentity();

    // Especifica a proje��o perspectiva(angulo,aspecto,zMin,zMax)
    gluPerspective(angle,fAspect,0.1,1200);

    PosicionaObservador();
}

// Fun��o callback chamada quando o tamanho da janela � alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    // Para previnir uma divis�o por zero
    if ( h == 0 )
        h = 1;

    // Especifica as dimens�es da viewport
    glViewport(0, 0, w, h);

    // Calcula a corre��o de aspecto
    fAspect = (GLfloat)w/(GLfloat)h;

    EspecificaParametrosVisualizacao();
}

// Fun��o callback chamada para gerenciar eventos de teclas normais (ESC)
void Teclado (unsigned char tecla, int x, int y)
{
    if(tecla==27) // ESC ?
    {
        // Libera mem�ria e finaliza programa
        exit(0);
    }
}

// Fun��o callback para tratar eventos de teclas especiais
void TeclasEspeciais (int tecla, int x, int y)
{
    switch (tecla)
    {
    case GLUT_KEY_HOME:
        if(angle>=10)
            angle -=5;
        break;
    case GLUT_KEY_END:
        if(angle<=150)
            angle +=5;
        break;
    }
    EspecificaParametrosVisualizacao();
    glutPostRedisplay();
}

// Fun��o callback para eventos de bot�es do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
    if(state==GLUT_DOWN)
    {
        // Salva os par�metros atuais
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

// Fun��o callback para eventos de movimento do mouse
#define SENS_ROT	10.0
#define SENS_OBS	15.0
#define SENS_TRANSL	30.0
void GerenciaMovim(int x, int y)
{
    // Bot�o esquerdo ?
    if(bot==GLUT_LEFT_BUTTON)
    {
        // Calcula diferen�as
        int deltax = x_ini - x;
        int deltay = y_ini - y;
        // E modifica �ngulos
        rotY = rotY_ini - deltax/SENS_ROT;
        rotX = rotX_ini - deltay/SENS_ROT;
    }
    // Bot�o direito ?
    else if(bot==GLUT_RIGHT_BUTTON)
    {
        // Calcula diferen�a
        int deltaz = y_ini - y;
        // E modifica dist�ncia do observador
        obsZ = obsZ_ini + deltaz/SENS_OBS;
    }
    // Bot�o do meio ?
    else if(bot==GLUT_MIDDLE_BUTTON)
    {
        // Calcula diferen�as
        int deltax = x_ini - x;
        int deltay = y_ini - y;
        // E modifica posi��es
        obsX = obsX_ini + deltax/SENS_TRANSL;
        obsY = obsY_ini - deltay/SENS_TRANSL;
    }
    PosicionaObservador();
    glutPostRedisplay();
}

// Fun��o respons�vel por inicializar par�metros e vari�veis
void Inicializa (void)
{
    // Define a cor de fundo da janela de visualiza��o como branca
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // Inicializa a vari�vel que especifica o �ngulo da proje��o
    // perspectiva
    angle=60;

    // Inicializa as vari�veis usadas para alterar a posi��o do
    // observador virtual
    rotX = 0;
    rotY = 0;
    obsX = obsY = 0;
    obsZ = 20;
}

// Programa Principal
int main(void)
{
    // Define do modo de opera��o da GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // Especifica a posi��o inicial da janela GLUT
    glutInitWindowPosition(5,5);

    // Especifica o tamanho inicial em pixels da janela GLUT
    glutInitWindowSize(450,450);

    // Cria a janela passando como argumento o t�tulo da mesma
    glutCreateWindow("Desenho do wireframe de um cubo");

    // Registra a fun��o callback de redesenho da janela de visualiza��o
    glutDisplayFunc(Desenha);

    // Registra a fun��o callback de redimensionamento da janela de visualiza��o
    glutReshapeFunc(AlteraTamanhoJanela);

    // Registra a fun��o callback para eventos de bot�es do mouse
    glutMouseFunc(GerenciaMouse);

    // Registra a fun��o callback para eventos de movimento do mouse
    glutMotionFunc(GerenciaMovim);

    // Registra a fun��o callback para tratamento das teclas normais
    glutKeyboardFunc (Teclado);

    // Registra a fun��o callback para tratamento das teclas especiais
    glutSpecialFunc (TeclasEspeciais);

    // Chama a fun��o respons�vel por fazer as inicializa��es
    Inicializa();

    // Inicia o processamento e aguarda intera��es do usu�rio
    glutMainLoop();

    return 0;
}
