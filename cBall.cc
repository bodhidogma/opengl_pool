// File:        cBall.cc
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
// 
// $Revision: 1.8 $
/*
 * $Log: not supported by cvs2svn $
 * Revision 1.7  1999/11/19 22:36:57  paulmcav
 * Balls displaying on the table, and more!
 *
 * Revision 1.6  1999/11/11 20:38:31  paulmcav
 * working on perspective use
 *
 * Revision 1.5  1999/11/10 08:19:19  paulmcav
 * added updates to ball management classes
 *
 * Revision 1.4  1999/11/10 00:21:04  paulmcav
 * misc updates.  added ball(s) class to manage ball movement/ drawing.
 *
 * Revision 1.3  1999/11/08 20:21:40  paulmcav
 * added new ball management classes.
 *
 */

#include "cBall.h"
#include "colors.h"

#include "cTexMaps.h"

#include <GL/glut.h>
#include <iostream.h>
#include <assert.h>

// ------------------------------------------------------------------
//  Func: 
//  Desc: 
//
//  Ret:  
// ------------------------------------------------------------------

extern cTexMaps *texList;

cBall::cBall( int num, int wire, int tex )
{
    if ( num )
	flg_Wire = wire;
    else 
	flg_Wire = 0;
    flg_Texture = tex;

    ballnum = num;	// ball number
    SetColor( BALL0 );
    
    rotation = 0;
    normal[0] = 0.0;	// normal is Y vector
    normal[1] = 1.0;
    normal[2] = 0.0;

}

cBall::~cBall()
{
}

int
cBall::Draw()
{
    glColor4fv( color );

//    glPushMatrix();		// save current position info
    
    glTranslatef( pos[0], pos[1], pos[3] );
    glRotatef( rotation, normal[0], normal[1], normal[2] );
    
    if ( flg_Texture && ballnum ) {
	glEnable( GL_TEXTURE_2D );
	texList->Bind( GL_TEXTURE_2D, (tex_list)(ballnum) );
    }
    
    if ( flg_Wire ){		// wire frame
	glutWireSphere( BALL_R, 20, 16 );
    }
    else {			// solid
	glCallList( dlist );
    }
    
    glDisable( GL_TEXTURE_2D );
    
//    glPopMatrix();
    return 0;
}

int
cBall::Move()
{
    rotation += 5;
    rotation %= 360;

    return 0;
}

int
cBall::Resize( void )
{
    GLUquadricObj *q = gluNewQuadric();
    assert( q );
    
    dlist = glGenLists(1);
    glNewList( dlist, GL_COMPILE );
    {
	gluQuadricNormals( q, GL_SMOOTH );
	gluQuadricTexture( q, GL_TRUE );
	gluSphere( q, BALL_R, 20,16 );
    }
    glEndList();

    gluDeleteQuadric( q );

    return 0;
}

int
cBall::SetFlags( int wire, int texture )
{
//    if ( !ballnum )
	flg_Wire = wire;
    flg_Texture = texture;

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
    

int
cBall::SetPosition( float x, float y )
{
    pos[0] = x;
    pos[1] = y;
    pos[2] = 0;

    return 0;
}

int
cBall::SetNumber( int num )
{
    return (ballnum = num);
}
