// File:        glcViewport.h
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
//              
// 
// $Revision: 1.3 $

/*
 * $Log: glcViewport.h,v $
 * Revision 1.3  1999/11/12 21:05:40  paulmcav
 * more perspective work
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

#ifndef _GLCVIEWPORT_H_
#define _GLCVIEWPORT_H_

/*
 * Simple viewport management class.
 * Typical use is with glcWindow implementation
 *
 * Vars:
 * v<?>		viewport size information
 * 
*/

class glcViewport
{
private:
protected:
    int vW, vH,		// viewport size's
	vX, vY;
	
    float fW, fH;	// float values for width / height

public:
    glcViewport( int x, int y, int w, int h );
    virtual ~glcViewport();

    virtual int Display( void ) { return 0; }
    virtual int Resize( int x, int y, int w, int h ) { return 0; }

    virtual int SetView( void ){ return 0; }

    void dump( void );		// dump some viewport info
};

#endif


