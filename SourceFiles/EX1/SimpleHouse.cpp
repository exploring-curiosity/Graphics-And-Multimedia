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
void myDispC() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	glVertex2d(320, 440);
	glVertex2d(120, 280);
	glVertex2d(520, 280);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2d(170, 280);
	glVertex2d(170, 40);
	glVertex2d(470, 40);
	glVertex2d(470, 280);
	glEnd();
	glBegin(GL_QUADS);
	glVertex2d(220, 200);
	glVertex2d(300, 200);
	glVertex2d(300, 40);
	glVertex2d(220, 40);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex2d(360, 230);
	glVertex2d(420, 230);
	glVertex2d(420, 170);
	glVertex2d(360, 170);
	glEnd();
	glBegin(GL_QUADS);
	glVertex2d(360, 230);
	glVertex2d(375, 220);
	glVertex2d(375, 180);
	glVertex2d(360, 170);
	
	glVertex2d(420, 230);
	glVertex2d(405, 220);
	glVertex2d(405, 180);
	glVertex2d(420, 170);
	glEnd();
	glFlush();
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1440, 480);
	glutCreateWindow("Exercise1");
	glutDisplayFunc(myDispC);
	myInit();
	glutMainLoop();
	return 1;
}