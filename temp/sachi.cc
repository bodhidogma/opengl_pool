#include <GL/glut.h>
#include <stdlib.h>
#include <string.h>

void CreateSub(void);
void keyboard(unsigned char key, int x, int y);
static GLfloat size = 3.0f;
static GLfloat someAxis=9.5;
static GLfloat theta[] = {0.0,0.0,0.0}; // places along x, y and z axes
static GLint axis = 2;                  // x-, y- or z-axis?
static double radius = 1.5;             // the radius of the sphere
static double zAxis = -18.0;            // place on the zAxis (used in glTranslatef) 
static double increment = 0.22;         // the rate of the radius increment
static double rotateAngle = 2.5;        // the rotation angle in degrees 
static int winWidth = 640;                  // the width of the window
static int winHeight = 450;                 // the heigh
static double z = 0.2f;

void init(void)
{ 
	GLfloat mat_specular[]={0.3f, 0.3f, 0.3f, 1.0f};
	GLfloat mat_shininess[]={50.0};
    GLfloat light_ambient[]={3.0, 0.0, 2.0, 0.5};
	GLfloat light_position[]={1.0, 1.0, 1.0, 0.5};
    GLfloat white_light[]={1.0, 1.0, 5.0, 1.0};
	glClearColor(0.3f, 0.5f, 0.7f, 0.0f); 
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT3, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT3, GL_POSITION, light_position);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT3, GL_SPECULAR, white_light);
	
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT3);
    glEnable(GL_DEPTH_TEST);   
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
	glLoadIdentity();

	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);

	glTranslatef(0.0, 0.0, zAxis);
    glColor3f(3.0, 0.0, 2.0);
	glutSolidSphere(radius, 10.0, 10.0);
	glFlush();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	if(w > h)
		glScalef(1.0, 1.5, 1.0);
	else 
		glScalef(1.0, 1.0, 1.0);
	glFrustum(-1.0, 1.0, -1.0, 1.0, 0.1, 20.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void move(void)
{
	if(zAxis < -1.3)
		zAxis += increment;

	theta[axis] += 2.5;
	if( theta[axis] > 360.0 ) 
		theta[axis] -= 360.0;

	glutPostRedisplay();
}

void output(int x, int y, char *string)
{
    int len, i;

    glRasterPos2f(x, y);
    len = (int) strlen(string);
    for (i = 0; i < len; i++) {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}

    glutPostRedisplay();
}

void reshape2(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	if(w > h)
		glScalef(1.0, 1.5, 1.0);
	else 
        glScalef(1.0, 1.0, 1.0);
    glFrustum(-1.0, 1.0, -1.0, 1.0, 0.1, 20.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  	
}

void tick(void)
{
    glutPostRedisplay();
}

void DisplayInfo(void)
{
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT3);
	glDisable(GL_DEPTH_TEST);

    glTranslatef(0.0f, 0.0f, -1.7f);
	glColor3f(0.0, 0.0, 0.0);
	glutSolidCube(size);

    glLoadIdentity();
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	switch(key) {
	case 'C':
	case 'c':
  	    
    	glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT3);
        glEnable(GL_DEPTH_TEST);
		glutDisplayFunc(display);
		glutReshapeFunc(reshape);
		glutIdleFunc(move);
	    break;

	case 'H':
	case 'h':
		CreateSub();
		break;

	case 'Q':
	case 'q':
		exit(0);
	}
	 
	glutPostRedisplay();
}

void CreateSub(void)
{
   	glutDisplayFunc(DisplayInfo);
	glutReshapeFunc(reshape2);
	glutIdleFunc(tick);
}

void mainMenu(int id)
{
	switch (id) {
   case 1:
	   axis = 0;
       break;
   case 2:
	   axis = 1;
	   break;
   case 3:
	   axis = 2; 
	   break;
   case 4:
	   CreateSub();
	   break;
   case 5:
	   exit(1);
	}
   theta[axis] += 2.0;
   if( theta[axis] > 360.0 ) 
	   theta[axis] -= 360.0;
   glutPostRedisplay();

}

int main(int argc, char** argv)
{
	int menu;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(450, 450);
//	glutInitWindowPosition(100, 100);
//	win = glutCreateWindow("Sphere");
	glutCreateWindow("Sphere");
	menu = glutCreateMenu(mainMenu);
	glutAddMenuEntry("Rotate X", 1);
	glutAddMenuEntry("Rotate Y", 2);
	glutAddMenuEntry("Rotate Z", 3);
	glutAddMenuEntry("Help", 4);
	glutAddMenuEntry("Quit", 5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(move);
	glutMainLoop();
	return 0;
}
