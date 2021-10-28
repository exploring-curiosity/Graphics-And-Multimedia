#include<gl/glut.h>
#include<iostream>
#include<bits/stdc++.h>

using namespace std;
vector<vector<GLfloat>> coords(8, vector<GLfloat>(3));
double alpha=0, beta=0, gamma=0;
bool flag = true;
int xwmin = 100, xwmax = 300, ywmin = 100, ywmax = 300;
pair<int, int> P1, P2;
int X1, X2, Y1, Y2;
int stage = 0;
bool clipped = false;

void init() {
	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glPointSize(4);
	glLoadIdentity();
	gluOrtho2D(-500, 500, -500, 500);
}

void init3D() {
	glClearColor(1, 1, 1, 1);
	glLoadIdentity();
	glOrtho(-500, 500, -500, 500, -500, 500);
	glEnable(GL_DEPTH_TEST);
}


void DDA(int a, int b, int c, int d) {
	int dx = c - a;
	int dy = d - b;
	int steps;
	double xInc, yInc;
	double x=a, y=b;
	steps = max(abs(dx), abs(dy));
	xInc = dx*1.0 / steps;
	yInc = dy * 1.0 / steps;
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	for (int i = 0; i < steps; i++) {
		x += xInc;
		y += yInc;
		glVertex2f(round(x), round(y));
	}
	glEnd();
}

void Brh(int a, int b, int c, int d) {
	glBegin(GL_POINTS);
	int dx = abs(c - a), dy = abs(d - b);
	if (dx > dy) {
		if (a > c) swap(a, c), swap(b, d);
		int inc = 1;
		if (b > d) inc = -1;
		int p = 2 * dy - dx;
		while (a <= c) {
			glVertex2d(a, b);
			if (p < 0) {
				p += 2 * dy;
				a++;
			}
			else {
				p += 2 * dy - 2 * dx;
				a++;
				b += inc;
			}
		}
	}
	else {
		if (b > d) swap(b, d), swap(a, c);
		int inc = 1;
		if (c < a) inc = -1;
		int p = 2 * dx - dy;
		while (b <= d) {
			glVertex2f(a, b);
			if (p < 0) {
				p += 2 * dx;
				b++;

			}
			else {
				p += 2 * dx - 2 * dy;
				b++;
				a += inc;
			}
		}
	}
	glEnd();
}

void plot(int cx, int cy, int x, int y) {
	glVertex2d(cx + x, cy + y);
	glVertex2d(cx + x, cy - y);
	glVertex2d(cx - x, cy - y);
	glVertex2d(cx - x, cy + y);
	glVertex2d(cx + y, cy + x);
	glVertex2d(cx + y, cy - x);
	glVertex2d(cx - y, cy - x);
	glVertex2d(cx - y, cy + x);
}

void MPCircle(int r,int cx,int cy) {
	glBegin(GL_POINTS);
	int p = 1 - r;
	int x = 0,y = r;
	plot(cx,cy,x, y);
	while (x <= y) {
		if (p < 0) {
			x++;
			plot(cx,cy,x, y);
			p += 2 * x + 1;
		}
		else {
			x++, y--;
			plot(cx,cy,x, y);
			p += 2 * x - 2 * y + 1;
		}
	}
	glEnd();
}

void DrawCube() {
	glBegin(GL_QUADS);

	glColor3f(1, 0, 0);
	glVertex3f(coords[0][0], coords[0][1], coords[0][2]);
	glVertex3f(coords[1][0], coords[1][1], coords[1][2]);
	glVertex3f(coords[2][0], coords[2][1], coords[2][2]);
	glVertex3f(coords[3][0], coords[3][1], coords[3][2]);


	glColor3f(0, 1, 0);
	glVertex3f(coords[4][0], coords[4][1], coords[4][2]);
	glVertex3f(coords[5][0], coords[5][1], coords[5][2]);
	glVertex3f(coords[6][0], coords[6][1], coords[6][2]);
	glVertex3f(coords[7][0], coords[7][1], coords[7][2]);


	glColor3f(0, 0, 1);
	glVertex3f(coords[0][0], coords[0][1], coords[0][2]);
	glVertex3f(coords[1][0], coords[1][1], coords[1][2]);
	glVertex3f(coords[5][0], coords[5][1], coords[5][2]);
	glVertex3f(coords[4][0], coords[4][1], coords[4][2]);


	glColor3f(1, 0, 1);
	glVertex3f(coords[0][0], coords[0][1], coords[0][2]);
	glVertex3f(coords[4][0], coords[4][1], coords[4][2]);
	glVertex3f(coords[7][0], coords[7][1], coords[7][2]);
	glVertex3f(coords[3][0], coords[3][1], coords[3][2]);


	glColor3f(0, 1, 1);
	glVertex3f(coords[1][0], coords[1][1], coords[1][2]);
	glVertex3f(coords[2][0], coords[2][1], coords[2][2]);
	glVertex3f(coords[6][0], coords[6][1], coords[6][2]);
	glVertex3f(coords[5][0], coords[5][1], coords[5][2]);


	glColor3f(1, 1, 0);
	glVertex3f(coords[2][0], coords[2][1], coords[2][2]);
	glVertex3f(coords[3][0], coords[3][1], coords[3][2]);
	glVertex3f(coords[7][0], coords[7][1], coords[7][2]);
	glVertex3f(coords[6][0], coords[6][1], coords[6][2]);

	glEnd();
}
void Axis() {
	glBegin(GL_LINES);
	glColor3f(0, 0, 1);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 500);

	glColor3f(1, 0, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(500, 0, 0);

	glColor3f(0, 1, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 500, 0);
	glEnd();
}
int getRC(pair<int, int>& P)
{
	int rc = 0;
	if (P.first < xwmin) rc |= 1;
	else if (P.first > xwmax) rc |= 1 << 1;
	if (P.second < ywmin) rc |= 1 << 2;
	else if (P.second > ywmax) rc |= 1 << 3;
	return rc;
}
void findIntersection(pair<int, int>& P, double m, int rc) {

	if (rc == 0) return;
	// y = ywmax
	if ((rc >> 3) & 1) {
		//x =X1 + (y-Y1)/m
		P.second = ywmax;
		P.first = X1 + (ywmax - Y1) / m;
		return;
	}
	//y = ywmin
	if ((rc >> 2) & 1) {
		//x =X1 + (y-Y1)/m
		P.second = ywmin;
		P.first = X1 + (ywmin - Y1) / m;
		return;
	}
	// x= xwmax
	if ((rc >> 1) & 1) {
		//y =Y1 + (x-X1)*m
		P.first = xwmax;
		P.second = Y1 + (xwmax - X1) * m;
		return;
	}
	// x= xwmin
	if (rc & 1) {
		//y =Y1 + (x-X1)*m
		P.first = xwmin;
		P.second = Y1 + (xwmin - X1) * m;
		return;
	}
}
void PerformClipping(pair<int, int>& P1, pair<int, int>& P2,int st)
{
	int rc1 = getRC(P1), rc2 = getRC(P2);
	//Checking for trivial OR
	if (st == stage) {
		glBegin(GL_LINES);
		glVertex2d(P1.first, P1.second);
		glVertex2d(P2.first, P2.second);
		glEnd();
		return;
	}
	if (int(rc1 | rc2) == 0) {

		glBegin(GL_LINES);
		glVertex2d(P1.first, P1.second);
		glVertex2d(P2.first, P2.second);
		clipped = true;
		glEnd();
		return;
	}
	else if (int(rc1 & rc2) != 0) {
		clipped = true;
		return;
	}
	double m = (Y2 - Y1) * 1.0 / (X2 - X1);
	findIntersection(P1, m, rc1);
	findIntersection(P2, m, rc2);
	PerformClipping(P1, P2,st+1);
}
void drawOriginal() {
	glBegin(GL_LINES);
	glVertex2d(P1.first, P1.second);
	glVertex2d(P2.first, P2.second);
	glEnd();
}

void drawWindow() {
	glBegin(GL_LINE_LOOP);
	glVertex2d(xwmin, ywmin);
	glVertex2d(xwmax, ywmin);
	glVertex2d(xwmax, ywmax);
	glVertex2d(xwmin, ywmax);
	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glColor3f(1, 0, 0);
	//DDA(100, 100, -100, -100);
	//DDA(-100, 50, 50, 100);
	//DDA(-100, -100, 100, 100);
	//Brh(100, 100, -100, -100);
	//Brh(-100, 50, 50, 100);
	//Brh(-100, -100, 200, 100);
	//MPCircle(100, 100, 100);
	/*
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (flag) glOrtho(-500, 500, -500, 500, -500, 500);
	else gluPerspective(100, 1, 0.1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 300, 0, 0, 0, 0, 1, 0);
	glRotatef(alpha, 0, 1, 0);
	glRotatef(beta, 1, 0, 0);
	glRotatef(gamma, 0, 0, 1);
	
	//glTranslatef(-100, 0, 0);
	//Axis();
	DrawCube();*/
	P1 = { X1, Y1 };
	P2 = { X2,Y2 };
	glColor3f(0, 1, 0);
	drawWindow();
	glColor3f(0, 0, 0);
	if(stage==0)
	drawOriginal();
	glColor3f(1, 0, 0);
	if(stage>0)
	PerformClipping(P1, P2,0);
	
	glFlush();
}

void timer(int v) {
	if (clipped) stage = 0, clipped = false;
	else stage++;
	glutPostRedisplay();
	glutTimerFunc(1000, timer, v);
}

void keyPress(int key,int x,int y) {
	switch (key) {
	case GLUT_KEY_RIGHT:alpha+=0.1; break;
	case GLUT_KEY_LEFT:alpha-=0.1; break;
	case GLUT_KEY_UP:beta+=0.1; break;
	case GLUT_KEY_DOWN:beta-=0.1; break;
	case GLUT_KEY_PAGE_UP:gamma+=0.1; break;
	case GLUT_KEY_PAGE_DOWN:gamma-=0.1; break;
	case GLUT_KEY_HOME:flag = !flag; break;
	}
	glutPostRedisplay();
}

int main(int argc, char* argv[]) {
	GLfloat x1 = -100, Y1 = -100, z1 = -100, x2 = 100, y2 = 100, z2 = 100;
	/*cout << "Enter cube dimensions:" << endl;
	cout << "Enter min x,y,z: ";
	cin >> x1 >> Y1 >> z1;
	cout << "Enter max x,y,z: ";
	cin >> x2 >> y2 >> z2;

	cout << "Enter Transformation Operation" << endl << "1.Translate" << endl << "2.Rotate" << endl << "3.Scale" << endl;
	cout << "Choice: ";
	cin >> ch;

	switch (ch) {
	case 1: cout << "Enter tx,ty,tz: ";
		cin >> tx >> ty >> tz;
		break;
	case 2: cout << "Enter Axis to rotate about X(1), Y(2), Z(3): ";
		cin >> RotAxis;
		cout << "Enter rotation ang: ";
		cin >> ang;
		rad = ang * PI / 180;
		break;
	case 3: cout << "Enter sx,sy,sz: ";
		cin >> sx >> sy >> sz;
		cout << "Enter point to scale about x,y,z: ";
		cin >> xf >> yf >> zf;
		break;
	default: cout << "invalid";
	}
	*/
	coords[0][0] = x1;
	coords[0][1] = Y1;
	coords[0][2] = z1;

	coords[1][0] = x1;
	coords[1][1] = y2;
	coords[1][2] = z1;

	coords[2][0] = x2;
	coords[2][1] = y2;
	coords[2][2] = z1;

	coords[3][0] = x2;
	coords[3][1] = Y1;
	coords[3][2] = z1;

	coords[4][0] = x1;
	coords[4][1] = Y1;
	coords[4][2] = z2;

	coords[5][0] = x1;
	coords[5][1] = y2;
	coords[5][2] = z2;

	coords[6][0] = x2;
	coords[6][1] = y2;
	coords[6][2] = z2;

	coords[7][0] = x2;
	coords[7][1] = Y1;
	coords[7][2] = z2;

	X1 = 0;
	Y1 = 0;
	X2 = 400;
	Y2 = 500;

	

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("Model Practise");
	glutDisplayFunc(display);
	glutTimerFunc(1000, timer, 0);
	init3D();
	glutSpecialFunc(keyPress);
	glutMainLoop();
	return 1;
}


/*

2D:

translation
1 0 tx
0 1 ty
0 0 1

Scaling
sx 0  (1-sx)xf
 0 sy (1-sy)yf
 0 0  1

 Rotation:
 rad = ang*PI/180

 cos -sin xr(1-cos) + yr(1-sin)
 sin  cos yr(1-cos)-xr(1-sin)
 0    0   1


 Shearing:
 about X
 1 shx 0
 0 1   0
 0 0   1

 about Y
 1   0 0
 shy 1 0
 0   0 1


 reflection:
 about xaxis:

 1 0  0
 0 -1 0
 0 0  1

 about y-axis:
 -1 0 0 
  0 1 0
  0 0 1

about x=y line
0 1 0
1 0 0
0 0 1

about origin:
-1 0 0
0 -1 0
 0 0 1


3D:
translate

1 0 0 tx
0 1 0 ty
0 0 1 tz
0 0 0 1

rotate:

X:
1 0 0 0
0 c -s 0
0 s c 0
0 0 0 1

Y:
c 0 s 0 
0 1 0 0 
-s 0 c 0
0 0 0 1

Z:
c -s 0 0
s c 0  0
0 0 1 0
0 0  0 1

Scale:
sx 0 0 (1-sx)xf
0 sy 0 (1-sy)yf
0 0 sz (1-sz)zf
0 0  0 1



*/