// File:        cVstatus.h
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
//              
// 
// $Revision: 1.3 $

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  1999/10/29 07:12:22  paulmcav
 * added some more documentation to the class
 *
 * Revision 1.1  1999/10/29 04:31:21  paulmcav
 * added viewport class to manage glviewports in a window.
 * Also enabled texture mapping class!
 *
 * Revision 1.1  1999/10/25 06:33:21  paulmcav
 * working project with fancy windowing class for GL.
 * Tex maps sorta working, looks sharp though!
 *
 * 
*/

#ifndef _CVSTATUS_H_
#define _CVSTATUS_H_

#include "glcViewport.h"

#include <GL/glut.h>

#define V_STATUS_HEIGHT	26
#define SC_BALL_W	22

/*
 * cVstatus: status viewport
 *
 * Simple viewport to display application status on the screen.
 *
 * Vars:
 * myLists 	display lists to draw in status window
 * cMessage	a simple text message to display (if !NULL)
 * iBallList[]	list of billiard balls not on the table.  (to show as sunk)
 * iBallCnt	# of listed billiard balls
*/

class cVstatus : public glcViewport
{
private:
    GLuint myLists;
    
protected:
    char *cMessage;
    int  iBallList[15];
	
	 

    int  iBallCnt;
    
public:
    cVstatus( int x, int y, int w );
    ~cVstatus();
    
    int Display( void );
    int Resize( int x, int y, int w, int h );

    int SetView( void );

    int Message( char *msg );

    int DrawBallQ( void );

    int ResetBalls( void );
    int AddBalls( int ballnum );
	
};

#endif


