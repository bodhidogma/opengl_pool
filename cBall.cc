// File:        cBall.cc
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
// 
// $Revision: 1.5 $
/*
 * $Log: not supported by cvs2svn $
 * Revision 1.4  1999/11/10 00:21:04  paulmcav
 * misc updates.  added ball(s) class to manage ball movement/ drawing.
 *
 * Revision 1.3  1999/11/08 20:21:40  paulmcav
 * added new ball management classes.
 *
 */

#include "cBall.h"
#include "colors.h"

#include <GL/glut.h>

// ------------------------------------------------------------------
//  Func: 
//  Desc: 
//
//  Ret:  
// ------------------------------------------------------------------


cBall::cBall( int wire, int tex )
{
    flg_Wire = wire;
    flg_Texture = tex;

    SetColor( BALL0 );
}

cBall::~cBall()
{
}

int
cBall::Draw()
{
    glColor4fv( color );

//    glPushMatrix();		// save current position info
    
    glTranslatef( (BALL_R*2.5), 0.0, 0.0 );
    
    if ( flg_Wire ){		// wire frame
	glutWireSphere( BALL_R, 20, 16 );
    }
    else if ( flg_Texture ){	// texture mapped
    }
    else {			// solid
	glutSolidSphere( BALL_R, 20, 16 );
    }
    
//    glPopMatrix();
    return 0;
}

int
cBall::Move()
{
    return 0;
}

int
cBall::SetFlags( int wire, int texture )
{
    return 0;
}

int
cBall::SetColor( float r, float g, float b, float a )
{
    color[0] = r;		// (R)ed
    color[1] = g;		// (G)reen
    color[2] = b;		// (B)lue
    color[3] = a;		// (A)lpha (channel)
    
    return 0;
}

int
cBall::SetColor( float c[3] )
{
    color[0] = c[0];		// (R)ed
    color[1] = c[1];		// (G)reen
    color[2] = c[2];		// (B)lue
    
    return 0;
}
    
