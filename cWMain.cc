// File:        cWMain.cc
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
// 
// $Revision: 1.2 $
/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  1999/10/25 06:33:21  paulmcav
 * working project with fancy windowing class for GL.
 * Tex maps sorta working, looks sharp though!
 *
 */

#include "cWMain.h"
#include "colors.h"

#include "glUtil.h"
#include "common.h"

#include "cVmain.h"
#include "cVstatus.h"

#include <iostream.h>


// ------------------------------------------------------------------
//  Func: 
//  Desc: 
//
//  Ret:  
// ------------------------------------------------------------------

cWMain::cWMain( char *title, int w, int h, unsigned int mode ) :
	glcWindow( title, w, h, mode ),
	views(0)
{
    views = new glcViewport *[ mw_count ];
    assert( views );
    
    views[ mw_main ] = new cVmain( 0, 0, w, h-V_STATUS_HEIGHT );
    assert( views[ mw_main ] );
    
    views[ mw_status ] = new cVstatus( 0,
	    h-V_STATUS_HEIGHT, w );
    assert( views[ mw_status ] );
    
    views[ mw_count ] = NULL;
    
    ((cVstatus*)views[ mw_status ])->Message( "Welcome .. " );
    
    glClearColor( BLACK, 1.0 );
}

cWMain::~cWMain()
{
    if ( views )
	delete[] views;
    views = NULL;
}

int
cWMain::Display( void )
{
    int cnt;

    // init window for drawing
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    glEnable( GL_SCISSOR_TEST );
    
    // draw all my views!
    for ( cnt = mw_main; cnt < mw_count; cnt++ ){
	views[ cnt ]->Display();
    }
    
    glDisable( GL_SCISSOR_TEST );

    glutSwapBuffers();
    
    return 0;
}

int
cWMain::Resize( int w, int h )
{
    int cnt, nx, ny, nw, nh;

    nx = -1;
    nw = w;

    for ( cnt = mw_main; cnt < mw_count; cnt++ ){
	nh = h;
	ny = -1;
	
	switch (cnt){
	    case mw_main:
		nh = h-V_STATUS_HEIGHT;
		break;
	    case mw_status:
		ny = h-V_STATUS_HEIGHT;
		break;
	}
		    
	views[ cnt ]->Resize( nx,ny, nw,nh );
    }
    
    return 0;
}

int
cWMain::Keys( unsigned char key, int mx, int my )
{
    return 0;
}


int
cWMain::Intro( void )
{
    return 0;
}
