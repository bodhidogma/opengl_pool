// File:        cBallList.cc
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
// 
// $Revision: 1.2 $
/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  1999/11/08 20:21:40  paulmcav
 * added new ball management classes.
 *
 */

#include "cBallList.h"

#include "colors.h"

#include "GL/glut.h"
#include <assert.h>

// ------------------------------------------------------------------
//  Func: 
//  Desc: 
//
//  Ret:  
// ------------------------------------------------------------------

cBallList::cBallList( float x, float y, float w, float h ) :
    balls(0)
{
    balls = new cBall[16];
    assert( balls );

    xMin = x;
    yMin = y;
    xMax = x + w;
    yMax = y + h;
}

cBallList::~cBallList()
{
    if ( balls )
	delete balls;
}

int
cBallList::Draw()
{
    glTranslatef( xMin, yMin, 0.0 );
    glColor3f( YELLOW );
    glutWireSphere( 40, 20, 16 );
    return 0;
}

int
cBallList::Move()
{
    return 0;
}
    
int
cBallList::Resize( float x, float y, float w, float h )
{
    return 0;
}

int
cBallList::EnableBall( int num )
{
    return 0;
}

