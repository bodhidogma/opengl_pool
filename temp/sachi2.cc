/* *****************************************************************

  PROJECT NAME:		Virtual Billiards
  CLASS/TERM:		csc630.01/Fall 1999
  GROUP NUMBER:		3
  GROUP MEMBERS:	Scott Emery, Sachiko Halper, 
					Paul McAvoy, Soudabeh Sanaee

******************************************************************* */


#include <GL/glut.h>
#include <stdlib.h>
#include <string.h>


int imagewidth = 371;				//image width in pixels
int imageheight = 528;				//image height in pixels

GLubyte backimage[imageheight][imagewidth][3];	//image array -- the last
												//value is the image depth
void CreateHelp(void);
void keyboard(unsigned char key, int x, int y);



void init(void)
//Initial operating procedures of the program.
{ 
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 
	glShadeModel(GL_FLAT);
	//makeBackgroundImage function goes here -- this is what I can't figure
	//out -- how to create the image in the window.  Hmm... 
    glEnable(GL_DEPTH_TEST);   
}



void display(void)
//Registered GLUT display callback functions.  Includes procedures to render
//and re-render the scene.
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glRasterPos2i(0,0);
	//glDrawPixels(imagewidth, imageheight, GL_RGB, GL_UNSIGNED_BYTE, backimage);
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glLoadIdentity();
	glFlush();
	glutSwapBuffers();
}



void reshape(int w, int h)
//Responsible for handling the re-sizing of the main menu window
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
}



void reshapeHelp(int w, int h)
//Responsible for the re-sizing of the help (instructions) window.
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);  	
}



void displayHelp(void)
//Includes procedures used to render the help screen.
{
	glDisable(GL_DEPTH_TEST);
    glLoadIdentity();
	glutSwapBuffers();
}



void keyboard(unsigned char key, int x, int y)
//Links specific keyboard keys with specific routines that are invoked
//once the key is depressed.
{
	switch(key) {
	case 'C':
	case 'c':
        glEnable(GL_DEPTH_TEST);
		glutDisplayFunc(display);
		glutReshapeFunc(reshape);
	    break;

	case 'H':
	case 'h':
		CreateHelp();
		break;

	case 'Q':
	case 'q':
		exit(0);
	}
	 
	glutPostRedisplay();
}



void CreateHelp(void)
//Creates the Help (instructions) window.
{
   	glutDisplayFunc(displayHelp);
	glutReshapeFunc(reshapeHelp);
}



void mainMenu(int key)
//Contains the main menu options and directs their functions.
{
   switch(key) {
   case 1:
	   //Option for a new game
       break;
   case 2:
	   //Option for a possible 2-player game
	   break;
   case 3:
	   //Option for a possible practice mode
	   break;
   case 4:
	   CreateHelp();
	   break;
   case 5:
	   exit(1);
	}
}

int main(int argc, char** argv)
//Contains routines necessary for initializing the window, display callback, 
//and running the program.
{
	int menu;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(371, 528);
	glutInitWindowPosition(150, 200);
	glutCreateWindow("Virtual Billiards - MESH Gaming 1999");

	//Main menu creation
		menu = glutCreateMenu(mainMenu);
		glutAddMenuEntry("New Game", 1);
		glutAddMenuEntry("2-Player", 2);
		glutAddMenuEntry("Practice", 3);
		glutAddMenuEntry("Help", 4);
		glutAddMenuEntry("Quit", 5);
		glutAttachMenu(GLUT_RIGHT_BUTTON);

	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
