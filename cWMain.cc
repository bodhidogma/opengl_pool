// File:        cWMain.cc
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
// 
// $Revision: 1.8 $
/*
 * $Log: not supported by cvs2svn $
 * Revision 1.7  1999/11/11 20:38:31  paulmcav
 * working on perspective use
 *
 * Revision 1.6  1999/11/10 20:04:49  paulmcav
 * updated project for use with animation
 *
 * Revision 1.5  1999/11/10 00:21:04  paulmcav
 * misc updates.  added ball(s) class to manage ball movement/ drawing.
 *
 * Revision 1.4  1999/11/02 08:47:04  paulmcav
 * added menu / kb callback support; & help window
 *
 * Revision 1.3  1999/10/29 07:12:22  paulmcav
 * added some more documentation to the class
 *
 * Revision 1.2  1999/10/29 04:31:21  paulmcav
 * added viewport class to manage glviewports in a window.
 * Also enabled texture mapping class!
 *
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
//  Func: cWMain( title, w,h, mode )
//  Desc: setup child viewports, and any window setup stuff.
//
//  Ret:  n/a
// ------------------------------------------------------------------

cWMain::cWMain( char *title, int w, int h, unsigned int mode, int cb ) :
	glcWindow( title, w, h, mode, cb ),
	views(0),
	iAnim(0)
{
    views = new glcViewport *[ mw_count ];
    assert( views );
    
    views[ mw_main ] = new cVmain( 0, 0, w, h-V_STATUS_HEIGHT );
    assert( views[ mw_main ] );
    
    views[ mw_status ] = new cVstatus( 0, h-V_STATUS_HEIGHT, w );
    assert( views[ mw_status ] );
    
    views[ mw_count ] = NULL;
    
    ((cVstatus*)views[ mw_status ])->Message( "Welcome .. " );
    
    ((cVmain*)views[ mw_main ])->setstatus( (cVstatus*)views[ mw_status ] );
    
    glClearColor( BLACK, 1.0 );
}

// ------------------------------------------------------------------
//  Func: ~cWMain()
//  Desc: main window destructor.  Delete all child viewports.
//
//  Ret:  n/a
// ------------------------------------------------------------------

cWMain::~cWMain()
{
    if ( views )
	delete[] views;
    views = NULL;
}

// ------------------------------------------------------------------
//  Func: Display()
//  Desc: Display main window child viewports
//
//  Ret:  0
// ------------------------------------------------------------------

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

// ------------------------------------------------------------------
//  Func: Resize( w,h )
//  Desc: Handle resizing of main window.  Adjust child viewports accordingly
//
//  Ret:  0
// ------------------------------------------------------------------

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

// ------------------------------------------------------------------
//  Func: Keys( key, mx, my )
//  Desc: Main window keyboard handler callback
//
//  Ret:  0
// ------------------------------------------------------------------

int
cWMain::Keys( unsigned char key, int mx, int my )
{
    switch( key ){
	case 27:
	case 'q':
	    quit_game();
	    break;

	case 'i':
	    iAnim = 0;
 	    ((cVmain*)views[ mw_main ])->Intro();
	    Display();
	    break;
	    
	case 'h':
	    iAnim = 0;
    	    ((cVmain*)views[ mw_main ])->Help();
	    Display();
	    break;
	    
	case 'w':
    	    ((cVmain*)views[ mw_main ])->Wire();
	    Display();
	    break;
	    
	case ' ':
	    Display();
	    break;
	    
	case 'a':
	    iAnim ^= 1;
	    break;
    }
    
    if ( iAnim )
	UseCallBack( WCB_IDLE );
    else
	UseCallBack( WCB_IDLE, 0 );	// turns off idle
    
    return 0;
}

// ------------------------------------------------------------------
//  Func: Menu( int opt )
//  Desc: 
//
//  Ret:  0
// ------------------------------------------------------------------

int
cWMain::Menu( int opt )
{
    switch( opt ){
	case mM_New:
	break;
	
	case mM_Practice:
	break;

	case mM_TwoPlayer:
	break;

	case mM_Help:
    	    ((cVmain*)views[ mw_main ])->Help();
	    Display();
	    break;

	case mM_Quit:
	    quit_game();
	    break;
    }

    return 0;
}
    
// ------------------------------------------------------------------
//  Func: Init( )
//  Desc:
//
//  Ret:  0
// ------------------------------------------------------------------

int
cWMain::Init( void )
{
    int m;

    m = UseCallBack( WCB_MENU );
    glutAddMenuEntry( "New Game", mM_New );
    glutAddMenuEntry( "Practice", mM_Practice);
    glutAddMenuEntry( "2-Player", mM_TwoPlayer );
    glutAddMenuEntry( "Help", mM_Help );
    glutAddMenuEntry( "Quit", mM_Quit );
    glutAttachMenu( GLUT_RIGHT_BUTTON );
    
    return 0;
}

int
cWMain::Idle( void )
{
    int ret;

    ret = ((cVmain*)views[ mw_main ])->Animate();
    Display();
    
    if ( ret ) {
	UseCallBack( WCB_IDLE, 0 );	// turns off idle
        iAnim = 0;
    }
    
    return 0;
}

