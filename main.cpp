#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <iostream>

float RotationSpeed = 0;
float RotationSpeed1 = 0;
float RotationSpeed2 = 0;
float RotationSpeed3 = 0;

float Self_angle = 0;

void CreateCircle(float radius)
{
    float _angle = 0;
    glLineWidth(3.0);
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    	for(int i = 0; i<100; i++){
    		_angle = 2*3.1416*i/100; //2 x pi x r
    		glVertex3f(radius*cos(_angle), 0, radius*sin(_angle));
		}
	glEnd();
}


void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(-60.0, 40.0, 0, 0, 0, 0, 0, 1.0, 0);

    glPushMatrix();
    glDisable(GL_LIGHTING);
    glColor3f(1, 0.7, 0);
    glRotatef(Self_angle, 0, 1.0, 0);
    glutSolidSphere(6.5, 15.0, 15.0);
    glEnable(GL_LIGHTING);
    glPopMatrix();


	CreateCircle(12.0);
	glPushMatrix();
	glTranslatef(12.0*cos(RotationSpeed/0.13), 0, 12.0*sin(RotationSpeed/0.13));
	glRotatef(Self_angle, 0, 1.0, 0);
    glDisable(GL_LIGHTING);
    glColor3f(0.4, 0.4, 0.4);
    glutSolidSphere(1.5, 15.0, 15.0);
    glEnable(GL_LIGHTING);
    glPopMatrix();

    CreateCircle(19.0);
	glPushMatrix();
	glTranslatef(19.0*cos(RotationSpeed1/0.15), 0, 19.0*sin(RotationSpeed1/0.15));
    glRotatef(Self_angle, 0, 1.0, 0);
    glDisable(GL_LIGHTING);
    glColor3f(1, 0.6, 0);
    glutSolidSphere(3.3, 15.0, 15.0);
    glEnable(GL_LIGHTING);
    glPopMatrix();

    CreateCircle(27.0);
	glPushMatrix();
	glTranslatef(27.0*cos(RotationSpeed/0.28), 0, 27.0*sin(RotationSpeed/0.28));
    glRotatef(Self_angle, 0, 1.0, 0);
    glDisable(GL_LIGHTING);
    glColor3f(0, 0.5, 0.9);
    glutSolidSphere(3.7, 15.0, 15.0);
    glEnable(GL_LIGHTING);
    glPopMatrix();

    CreateCircle(35.0);
	glPushMatrix();
	glTranslatef(35.0*cos(RotationSpeed/0.35), 0, 35.0*sin(RotationSpeed/0.35));
    glRotatef(Self_angle, 0, 1.0, 0);
    glDisable(GL_LIGHTING);
    glColor3f(1.0, 0.2, 0);
    glutSolidSphere(3.0, 15.0, 15.0);
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

void key_callback(unsigned char key, int x, int y){

    switch(key){
    	case 27:
    		exit(0);
	}
}

void spining(void){

	RotationSpeed = RotationSpeed + 0.0006;
	RotationSpeed1 = RotationSpeed1 + 0.0004;
	RotationSpeed2 = RotationSpeed2 + 0.0002;
	RotationSpeed3 = RotationSpeed3 + 0.0001;
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


void spining(int x){

	Self_angle = Self_angle + 1.5;
	if(Self_angle > 360){
		Self_angle = -360;
	}
	glutPostRedisplay();
	glutTimerFunc(25, spining, 0);
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

    glutIdleFunc(spining);

    glutKeyboardFunc(key_callback);

    glutTimerFunc(25, spining, 0);

    glutMainLoop();

    return 0;
}
