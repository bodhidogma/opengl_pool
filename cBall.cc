// File:        cBall.cc
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
// 
// $Revision: 1.12 $
/*
 * $Log: not supported by cvs2svn $
 * Revision 1.11  1999/11/24 19:32:06  paulmcav
 * adde profiling / drawing routines
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
#include "cAudio.h"

#include <GL/glut.h>
#include <iostream.h>
#include <assert.h>
#include <string.h>

#define BUMPER_AUDIO	"data/bumper.au"

// ------------------------------------------------------------------
//  Func: 
//  Desc: 
//
//  Ret:  
// ------------------------------------------------------------------

extern cTexMaps *texList;
extern cAudio *audio;

cBall::cBall( int num, int wire, int tex )
{
    move = 0; 
    if ( num )
	flg_Wire = wire;
    else 
	flg_Wire = 0;
    flg_Texture = tex;

    ballnum = num;	// ball number
    SetColor( BALL0 );
    
    rotation = 0;

    memset( pos, 0, sizeof(float)*2*3 );
    memset( vel, 0, sizeof(float)*2*3 );
    memset( accel, 0, sizeof(float)*2*3 );
    
}

cBall::~cBall()
{
}

int
cBall::Draw()
{

//    glPushMatrix();		// save current position info
    
    // move ball into correct position
    glTranslatef( pos[bN][bX], pos[bN][bY], pos[bN][bZ] );
    glRotatef( rotation, BALL_NORMAL );
    
    if ( flg_Texture && ballnum ) {		// use texture map
	glEnable( GL_TEXTURE_2D );
	texList->Bind( GL_TEXTURE_2D, (tex_list)(ballnum) );
    }
    else {
        glColor4fv( color );			// else use ball color
    }
   
    if ( flg_Wire ){		// wire frame
	glutWireSphere( BALL_R, 20, 16 );
    }
    else {			// solid
	glCallList( dlist );
    }
    
    glDisable( GL_TEXTURE_2D );
    
    
//    then2now();		// copy all then values to now values
//    glPopMatrix();
    return 0;
}

int
cBall::MoveWall( int x, int y )
{
    float d_pos;	// delta position
    float mx = 0+BALL_R, my = 0+BALL_R;
    int   bump = 0;
    
    if ( ballnum ) { 
	rotation += 20;
	rotation %= 360;
    }
    else {
	pos[bN][bX] += vel[bN][bX];
	if ( pos[bN][bX] >= x ) {
	    vel[bN][bX] *= -1;			// reflection
	    
	    d_pos = pos[bN][bX] - x;		// dx past edge of table
	    pos[bN][bX] = x-d_pos;
	    bump = 1;
audio->PlayFile( "data/bumper.au" );
	}
	else if ( pos[bN][bX] <= mx ) {
	    vel[bN][bX] *= -1;			// reflection
	    
	    d_pos = mx-pos[bN][bX];		// dx past edge of table
	    pos[bN][bX] = mx + d_pos;
	    bump = 1;
audio->PlayFile( "data/bumper.au" );
	}
	
	pos[bN][bY] += vel[bN][bY];
	if ( pos[bN][bY] >= y ) {
	    vel[bN][bY] *= -1;			// reflection
	    
	    d_pos = pos[bN][bY] - y;		// dx past edge of table
	    pos[bN][bY] = y-d_pos;
	    bump = 1;
audio->PlayFile( "data/bumper.au" );
	}
	else if ( pos[bN][bY] <= my ) {
	    vel[bN][bY] *= -1;			// reflection
	    
	    d_pos = my-pos[bN][bY];		// dx past edge of table
	    pos[bN][bY] = mx+d_pos;
	    bump = 1;
audio->PlayFile( "data/bumper.au" );
	}
	    
    }

    if ( bump ) {
    }
    return 0;
}

int
cBall::MoveBall( void )
{
    vel[bN][bX] -= (K_FRICTION*vel[bN][bX]);
    vel[bN][bY] -= (K_FRICTION*vel[bN][bY]);
    
//    cout << "x: " << vel[bN][bX] << " y: " << vel[bN][bY] << endl;
    
    return (fabs(vel[bN][bX])+fabs(vel[bN][bY]) > .5);
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
    color[bR] = r;		// (R)ed
    color[bG] = g;		// (G)reen
    color[bB] = b;		// (B)lue
    color[bA] = a;		// (A)lpha (channel)
    
    return 0;
}

int
cBall::SetColor( float c[3] )
{
    color[bR] = c[bR];		// (R)ed
    color[bG] = c[bG];		// (G)reen
    color[bB] = c[bB];		// (B)lue
    
    return 0;
}
    

int
cBall::SetPosition( float x, float y )
{
    pos[bN][bX] = x;
    pos[bN][bY] = y;
    pos[bN][bZ] = 0;

/*    pos[bT][bX] = x;
    pos[bT][bY] = y;
    pos[bT][bZ] = 0;
*/
    return 0;
}

int
cBall::SetNumber( int num )
{
/*    if ( !num ){
	vel[bN][bX] = 1;	// cue ball x velocity now
	vel[bN][bY] = 2;	// cue ball y velocity now
    }
*/
    return (ballnum = num);
}

int
cBall::then2now( void )
{
    int c;
    
    for( c=0; c<3; c++ ){		// now values = then values
	pos[bN][c] = pos[bT][c];
	vel[bN][c] = pos[bT][c];
	accel[bN][c] = pos[bT][c];
    }
    
    return 0;
}
