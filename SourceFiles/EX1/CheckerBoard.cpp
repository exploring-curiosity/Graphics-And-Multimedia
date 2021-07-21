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
void myDispB()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
	for (int i = 0; i <= 8; i++)
	{
		glVertex2d(120 + i * 50, 40);
		glVertex2d(120 + i * 50, 440);
	}
	for (int i = 0; i <= 8; i++)
	{
		glVertex2d(120 , 40 + i * 50);
		glVertex2d(520 , 40 + i*50);
	} 
	glEnd();
	glBegin(GL_QUADS);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			glVertex2d(120 + j * 100, 40 + i * 100);
			glVertex2d(170 + j * 100, 40 + i * 100);
			glVertex2d(170 + j * 100, 90 + i * 100);
			glVertex2d(120 + j * 100, 90 + i * 100);
		}
		for (int j = 0; j < 4; j++)
		{
			glVertex2d(170 + j * 100, 90 + i * 100);
			glVertex2d(220 + j * 100, 90 + i * 100);
			glVertex2d(220 + j * 100, 140 + i * 100);
			glVertex2d(170 + j * 100, 140 + i * 100);
		}
	}
	glEnd();
	glFlush();
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1440, 480);
	glutCreateWindow("Exercise1");
	glutDisplayFunc(myDispB);
	myInit();
	glutMainLoop();
	return 1;
}