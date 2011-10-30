// File:        cBall.h
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
//              
// 
// $Revision: 1.13 $

/*
 * $Log: cBall.h,v $
 * Revision 1.13  1999/12/08 08:27:00  paulmcav
 * balls now fall into pockets.  Works pretty good!
 *
 * Revision 1.12  1999/12/08 01:08:16  paulmcav
 * added more stuff!
 *
 * Revision 1.11  1999/12/06 21:19:46  paulmcav
 * updated game to allow collisions between balls
 *
 * Revision 1.10  1999/12/06 09:21:17  paulmcav
 * added windos portability code/utils
 *
 * Revision 1.9  1999/12/06 04:49:24  paulmcav
 * added pooltable model loading / rendering.
 * Cue stick hit now works.  Timing is a bit better
 * Includes timing statistics
 *
 * Revision 1.8  1999/11/24 18:58:48  paulmcav
 * more manipulations for ball movement.
 *
 * Revision 1.7  1999/11/22 22:17:08  paulmcav
 * enabled ball bouncing
 *
 * Revision 1.6  1999/11/20 07:53:56  paulmcav
 * added texmap support, some more menu options, lighting, cleanup, etc.
 *
 * Revision 1.5  1999/11/19 22:36:57  paulmcav
 * Balls displaying on the table, and more!
 *
 * Revision 1.4  1999/11/11 20:38:31  paulmcav
 * working on perspective use
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
 * 
*/

#ifndef _CBALL_H_
#define _CBALL_H_

#define BALL_R		1.125
#define BALL_NORMAL	1,0,0		// normal vector

#define K_FRICTION	.1
#define S_FRICTION	.2

#include <GL/glut.h>

/*
*/

#define BALL_AXIS_DATA( field, state, x,y,z )	\
	field[state][bX] = x;			\
	field[state][bY] = y;			\
	field[state][bZ] = z

enum ball_state {	// (N)ow (T)hen
    bN,
    bT
};
    
enum ball_axis {	// X,Y,Z
    bX,
    bY,
    bZ
};

enum ball_color {	// R,G,B,A
    bR,
    bG,
    bB,
    bA
};

class cBall
{
private:
protected:
public:
    int   move;
    GLfloat pos[2][3];		// x,y,z
    GLfloat vel[2][3];
    GLfloat accel[2][3];
//    GLfloat momentum;
//    GLfloat mass;
//    GLfloat torque;
//    GLfloat friction[2];	// static, kinetic

    int   rotation[2];
//    GLfloat normal[3];

    int   ballnum;	// ball number (>= 0 ok, <0 = off)
    int	  enabled;
    int   dlist;	// display list
    
    int   flg_Wire;		// wireframe
    int   flg_Texture;		// texture mapped
    GLfloat color[4];		// color
    
    cBall( void );
    cBall( int num, int wire, int tex=0 );
    ~cBall();
    
    int init( int num, int wire, int tex=0 );
    
    int Draw(void);
    int MoveWall( int x, int y );
    int MovePocket( int y );
    int MoveBall( cBall *balls, int numballs );
    int Resize(void);

    int SetFlags( int wire, int texture );
    int SetColor( GLfloat r, GLfloat g, GLfloat b, GLfloat a=1.0 );
    int SetColor( GLfloat c[3] );
//    int SetColor( GLfloat c[4] );
    
    int SetPosition( GLfloat x, GLfloat y );
    int SetNumber( int ballnum );

    int then2now( void );
    
    GLfloat distance( cBall &to, GLfloat &x, GLfloat &y );
    GLfloat mag( void );
    int HitBall( GLfloat x, GLfloat y );
    
    int Enabled(void) { return enabled; }
    
    int CheckPocket( );
    
};


#endif

