// File:        cHelp.cc
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


#include <iostream.h>

#include "cHelp.h"
#include "common.h"


// ------------------------------------------------------------------
//  Func: menuHelp( mode )
//  Desc: display a help menu with options
//
//  Ret:  -
// ------------------------------------------------------------------

void
menuHelp( int mode )
{
    if ( mode ) {
	glClearColor( 0.0, 0.0, 0.0, 1.0 );
	glShadeModel( GL_SMOOTH );
	
	glutDisplayFunc( dispHelp );
	glutReshapeFunc( reszHelp );
    }
}

// ------------------------------------------------------------------
//  Func: dispHelp()
//  Desc: manage help display
//
//  Ret:  -
// ------------------------------------------------------------------

void
dispHelp( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    
    glColor4f( 1.0, 0.2, 0.8, 1 );
    glutSolidSphere( 10, 20, 16 );
    
    glColor4f( 1.0, 1.0, 1.0, 1 );
    glputs( 10,10, "Some kind of a help menu!" );
    
    glutSwapBuffers();
}

// ------------------------------------------------------------------
//  Func: reszHelp( w,h )
//  Desc: manage the resizing of the help window
//
//  Ret:  -
// ------------------------------------------------------------------

void
reszHelp( int w, int h )
{
    glViewport( 0,0, w,h );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    gluOrtho2D( 0, w, h, 0 );
    
    glMatrixMode( GL_MODELVIEW );
}

// ------------------------------------------------------------------
//  Func: keysHelp( kep, x,y )
//  Desc: manage kep presses while in help window
//
//  Ret:  -
// ------------------------------------------------------------------

void
keysHelp( unsigned char cKey, int ikX, int ikY )
{
}

