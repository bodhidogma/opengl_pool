// File:        cBall.cc
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
// 
// $Revision: 1.16 $
/*
 * $Log: not supported by cvs2svn $
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
#include <math.h>

#define MIN_BALL_MOVE	.5

extern cTexMaps *texList;
extern cAudio *audio;

// ------------------------------------------------------------------
//  Func: cBall( num, wire, tex )
//  Desc: Create a ball, and set some state flags
//
//  Ret:  
// ------------------------------------------------------------------

cBall::cBall( void )
{
	init( 0, 0 );
}

cBall::cBall( int num, int wire, int tex )
{
    init( num, wire, tex );
}

int
cBall::init(int num, int wire, int tex )
{
    move = 0; 
    if ( num )
	flg_Wire = wire;
    else 
	flg_Wire = 0;
    flg_Texture = tex;

    ballnum = num;	// ball number
    enabled = 1;	// ball is available
    SetColor( BALL0 );
    
    rotation[0] = 0;	// initial rotation
    rotation[1] = 0;

    memset( pos, 0, sizeof(GLfloat)*2*3 );
    memset( vel, 0, sizeof(GLfloat)*2*3 );
    memset( accel, 0, sizeof(GLfloat)*2*3 );

	return 0;
}

// ------------------------------------------------------------------
//  Func: ~cBall()
//  Desc: ball destructor
//
//  Ret:  
// ------------------------------------------------------------------

cBall::~cBall()
{
}

// ------------------------------------------------------------------
//  Func: Draw()
//  Desc: Draw the ball in all its glory
//
//  Ret:  
// ------------------------------------------------------------------

int
cBall::Draw( void )
{

//    glPushMatrix();		// save current position info
    
    // move ball into correct position
    glTranslatef( pos[bN][bX], pos[bN][bY], pos[bN][bZ] );
    glRotatef( rotation[0], 1,0,0 );
    glRotatef( rotation[1], 0,1,0 );
    
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

// ------------------------------------------------------------------
//  Func: MoveWall( x,y )
//  Desc: Move ball and check to see if ball hit a wall
//	  x = table width, y = table height
//
//  Ret:  
// ------------------------------------------------------------------

int
cBall::MoveWall( int x, int y )
{
    GLfloat d_pos;	// delta position
    GLfloat mx = 0+BALL_R, my = 0+BALL_R;
    int  in_pocket = 0;
    
    pos[bN][bX] += vel[bN][bX];
    
    // calculate rotation based on Dx traveled
    rotation[0] += (int)((vel[bN][bX]/2*M_PI*BALL_R)*360);
//    rotation[0] += (int)(.2*360);
    rotation[0] %= 360;
    
    if ( pos[bN][bX] > x/2 ) {		// right pockets?
	if ( pos[bN][bX] >= x ) {	// went in (close!)
	   in_pocket = MovePocket( y ); 
	}
    }
    else {				// left pockets?
	if ( pos[bN][bX] <= mx ) {	// went in (close!)
	   in_pocket = MovePocket( y ); 
	}
    }

    if ( in_pocket )
	return in_pocket;
    
    if ( pos[bN][bX] >= x ) {		// right wall
	vel[bN][bX] *= -1;			// reflection
	
	d_pos = pos[bN][bX] - x;		// dx past edge of table
	pos[bN][bX] = x-d_pos;
	audio->PlayFile( BUMPER_AUDIO );
    }
    else if ( pos[bN][bX] <= mx ) {		// left wall
	vel[bN][bX] *= -1;			// reflection
	
	d_pos = mx-pos[bN][bX];		// dx past edge of table
	pos[bN][bX] = mx + d_pos;
	audio->PlayFile( BUMPER_AUDIO );
    }
    
    pos[bN][bY] += vel[bN][bY];
    
    // calculate rotation based on Dx traveled
    rotation[1] += (int)((vel[bN][bY]/2*M_PI*BALL_R)*360);
//    rotation[1] -= (int)(.2*360);
    rotation[1] %= 360;
    
    if ( pos[bN][bY] >= y ) {		// top
	vel[bN][bY] *= -1;			// reflection
	
	d_pos = pos[bN][bY] - y;		// dx past edge of table
	pos[bN][bY] = y-d_pos;
	audio->PlayFile( BUMPER_AUDIO );
    }
    else if ( pos[bN][bY] <= my ) {		// bottom
	vel[bN][bY] *= -1;			// reflection
	
	d_pos = my-pos[bN][bY];		// dx past edge of table
	pos[bN][bY] = mx+d_pos;
	audio->PlayFile( BUMPER_AUDIO );
    }

    return 0;
}

// ------------------------------------------------------------------
//  Func: MovePocket( y )
//  Desc: Look to see if ball went into any three side pockets
//  TODO  fix the problem with not going into enough corner pocket (y)
//
//  Ret:  
// ------------------------------------------------------------------

int
cBall::MovePocket( int y )
{
    int in = 0;
    
    if ( pos[bN][bY] < 4*BALL_R			// corner pockets
         || pos[bN][bY] > y-4*BALL_R ) {
	in = 1;
    }
    else {					// center pocket
	y /= 2;
	if ( pos[bN][bY] < y+4*BALL_R && 
	     pos[bN][bY] > y-4*BALL_R ) {
	    in = 1;
	}
    }
    
    if ( in ) {
	audio->PlayFile( SUNK_AUDIO );
    }
    
    return in;
}

// ------------------------------------------------------------------
//  Func: MoveBall()
//  Desc: move the ball and reduce it's velocity
//
//  Ret:  
// ------------------------------------------------------------------

int
cBall::MoveBall( cBall *balls, int numballs )
{
    int i;
    GLfloat dx, x,y;
    
    vel[bN][bX] -= (K_FRICTION*vel[bN][bX]);
    vel[bN][bY] -= (K_FRICTION*vel[bN][bY]);
    
    for ( i=0; i < numballs; i++ ) {	// look at all balls
	if ( i != ballnum		//   don't check against self
	     && balls[i].Enabled() )	//   ball is actually avalable
       	    {
	    dx = distance( balls[ i ], x,y );
	    
	    if ( dx <= 2*BALL_R ) {	// collision with a ball
		balls[i].HitBall( vel[bN][bX], vel[bN][bY] );
		vel[bN][bX] = 0;
		vel[bN][bY] = 0;
		audio->PlayFile( HIT_AUDIO );
	    }
	}
    }
//    cout << "x: " << vel[bN][bX] << " y: " << vel[bN][bY] << endl;
    
    move = (fabs(vel[bN][bX])+fabs(vel[bN][bY]) > MIN_BALL_MOVE );
    
    return move;
}

// ------------------------------------------------------------------
//  Func: Resize()
//  Desc: Called once: setup the ball display lists
//
//  Ret:  
// ------------------------------------------------------------------

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

// ------------------------------------------------------------------
//  Func: SetFlags( wire, texture )
//  Desc: Set wire/texture flags for the ball
//
//  Ret:  
// ------------------------------------------------------------------

int
cBall::SetFlags( int wire, int texture )
{
//    if ( !ballnum )
	flg_Wire = wire;
    flg_Texture = texture;

    return 0;
}

// ------------------------------------------------------------------
//  Func: SetColor( r,g,b, a )
//  Desc: Set ball color attributes
//
//  Ret:  
// ------------------------------------------------------------------

int
cBall::SetColor( GLfloat r, GLfloat g, GLfloat b, GLfloat a )
{
    color[bR] = r;		// (R)ed
    color[bG] = g;		// (G)reen
    color[bB] = b;		// (B)lue
    color[bA] = a;		// (A)lpha (channel)
    
    return 0;
}

// ------------------------------------------------------------------
//  Func: SetColor( c[3] )
//  Desc: Set ball color attributes
//
//  Ret:  
// ------------------------------------------------------------------

int
cBall::SetColor( GLfloat c[3] )
{
    color[bR] = c[bR];		// (R)ed
    color[bG] = c[bG];		// (G)reen
    color[bB] = c[bB];		// (B)lue
    
    return 0;
}
    
// ------------------------------------------------------------------
//  Func: SetPosition( x,y )
//  Desc: Set ball x,y position
//
//  Ret:  
// ------------------------------------------------------------------

int
cBall::SetPosition( GLfloat x, GLfloat y )
{
    pos[bN][bX] = x;
    pos[bN][bY] = y;
    pos[bN][bZ] = 0;

    return 0;
}

// ------------------------------------------------------------------
//  Func: SetNumber( num )
//  Desc: tell a ball what number it is
//
//  Ret:  
// ------------------------------------------------------------------

int
cBall::SetNumber( int num )
{
    if ( num < 0 ) { 	// turn off ball
	enabled = 0;
	move = 0;
    }
    else {
	enabled = 1;
	ballnum = num;
    }
	
    return ballnum ;
}

// ------------------------------------------------------------------
//  Func: 
//  Desc: 
//
//  Ret:  
// ------------------------------------------------------------------

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

GLfloat
cBall::distance( cBall &to, GLfloat &dx, GLfloat &dy )
{
    GLfloat H;
    
    dx = to.pos[bN][bX] - pos[bN][bX];
    dy = to.pos[bN][bY] - pos[bN][bY];
    
    H = sqrt( dx*dx + dy*dy );
    
    dx /= H;		// unitize the vector
    dy /= H;
    
//    cout << "H(" << to.ballnum << "): " <<  H << endl;
    
    return H;
}

GLfloat
cBall::mag( void )
{
    return sqrt( pos[bN][bX]*pos[bN][bX] + pos[bN][bY]*pos[bN][bY] );
}

int
cBall::HitBall( GLfloat x, GLfloat y )
{
    vel[bN][bX] = x;
    vel[bN][bY] = y;
    
    move = (fabs(x)+fabs(y) > MIN_BALL_MOVE );
    
//    cout <<"Hit("<< ballnum <<","<< move <<") X:"<< x <<" Y:"<< y << endl;
    
    return move;
}

