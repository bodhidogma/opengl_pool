// File:        glUtil.cc
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
// 
// $Revision: 1.1 $
/*
 * $Log: not supported by cvs2svn $
 */

#include "glUtil.h"
#include "colors.h"

#include <iostream.h>
#include <assert.h>

// ------------------------------------------------------------------
//  Func: 
//  Desc: 
//
//  Ret:  
// ------------------------------------------------------------------

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
//    GLfloat pos[4];

    if ( !buff )
	return 0;
    
    glRasterPos2f( x,y );
    
    for ( ptr=buff; *ptr; ptr++ ) {
	glutBitmapCharacter( GLUT_BITMAP_9_BY_15, *ptr );
    }

    glPopMatrix();
    return (ptr-buff);
}


int
glshadebox( int x, int y, int w, int h, int raised=1 )
{
    glBegin( GL_LINES );
    {
	if ( raised )
	    glColor3f( GRAY44 );
	else
	    glColor3f( WHITE );
	glVertex2i( x, h );		// |
	glVertex2i( x, y );
	glVertex2i( x, y+1 );		// _
	glVertex2i( w, y+1 );

	if ( raised )
	    glColor3f( WHITE );
	else
	    glColor3f( GRAY44 );
	glVertex2i( x+1, h-1 );		// _
	glVertex2i( w, h-1 );
	glVertex2i( w-1, h-1 );		// |
	glVertex2i( w-1, y+1 );
    }
    glEnd();

    return 0;
}


int
glshadebar( int x, int y, int w, int h, int raised=1 )
{
    glBegin( GL_LINES );
    {
	if ( raised )
	    glColor3f( GRAY44 );
	else
	    glColor3f( WHITE );
	if ( h > w ) {
	    glVertex2i( x, h );		// |
	    glVertex2i( x, y );
	}
	else {
	    glVertex2i( x, y );		// _
	    glVertex2i( w, y );
	}

	if ( raised )
	    glColor3f( WHITE );
	else
	    glColor3f( GRAY44 );
	if ( w > h ) {
	    glVertex2i( x, y+1 );	// _
	    glVertex2i( w, y+1 );
	}
	else {
	    glVertex2i( x+1, h );	// |
	    glVertex2i( x+1, y );
	}
    }
    glEnd();

    return 0;
}
