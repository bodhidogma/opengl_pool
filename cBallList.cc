// File:        cBallList.cc
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
// 
// $Revision: 1.4 $
/*
 * $Log: not supported by cvs2svn $
 * Revision 1.3  1999/11/10 08:19:19  paulmcav
 * added updates to ball management classes
 *
 * Revision 1.2  1999/11/10 00:21:04  paulmcav
 * misc updates.  added ball(s) class to manage ball movement/ drawing.
 *
 * Revision 1.1  1999/11/08 20:21:40  paulmcav
 * added new ball management classes.
 *
 */

#include "cBallList.h"

#include "colors.h"

#include <GL/glut.h>
#include <assert.h>
#include <iostream.h>

// ------------------------------------------------------------------
//  Func: 
//  Desc: 
//
//  Ret:  
// ------------------------------------------------------------------

cBallList::cBallList( float x, float y, float w, float h ) :
    balls(0)
{
    GLfloat BallClr[][3] = {
	{ BALL0 },
	{ BALL1 }, { BALL2 }, { BALL3 }, { BALL4 }, { BALL5 },
	{ BALL6 }, { BALL7 }, { BALL8 }, { BALL9 }, { BALL10 },
	{ BALL11 }, { BALL12 }, { BALL13 }, { BALL14 }, { BALL15 } };
    int bc;
	
    balls = new cBall[ b_count ](1);	// some balls
    assert( balls );

    xMin = x;
    yMin = y;
    xMax = x + w;
    yMax = y + h;

    for ( bc=0; bc< b_count; bc++ )
	balls[ bc ].SetColor( BallClr[ bc ] );
    
    tick = 0;
}

cBallList::~cBallList()
{
    if ( balls )
	delete[] balls;
}

int
cBallList::Draw()
{
    int bc;

    // move to table origin
    glTranslatef( xMin, yMin, 0.0 );
    
    for ( bc=0; bc< b_count; bc++ ) {
	balls[ bc ].Draw();
    }
    
    return 0;
}

int
cBallList::Move()
{
    int bc;

    for ( bc=0; bc< b_count; bc++ ) {
	balls[ bc ].Move();
    }
    
    cout << "tick: " << tick << endl;
    
    if ( tick++ > 20 )
	tick = 0;
	
    return !tick;
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

