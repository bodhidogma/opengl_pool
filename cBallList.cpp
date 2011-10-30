// File:        cBallList.cc
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
// 
// $Revision: 1.16 $
/*
 * $Log: cBallList.cc,v $
 * Revision 1.16  1999/12/08 08:27:00  paulmcav
 * balls now fall into pockets.  Works pretty good!
 *
 * Revision 1.15  1999/12/08 01:08:16  paulmcav
 * added more stuff!
 *
 * Revision 1.14  1999/12/06 21:19:46  paulmcav
 * updated game to allow collisions between balls
 *
 * Revision 1.13  1999/12/06 09:21:17  paulmcav
 * added windos portability code/utils
 *
 * Revision 1.12  1999/12/06 04:49:24  paulmcav
 * added pooltable model loading / rendering.
 * Cue stick hit now works.  Timing is a bit better
 * Includes timing statistics
 *
 * Revision 1.11  1999/12/03 21:57:34  paulmcav
 * Added que stick action to game
 *
 * Revision 1.10  1999/11/24 18:58:48  paulmcav
 * more manipulations for ball movement.
 *
 * Revision 1.9  1999/11/22 22:17:08  paulmcav
 * enabled ball bouncing
 *
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
#include "cTexMaps.h"
#include "cAudio.h"

#include "colors.h"

#include <GL/glut.h>
#include <assert.h>
#include <iostream.h>
#include <math.h>

extern cTexMaps *texList;
extern cAudio *audio;

// ------------------------------------------------------------------
//  Func: cBallList( x,y, w,h )
//  Desc: create a list of balls on the table, and set 'em up!
//
//  Ret:  
// ------------------------------------------------------------------

cBallList::cBallList( GLfloat x, GLfloat y, GLfloat w, GLfloat h ) :
    balls(NULL)
    ,xMin(x+BALL_R)
    ,xMax(x + w-BALL_R)
    ,yMin(y+BALL_R)
    ,yMax(y + h-BALL_R)
    ,hDiv(yMax/8)
    ,wDiv(xMax/4)
    ,iWire(DEF_WIRE)
    ,iTex(DEF_TEX)
{
    int bc;

    balls = new cBall[ b_count ];	// some balls
    assert( balls );

    status = NULL;

    Reset();
    
    for ( bc=0; bc< b_count; bc++ ) {
	balls[ bc ].Resize();
    }
}

int
cBallList::Reset( void )
{
    GLfloat BallClr[][3] = {
	{ BALL0 },
	{ BALL1 }, { BALL2 }, { BALL3 }, { BALL4 }, { BALL5 },
	{ BALL6 }, { BALL7 }, { BALL8 }, { BALL9 }, { BALL10 },
	{ BALL11 }, { BALL12 }, { BALL13 }, { BALL14 }, { BALL15 } };
    int bc;
    GLfloat rp[3];	// rack position
	
//    for ( bc=b_count-1; bc; --bc ) {
    for ( bc=0; bc<b_count; ++bc ) {		// loop through all balls

	balls[ bc ].SetNumber( bc );
	balls[ bc ].SetColor( BallClr[ bc ] );
	
	if ( !bc ) {	// cue ball .. no texmap
	    balls[bc].SetPosition( wDiv*2,hDiv*2);
	    balls[bc].SetFlags( 0,iTex );
	}
	else { 		// other balls
	    RackPosition( bc, rp );		// find racking position
	    balls[bc].SetPosition( wDiv*2+rp[0], yMax-(hDiv*2)+rp[1] );
	    balls[bc].SetFlags( iWire,iTex );
	    
	    if ( status ) {
		status->ToggleBall( bc, 0 );
	    }
	}
    }
    if ( status ) {
	status->DrawBallQ();
    }

    return 0;
}

// ------------------------------------------------------------------
//  Func: ~cBallList
//  Desc: destroy all our balls
//
//  Ret:  
// ------------------------------------------------------------------

cBallList::~cBallList()
{
    if ( balls )
	delete[] balls;
}

// ------------------------------------------------------------------
//  Func: Draw()
//  Desc: draw all the balls on the table
//
//  Ret:  
// ------------------------------------------------------------------

int
cBallList::Draw( void )
{
    int bc;

    // move to table origin
    glTranslatef( 0,0, (BALL_R*1.0) );
    
    for ( bc=0; bc< b_count; bc++ ) {
	if ( !balls[bc].Enabled() )		// skip ball if not active
	    continue;

	glPushMatrix();				// origin is at bottom left.
	
//	balls[ bc ].Draw();
	
	// move ball into correct position
	glTranslatef(
		balls[bc].pos[bN][bX],
		balls[bc].pos[bN][bY],
		balls[bc].pos[bN][bZ] );
	glRotatef( balls[bc].rotation[0], 1,0,0 );
	glRotatef( balls[bc].rotation[1], 0,1,0 );
	
	if ( balls[bc].flg_Texture && bc ) {		// use texture map
	    glEnable( GL_TEXTURE_2D );
	    texList->Bind( GL_TEXTURE_2D, (tex_list)(bc) );
	}
	else {
	    glColor4fv( balls[bc].color );		// else use ball color
	}
       
	if ( balls[bc].flg_Wire ){		// wire frame
	    glutWireSphere( BALL_R, 20, 16 );
	}
	else {			// solid
	    glCallList( balls[bc].dlist );
	}
	
	glDisable( GL_TEXTURE_2D );
 
	glPopMatrix();
    }
    
    return 0;
}

// ------------------------------------------------------------------
//  Func: Move()
//  Desc: Move the balls around, and check for collisions
//
//  Ret: 0 if all balls stopped moving 
// ------------------------------------------------------------------

int
cBallList::Move( void )
{
    int bc;
    int anim = 0;
    int sunk = 0;

    for ( bc=0; bc< b_count; bc++ ) {
	if ( balls[ bc ].move ) {		// if a ball is 'move'ing
	    sunk = balls[ bc ].MoveWall( xMax, yMax );	// move ball and bounce
	    if ( !sunk ) {
	    	anim |= balls[ bc ].MoveBall( balls, b_count );
	    }
	    else if ( bc ) {
		balls[ bc ].SetNumber( -1 );
		status->ToggleBall( bc );
	        status->DrawBallQ();
	    }
	}
    }
    
    return !anim;		// look to see if any balls are moving
}

// ------------------------------------------------------------------
//  Func: MoveToBall( num )
//  Desc: Move to ballnum position on the table
//
//  Ret:  
// ------------------------------------------------------------------

int
cBallList::MoveToBall( int num )
{
    glTranslatef(				// ball center
	    balls[num].pos[bN][bX],
	    balls[num].pos[bN][bY],
	    balls[num].pos[bN][bZ] );
    
    return 0;
}

// ------------------------------------------------------------------
//  Func: HitBall( num, x,y )
//  Desc: Impart some velocity to ball 'num' in the x,y direction
//
//  Ret:  
// ------------------------------------------------------------------

int
cBallList::HitBall( int num, GLfloat x, GLfloat y )
{
    balls[num].HitBall( x,y );
    return 0;
}

// ------------------------------------------------------------------
//  Func: Resize( x,y, w,h )
//  Desc: Called on 1st drawing. Setup balls
//
//  Ret:  
// ------------------------------------------------------------------

int
cBallList::Resize( GLfloat x, GLfloat y, GLfloat w, GLfloat h )
{
    int bc;

    for ( bc=0; bc< b_count; bc++ ) {
	balls[ bc ].Resize();
    }
    
    return 0;
}

// ------------------------------------------------------------------
//  Func: EnableBall( num )
//  Desc: 
//
//  Ret:  
// ------------------------------------------------------------------

int
cBallList::EnableBall( int num )
{
    balls[ num ].SetNumber( num );

    return 0;
}

// ------------------------------------------------------------------
//  Func: RackPosition( ball, pos[3] )
//  Desc: Find racking position for ball. Return in pos[?]
//
//  Ret:  
// ------------------------------------------------------------------

int
cBallList::RackPosition( int ball, GLfloat *pos )
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

// ------------------------------------------------------------------
//  Func: SetFlags( wire, tex )
//  Desc: Set wireframe / texture mapped flags for all balls
//
//  Ret:  
// ------------------------------------------------------------------

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


int
cBallList::setstatus( cVstatus *stat )
{
    if ( stat ) {
	status = stat;
    }
    return 0;
}
