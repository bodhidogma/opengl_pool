// File:        glcViewport.cc
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
// 
// $Revision: 1.1 $
/*
 * $Log: not supported by cvs2svn $
 */

#include "glcViewport.h"

#include <iostream.h>

// ------------------------------------------------------------------
//  Func: 
//  Desc: 
//
//  Ret:  
// ------------------------------------------------------------------

glcViewport::glcViewport( int x, int y, int w, int h ) :
	vW(w), vH(h),
	vX(x), vY(y)
{
}

glcViewport::~glcViewport( void )
{
}

void
glcViewport::dump( void )
{
    cout << "vX: " << vX;
    cout << " vY: " << vY;
    cout << " vW: " << vW;
    cout << " vH: " << vH;
    cout << endl;
}
    

