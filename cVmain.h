// File:        cVMain.h
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
//              
// 
// $Revision: 1.2 $

/*
 * $Log: not supported by cvs2svn $
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

/*
 * Main view implementation. Base class is glcViewport
 *
 * Manage and draw main application view
*/

class cVmain : public glcViewport {
private:
    
protected:
    
public:
    cVmain( int x, int y, int w, int h );
    ~cVmain();

    int Display( void );
    int Resize( int x, int y, int w, int h );

    int SetView( void );
    
    int Intro( void );
};

#endif


