// File:        cBallList.h
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
//              
// 
// $Revision: 1.15 $

/*
 * $Log: cBallList.h,v $
 * Revision 1.15  1999/12/08 08:27:00  paulmcav
 * balls now fall into pockets.  Works pretty good!
 *
 * Revision 1.14  1999/12/08 01:08:16  paulmcav
 * added more stuff!
 *
 * Revision 1.13  1999/12/06 21:19:46  paulmcav
 * updated game to allow collisions between balls
 *
 * Revision 1.12  1999/12/06 09:21:17  paulmcav
 * added windos portability code/utils
 *
 * Revision 1.11  1999/12/06 04:49:24  paulmcav
 * added pooltable model loading / rendering.
 * Cue stick hit now works.  Timing is a bit better
 * Includes timing statistics
 *
 * Revision 1.10  1999/12/03 21:57:34  paulmcav
 * Added que stick action to game
 *
 * Revision 1.9  1999/11/24 19:32:06  paulmcav
 * adde profiling / drawing routines
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
 * 
*/

#ifndef _CBALLLIST_H_
#define _CBALLLIST_H_

#include "cBall.h"
#include "cVstatus.h"


enum bl_balls {
    b_que,
    b_yellow,
    b_blue,
    b_red,
    b_purple,
    b_orange,
    b_green,
    b_magenta,
    b_black,
    b_syellow,
    b_sblue,
    b_sred,
    b_spurple,
    b_sorange,
    b_sgreen,
    b_smagenta,
#if 0 
#endif
    b_count
};

/*
*/

class cBallList
{
private:
    cBall *balls;
    GLfloat xMin, xMax, yMin, yMax;	// table dimensions
    GLfloat hDiv, wDiv;
    int iWire, iTex;
    cVstatus *status;

protected:
public:
    cBallList( GLfloat x, GLfloat y, GLfloat w, GLfloat h );
    ~cBallList();
    
    int Draw();
    int Move();
    
    int MoveToBall( int num );
    int HitBall( int num, GLfloat x, GLfloat y );
    
    int Resize( GLfloat x, GLfloat y, GLfloat w, GLfloat h );
    
    int EnableBall( int num );
    
    int RackPosition( int ball, GLfloat *pos );
    
    int SetFlags( int wire, int tex );
    int Reset( void );
    
    int setstatus( cVstatus *sptr );
    
    
};

#endif

