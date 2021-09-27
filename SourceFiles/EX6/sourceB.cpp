#include<gl/glut.h>
#include<vector>
#include<utility>
#include<iostream>
#include<math.h>
using namespace std;


int n;
vector<pair<int, int>> coords;
int xv_min, xv_max, yv_min, yv_max;
int xw_min = 0, yw_min = 0, xw_max = 1000, yw_max = 1000;
double sx, sy;

void myInit(void) {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1000, 0, 1000);
}

void drawVWPort() {
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2d(xv_min, yv_min);
	glVertex2d(xv_min, yv_max);
	glVertex2d(xv_max, yv_max);
	glVertex2d(xv_max, yv_min);
	glEnd();
}

void drawWPolygon() {
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < n; i++) {
		glVertex2d(coords[i].first, coords[i].second);
	}
	glEnd();
}
void drawVPolygon() {
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 0.0f, 0.0f);
	for (int i = 0; i < n; i++) {
		glVertex2d(xv_min + (coords[i].first - xw_min) * sx, yv_min + (coords[i].second - yw_min) * sy);
	}
	glEnd();
}

void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	drawWPolygon();
	drawVPolygon();
	drawVWPort();
	glFlush();
}

int main(int argc, char** argv) {
	cout << "Enter Ploygon Dimensions" << endl;
	cout << "Enter number of vertices: ";
	cin >> n;
	int x, y;
	for (int i = 0; i < n; i++) {
		cout << "Enter vertex " << i + 1 << " : ";
		cin >> x >> y;
		coords.push_back(make_pair(x, y));
	}
	cout << "Enter Viewport details" << endl;
	cout << "Enter min x and max x : ";
	cin >> xv_min >> xv_max;
	cout << "Enter min y and max y : ";
	cin >> yv_min >> yv_max;

	sx = (xv_max - xv_min) * 1.0 / (xw_max - xw_min);
	sy = (yv_max - yv_min) * 1.0 / (yw_max - yw_min);

	cout << "Black -> original polygon " << endl;
	cout << "Red   -> transformed polygon" << endl;
	cout << "Green -> view port" << endl;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("Transformation");
	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();
	return 0;
}