#include<GL/glut.h>
#include<bits/stdc++.h>
using namespace std;
double X1, Y1, X2, Y2;
double arrx1[4], arry1[4], arrx2[4], arry2[4];
void myInit() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1000.0, 0.0, 1000.0);
}
void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	int j = 0;
	while (j < 1) {
		X1 = arrx1[j];
		Y1 = arry1[j];
		X2 = arrx2[j];
		Y2 = arry2[j];

		double dx = X2 - X1;
		double dy = Y2 - Y1;
		double d = 2*dy - dx;
		int x, y, Xend;
		if (dx < 0) {
			x = X2;
			y = Y2;
			Xend = X1;
		}
		else {
			x = X1;
			y = Y1;
			Xend = X2;
		}
		glBegin(GL_POINTS);
		while (x <= Xend) {
			glVertex2d(x, y);
			if (d < 0) {
				d = d + 2*dy;
				x++;
			}
			else {
				d = d + 2*dy-2*dx;
				x++;
				y++;
			}
		}
		glEnd();
		j++;
	}
	glFlush();
}
int main(int argc, char* argv[]) {
	int i = 0;
	while (i < 1)
	{
		cout << "Enter two end points of the line to be drawn:" << endl;
		cout << endl << "Case " << i + 1 << ":";
		cout << endl << "Enter Point1( X1 , Y1):" << endl;
		cin >> X1;
		cin >> Y1;
		arrx1[i] = X1;
		arry1[i] = Y1;
		cout << endl;
		cout << endl << "Case " << i + 1 << ":";
		cout << endl << "Enter Point2( X2 , Y2):" << endl;
		cin >> X2;
		cin >> Y2;
		arrx2[i] = X2;
		arry2[i] = Y2;
		i++;
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("Ex2 Bresenham's Line");
	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();
	return 1;
}