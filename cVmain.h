// File:        cVMain.h
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
 * 
*/

#ifndef _CVMAIN_H_
#define _CVMAIN_H_

#include <GL/glut.h>

#include "glcViewport.h"
#include "cVstatus.h"

/*
 * Main view implementation. Base class is glcViewport
 *
 * Manage and draw main application view
*/

class cVmain : public glcViewport {
private:
    int iIntroWin;
    int iHelpWin;
    
    cVstatus *Vstat;
    
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
    
    int Help( void ){ return iHelpWin ^= 1; }
    int Intro( void ){ return iIntroWin ^= 1; }
};

#endif


