// File:        cVMain.h
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
//              
// 
// $Revision: 1.15 $

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.14  1999/12/03 21:57:34  paulmcav
 * Added que stick action to game
 *
 * Revision 1.13  1999/12/01 21:06:11  paulmcav
 * *** empty log message ***
 *
 * Revision 1.12  1999/11/24 18:58:48  paulmcav
 * more manipulations for ball movement.
 *
 * Revision 1.11  1999/11/20 21:41:30  paulmcav
 * added audio playback support.
 *
 * Revision 1.10  1999/11/20 07:53:57  paulmcav
 * added texmap support, some more menu options, lighting, cleanup, etc.
 *
 * Revision 1.9  1999/11/18 01:12:19  paulmcav
 * added help menu again, intro win, got correct fovy
 *
 * Revision 1.8  1999/11/17 21:05:56  paulmcav
 * added mouse movement support
 *
 * Revision 1.7  1999/11/11 20:38:31  paulmcav
 * working on perspective use
 *
 * Revision 1.6  1999/11/10 20:04:49  paulmcav
 * updated project for use with animation
 *
 * Revision 1.5  1999/11/10 08:19:19  paulmcav
 * added updates to ball management classes
 *
 * Revision 1.4  1999/11/10 00:21:04  paulmcav
 * misc updates.  added ball(s) class to manage ball movement/ drawing.
 *
 * Revision 1.3  1999/11/02 08:47:04  paulmcav
 * added menu / kb callback support; & help window
 *
 * Revision 1.2  1999/10/29 07:12:22  paulmcav
 * added some more documentation to the class
 *
 * Revision 1.1  1999/10/29 04:31:21  paulmcav
 * added viewport class to manage glviewports in a window.
 * Also enabled texture mapping class!
 *
 * 
*/

#ifndef _CVMAIN_H_
#define _CVMAIN_H_

#include <GL/glut.h>

#include "glcViewport.h"
#include "cVstatus.h"

#include "cTable.h"

/*
 * Main view implementation. Base class is glcViewport
 *
 * Manage and draw main application view
*/

#define VMAIN_HEIGHT 100	// 100
#define VMAIN_DXCNTR 400	// 86

#define VMAIN_MINXD  -18
#define VMAIN_MAXXD   90

class cVmain : public glcViewport {
private:
    int iIntroWin;
    int iHelpWin;
    int Xdeg, Ydeg;
    int StickRotZ, StickTrY;
    float fovy;
    
    cVstatus *Vstat;
    cTable *table;
    
    float tmp;
    int  flg_wire, flg_tex;
    
protected:
    
public:
    cVmain( int x, int y, int w, int h );
    ~cVmain();

    int setstatus( cVstatus *stat );

    int Display( void );
    int Resize( int x, int y, int w, int h );

    int SetView( void );
    
    int DoIntro( void );
    int DoHelp( void );

    int help_message( float x, float y, float w, float h );

    int Help( int flag =-1 );
    int Intro( int flag =-1 );
    
    int Animate( void );
    int Wire( int flag =-1 );
    int Texmap( int flag =-1 );
    
    int Xrot( int deg );
    int Yrot( int deg );
    
    int StickRot( int deg );
    int StickTr( int dx );
    int StickToggle( int val );
};

#endif


