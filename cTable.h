// File:        cTable.h
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
//              
// 
// $Revision: 1.7 $

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.6  1999/12/06 04:49:24  paulmcav
 * added pooltable model loading / rendering.
 * Cue stick hit now works.  Timing is a bit better
 * Includes timing statistics
 *
 * Revision 1.5  1999/12/03 21:57:34  paulmcav
 * Added que stick action to game
 *
 * Revision 1.4  1999/12/01 21:06:11  paulmcav
 * *** empty log message ***
 *
 * Revision 1.3  1999/11/20 07:53:56  paulmcav
 * added texmap support, some more menu options, lighting, cleanup, etc.
 *
 * Revision 1.2  1999/11/19 22:36:57  paulmcav
 * Balls displaying on the table, and more!
 *
 * Revision 1.1  1999/11/10 08:19:19  paulmcav
 * added updates to ball management classes
 *
 * 
*/

#ifndef _CTABLE_H_
#define _CTABLE_H_

#include "cBallList.h"

/*
*/

enum tl_tables {
    tl_solid,
    tl_wire,
    tl_stick,
    tl_count
};

class cTable
{
private:
    cBallList *lBalls;				// table balls
    GLfloat xMin, xMax, yMin, yMax;
    int   iWire, iTex;
    GLfloat StickRotZ, StickTrY, StickDY;
    int   iStick;				// draw stick
    int   dlist;
    GLuint  plist;
    GLfloat pHeight;

protected:
    int  make_table( int wire, int lnum );
    int  make_stick( int lnum );

public:
    cTable( GLfloat x, GLfloat y, GLfloat w, GLfloat h );
    ~cTable();

    int Draw( void );
    int Move( void );

    int Resize( GLfloat x, GLfloat y, GLfloat w, GLfloat h );
    int SetFlags( int wire, int tex );
    
    int StickRot( int deg );
    int StickTr( int dx );
    int StickToggle( int val );
	
};

#endif


