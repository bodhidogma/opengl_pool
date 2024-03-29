// File:        glcViewport.cc
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
// 
// $Revision: 1.2 $
/*
 * $Log: glcViewport.cc,v $
 * Revision 1.2  1999/10/29 07:12:22  paulmcav
 * added some more documentation to the class
 *
 * Revision 1.1  1999/10/29 04:31:21  paulmcav
 * added viewport class to manage glviewports in a window.
 * Also enabled texture mapping class!
 *
 */

#include "glcViewport.h"

#include <iostream.h>

// ------------------------------------------------------------------
//  Func: glcViewport( x,y, w,h )
//  Desc: create a new viewport with given size info
//
//  Ret:  n/a
// ------------------------------------------------------------------

glcViewport::glcViewport( int x, int y, int w, int h ) :
	vW(w), vH(h),
	vX(x), vY(y)
{
}

// ------------------------------------------------------------------
//  Func: ~glcViewport()
//  Desc: generic destrictor... every class should have one!
//
//  Ret:  n/a
// ------------------------------------------------------------------

glcViewport::~glcViewport( void )
{
}

// ------------------------------------------------------------------
//  Func: dump()
//  Desc: dump some info about the viewport
//
//  Ret:  n/a
// ------------------------------------------------------------------

#ifndef _USE_OLD_IOSTREAMS
using namespace std;
#endif

void
glcViewport::dump( void )
{
    cout << "vX: " << vX;
    cout << " vY: " << vY;
    cout << " vW: " << vW;
    cout << " vH: " << vH;
    cout << endl;
}
    

