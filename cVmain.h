// File:        cVMain.h
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

#ifndef _CVMAIN_H_
#define _CVMAIN_H_

#include <GL/glut.h>

#include "glcViewport.h"

/*
*/

class cVmain : public glcViewport {
private:
    GLuint texIntro;
    
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


