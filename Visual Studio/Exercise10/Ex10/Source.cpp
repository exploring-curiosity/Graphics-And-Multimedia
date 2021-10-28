/*#include<gl/glut.h>
#include<iostream>
using namespace std;

void init() {
	glClearColor(1, 1, 1, 1);
	glOrtho(-500, 500, -500, 500, -500, 500);
	glEnable(GL_DEPTH_TEST);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1, 0, 0);
	glutWireCube(100);
	glFlush();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("Lighting and animation");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 1;
}
*/
#include<gl/glut.h>
#include<iostream>
using namespace std;

int alpha = 45, theta = 45;
bool flag = true;

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
	glLoadIdentity();
	glRotatef(alpha, 0, 1, 0);
	glRotatef(theta, 1, 0, 0);
	glutSolidCube(100);
	glFlush();
}


void keyPress(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_RIGHT: alpha++;
		break;
	case GLUT_KEY_LEFT:
		alpha--;
		break;
	case GLUT_KEY_UP:
		theta++;
		break;
	case GLUT_KEY_DOWN:
		theta--;
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
	glutMainLoop();
	
	return 0;
}