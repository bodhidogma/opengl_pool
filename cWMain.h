// File:        cWMain.h
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
//              
// 
// $Revision: 1.1 $

/*
 * $Log: not supported by cvs2svn $
 * 
*/

#ifndef _CWMAIN_H_
#define _CWMAIN_H_

#include "glWindow.h"

/*
 *
*/

class cWMain : public glWindow
{
private:
    GLuint texIntro;

protected:
    float vX, vY, vW, vH;
    
public:
    cWMain( char *title, int w, int h, unsigned int mode );
    ~cWMain();

    int Display( void );
    int Resize( int w, int h );
    
    int Keys( unsigned char key, int mx, int my );

    int Intro( void );
};
	


#endif


