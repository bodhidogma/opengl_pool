#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream.h>

#include <unistd.h>


//#include "box.h"
#include "pooltable.h"
//#include "box_obj.h"

int spin =0, move=0;
int beginx, beginy;
int dx = 0, dy = 0;

void init(void)
{   
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = { 1.0, 0.0, 1.0, 0.0 };
    GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };

    
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
//    glClearColor (0.0, 0.0, 0.0, 1.0);
   
    glShadeModel( GL_SMOOTH );
    glEnable( GL_COLOR_MATERIAL );

    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess );
    glLightfv( GL_LIGHT0, GL_POSITION, light_position );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, white_light );
    glLightfv( GL_LIGHT0, GL_SPECULAR, white_light );
	   
    glEnable( GL_LIGHTING );
//    glEnable( GL_LIGHT0 );

}

void draw_raw( void )
{
    int cnt, pos;
    
    for ( cnt=0, pos=0; cnt< rawobj[3]; cnt++ ){
//    for ( cnt=0, pos=0; cnt< 3; cnt++ ){
    	glDrawElements( GL_LINE_STRIP,
	    rawobj__iii[pos]*3,
	    GL_UNSIGNED_INT, &rawobj__iii[pos+2] );
	
//	cout << "cnt: " << cnt << " p: " << pos << " # " << rawobj__iii[pos];
	
	pos += (rawobj__iii[pos]* 3)+2;

//	cout << " -> " <<  rawobj__iii[pos] << endl;

    }

}

void display(void)
{
    int cnt, tmp;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
    GLfloat verticies[] =
   	{ -200.0, -100.0, 0.0,
	  -200.0, 100.0, 0.0,
	   0.0, 100.0, 0.0,
	   0.0, -100.0, 0.0 };

    int vlist[] = {
	0, 1 ,2,
	3, 4, 5,
	6, 7, 8,
	9, 10, 11 };
    
    glColor3ub( 100,40,180 );
    
    glPushMatrix();
       	
    glRotatef( dx, 1, 0, 0 );
    glRotatef( dy, 0, 1, 0 );
    
//    glRotatef(-45, 1, 0, 0 );
    
    glInterleavedArrays( GL_V3F, 0, verticies );
//    glDrawArrays( GL_QUADS, 0, 4 );
//    glDrawElements( GL_QUADS, 4, GL_UNSIGNED_INT, vlist );

//    glInterleavedArrays( GL_V3F, 0, (GLvoid *)(&rawobj__iii[2]) );
//    glDrawArrays( GL_LINES, 0, 576 );
	    
//    glInterleavedArrays( GL_V3F, 0, rawobj____i );
//    glInterleavedArrays( GL_V3F, 0, Box01_vertex );
//    glInterleavedArrays( GL_V3F, 0, Torus01_vertex );

    glEnable( GL_DEPTH_TEST );
    glEnable( GL_CULL_FACE );
    
//    glutWireSphere( 400, 20, 16 );
    
    glRotatef( -90, 1, 0, 0 );
    glTranslatef( -225, 0, 0 );

//    draw_raw();

    glDrawElements( GL_LINE_STRIP,
	    sizeof(vlist)/sizeof(long),
	    GL_UNSIGNED_INT, vlist );

/*    glDrawElements(
	    GL_LINE_STRIP,
//	    GL_TRIANGLE_STRIP,
//	    3,
	    sizeof(Torus01_face)/sizeof(long),
	    GL_UNSIGNED_INT, Torus01_face );
*/    
//    glDrawArrays( GL_LINES, 0, sizeof(Cylinder03_vertex)/sizeof(Point3) );
    
/*
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, -1.0, 0.0);
   glTexCoord2f(0.0, 3.0); glVertex3f(-2.0, 1.0, 0.0);
   glTexCoord2f(3.0, 3.0); glVertex3f(0.0, 1.0, 0.0);
   glTexCoord2f(3.0, 0.0); glVertex3f(0.0, -1.0, 0.0);

   glTexCoord2f(0.0, 0.0); glVertex3f(1.0, -1.0, 0.0);
   glTexCoord2f(0.0, 3.0); glVertex3f(1.0, 1.0, 0.0);
   glTexCoord2f(3.0, 3.0); glVertex3f(2.41421, 1.0, -1.41421);
   glTexCoord2f(3.0, 0.0); glVertex3f(2.41421, -1.0, -1.41421);
   glEnd();
*/
 
    glPopMatrix();

//   glFlush();
   glutSwapBuffers();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60.0, (GLfloat) h/(GLfloat) w, 1.0, 128.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(0.0, 0.0, -3.0);
   
   glScalef( .002, .002, .002 );
}

/* ARGSUSED1 */
void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
      case 'q':
         exit(0);
         break;
	 
      case ' ':
	 glutPostRedisplay();
	 break;
	
      default:
         break;
   }
}



void mouse( int button, int state, int x, int y )
{
    if ( button == GLUT_LEFT_BUTTON ) {
	if ( state == GLUT_DOWN ) {
	    glutIdleFunc( NULL );
	    spin = 0;
	    move = 1;
	    beginx = x;
	    beginy = y;
    	}
	else {	// GLUT_UP 
	    move = 0;
	}
    }
}

void mousemove( int x, int y )
{
    if ( move ) {
	if ( y-beginy )
	    dx -= (y-beginy);
	
	if ( x-beginx )
	    dy += (x-beginx);
	
	if ( dx < -15 )
	    dx = -15;
	if ( dx > 90 )
	    dx = 90;
	
	
	cout << "dx: " << dx << " dy: " << dy << endl;
	
	
	beginx = x;
	beginy = y;
	
	glutPostRedisplay();

//	glutIdleFunc( idle );
    }
}

void idle( void )
{
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(512, 512);
   glutCreateWindow(argv[0]);
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   
   glutMouseFunc( mouse );
   glutMotionFunc( mousemove );
   
   glutMainLoop();

   return 0; 
}
