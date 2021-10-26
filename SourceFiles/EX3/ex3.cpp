#include<GL/glut.h>
#include<iostream>
#include<math.h>

int a1,b1,a2,b2;
void display()
{
	int x1=a1,y1=b1,x2=a2,y2=b2;
	int dx,dy,endx,endy,p,x,y;
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	glPointSize(4.0);
	dx=abs(x1-x2);
	dy=abs(y1-y2);
	if(dy<=dx)
	{
		p=2*dy-dx;
		if(x1>x2)
		{
			x=x2;
			y=y2;
			endx=x1;
			endy=y1;
		}
		else
		{
			x=x1;
			y=y1;
			endx=x2;
			endy=y2;
		}
		glColor3d(1.0,0.0,0.0);
		if(endy>=y)
		{
			while(x<=endx)
			{
				glBegin(GL_POINTS);
				glVertex2d(x,y);		
				glEnd();
				
				x+=1;
				if(p<0)
				{
					p+=2*dy;
				}
				else
				{
					p+=2*(dy-dx);
					y+=1;
				}
			}
		}
		else
		{
			while(x<=endx)
			{
				glBegin(GL_POINTS);
				glVertex2d(x,y);		
				glEnd();
				
				x+=1;
				if(p<0)
				{
					p+=2*dy;
				}
				else
				{
					p+=2*(dy-dx);
					y-=1;
				}
			}
		}
		
	}
	else
	{
		p=2*dx-dy;
		if(y1>y2)
		{
			x=x2;
			y=y2;
			endy=y1;
			endx=x1;
		}
		else
		{
			x=x1;
			y=y1;
			endy=y2;
			endx=x2;
		}
		glColor3d(0.0,1.0,0.0);
		if(endx>=x)
		{
			while(y<=endy)
			{
				glBegin(GL_POINTS);
				glVertex2d(x,y);		
				glEnd();
				
				y+=1;
				if(p<0)
				{
					p+=2*dx;
				}
				else
				{
					p+=2*(dx-dy);
					x+=1;
				}
			}
		}
		else
		{
			while(y<=endy)
			{
				glBegin(GL_POINTS);
				glVertex2d(x,y);		
				glEnd();
				
				y+=1;
				if(p<0)
				{
					p+=2*dx;
				}
				else
				{
					p+=2*(dx-dy);
					x-=1;
				}
			}
		}
	}
	glFlush();
}	
	
void init()
{
	glClearColor(0.0,0.5,1.0,0.0);
}

void reshape(int w,int h)
{
	//viewport
	glViewport(0,0,w,h);	
	//projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluOrtho2D(0,640,0,480);
	
	glMatrixMode(GL_MODELVIEW);	
}

int main(int argc,char *argv[])
{
	std::cout<<"Enter x1 and y1 : ";
	std::cin>>a1>>b1;
	std::cout<<"Enter x2 and y2 : ";
	std::cin>>a2>>b2;
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB);
	
	glutInitWindowPosition(300,100);
	glutInitWindowSize(640,480);
	
	glutCreateWindow("Ex3 - Bresenham's Line Drawing Algorithm");
	glutDisplayFunc(display);	
	glutReshapeFunc(reshape);
	init();
	
	glutMainLoop();
	
	return 1;	
}
