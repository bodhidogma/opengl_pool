// File:        proj1.c
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        cs630 project #1
// 		Use the OpenGL library to draw multicolored solid obects.
// 		Use frustom 
// 
// $Revision: 1.1 $
/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  1999/09/25 07:36:14  paulmcav
 * added multi textures, better axis movement, coordinate axis & more
 *
 * Revision 1.1.1.1  1999/09/24 15:42:55  paulmcav
 * Imported sources
 *
 */

// ------------------------------------------------------------------
// Use common GLut toolkit for support functions and nice things.
// readtex.h is included to support loading SGI 'rgb' type files for
//  	texture maps
 
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

//#include "proj1.h"
//#include "readtex.h"

// ------------------------------------------------------------------
// Some static vars used to control animaton, and various states of program
// execution.
 
// state vars
static int animate = 0;
static int wire = 0;
static int map = 0;

#define S_YEAR 245.0
#define S_DAY 0.0
#define S_X 1.0
#define S_Y 1.0
#define S_Z 1.0
#define S_D 1.0

#define step 1.0

// position information
static int     year = S_YEAR,
	       day = S_DAY;

static GLfloat fX = S_X,
	       fY = S_Y,
	       fZ = S_Z,
	       fD = S_D;

// gl object(s)
GLuint MyObject;

GLuint texName[2];


void init( void );
void idle( void );
void display( void );
void reshape( int w, int h );
void keyboard( unsigned char key, int x, int y );
void specialkeys( int key, int x, int y );
void mousefunc( int b, int s, int mx, int my );

// ------------------------------------------------------------------
//  Func: main( c, v )
//        c = number of arguments passed
//        v = argument list
//  Desc: main entry point
//
//  Ret:  0
// ------------------------------------------------------------------

int main( int argc, char *argv[] )
{

    // configure our GL custom functions
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize( 500, 500 );
//    glutInitWindowPosition( 100, 100 );
    glutCreateWindow( argv[0] );
    init();

    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
    glutKeyboardFunc( keyboard ); 
    glutSpecialFunc( specialkeys );
    glutMouseFunc( mousefunc );
    
    // start idle function if we are animating
    if ( animate )
	glutIdleFunc( idle );
    
    // get to it!
    glutMainLoop();
    return 0;
}

// ------------------------------------------------------------------
//  Func: init()
//  Desc: initialize GL session.
//  	  Used to define some shapes, set up the lighting, and load
//  	  texture maps for use later.
//
//  Ret:  
// ------------------------------------------------------------------

void init( void )
{
    GLUquadricObj *q = gluNewQuadric();
    
    // set GL options as desired
    glEnable( GL_COLOR_MATERIAL );
    glEnable( GL_CULL_FACE );
    glEnable( GL_DEPTH_TEST );
    
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    glShadeModel( GL_SMOOTH );
    
    // want to pre-create some objects
    MyObject = glGenLists(4);
    
    // cordinates
    glNewList( MyObject , GL_COMPILE );
    {
	glBegin( GL_LINES );
	glVertex3f( 0.0, 1.0, 0.0 );
	glVertex3f( 0.0, -1.0, 0.0 );
	glVertex3f( 1.0, 0.0, 0.0 );
	glVertex3f( -1.0, 0.0, 0.0 );
	glVertex3f( 0.0, 0.0, 1.0 );
	glVertex3f( 0.0, 0.0, -1.0 );
	glEnd();
	
	// arrow heads
	glTranslatef( 0.0, 0.0, 1.0 );		// +Z
        glutSolidCone( 0.05, 0.1, 5, 1 );
	glTranslatef( 0.0, 0.0, -2.0 );
	
	glRotatef( 180, 1.0, 0.0, 0.0 );
        glutSolidCone( 0.05, 0.1, 5, 1 );	// -Z
	
	glTranslatef( 0.0, 1.0, -1.0 );		
	glRotatef( -90, 1.0, 0.0, 0.0 );
        glutSolidCone( 0.05, 0.1, 5, 1 );	// +Y
	
	glTranslatef( 0.0, 0.0, -2.0 );
	glRotatef( 180, 1.0, 0.0, 0.0 );
        glutSolidCone( 0.05, 0.1, 5, 1 );	// -Y
	
	glRotatef( 90, 0.0, 1.0, 0.0 );
	glTranslatef( 1.0, 0.0, 1.0 );
        glutSolidCone( 0.05, 0.1, 5, 1 );	// +X
	
	glTranslatef( 0.0, 0.0, -2.0 );
	glRotatef( 180, 0.0, 1.0, 0.0 );
        glutSolidCone( 0.05, 0.1, 5, 1 );	// -X
	
	glTranslatef( 0.0, 0.0, -1.0 );
	glRotatef( 90, 1.0, 0.0, 0.0 );
	glRotatef( 270, 0.0, 0.0, 1.0 );
	
//        glutSolidCone( 0.1, 0.2, 5, 1 );	// -X
    }
    glEndList();
    
    // ecliptic
    glNewList( MyObject+1 , GL_COMPILE );
    {
    	glRotatef( -90.0, 1.0, 0.0, 0.0 );
	gluQuadricNormals( q, GL_SMOOTH );
	gluQuadricTexture( q, GL_TRUE );
	gluDisk( q, 1.99, 2.01, 32, 1 );
    	glRotatef( 90.0, 1.0, 0.0, 0.0 );

    }
    glEndList();

    // sun
    glNewList( MyObject+2 , GL_COMPILE );
    {
    	glRotatef( -90.0, 1.0, 0.0, 0.0 );
	gluQuadricNormals( q, GL_SMOOTH );
	gluQuadricTexture( q, GL_TRUE );
        gluSphere( q, .35, 20, 16 );
    	glRotatef( 90.0, 1.0, 0.0, 0.0 );

    }
    glEndList();

    // planet 
    glNewList( MyObject+3 , GL_COMPILE );
    {
    	glRotatef( -90.0, 1.0, 0.0, 0.0 );
	gluQuadricNormals( q, GL_SMOOTH );
	gluQuadricTexture( q, GL_TRUE );
	gluSphere( q, 0.2, 10, 8 );
    	glRotatef( 90.0, 1.0, 0.0, 0.0 );
	
	glBegin( GL_LINES );
	glVertex3f( 0.0, 0.25, 0.0 );
	glVertex3f( 0.0, -0.25, 0.0 );
	glEnd();

    }
    glEndList();

    // moon
    glNewList( MyObject+4 , GL_COMPILE );
    {
    	glRotatef( -90.0, 1.0, 0.0, 0.0 );
	gluQuadricNormals( q, GL_SMOOTH );
	gluQuadricTexture( q, GL_TRUE );
	gluSphere( q, 0.07, 10, 8 );
    	glRotatef( 90.0, 1.0, 0.0, 0.0 );

    }
    glEndList();

    gluDeleteQuadric( q );

    // configure our lighting arrangement
    glEnable( GL_LIGHTING );
    {
        GLfloat light_position[] = { 1.0, 1.0, 0.0, 0.0 };
        GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat mat_shininess[] = { 20.0 };
	
        GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat gray[] = { 0.7, 0.7, 0.7, 1.0 };
//	GLfloat teal[] = { 0.0, 1.0, 0.8, 1.0 };
    
	// set position and lighting types
        glLightfv( GL_LIGHT0, GL_POSITION, light_position );
//        glMaterialfv( GL_FRONT, GL_DIFFUSE, teal );
        glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess );
	
        glLightfv( GL_LIGHT0, GL_DIFFUSE, gray );

        glEnable( GL_LIGHT0 );
    }

    // filtering / mipmaps
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST );

    glTexGeni( GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );
    glTexGeni( GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );
    
    glGenTextures( 2, texName );
    
    glBindTexture( GL_TEXTURE_2D, texName[0] );
    // load our mipmaps into memory for use later
//    if ( !LoadRGBMipmaps( "sun.rgb", GL_RGB )) {
//	printf( "Error: couldn't load texture image\n" );
//	exit(1);
//    }
    
    glBindTexture( GL_TEXTURE_2D, texName[1] );
//    if ( !LoadRGBMipmaps( "earth.rgb", GL_RGB )) {
//	printf( "Error: couldn't load texture image\n" );
//	exit(1);
//   }


}

// ------------------------------------------------------------------
//  Func: reshape( width, height )
//  	  width = screen width
//  	  height = screen height
//  Desc: Handle changes in windor re-sizing.  Adjust Frustom settings.
//
//  Ret:  
// ------------------------------------------------------------------

void reshape( int w, int h )
{
    GLfloat hp = (GLfloat) h / (GLfloat) w;
    GLfloat wp = (GLfloat) w / (GLfloat) h;
    
    glViewport( 0,0, (GLsizei) w, (GLsizei) h );
    glMatrixMode( GL_PROJECTION ) ;
    glLoadIdentity();
    // configure our viewport (frustom)
    //  l,r | b,t | n,f
//    glFrustum( -.75, .75, -.75, .75, 10.0, 100.0 );
    glMatrixMode( GL_MODELVIEW );
    glTranslatef( 0.0, 0.0, -20.0 );
     
}

// ------------------------------------------------------------------
//  Func: display()
//  Desc: Update display.  Re-render GL scene according to criteria.
//
//  Ret:  
// ------------------------------------------------------------------

void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glPushMatrix();

    // axis
    glCallList( MyObject );
    
    // ecliptic
    glCallList( MyObject+1 );
    
    glRotatef( (GLfloat) year, 0.0, 1.0, 0.0 );
    
    if ( map )
	glEnable( GL_TEXTURE_2D );
    else
	glDisable( GL_TEXTURE_2D );
    
    // sun
    glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT );
    glColor3f( 1.0, 0.9, 0.2 );
    if ( wire ) {
	glDisable( GL_TEXTURE_2D );
    	glRotatef( -90, 1.0, 0.0, 0.0 );
        glutWireSphere( .35, 20, 16 );
    	glRotatef( 90, 1.0, 0.0, 0.0 );
    }
    else {
        glBindTexture( GL_TEXTURE_2D, texName[0] );
        glCallList( MyObject+2 );
    }
    
    // planet
    glTranslatef( 2.0, 0.0, 0.0 );
    glRotatef( (GLfloat) day, 0.13, 1.0, 0.0 );
    glColor3f( .1, .1, .9 );
    if ( wire ) {
        glDisable( GL_TEXTURE_2D );
    	glRotatef( -90, 1.0, 0.0, 0.0 );
	glutWireSphere( 0.2, 10, 8 );
    	glRotatef( 90, 1.0, 0.0, 0.0 );
    }
    else {
        glBindTexture( GL_TEXTURE_2D, texName[1] );
	glCallList( MyObject+3 );
    }
    
    glDisable( GL_TEXTURE_2D );
    // moon
    glTranslatef( .5, 0.0, 0.0 );
    glColor3f( .7, .7, .7 );
    if ( wire )
    	glCallList( MyObject+4 );
    else 
    	glCallList( MyObject+4 );
    
    glPopMatrix();

    glutSwapBuffers();
}

// ------------------------------------------------------------------
//  Func: idle()
//  Desc: Idle loop animation function
//
//  Ret:  
// ------------------------------------------------------------------

void idle( void ) 
{
    day = (day+30) % 360;
    year = (year+1) % 360;
    glutPostRedisplay();
}

// ------------------------------------------------------------------
//  Func: keyboard( key, x,y )
//  	  key = ascii key code
//  	  x = mouse x position
//  	  y = mouse y position
//  Desc: handle normal alpha key presses.  Update dispaly as needed.
//
//  Ret:  
// ------------------------------------------------------------------

void keyboard( unsigned char key, int x, int y )
{
    switch( key ){
	case 27:			// exit program
	case 'q':
	    exit(0);
	    break;

	case 'a':			// toggle animation
	    animate ^= 1;
	    if ( animate )
		glutIdleFunc( idle );
	    else
		glutIdleFunc( NULL );
    
	    break;

	case 'd':			// rotate planet by a day
	    day = (day+10) % 360;
	    glutPostRedisplay();
	    break;
	    
	case 'D':			// "" backwards
	    day = (day-10) % 360;
	    glutPostRedisplay();
	    break;

	case 'y':			// rotate planet around sun
	    year = (year+5) % 360;
	    glutPostRedisplay();
	    break;
	    
	case 'Y':			// "" backwards
	    year = (year-5) % 360;
	    glutPostRedisplay();
	    break;

	case 'p':			// display position information
	    printf( "Pos: Y=%d, D=%d, X=%.1f, Y=%.1f, Z=%.1f, D=%.1f\n",
		    (int)year, (int)day, fX, fY, fZ, fD );
	    break;

	case 'w':			// toggle wireframe mode
	    wire ^= 1;
	    glutPostRedisplay();
	    break;

	case 'm':			// toggle texture mapping
	    map ^= 1;
	    glutPostRedisplay();
	    break;

	case 'r':			// reset position settings
	    year = S_YEAR;
	    day = S_DAY;
	    fX = S_X;
	    fY = S_Y;
	    fZ = S_Z;
   	    glLoadIdentity();
	    glTranslatef( 0.0, 0.0, -20.0 );
	    glutPostRedisplay();
	    break;
	    
	case 'i':			// display information
	    printf( "Instructions:\n" );
	    printf( " (q)uit\n" );
	    printf( " (i)nstructions\n" );
	    printf( " (r)eset settings\n" );
	    printf( " (a)nimate\n" );
	    printf( " (y)ear\n" );
	    printf( " (d)ay\n" );
	    printf( " (p)rint settings\n" );
	    printf( " (w)ireframe\n" );
	    printf( " (m)ipmapping\n" );
	    printf( " (up/dn) Y axis traverse\n" );
	    printf( " (rt/lt) X axis traverse\n" );
	    printf( " (pg up/pg dn) Z axis zoom\n" );
	    break;
	    
	default:
	    break;
    }
}

// ------------------------------------------------------------------
//  Func: specialkeys( key, x,y )
//  	  key = special GL keycode
//  	  x = mouse x position
//  	  y = mouse y position
//  Desc: handle specialty keys, page up, dn, arrow keys etc.
//        update display after a key was pressed.
//
//  Ret:  
// ------------------------------------------------------------------

void specialkeys( int key, int mx, int my )
{
    int x = 0, y = 0, z = 0, d = 0;
    
    switch( key ){
	case GLUT_KEY_UP:		// move along X axis
	    y = -step;
	    break;

	case GLUT_KEY_DOWN:		// "" back
	    y = step;
	    break;

	case GLUT_KEY_LEFT:		// move along Y axis
	    x = step;
	    break;

	case GLUT_KEY_RIGHT:		// "" back
	    x = -step;
	    break;

	case GLUT_KEY_PAGE_UP:		//  into Z axis
	    z = -(10*step);
	    break;

	case GLUT_KEY_INSERT:	// "" out
	    z = (10*step);
	    break;

	case GLUT_KEY_HOME:		//  into Z axis
	    d = -step;
	    break;

	case GLUT_KEY_END:	// "" out
	    d = step;
	    break;
    }
    
    if ( x )
	glRotatef( x, 0.0, 0.0, 1.0 );
    if ( y )
	glRotatef( y, 1.0, 0.0, 0.0 );
    if ( z )
	glRotatef( z, 0.0, 1.0, 0.0 );

    if ( d )
	glTranslatef( 0.0, 0.0, d );
    
    glutPostRedisplay();
}


void mousefunc( int b, int s, int mx, int my )
{
    int x = 0, y = 0, z = 0, d = 0;
    
    if ( b == GLUT_LEFT_BUTTON ) {
//	printf( " mx = %d, my = %d\n", mx, my );
	
    }
}
