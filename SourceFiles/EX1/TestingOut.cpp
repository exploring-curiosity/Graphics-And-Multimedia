#include<GL/glut.h>
void myInit()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(5);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1440.0, 0.0, 480.0);
}
void myDispA() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	glVertex2d(100, 100);
	glVertex2d(150, 230);
	glVertex2d(170, 130);
	glVertex2d(300, 350);
	glEnd();
	glFlush();
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1440, 480);
	glutCreateWindow("Exercise1");
	glutDisplayFunc(myDispD);
	myInit();
	glutMainLoop();
	return 1;
}