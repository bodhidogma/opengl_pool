// File:        glcViewport.h
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

#ifndef _GLCVIEWPORT_H_
#define _GLCVIEWPORT_H_

/*
*/

class glcViewport
{
private:
protected:
    int vW, vH,
	vX, vY;

public:
    glcViewport( int x, int y, int w, int h );
    virtual ~glcViewport();

    virtual int Display( void ) { return 0; }
    virtual int Resize( int x, int y, int w, int h ) { return 0; }

    virtual int SetView( void ){ return 0; }

    void dump( void );
};

#endif


