// File:        cBallList.cc
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
// 
// $Revision: 1.7 $
/*
 * $Log: not supported by cvs2svn $
 * Revision 1.6  1999/11/18 02:02:23  paulmcav
 * added pool table drawing
 *
 * Revision 1.5  1999/11/11 20:38:31  paulmcav
 * working on perspective use
 *
 * Revision 1.4  1999/11/10 20:04:49  paulmcav
 * updated project for use with animation
 *
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
    float rp[3];	// rack position
	
    balls = new cBall[ b_count ](1);	// some balls
    assert( balls );

    xMin = x;
    yMin = y;
    xMax = x + w;
    yMax = y + h;

    hDiv = yMax/8;
    wDiv = xMax/4;
    
//    for ( bc=b_count-1; bc; --bc ) {
    for ( bc=0; bc<b_count; ++bc ) {
	balls[ bc ].SetColor( BallClr[ bc ] );
	
	if ( !bc ) {	// cue ball
	    balls[bc].SetPosition( wDiv*2,hDiv*2);
//    	    cout << "hDiv: " << hDiv*2 << endl;
	}
	else { 		// other balls
	    RackPosition( bc, rp );
	    balls[bc].SetPosition( wDiv*2+rp[0], yMax-(hDiv*2)+rp[1] );
	}

    }
    
    tick = 0;
}

int
cBallList::RackPosition( int ball, float *pos )
{
    int row;
    int col;
    
    switch( ball ){
	case 1: row = 0;
		break;
	case 2:
	case 3: row = 1;
		break;
	case 4: 
	case 8:
	case 6: row = 2;
		break;
	case 7:
	case 5:
	case 9:
	case 10: row = 3;
		 break;
	case 11:
	case 12:
	case 13:
	case 14:
	case 15: row = 4;
		 break;
    };
	    
    switch( ball ){
	case 1:
	case 8:
	case 13: col = 0;
		 break;
	case 2:
	case 5: col = -1;
		break;
	case 3:
	case 9: col = 1;
		break;
	case 4: 
	case 12: col = -2;
		break;
	case 6: 
	case 14: col = 2;
		break;
	case 7: col = -3;
		break;
	case 10: col = 3;
		break;
	case 11: col = -4;
		break;
	case 15: col = 4;
		break;
    };
	    
    pos[2] = 0;
    pos[1] = row*BALL_R*2;
    pos[0] = col*BALL_R*2;
    
    return 0;
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

//    cout << "blD" << endl;
    
    // move to table origin
//    glTranslatef( xMin, yMin, 0.0 );
    glTranslatef( 0,0, BALL_R );
    
    for ( bc=0; bc< b_count; bc++ ) {
	glPushMatrix();
	balls[ bc ].Draw();
	glPopMatrix();
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
    
//    cout << "tick: " << tick << endl;
    
    if ( tick++ > 4 )
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

