//****************************************************************
// FILE: proj1.c. This program creates a window and draws a solid*
//       3D object in a perspective view, beginning small in the *
//       background and enlarging as the object appraoches the   *
//       viewer.                                                 *
//                                                               *
// AUTHOR: Soudabeh Maher                                        *
//                                                               *
// USAGE COMMENTS: Link the file with opengl32.lib, glut32.lib,  *
//                 and glu32.lib.                                *
//                                                               *
// LIBRARIES:                                                    *
//                 Proj1.h -- the header file                    *
//                                                               *
// FUNCTIONS/METHODS DEFINED:                                    *
//     void Init        -- initializes light & background color  *
//     void Display     -- displays & rotates the sphere         *
//     void Reshape     -- reshapes the object according to width*
//                         & height of the output window         *
//     void MoveForward -- moves the object forward              *
//     void MoveBackward-- moves the object backward             *
//     void Mouse       -- defines the effects of mouse clicks   *
//     void Keyboard    -- defines the effects of differnt keys  *
//     void PlaySound   -- plays sound                           *
//                                                               *
// GENERAL COMMENTS:   The first project in opengl for CSC630    *
//                                                               *
//****************************************************************

#include "soudi.h"

static BallType ball1;
static BallType ball2;
GLfloat light_ambient[] ={3.0, 1.0, 0.0, 1.0};
GLfloat light_ambient0[] ={1.0, 3.0, 3.0, 1.0};


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(60, 60);
	glutCreateWindow("Moving Object In Perspective View - CSC630 / Project 1");
	Init();
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	if ( direction == 1)
        glutIdleFunc(MoveForward);

    else if ( direction == -1)
	    glutIdleFunc(MoveBackward);

 	glutMainLoop();
	return 0;
}

//****************************************************************
// Init : does the operation that need to be done once. It sets  *
//        the background color and initialize light related      *
//        values. Enable light effects.                          *
//                                                               *
//****************************************************************

void Init(void)
{
    GLfloat mat_specular[]  ={1.0, 1.0, 1.0, 1.0};
	GLfloat mat_shininess[] ={50.0};
//	GLfloat light_ambient[] ={1.0, 3.0, 3.0, 1.0};
    GLfloat light_position[]={2.0, 1.0, -0.5, 0.0};
	GLfloat yellow_light[]   ={5.0, 5.0, 1.0, 1.0};
	
    glClearColor(0.1f, 0.0f, 0.4f, 0.0f);
    glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

//    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  yellow_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, yellow_light);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

	ball1.xCo = 3.0;
	ball2.xCo = -ball1.xCo;
	ball1.r   = 0.9f;
	ball2.r   = 0.9f;
}

//****************************************************************
// Display: displays the object on the output window.            *
//          It rotates the object around the line x = y          *
//          Also it shows the object on different position on    *
//          Z-axis and so makes it animate.                      *
//                                                               *
//****************************************************************


void Display(void)
{
	
 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.1f, 0.2f, 0.3f);

//	glLoadIdentity();
	glPushMatrix();
	
	glTranslatef(ball1.xCo, 0.0f, -9.0);

	// the object rotates around the line x - y = 0;
	glRotatef(angle, 0.0, 0.0, 1.0);

	glPushMatrix();
	glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient0);
    glPopMatrix();

	if (maxSizeFlag == 0)
	//   glutSolidSphere(ball1.r, 30, 30);
	     glutWireSphere(ball1.r, 20, 20);
    glPopMatrix();

//	glLoadIdentity();
	glPushMatrix();
	
	glTranslatef(ball2.xCo, 0.0f, -9.0f);

	// the object rotates around the line z = 1;
	glRotatef(-angle, 0.0, 0.0, 1.0);
 //   glMaterialfv(GL_FRONT, GL_AMBIENT, light_ambient);

	glPushMatrix();
	glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glPopMatrix();

	if (maxSizeFlag == 0)
	   glutWireSphere(ball2.r, 15, 15);
	     
    glPopMatrix();	

	glFlush();

	glutSwapBuffers();
}

//****************************************************************
// Reshape: reshapes the object according to the changes in width*
//          and height of the output window.                     *
//          Shows the object in perspective view.                *
//                                                               *
//****************************************************************

void Reshape(int  w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    if ( w < h)
	    glFrustum(-3.0, 3.0, -3.0*h/w, 3.0*h/w, 4.0, 19.0);
    else 
		glFrustum(-3.0*w/h, 3.0*w/h, -3.0, 3.0, 4.0, 19.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//****************************************************************
// MoveForward: spins and moves the object forward by changing   *
//              its position on z_axis.                          *
//                                                               *
//****************************************************************

void MoveForward(void)
{

    float distance;

	if ( ball1.xCo <= 4.0f && ball1.xCo >= -4.0f)
    {

	    ball1.xCo -= 0.09f * direction;
        ball2.xCo = -ball1.xCo;
	} 

    distance = ball1.xCo - ball2.xCo;

    if (abs((int)distance) <= (ball1.r + ball2.r) )
	    direction *= -1;

	angle += (direction * clockWise * 1.5);
	
	if( angle > 360.0 ) 
		angle -= 360.0;

	glutPostRedisplay();
}

//****************************************************************
// MoveBachward: spins and moves the object backward by changing *
//               its position on z_axis.                         *
//                                                               *
//****************************************************************

void MoveBackward(void)
{
	float distance;
     
	if ( ball1.xCo <= 4.0f && ball1.xCo >= -4.0f)
	{
		ball1.xCo += 0.09f * direction;
	    ball2.xCo = -ball1.xCo;
	}

    distance = ball1.xCo - ball2.xCo;

    if (abs((int)distance) <= (ball1.r + ball2.r) )
		direction *= -1;
	
	angle -= (direction * clockWise * 1.5);
	
	if( angle < -360.0 ) 
		angle += 360.0;

	glutPostRedisplay();
}

//****************************************************************
// Mouse: defines the effects of mouse bottons on the movement   *
//        of the object.                                         *
//        right btn  -- rotate twice faster                      * 
//        middle btn -- rotate faster and faster with each btn   *
//                      click                                    *
//        left btn   -- rotate in oposite direction twice faster *
//                                                               *
//****************************************************************

void Mouse(int btn, int state, int x, int y)
{

    // mouse callback, changes the speed and angle of rotation

	if (btn == GLUT_LEFT_BUTTON   && state == GLUT_DOWN) 
		clockWise = 2;
	if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) 
		clockWise *= 2;
	if (btn == GLUT_RIGHT_BUTTON  && state == GLUT_DOWN) 
		clockWise = -2;
}

//****************************************************************
// Keyboard: defines the effects of different keys on the        *
//           movement of the object.                             *
//           r or R : repeats the forward motion                 *
//           b or B : repeats the backward motion                *
//           i or I : gives a little menu for the program.       *
//           q or Q : quits the program                          *
//                                                               *
//****************************************************************

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'R':
	case 'r':
	    direction = 1;
	    ball1.xCo = 4.0f;
		ball2.xCo = -ball1.xCo;
		maxSizeFlag = 0;
		glutIdleFunc(MoveForward);
		break;
	case 'b':
	case 'B':
		direction = 1;
		ball1.xCo = -4.0f;
    	ball2.xCo = -ball1.xCo;
		maxSizeFlag = 0;
		glutIdleFunc(MoveBackward);
		break;
	case 'i':
	case 'I':
		
		//PlaySound( "sudi.wav", NULL, SND_FILENAME | SND_ASYNC );

        printf(" Isn't that nice?\n");
	printf(" You have to be in output window to use this options!\n");
        printf(" Hit 'r' or 'R' to repeat forward move!\n");
        printf(" Hit 'b' or 'B' to repeat backward move!\n");
        printf(" Hit 'i' or 'I' to see these information!\n");   
        printf(" Hit 'q' or 'Q' to quit!\n"); 
        break;
    case 'Q':
	case 'q': 
        exit (0);
		break;
	default:
		break;
	}
}

