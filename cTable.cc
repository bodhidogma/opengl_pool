// File:        cTable.cc
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
// 
// $Revision: 1.3 $
/*
 * $Log: not supported by cvs2svn $
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
#include <assert.h>

cTable::cTable( float x, float y, float w, float h )
{
    lBalls = new cBallList( x,y, w*.92,h*.92 );		// put balls on the table!
    assert( lBalls );
    
    xMin = x;
    xMax = w;
    yMin = y;
    yMax = h;
}

cTable::~cTable()
{
    if ( lBalls )
	delete lBalls;
}

int
cTable::Draw()
{
    glRotatef( -90, 1, 0, 0 );

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
    
    glTranslatef( xMax*.04, 0, 0 ); 
    glTranslatef( 0, yMax*.04, 0 ); 
    
    lBalls->Draw();
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


