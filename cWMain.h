// File:        cWMain.h
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
//              
// 
// $Revision: 1.12 $

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.11  1999/12/06 09:21:18  paulmcav
 * added windos portability code/utils
 *
 * Revision 1.10  1999/12/06 04:49:24  paulmcav
 * added pooltable model loading / rendering.
 * Cue stick hit now works.  Timing is a bit better
 * Includes timing statistics
 *
 * Revision 1.9  1999/12/03 21:57:34  paulmcav
 * Added que stick action to game
 *
 * Revision 1.8  1999/12/01 21:06:11  paulmcav
 * *** empty log message ***
 *
 * Revision 1.7  1999/11/20 07:53:57  paulmcav
 * added texmap support, some more menu options, lighting, cleanup, etc.
 *
 * Revision 1.6  1999/11/17 21:05:56  paulmcav
 * added mouse movement support
 *
 * Revision 1.5  1999/11/10 20:04:49  paulmcav
 * updated project for use with animation
 *
 * Revision 1.4  1999/11/02 08:47:04  paulmcav
 * added menu / kb callback support; & help window
 *
 * Revision 1.3  1999/10/29 07:12:22  paulmcav
 * added some more documentation to the class
 *
 * Revision 1.2  1999/10/29 04:31:21  paulmcav
 * added viewport class to manage glviewports in a window.
 * Also enabled texture mapping class!
 *
 * Revision 1.1  1999/10/25 06:33:21  paulmcav
 * working project with fancy windowing class for GL.
 * Tex maps sorta working, looks sharp though!
 *
 * 
*/

#ifndef _CWMAIN_H_
#define _CWMAIN_H_

#ifdef _WIN32
#  include <windows.h>
#else
#  include <sys/time.h>
#  include <unistd.h>
#endif

enum mw_views {
    mw_main,
    mw_status,
    mw_count
};

// Enumerate our Main Menu options
enum main_menu_options {
    mM_New,
    mM_Practice,
    mM_TwoPlayer,
    mM_Help,
    mM_About,
    mM_Wireframe,
    mM_Texmap,
    mM_StickMove,
    mM_StickHit,
    mM_Quit
};


#include "glcWindow.h"
#include "glcViewport.h"

/*
 * cWMain: main window manager
 *
 * Derived class from glcWindow for managing main display context.
 * Uses Display, Resize, Keys callbacks.
 * 
 * wm_views: enum'd viewport's in main window
 * 
 * Vars:
 * views	dynamic array of viewport pointers
*/

class cWMain : public glcWindow
{
private:
    glcViewport **views;
    int iAnim;			// idle loop animation working.
    int pX, pY;
    int MMove; 			// mouse move
    int StMove, StHit;
    double elapsed;
    long frames;
    int iTmp;

#ifdef _WIN32
	DWORD  tStart, tEnd;
#else
    struct timeval tStart, tEnd;
#endif
    
protected:
    
public:
    cWMain( char *title, int w, int h, unsigned int mode, int cb=0 );
    ~cWMain();

    int Display( void );
    int Resize( int w, int h );
    
    int Keys( unsigned char key, int mx, int my );
    int Menu( int opt );

    int MouseClk( int b, int s, int x, int y );
    int MouseMove( int x, int y );
    
    int Init( void );
    int Idle( void );

    int Animate( void );

    int stat_message( char *msg );
};
	


#endif


