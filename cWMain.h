// File:        cWMain.h
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
//              
// 
// $Revision: 1.2 $

/*
 * $Log: not supported by cvs2svn $
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

#include "glcWindow.h"
#include "glcViewport.h"

/*
 *
*/

class cWMain : public glcWindow
{
private:
    glcViewport **views;

protected:
    
public:
    cWMain( char *title, int w, int h, unsigned int mode );
    ~cWMain();

    int Display( void );
    int Resize( int w, int h );
    
    int Keys( unsigned char key, int mx, int my );

    int Intro( void );
};
	


#endif


