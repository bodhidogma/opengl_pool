// File:        cBall.h
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
//              
// 
// $Revision: 1.7 $

/*
 * $Log: not supported by cvs2svn $
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

#include <GL/glut.h>

/*
*/

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
    float pos[2][3];		// x,y,z
    float vel[2][3];
    float accel[2][3];
//    float momentum;
//    float mass;
//    float torque;
//    float friction[2];	// static, kinetic

    int   rotation;
//    float normal[3];

    int   ballnum;	// ball number
    int   dlist;	// display list
    
    int   flg_Wire;		// wireframe
    int   flg_Texture;		// texture mapped
    float color[4];		// color
    
    
protected:
    int then2now( void );

public:
    cBall( int num, int wire, int tex=0 );
    ~cBall();
    
    int Draw(void);
    int MoveWall( int x, int y );
    int MoveBall(void);
    int Resize(void);

    int SetFlags( int wire, int texture );
    int SetColor( float r, float g, float b, float a=1.0 );
    int SetColor( float c[3] );
//    int SetColor( float c[4] );
    
    int SetPosition( float x, float y );
    int SetNumber( int ballnum );
};


#endif

