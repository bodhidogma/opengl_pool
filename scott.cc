/* ************************************************************
   
FILENAME:  scott.cc
AUTHOR:    Paul McAvoy w/ cuestick implementations by Scott Emery
DATE:	   11/22/99

************************************************************* */

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream.h>

#include <unistd.h>
#include <assert.h>
#include <math.h>


//#include "box.h"
#include "pooltable.h"
#include "models.h"
//#include "box_obj.h"

int spin =0, move=0;
int beginx, beginy;
int dx = 0, dy = 0;
int stickflag = 0;

GLuint dlist;
GLuint sticklist;

    GLfloat Box01_vertex[] = {
         .147160, .208735,-.328553,	// 0
        -.133291, .423785, .025140,	// 1
         .147384, .208563, .378553,	// 2
         .427836,-.006487, .024859,	// 3
        -.157088,-.188042,-.328553,	// 4
         .123587,-.403264, .024859,	// 5
        -.156864,-.188213, .378553,	// 6
        -.437540, .027008, .025140	// 7
	};

    long Box01_face[] = {
        0,1,2, 2,3,0,
	4,5,6, 6,7,4,
	0,3,5, 5,4,0,
        3,2,6, 6,5,3,
	2,1,7, 7,6,2,
	1,0,4, 4,7,1
	};
/*
    GLfloat Box01_vertex[] = {
        -.5, .5, .5,	// 0
        -.5,-.5, .5,	// 1
         .5,-.5, .5,	// 2
         .5, .5, .5,	// 3
         .5, .5,-.5,	// 4
         .5,-.5,-.5,	// 5
        -.5,-.5,-.5,	// 6
        -.5, .5,-.5	// 
	};

    long Box01_face[] = {
        0,1,2, 2,3,0,
//	4,5,6, 6,7,4,
//	0,3,5, 5,4,0,
//      3,2,6, 6,5,3,
//	2,1,7, 7,6,2,
//	1,0,4, 4,7,1
	};
*/
#define L_POS -1, 1, 1
    
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 5.0 };
    GLfloat light_position[] = { L_POS , 0.0 };
    GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };


GLvoid
glmCross( GLfloat *u, GLfloat *v, GLfloat *n )
{
    assert(u); assert(v); assert(n);

    n[0] = u[1]*v[2] - u[2]*v[1];
    n[1] = u[2]*v[0] - u[0]*v[2];
    n[2] = u[0]*v[1] - u[1]*v[0];
}

GLvoid
glmNormalize( GLfloat *v )
{
    GLfloat l;
    
    assert(v);

    l = (GLfloat)sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2] );
    v[0] /= l;
    v[1] /= l;
    v[2] /= l;
}
    
void draw_raw( void )
{
    GLfloat u[3];
    int cnt, v, pos, f;
	    
    for ( cnt=0, pos=0; cnt< rawobj[3]; cnt++ ){
//    for ( cnt=0, pos=0; cnt< 3; cnt++ ){
	for (v=0; v<rawobj__iii[pos]*3; v++ ){
	    
	    f = rawobj__iii[pos+2+v];
	    memcpy( &u[0], &rawobj____i[ f*3 ], sizeof(GLfloat)*3 );
	    
	    glNormal3fv( u );
	    glArrayElement( f );
	}
//	cout << "cnt: " << cnt << " p: " << pos << " # " << rawobj__iii[pos];
	
	pos += (rawobj__iii[pos]* 3)+2;

//	cout << " -> " <<  rawobj__iii[pos] << endl;

    }

}

void init(void)
{   
    GLfloat u[3], v[3], n[3];
    int cnt, f,f2;

//    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    glClearColor (0.0, 0.0, 0.0, 1.0);
    
//    glCullFace( GL_BACK );
//    glFrontFace( GL_CCW );
//    glEnable( GL_CULL_FACE );
    
    glEnable( GL_COLOR_MATERIAL );
//    glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
    
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );

    glEnable( GL_DEPTH_TEST );
    glShadeModel( GL_SMOOTH );

//    glPolygonMode( GL_FRONT, GL_FILL );
//    glDepthFunc( GL_LESS );
    
//    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess );
    glLightfv( GL_LIGHT0, GL_POSITION, light_position );
//    glLightfv( GL_LIGHT0, GL_DIFFUSE, white_light );
//    glLightfv( GL_LIGHT0, GL_SPECULAR, white_light );

    dlist = glGenLists(1);
    
    glNewList( dlist, GL_COMPILE );
    
    glColor3ub( 180,40,100 );
    glutWireSphere( 1, 20, 16 );
    
        glColor3f( 1,1,1 );

/*   	glInterleavedArrays( GL_V3F, 0, Box01_vertex );
	glBegin( GL_TRIANGLES );
	for ( cnt = 0; cnt < sizeof(Box01_face)/sizeof(long); cnt++ ){
//	for ( cnt = 0; cnt < (3*3) ; cnt++ ){
		f = Box01_face[ cnt ];
		memcpy( &u[0], &Box01_vertex[f*3], sizeof(GLfloat)*3 );
*	    if ( !(cnt%3) ) {
		f2 = Box01_face[ cnt+1 ];
		memcpy( &v[0], &Box01_vertex[f2*3], sizeof(GLfloat)*3 );
		
		glmCross( u, v, n );
		
		glmNormalize( n );

		glNormal3fv( n );
		
		cout << "c: " << cnt << " f=" << f << " f2=" << f2 << endl;
		cout << " (f: " << Box01_vertex[f*3];
		cout << "," << Box01_vertex[f2*3] << " )" << endl;
		cout << " u: " << u[0] <<" " << u[1] <<" " << u[2] << endl;
		cout << " v: " << v[0] <<" " << v[1] <<" " << v[2] << endl;
		cout << " n: " << n[0] <<" " << n[1] <<" " << n[2] << endl;
		
	    }
*
	    glNormal3fv( u );
	    glArrayElement( f );
	}
        glEnd();
*/
/*   	glInterleavedArrays( YBALLFORMAT, 0,(GLvoid*)&YBALLMODEL );
	glBegin( GL_TRIANGLES );
	for ( cnt=0; cnt < YBALLPOLYCNT *3; cnt++ ) {
	    memcpy( &u[0], &YBALLMODEL[ cnt ], sizeof(GLfloat)*3 );
	    glNormal3fv( u );
	    glArrayElement( cnt );
        }
	glEnd();
*/
        glInterleavedArrays( GL_V3F, 0, rawobj____i );
	glBegin( GL_TRIANGLES );
            draw_raw();
	glEnd();
		
    glEndList();
		
    
//    glDrawArrays( GL_QUADS, 0, 4 );
//    glDrawElements( GL_QUADS, 4, GL_UNSIGNED_INT, vlist );

//    glInterleavedArrays( GL_V3F, 0, (GLvoid *)(&rawobj__iii[2]) );
//    glDrawArrays( GL_LINES, 0, 576 );
	    
//    glInterleavedArrays( GL_V3F, 0, Box01_vertex );
//    glInterleavedArrays( GL_V3F, 0, Torus01_vertex );

    sticklist = glGenLists (1);
    glNewList (sticklist, GL_COMPILE);
         glTranslatef( 0, -500, 400);
         glRotatef(240.0, 1.0, 0, 0);
         glutSolidCone(10, 600, 20, 16);
    glEndList ();
}

void display(void)
{
//    int cnt, tmp;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
    
    glPushMatrix();
    
    glTranslatef( L_POS );
    glColor3f( 1,1,1 );
    glutSolidSphere( .05, 10, 8 );
    
    glPopMatrix();
    glPushMatrix();
    
    
    glRotatef( dx, 1, 0, 0 );
    glRotatef( dy, 0, 1, 0 );
    
    glRotatef( -90, 1, 0, 0 );
//    glLightfv( GL_LIGHT0, GL_POSITION, light_position );
//    glRotatef(-45, 1, 0, 0 );
    
//    glColor3ub( 180,40,100 );
//    glutWireSphere( 1, 20, 16 );
    
//    glRotatef( -90, 1, 0, 0 );
//    glTranslatef( -225, 0, 0 );

    glEnable( GL_NORMALIZE );
//    glScalef( 4, 4, 4 );
    glScalef( .002, .002, .002 );
    
    glCallList( dlist );
    
    if( stickflag )
    	glCallList( sticklist );

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
      
      case 's':
	 if( stickflag )
	     stickflag = 0;
	 else
	     stickflag = 1;
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
	
/*	if ( dx < -15 )
	    dx = -15;
	if ( dx > 90 )
	    dx = 90;
*/	
	
//	cout << "dx: " << dx << " dy: " << dy << endl;
	
	
	beginx = x;
	beginy = y;
	
	glutPostRedisplay();

//	glutIdleFunc( idle );
    }
}

void drawstick( void )
{
        
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
