// File:        cWMain.h
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
//              
// 
// $Revision: 1.5 $

/*
 * $Log: not supported by cvs2svn $
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
    int iTmp;

protected:
    
public:
    cWMain( char *title, int w, int h, unsigned int mode, int cb=0 );
    ~cWMain();

    int Display( void );
    int Resize( int w, int h );
    
    int Keys( unsigned char key, int mx, int my );
    int Menu( int opt );

    int Init( void );
    int Idle( void );
};
	


#endif


