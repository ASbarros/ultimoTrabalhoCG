//*****************************************************
//
// Exemplo3DPiramide.cpp
// Um programa OpenGL que abre uma janela GLUT e desenha
// o wireframe de uma pirâmide.
//
// Navegação via botões do mouse + movimento:
// - botão esquerdo: rotaciona objeto
// - botão direito:  aproxima/afasta
// - botão do meio:  translada objeto
//
// Teclas Home e End fazem zoom in/zoom out
//
// Marcelo Cohen e Isabel H. Manssour
// Este código acompanha o livro
// "OpenGL - Uma Abordagem Prática e Objetiva"
//
//*****************************************************

#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

// Variáveis para controles de navegação
GLfloat angle, fAspect;
GLfloat rotX, rotY, rotX_ini, rotY_ini;
GLfloat obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini;
int x_ini,y_ini,bot;

// Define um vértice
struct VERT
{
    float x,y,z;	// posição no espaço
};

// Define uma face
struct FACE
{
    int total;	// total de vértices
    int ind[8];	// índices para o vetor de vértices
};

// Define um objeto 3D
struct OBJ
{
    VERT *vertices;		// aponta para os vértices
    FACE *faces;		// aponta para as faces
    int total_faces;	// total de faces no objeto
};

// Definição dos vértices
VERT vertices[] =
{
    { 0, 0, 0 },	// v0 canto inf esquerdo diant.
    { 0, 10, 0 },	// v1 canto sup esquerdo diant.
    { 10, 0, 0 },	// v2 canfo inf direito  diant.
    { 10, 10, 0 },	// v3 canfo sup direito  diant.
    { 0,6,0 },  // 4
    {10,6,0},    // 5
    {5,0,0},    // 6
    {3.5,6,0}, // 7
    {3.5,0,0}, // 8
    {6.5,6,0}, // 9
    {6.5,0,0}, // 10
    {50,10,0}, // 11
    {25,25,25}, // 12  Bico do telhado
    {0,10,50}, // 13
    {50,10,50}, // 14
    {50,10,30}, // 15
    {70,10,30}, // 16
    {70,10,10}, // 17
    {50,10,10}, // 18
    {50,10,0}, // 19
    {3.5,10,0}, // 20
    {6.5,10,0}, // 21
    {10,10,50}, // 22
    {30,10,50}, // 23
    {30,10,40}, // 23
    {10,10,40}, // 23


};
// Definição das faces
FACE faces[] =
{
    { 4, { 1,0,2,3}},	// lado dianteiro
};
FACE faces2[] =
{
    { 4, { 0,8,7,1}},
    { 4, { 1,7,9,3}},
    { 4, { 9,10,2,3}},
};
FACE faces3[] =
{
    { 3, { 1,12,11}},
    { 3, { 1,13,12}},
    { 3, { 13,14,12}},
    { 3, { 14,15,12}},
    { 3, { 15,16,12}},
    { 3, { 16,17,12}},
    { 3, { 17,18,12}},
    { 3, { 18,19,12}},
    { 4, { 22,23,24,25}},

};
FACE faces4[] =
{
    { 6, { 0,10,9,7,20,1}},
    { 4, { 10,2,3,21}},
};
OBJ telhado =
{
    vertices, faces3, 9
};
// Finalmente, define o objeto pirâmide
OBJ faceParede =
{
    vertices, faces, 1
};
OBJ facePorta =
{
    vertices, faces2, 3
};
OBJ faceJanela =
{
    vertices, faces4, 2
};
// Posição da fonte de luz
GLfloat posLuz[4] = { 0.0, 50.0, 50.0, 1.0 };

// Função responsável pela especificação dos parâmetros de iluminação
void DefineIluminacao (void)
{
    GLfloat luzAmbiente[4]= {0.2,0.2,0.2,1.0};
    GLfloat luzDifusa[4]= {0.7,0.7,0.7,1.0};	  // "cor"
    GLfloat luzEspecular[4]= {1.0, 1.0, 1.0, 1.0}; // "brilho"

    // Capacidade de brilho do material
    GLfloat especularidade[4]= {1.0,1.0,1.0,1.0};
    GLint especMaterial = 60;

    // Define a refletância do material
    glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
    // Define a concentração do brilho
    glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

    // Ativa o uso da luz ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

    // Define os parâmetros da luz de número 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
    glLightfv(GL_LIGHT0, GL_POSITION, posLuz );
}

// Desenha um objeto em wireframe
void DesenhaObjetoWireframe(OBJ *objeto)
{

    // Percorre todas as faces
    for(int f=0; f < objeto->total_faces; f++)
    {
        glBegin(GL_POLYGON);
        // Percorre todos os vértices da face
        for(int v=0; v < objeto->faces[f].total; v++)
            glVertex3f(objeto->vertices[objeto->faces[f].ind[v]].x,
                       objeto->vertices[objeto->faces[f].ind[v]].y,
                       objeto->vertices[objeto->faces[f].ind[v]].z);
        glEnd();
        /*
                glBegin(GL_QUADS);
                // Percorre todos os vértices da face
                for(int v=(objeto->faces[f].total) -1; v >= 0; v--)
                    glVertex3f(objeto->vertices[objeto->faces[f].ind[v]].x,
                               objeto->vertices[objeto->faces[f].ind[v]].y,
                               objeto->vertices[objeto->faces[f].ind[v]].z);
                glEnd();
        */
    }
}

// Função callback de redesenho da janela de visualização
void Desenha(void)
{
    // Limpa a janela de visualização com a cor
    // de fundo definida previamente
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Chama a função que especifica os parâmetros de iluminação
    DefineIluminacao();

    //glutWireCube(30);
    //glutWireTeapot(30);
    //glutWireCone(10,30, 50, 50);
    //glutWireSphere(5,35,5);
    //glutWireTorus(20, 40, 20, 20);
    //glutWireTetrahedron();
    //glutWireOctahedron();
    //glutWireDodecahedron();
    //glutWireIcosahedron();


    // Telhado

    glColor3f(1.0f, 0.0f, 0.0f);
    DesenhaObjetoWireframe(&telhado);

    glColor3f(0.0f, 0.0f, 0.0f);

    //PAREDES
    DesenhaObjetoWireframe(&faceJanela);
    //2
    glPushMatrix();
    glTranslated(10, 0, 0);
    DesenhaObjetoWireframe(&faceJanela);
    glRotated(-90,0,1,0);
    DesenhaObjetoWireframe(&faceParede);
    glTranslated(10,0,0);
    DesenhaObjetoWireframe(&facePorta);
    glTranslated(10,0,0);
    DesenhaObjetoWireframe(&facePorta);
    glTranslated(-20,0,0);
    glRotated(-90,0,1,0);
    glTranslated(-10,0,-10);
    DesenhaObjetoWireframe(&faceParede);
    glTranslated(-10,0,0);
    DesenhaObjetoWireframe(&facePorta);
    glPopMatrix();

    glColor3f(0.0f, 0.0f, 0.0f);

    //3
    glPushMatrix();
    glTranslated(20, 0, 0);
    DesenhaObjetoWireframe(&faceParede);
    glPopMatrix();

    //4
    glPushMatrix();
    glTranslated(30, 0, 0);
    DesenhaObjetoWireframe(&faceJanela);
    glRotated(-90,0,1,0);
    DesenhaObjetoWireframe(&faceParede);
    glPopMatrix();

    //5
    glPushMatrix();
    glTranslated(40, 0, 0);
    DesenhaObjetoWireframe(&faceJanela);
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
    DesenhaObjetoWireframe(&faceJanela);
    glPopMatrix();

    //8
    glPushMatrix();
    glTranslated(60, 0, 10);
    DesenhaObjetoWireframe(&faceJanela);
    glPopMatrix();

    //9
    glPushMatrix();
    glTranslated(70, 0, 10);
    glRotated(-90, 0, 1, 0);
    DesenhaObjetoWireframe(&facePorta);
    glPopMatrix();

    //10
    glPushMatrix();
    glTranslated(70, 0, 20);
    glRotated(-90, 0, 1, 0);
    DesenhaObjetoWireframe(&faceJanela);
    glPopMatrix();

    //11
    glPushMatrix();
    glTranslated(50, 0, 30);
    DesenhaObjetoWireframe(&faceJanela);
    glPopMatrix();

    //12
    glPushMatrix();
    glTranslated(60, 0, 30);
    DesenhaObjetoWireframe(&faceParede);
    glTranslated(-20,0,0);
    DesenhaObjetoWireframe(&facePorta);
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
    DesenhaObjetoWireframe(&faceJanela);

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
    DesenhaObjetoWireframe(&faceJanela);
    glTranslated(0,0,-10);
    DesenhaObjetoWireframe(&facePorta);
    glPopMatrix();

    //18
    glPushMatrix();
    glTranslated(30, 0, 50);
    glRotated(90, 0, 1, 0);
    DesenhaObjetoWireframe(&faceParede);
    glTranslated(0,0,10);
    DesenhaObjetoWireframe(&faceParede);
    glTranslated(10,0,0);
    DesenhaObjetoWireframe(&faceParede);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPopMatrix();

    //19
    glPushMatrix();
    glTranslated(20, 0, 40);
    DesenhaObjetoWireframe(&faceParede);

    glPopMatrix();

    //20
    glPushMatrix();
    glTranslated(10, 0, 40);
    DesenhaObjetoWireframe(&facePorta);
    glTranslated(-10, 0, 0);

    DesenhaObjetoWireframe(&facePorta);
    glTranslated(10, 0, 0);

    glRotated(90,0,1,0);
    DesenhaObjetoWireframe(&faceParede);
    glColor3f(0.0f, 0.0f, 0.0f);
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
    DesenhaObjetoWireframe(&faceJanela);
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
    DesenhaObjetoWireframe(&faceJanela);
    glPopMatrix();

    //26
    glPushMatrix();
    glTranslated(0, 0, 20);
    glRotated(90, 0, 1, 0);
    DesenhaObjetoWireframe(&faceJanela);
    glRotated(-90,0,1,0);
    DesenhaObjetoWireframe(&faceParede);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPopMatrix();

    //27
    glPushMatrix();
    glTranslated(0, 0, 10);
    glRotated(90, 0, 1, 0);
    DesenhaObjetoWireframe(&faceParede);
    glPopMatrix();




    //CHAO
    glColor3f(0.5f, 0.25f, 0.0f);

    //28 ATÉ 32
    for(int i = 0; i < 50; i = i + 10)
    {
        glPushMatrix();
        glTranslated(i, 0, 0);
        glRotated(90, 1, 0, 0);
        DesenhaObjetoWireframe(&faceParede);
        glPopMatrix();
    }
    //33 ATÉ 39
    for(int i = 0; i < 70; i = i + 10)
    {
        glPushMatrix();
        glTranslated(i, 0, 10);
        glRotated(90, 1, 0, 0);
        DesenhaObjetoWireframe(&faceParede);
        glPopMatrix();
    }

    //40 ATÉ 46
    for(int i = 0; i < 70; i = i + 10)
    {
        glPushMatrix();
        glTranslated(i, 0, 20);
        glRotated(90, 1, 0, 0);
        DesenhaObjetoWireframe(&faceParede);
        glPopMatrix();
    }

    //47 ATÉ 51
    for(int i = 0; i < 50; i = i + 10)
    {
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

    // Grama
    glColor3f(0, 1, 0);
    for(int i = 0; i < 120; i = i + 10)
    {
        glPushMatrix();
        glTranslated(-20+i,0, -10);
        glRotated(90,1, 0, 0);
        DesenhaObjetoWireframe(&faceParede);
        glPopMatrix();
    }
    for(int i = 0; i < 120; i = i + 10)
    {
        glPushMatrix();
        glTranslated(-20+i, 0, 0);
        glRotated(90,1, 0, 0);
        DesenhaObjetoWireframe(&faceParede);
        glPopMatrix();
    }
    for(int i = 0; i < 120; i = i + 10)
    {
        glPushMatrix();
        glTranslated(-20+i,0, 10);
        glRotated(90,1, 0, 0);
        DesenhaObjetoWireframe(&faceParede);
        glPopMatrix();
    }
    for(int i = 0; i < 120; i = i + 10)
    {
        glPushMatrix();
        glTranslated(-20+i,0, 20);
        glRotated(90,1, 0, 0);
        DesenhaObjetoWireframe(&faceParede);
        glPopMatrix();
    }
    for(int i = 0; i < 120; i = i + 10)
    {
        glPushMatrix();
        glTranslated(-20+i,0, 30);
        glRotated(90,1, 0, 0);
        DesenhaObjetoWireframe(&faceParede);
        glPopMatrix();
    }
    for(int i = 0; i < 120; i = i + 10)
    {
        glPushMatrix();
        glTranslated(-20+i,0, 40);
        glRotated(90,1, 0, 0);
        DesenhaObjetoWireframe(&faceParede);
        glPopMatrix();
    }
    for(int i = 0; i < 120; i = i + 10)
    {
        glPushMatrix();
        glTranslated(-20+i,0, 50);
        glRotated(90,1, 0, 0);
        DesenhaObjetoWireframe(&faceParede);
        glPopMatrix();
    }
    /*
        //TETO
        glColor3f(0.0f, 0.0f, 1.0f);

        //55 ATÉ 59
        for(int i = 0; i < 50; i = i + 10)
        {
            glPushMatrix();
            glTranslated(i, 10, 0);
            glRotated(90, 1, 0, 0);
            DesenhaObjetoWireframe(&faceParede);
            glPopMatrix();
        }
        //60 ATÉ 66
        for(int i = 0; i < 70; i = i + 10)
        {
            glPushMatrix();
            glTranslated(i, 10, 10);
            glRotated(90, 1, 0, 0);
            DesenhaObjetoWireframe(&faceParede);
            glPopMatrix();
        }

        //67 ATÉ 73
        for(int i = 0; i < 70; i = i + 10)
        {
            glPushMatrix();
            glTranslated(i, 10, 20);
            glRotated(90, 1, 0, 0);
            DesenhaObjetoWireframe(&faceParede);
            glPopMatrix();
        }

        //74 ATÉ 78
        for(int i = 0; i < 50; i = i + 10)
        {
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
    */
    // Executa os comandos OpenGL
    glutSwapBuffers();
}

// Função usada para especificar a posição do observador virtual
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

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
    // Especifica sistema de coordenadas de projeção
    glMatrixMode(GL_PROJECTION);
    // Inicializa sistema de coordenadas de projeção
    glLoadIdentity();

    // Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)
    gluPerspective(angle,fAspect,0.1,1200);

    PosicionaObservador();
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    // Para previnir uma divisão por zero
    if ( h == 0 )
        h = 1;

    // Especifica as dimensões da viewport
    glViewport(0, 0, w, h);

    // Calcula a correção de aspecto
    fAspect = (GLfloat)w/(GLfloat)h;

    EspecificaParametrosVisualizacao();
}

// Função callback chamada para gerenciar eventos de teclas normais (ESC)
void Teclado (unsigned char tecla, int x, int y)
{
    if(tecla==27) // ESC ?
    {
        // Libera memória e finaliza programa
        exit(0);
    }
}

// Função callback para tratar eventos de teclas especiais
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

// Função callback para eventos de botões do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
    if(state==GLUT_DOWN)
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
#define SENS_ROT	10.0
#define SENS_OBS	15.0
#define SENS_TRANSL	30.0
void GerenciaMovim(int x, int y)
{
    // Botão esquerdo ?
    if(bot==GLUT_LEFT_BUTTON)
    {
        // Calcula diferenças
        int deltax = x_ini - x;
        int deltay = y_ini - y;
        // E modifica ângulos
        rotY = rotY_ini - deltax/SENS_ROT;
        rotX = rotX_ini - deltay/SENS_ROT;
    }
    // Botão direito ?
    else if(bot==GLUT_RIGHT_BUTTON)
    {
        // Calcula diferença
        int deltaz = y_ini - y;
        // E modifica distância do observador
        obsZ = obsZ_ini + deltaz/SENS_OBS;
    }
    // Botão do meio ?
    else if(bot==GLUT_MIDDLE_BUTTON)
    {
        // Calcula diferenças
        int deltax = x_ini - x;
        int deltay = y_ini - y;
        // E modifica posições
        obsX = obsX_ini + deltax/SENS_TRANSL;
        obsY = obsY_ini - deltay/SENS_TRANSL;
    }
    PosicionaObservador();
    glutPostRedisplay();
}

// Função responsável por inicializar parâmetros e variáveis
void Inicializa (void)
{
    // Define a cor de fundo da janela de visualização como branca
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // Habilita a definição da cor do material a partir da cor corrente
    glEnable(GL_COLOR_MATERIAL);
    //Habilita o uso de iluminação
    glEnable(GL_LIGHTING);
    // Habilita a luz de número 0
    glEnable(GL_LIGHT0);

    // Inicializa a variável que especifica o ângulo da projeção
    // perspectiva
    angle=60;

    // Inicializa as variáveis usadas para alterar a posição do
    // observador virtual
    rotX = 0;
    rotY = 0;
    obsX = obsY = 0;
    obsZ = 20;


    glEnable(GL_DEPTH_TEST);
}

// Programa Principal
int main(void)
{
    // Define do modo de operação da GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // Especifica a posição inicial da janela GLUT
    glutInitWindowPosition(5,5);

    // Especifica o tamanho inicial em pixels da janela GLUT
    glutInitWindowSize(2000,1000);

    // Cria a janela passando como argumento o título da mesma
    glutCreateWindow("Desenho do wireframe de um cubo");

    // Registra a função callback de redesenho da janela de visualização
    glutDisplayFunc(Desenha);

    // Registra a função callback de redimensionamento da janela de visualização
    glutReshapeFunc(AlteraTamanhoJanela);

    // Registra a função callback para eventos de botões do mouse
    glutMouseFunc(GerenciaMouse);

    // Registra a função callback para eventos de movimento do mouse
    glutMotionFunc(GerenciaMovim);

    // Registra a função callback para tratamento das teclas normais
    glutKeyboardFunc (Teclado);

    // Registra a função callback para tratamento das teclas especiais
    glutSpecialFunc (TeclasEspeciais);

    // Chama a função responsável por fazer as inicializações
    Inicializa();

    // Inicia o processamento e aguarda interações do usuário
    glutMainLoop();

    return 0;
}
