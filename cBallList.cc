// File:        cBallList.cc
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
// 
// $Revision: 1.9 $
/*
 * $Log: not supported by cvs2svn $
 * Revision 1.8  1999/11/20 07:53:56  paulmcav
 * added texmap support, some more menu options, lighting, cleanup, etc.
 *
 * Revision 1.7  1999/11/19 22:36:57  paulmcav
 * Balls displaying on the table, and more!
 *
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
#include <math.h>

// ------------------------------------------------------------------
//  Func: 
//  Desc: 
//
//  Ret:  
// ------------------------------------------------------------------

cBallList::cBallList( float x, float y, float w, float h ) :
    balls(NULL),
    xMin(x+BALL_R),
    xMax(x + w-BALL_R),
    yMin(y+BALL_R),
    yMax(y + h-BALL_R),
    hDiv(yMax/8),
    wDiv(xMax/4),
    iWire(DEF_WIRE),
    iTex(DEF_TEX),
    tick(0)
{
    GLfloat BallClr[][3] = {
	{ BALL0 },
	{ BALL1 }, { BALL2 }, { BALL3 }, { BALL4 }, { BALL5 },
	{ BALL6 }, { BALL7 }, { BALL8 }, { BALL9 }, { BALL10 },
	{ BALL11 }, { BALL12 }, { BALL13 }, { BALL14 }, { BALL15 } };
    int bc;
    float rp[3];	// rack position
	
    balls = new cBall[ b_count ](0,iWire,iTex);	// some balls
    assert( balls );

//    for ( bc=b_count-1; bc; --bc ) {
    for ( bc=0; bc<b_count; ++bc ) {

	balls[ bc ].SetNumber( bc );
	balls[ bc ].SetColor( BallClr[ bc ] );
	
	if ( !bc ) {	// cue ball .. no texmap
	    balls[bc].SetPosition( wDiv*2,hDiv*2);
	    balls[bc].SetFlags( 0,iTex );
	}
	else { 		// other balls
	    RackPosition( bc, rp );
	    balls[bc].SetPosition( wDiv*2+rp[0], yMax-(hDiv*2)+rp[1] );
	    balls[bc].SetFlags( iWire,iTex );
	}

    }

    for ( bc=0; bc< b_count; bc++ ) {
	balls[ bc ].Resize();
    }
    
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
	balls[ bc ].MoveWall( xMax, yMax );
	balls[ bc ].MoveBall();
    }
    
//    cout << "tick: " << tick << endl;
    
    if ( tick++ > 125 )
	tick = 0;
	
    return !tick;
}
    
int
cBallList::Resize( float x, float y, float w, float h )
{
    int bc;

    for ( bc=0; bc< b_count; bc++ ) {
	balls[ bc ].Resize();
    }
    
    return 0;
}

int
cBallList::EnableBall( int num )
{
    return 0;
}

int
cBallList::RackPosition( int ball, float *pos )
{
    int row;
    int col;
    
    //         1
    //       9   2
    //     3   8  10
    //  11   5  12   6 
    // 7  13   4  14  15
    
    switch( ball ){
	case 1: row = 0;
		break;
	case 2:
	case 9: row = 1;
		break;
	case 3: 
	case 8:
	case 10: row = 2;
		break;
	case 11:
	case 5:
	case 12:
	case 6: row = 3;
		 break;
	case 7:
	case 13:
	case 4:
	case 14:
	case 15: row = 4;
		 break;
    };
	    
    switch( ball ){
	case 1:
	case 8:
	case 4: col = 0;
		 break;
	case 2:
	case 12: col = -1;
		break;
	case 9:
	case 5: col = 1;
		break;
	case 10: 
	case 14: col = -2;
		break;
	case 3: 
	case 13: col = 2;
		break;
	case 6: col = -3;
		break;
	case 11: col = 3;
		break;
	case 15: col = -4;
		break;
	case 7: col = 4;
		break;
    };
	    
    pos[2] = 0;
    pos[1] = row*(BALL_R*.707106)*2;
    pos[0] = col*(BALL_R*.707106)*2;
    
    return 0;
}


int
cBallList::SetFlags( int wire, int tex )
{
    int bc;

    iWire = wire;
    iTex = tex;
    
//    cout << "bl-status: " << wire << ", " << tex << endl;
    
    for ( bc=0; bc< b_count; bc++ ) {
	if ( bc ) 
	    balls[ bc ].SetFlags( wire, tex );
	else 
	    balls[ bc ].SetFlags( 0, tex );
    }
    
    return 0;
}


