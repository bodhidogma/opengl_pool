// File:        glpool.cc
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
// 
// $Revision: 1.2 $
/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  1999/10/13 05:22:43  paulmcav
 * template files for future classes
 *
 */

#include <stdlib.h>
#include <iostream.h>

#include <unistd.h>

#include "glpool.h"

// so we can define all globals here, but leave them as externs for others
#define __CH_EXTERNS__

#include "common.h"

// ------------------------------------------------------------------

// ------------------------------------------------------------------
//  Func: main( argc, argv )
//  Desc: main function
//
//  Ret:  0
// ------------------------------------------------------------------

int
main( int argc, char *argv[] )
{
    // init GL stuff
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize( 340, 340 );
    
    // configure GL callabcks for win0
    glutCreateWindow( "MESH - GLPool v.01" );
    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
    glutKeyboardFunc( keypress );
    glutSpecialFunc( specialkeys );
    glutMouseFunc( mouseclick );

    // init program (after creating our windows)
    init();
    
    glutIdleFunc( idle );
    
    // get it goin'
    glutMainLoop();
    
    return 0;
}

// ------------------------------------------------------------------
//  Func: init()
//  Desc: init our gl application settings
//
//  Ret:  -
// ------------------------------------------------------------------

void
init ( void )
{
    // GL options
    glEnable( GL_COLOR_MATERIAL );
    glEnable( GL_CULL_FACE );
    glEnable( GL_DEPTH_TEST );

    glClearColor( 0.0, 0.0, 0.0, 1.0 );
    glShadeModel( GL_SMOOTH );

    // adjust our lighting
#ifdef LIGHT
    glEnable( GL_LIGHTING );
    {
        GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
        GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 0.5 };
        GLfloat mat_shininess[] = { 20.0 };
	
        GLfloat gray[] = { 0.7, 0.7, 0.7, 1.0 };
    
	// set position and lighting types
        glLightfv( GL_LIGHT0, GL_POSITION, light_position );
        glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess );
	glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
	
        glLightfv( GL_LIGHT0, GL_DIFFUSE, gray );

        glEnable( GL_LIGHT0 );
    }
#endif

    // try setting our mouse cursor
    glutSetCursor( GLUT_CURSOR_CROSSHAIR );

    // other misc stuff
    init_menus();
}

// ------------------------------------------------------------------
//  Func: idle()
//  Desc: idle gl function loop
//
//  Ret:  -
// ------------------------------------------------------------------

void
idle ( void )
{
    GLubyte *image;
    GLenum fmt;
    int w,h;

    image = LoadRGBImage( "data/intro.rgb", &w, &h, &fmt ); 

    glBitmap( w,h, 1,1, 0,0, image );
    
    sleep(1);
    glutIdleFunc( NULL );
}

// ------------------------------------------------------------------
//  Func: display()
//  Desc: manage a re-draw/display of selected viewport
//
//  Ret:  -
// ------------------------------------------------------------------

void
display ( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glPushMatrix();

    // object
    glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT );
    glColor4f( 1.0, 0.9, 0.6, 1 );
    glutWireSphere( 15.0, 20, 16 );

//    glTranslatef( 0.0, 0.0, -1.0 );

//    glLoadIdentity();
    glputs( 5,5, "this is a test string!" );

    glPopMatrix();

    glutSwapBuffers();
}

// ------------------------------------------------------------------
//  Func: reshape( width, height )
//  Desc: reconfigure viewport when window resizes
//
//  Ret:  -
// ------------------------------------------------------------------

void
reshape ( int iWidth, int iHeight )
{
    GLfloat wh = (GLfloat) iWidth/ (GLfloat) iHeight;
    
    glViewport( 0,0, iWidth, iHeight );

    // configure our viewport
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    //  l,r | b,t | n,f
//    glFrustum( -100.0, 100.0, -100.0, 100.0, 10.0, 100.0 );
    gluPerspective( 90, wh, 1.0, 100.0 );
//    gluOrtho2D( 0, iWidth, iHeight, 0 );

    // configure our model matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glTranslatef( 1.0, 0.0, -40.0 );
    
}

// ------------------------------------------------------------------
//  Func: keypress( key, x,y )
//  Desc: handle normal ascii keypress'
//
//  Ret:  -
// ------------------------------------------------------------------

void
keypress ( unsigned char cKey, int ikX, int ikY )
{
    switch( cKey ){
	case 27:
	case 'q':
	    exit(0);
	    break;

	case 'h':
	    help ^= 1;
	    if ( help ) {
		menuHelp( help );
	    }
	    else {
		glEnable( GL_DEPTH_TEST );
		glutDisplayFunc( display );
		glutReshapeFunc( reshape );
	    }
	    glutPostRedisplay();
	    break;
    }

}

// ------------------------------------------------------------------
//  Func: specialkeys( key, x,y )
//  Desc: handle extended type keypresses
//
//  Ret:  -
// ------------------------------------------------------------------

void
specialkeys ( int cKep, int ikX, int ikY )
{
}

// ------------------------------------------------------------------
//  Func: mouseclick( button, state, x, y )
//  Desc: handle a mous button click
//
//  Ret:  -
// ------------------------------------------------------------------

void
mouseclick ( int b, int s, int imX, int imY )
{
}

// ------------------------------------------------------------------
//  Func: glputs( x,y, buffer )
//  Desc: put a string to the display at x,y
//
//  Ret:  # chars displayed
// ------------------------------------------------------------------

int
glputs( GLfloat x, GLfloat y, char *buff )
{
    char *ptr;
    GLfloat pos[4];

    if ( !buff )
	return 0;
    
    glPushMatrix();
//    glTranslatef( x,y, 0 );
    glGetFloatv( GL_VIEWPORT, pos );
//    cout << "Pos: " << pos[2] <<" "<< pos[3] << endl; 

    glGetFloatv( GL_CURRENT_RASTER_POSITION, pos );
//   cout << "Pos: " << pos[0] <<" "<< pos[1] <<" "  << pos[2] << endl; 
    
    glRasterPos2f( x,y );
    
    for ( ptr=buff; *ptr; ptr++ ) {
	glutBitmapCharacter( GLUT_BITMAP_9_BY_15, *ptr );
    }

    glPopMatrix();
    return (ptr-buff);
}

// ------------------------------------------------------------------
//  Func: quit()
//  Desc: exit application cleanly
//
//  Ret:  -
// ------------------------------------------------------------------

void
quit_game( void )
{
    exit(1);
}
