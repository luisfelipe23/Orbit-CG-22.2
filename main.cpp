#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <iostream>

float rotacao1 = 0.0;
float rotacao2 = 0.0;
float rotacao3 = 0.0;
float rotacao4 = 0.0;

float proprioE = 0;

float velMercurio = 0.13;
float velVenus = 0.15;
float velTerra = 0.28;
float velMarte = 0.35;

float zoom = -60.0;

//Cria os Planetas
void CreateCircle(float raio)
{
    float angulo = 0;
    glLineWidth(3.0);
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    	for(int i = 0; i<100; i++){
    		angulo = 2*3.1416*i/100; //2 x pi x r
    		glVertex3f(raio*cos(angulo), 0, raio*sin(angulo));
		}
	glEnd();
}

void pintarSol(float x, float y, float z) {
    glColor3f(x, y, z);
}

void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(zoom, 40.0, 0, 0, -5.0, 0, 0, 1.0, 0.0);

    //Marte
    CreateCircle(35.0);
	glPushMatrix();
	glTranslatef(35.0*cos(rotacao4/velMarte), 0, 35.0*sin(rotacao4/velMarte));
    glRotatef(proprioE, 0, 1.0, 0);
    glDisable(GL_LIGHTING);
    glColor3f(1.0, 0.2, 0);
    glutSolidSphere(3.0, 15.0, 15.0);
    glEnable(GL_LIGHTING);
    glPopMatrix();

    //Terra
    CreateCircle(27.0);
	glPushMatrix();
	glTranslatef(27.0*cos(rotacao3/velTerra), 0, 27.0*sin(rotacao3/velTerra));
    glRotatef(proprioE, 0, 1.0, 0);
    glDisable(GL_LIGHTING);
    glColor3f(0, 0.5, 0.9);
    glutSolidSphere(3.7, 15.0, 15.0);
    glEnable(GL_LIGHTING);
    glPopMatrix();

    //Venus
    CreateCircle(19.0);
	glPushMatrix();
	glTranslatef(19.0*cos(rotacao2/velVenus), 0, 19.0*sin(rotacao2/velVenus));
    glRotatef(proprioE, 0, 1.0, 0);
    glDisable(GL_LIGHTING);
    glColor3f(1, 0.6, 0);
    glutSolidSphere(3.3, 15.0, 15.0);
    glEnable(GL_LIGHTING);
    glPopMatrix();

    //Mercurio
    CreateCircle(12.0);
	glPushMatrix();
	glTranslatef(12.0*cos(rotacao1/velMercurio), 0, 12.0*sin(rotacao1/velMercurio));
	glRotatef(proprioE, 0, 1.0, 0);
    glDisable(GL_LIGHTING);
    glColor3f(0.4, 0.4, 0.4);
    glutSolidSphere(1.5, 15.0, 15.0);
    glEnable(GL_LIGHTING);
    glPopMatrix();

    //Sol
    glPushMatrix();
    glDisable(GL_LIGHTING);
    if ((velMercurio <= 0.01 && velMercurio >= -0.01) || (velVenus <= 0.01 && velVenus >= -0.01)) {
        glColor3f(0, 0, 0);
    }
    else
        pintarSol(1, 0.7, 0);
    glRotatef(proprioE, 0, 1.0, 0);
    glutSolidSphere(6.5, 15.0, 15.0);
    glEnable(GL_LIGHTING);
    glPopMatrix();

    glutSwapBuffers();
}

void init()
{
    glClearColor(0, 0, 0, 1);
    glShadeModel(GL_SMOOTH);

    GLfloat MATRIX_SHININESS[] = {50.0};
    GLfloat MATRIX_SPECULAR[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat LIGHT_POSITION[] = {0, 1.0, 1.0, 0};

    glLightfv(GL_LIGHT0, GL_POSITION, LIGHT_POSITION);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_DEPTH_TEST);

}


void KeyboardCallback(unsigned char key, int x, int y){

    switch(key){
    	case 27:
    	    printf("Sair");
    		exit(0);

        case 32: {
            printf("%.2f, %.2f, %.2f, %.2f\n\n", velMercurio, velVenus, velTerra, velMarte);
            velMercurio = velMercurio - 0.006;
            velVenus = velVenus - 0.006;
            velTerra = velTerra - 0.006;
            velMarte = velMarte - 0.006;

            glutPostRedisplay();
            break;
        }
	}
}

void AumentarZoom (int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == 0) {
            zoom += 5.0;
        }
    }
    if (button == GLUT_RIGHT_BUTTON) {
        if (state == 0) {
            zoom -= 5.0;
        }
    }
}

//retoção dos planetas no sol
void Rotacao(void){

	rotacao1 = rotacao1 + 0.0006;
	rotacao2 = rotacao2 + 0.0004;
	rotacao3 = rotacao3 + 0.0002;
	rotacao4 = rotacao4 + 0.0001;
	glutPostRedisplay();
}

void reshaping(int w, int h){

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-0.4, 0.4, -0.3, 0.3, 0.5, 2000);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();

}

//Rotação no proprio eixo
void Eixo(int x){

	proprioE = proprioE + 1.5;
	if(proprioE > 360){
		proprioE = -360;
	}
	glutPostRedisplay();
	glutTimerFunc(25, Eixo, 0);
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(900, 600);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Solar System");

    glutDisplayFunc(display);

    glutReshapeFunc(reshaping);

    glutIdleFunc(Rotacao);

    glutKeyboardFunc(KeyboardCallback);

    glutMouseFunc(AumentarZoom);

    glutTimerFunc(25, Eixo, 0);

    glutMainLoop();

    return 0;
}
