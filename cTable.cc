// File:        cTable.cc
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
// 
// $Revision: 1.4 $
/*
 * $Log: not supported by cvs2svn $
 * Revision 1.3  1999/11/18 02:02:23  paulmcav
 * added pool table drawing
 *
 * Revision 1.2  1999/11/10 20:04:49  paulmcav
 * updated project for use with animation
 *
 * Revision 1.1  1999/11/10 08:19:19  paulmcav
 * added updates to ball management classes
 *
 */

// table size: 4'x8' = 48"x96".  Playing area = 44"x88" (92%)

#include "cTable.h"
#include "colors.h"

#include <GL/glut.h>
#include <iostream.h>
#include <assert.h>

cTable::cTable( float x, float y, float w, float h )
{
    int cnt;
    float X,Y,W,H;

    lBalls = new cBallList( x,y, w*.92,h*.92 );	// put balls on the table!
    assert( lBalls );
    
    xMin = x;
    xMax = w;
    yMin = y;
    yMax = h;
    
    dlist = glGenLists(1);
    
    // create table display list
    glNewList( dlist, GL_COMPILE );
    {
	glTranslatef( -(xMax/2), 0, 0 ); 
	glTranslatef( 0, -(yMax/2), 0 ); 
	
	glColor3f( GRAY66 );
	glBegin( GL_QUADS );
	{
	    glVertex3f( 0, 0, 0 );
	    glVertex3f( xMax, 0, 0 );
	    glVertex3f( xMax, yMax, 0 );
	    glVertex3f( 0, yMax, 0 );
	}
	glEnd();

	glPushMatrix();
	glTranslatef( xMax*.04, yMax*.04, .1 ); 
	
	glColor3f( GREEN );
	glBegin( GL_QUADS );
	{
	    glVertex3f( 0, 0, 0 );
	    glVertex3f( xMax*.92, 0, 0 );
	    glVertex3f( xMax*.92, yMax*.92, 0 );
	    glVertex3f( 0, yMax*.92, 0 );
	}
	glEnd();
	glPopMatrix();

	X = xMax*.04;
	Y = yMax*.04;
	W = xMax*.92;
	H = yMax*.92;
	glColor3f( GRAY90 );
	
	glPushMatrix();
        glTranslatef( X/2, Y, 0 );
	
	for ( cnt = 1; cnt < 8; cnt++ ){
	    glTranslatef( 0, H/8, 0 );
	    glutSolidSphere( .5, 4, 4 );
	    glTranslatef( X+W, 0, 0 );
	    glutSolidSphere( .5, 4, 4 );
	    glTranslatef( -X-W, 0, 0 );
	}
	glPopMatrix();
	
	glPushMatrix();
        glTranslatef( X, Y/2, 0 );
	
	for ( cnt = 1; cnt < 4; cnt++ ){
	    glTranslatef( W/4, 0, 0 );
	    glutSolidSphere( .5, 4, 4 );
	    glTranslatef( 0,Y+H, 0 );
	    glutSolidSphere( .5, 4, 4 );
	    glTranslatef( 0,-Y-H, 0 );
	}
	glPopMatrix();
	
    }
    glEndList();

}

cTable::~cTable()
{
    if ( lBalls )
	delete lBalls;
}

int
cTable::Draw()
{
    glPushMatrix();
    
    glRotatef( -90, 1, 0, 0 );
    glCallList( dlist );
    
    glTranslatef( xMax*.04, 0, 0 ); 	// l,bottom of playing area
    glTranslatef( 0, yMax*.04, 0 ); 

    lBalls->Draw();
    
    glPopMatrix();

    return 0;
}

int 
cTable::Move()
{
    return (lBalls->Move());
}

int
cTable::Resize( float x, float y, float w, float h )
{
    return 0;
}





// ------------------------------------------------------------------
//  Func: 
//  Desc: 
//
//  Ret:  
// ------------------------------------------------------------------


