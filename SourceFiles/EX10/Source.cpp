#include<gl/glut.h>
#include<iostream>
#include<vector>
using namespace std;

GLfloat alpha = 0, theta = 0;
bool flag = true;
vector<vector<GLfloat>> coords(8, vector<GLfloat>(3));

void init(void)
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}



void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-500, 500, -500, 500, -500.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glRotatef(alpha, 0, 1, 0);
	glRotatef(theta, 1, 0, 0);
	//glShadeModel(GL_SMOOTH);
	glutSolidTeapot(100);
	glFlush();
}

void timer(int v) {
	alpha += 0.2;
	theta += 0.2;
	if (alpha == 360) alpha = 0;
	if (theta == 360) theta = 0;
	glutPostRedisplay();
	glutTimerFunc(100, timer, v);
}


void keyPress(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_RIGHT: alpha+=1;
		break;
	case GLUT_KEY_LEFT:
		alpha-=1;
		break;
	case GLUT_KEY_UP:
		theta+=1;
		break;
	case GLUT_KEY_DOWN:
		theta-=1;
		break;
	case GLUT_KEY_HOME: flag = !flag;
		break;
	}
	glutPostRedisplay();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("3D Scene");
	init();
	glutDisplayFunc(display);
	glutSpecialFunc(keyPress);
	glutTimerFunc(100,timer,0);
	glutMainLoop();
	
	return 0;
}