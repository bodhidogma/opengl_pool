// File:        cWMain.cc
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
// 
// $Revision: 1.15 $
/*
 * $Log: not supported by cvs2svn $
 * Revision 1.14  1999/12/06 04:49:24  paulmcav
 * added pooltable model loading / rendering.
 * Cue stick hit now works.  Timing is a bit better
 * Includes timing statistics
 *
 * Revision 1.13  1999/12/03 21:57:34  paulmcav
 * Added que stick action to game
 *
 * Revision 1.12  1999/11/24 18:58:48  paulmcav
 * more manipulations for ball movement.
 *
 * Revision 1.11  1999/11/20 21:41:30  paulmcav
 * added audio playback support.
 *
 * Revision 1.10  1999/11/20 07:53:57  paulmcav
 * added texmap support, some more menu options, lighting, cleanup, etc.
 *
 * Revision 1.9  1999/11/17 21:05:56  paulmcav
 * added mouse movement support
 *
 * Revision 1.8  1999/11/12 21:05:40  paulmcav
 * more perspective work
 *
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
#ifndef _WIN32
#  include <sys/time.h>
#  include <unistd.h>
#endif

extern GLfloat fFrameRate;

#define TValDiff( f, t ) \
	(t.tv_sec-f.tv_sec) + \
	fabs( (t.tv_usec-f.tv_usec)/1000000.0 )
	
// ------------------------------------------------------------------
//  Func: cWMain( title, w,h, mode )
//  Desc: setup child viewports, and any window setup stuff.
//
//  Ret:  n/a
// ------------------------------------------------------------------

cWMain::cWMain( char *title, int w, int h, unsigned int mode, int cb ) :
	glcWindow( title, w, h, mode, cb ),
	views(0),
	iAnim(0),
	pX(0), pY(0),
	MMove(0),
	StMove(0), StHit(0),
	elapsed(0), frames(0)
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
    if ( views ) {
	delete views[ mw_main ];
	delete views[ mw_status ];
	delete views;
    }
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
    
//    views[ mw_main ]->Display();
    // draw all my views!
    for ( cnt = mw_main; cnt < mw_count; cnt++ )
	views[ cnt ]->Display();
    
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
	    Menu( mM_Quit );
	    break;

	case 'i':
	    Menu( mM_About );
	    break;
	    
	case 'h':
	    Menu( mM_Help );
	    break;
	    
	case 'w':
	    Menu( mM_Wireframe );
	    break;
	    
	case 't':
	    Menu( mM_Texmap );
	    break;
	    
	case ' ':
	    StMove ^= 1;
	    StHit = 0;
    	    ((cVmain*)views[ mw_main ])->StickToggle( StMove );
 	    ((cVmain*)views[ mw_main ])->Intro(0);
    	    ((cVmain*)views[ mw_main ])->Help(0);
	    Display();
	    break;
	    
	case '1':
	    StHit ^= 1;
	    StMove = 1;  
    	    ((cVmain*)views[ mw_main ])->StickToggle( StMove );
 	    ((cVmain*)views[ mw_main ])->Intro(0);
    	    ((cVmain*)views[ mw_main ])->Help(0);
	    Display();
	    break;
	  
	case 'a':
	    Menu( mM_Practice );
	    break;
    }
    
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
	    iAnim ^= 1;
	    break;
	
	case mM_Practice:
	    iAnim ^= 1;
	    break;

	case mM_TwoPlayer:
	    iAnim ^= 1;
	    break;

	case mM_Help:
	    iAnim = 0;
    	    ((cVmain*)views[ mw_main ])->Help();
	    Display();
	    break;
	    
	case mM_About:
	    iAnim = 0;
 	    ((cVmain*)views[ mw_main ])->Intro();
	    Display();
	    break;

	case mM_Wireframe:
    	    ((cVmain*)views[ mw_main ])->Wire();
	    Display();
	    break;

	case mM_Texmap:
    	    ((cVmain*)views[ mw_main ])->Texmap();
	    Display();
	    break;

	case mM_Quit:
	    quit_game();
	    break;
    }
    
    if ( iAnim ) {
//	UseCallBack( WCB_IDLE );
        Animate();
    }
    else {
	UseCallBack( WCB_IDLE, 0 );	// turns off idle
    }

    return 0;
}

int
cWMain::MouseClk( int button, int state, int x, int y )
{
    if ( button == GLUT_LEFT_BUTTON ) {
	if ( state == GLUT_DOWN ) {
	    MMove = 1;
	    pX = x;
	    pY = y;
    	}
	else {				// GLUT_UP 
	    MMove = 0;
	}
    }
    return 0;
}

int
cWMain::MouseMove( int x, int y )
{
    int ret;

    if ( MMove ) {			// mouse is moving in window

	if ( StHit ) {
	    if ( y-pY ) {
	 	ret = ((cVmain*)views[ mw_main ])->StickTr( -(y-pY) );
	      	if ( ret ) {		// ball was hit
		    StHit  = 0;
		    StMove = 0;  
		    MMove  = 0;
		    iAnim  = 1;
		    Animate();
	        }
	    }
	}
	else if (StMove ) {
	    
	    if ( x-pX )
	       ((cVmain*)views[ mw_main ])->StickRot( (x-pX) );
	}
	else {
	    if ( y-pY )
	       ((cVmain*)views[ mw_main ])->Xrot( -(y-pY) );
	    if ( x-pX )
	       ((cVmain*)views[ mw_main ])->Yrot( (x-pX) );
	}
	
	pX = x;
	pY = y;
	
	glutPostRedisplay();
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
    glutAddMenuEntry( "About", mM_About );
    glutAddMenuEntry( "Wireframe", mM_Wireframe );
    glutAddMenuEntry( "TexMap", mM_Texmap );
    glutAddMenuEntry( "Quit", mM_Quit );
    glutAttachMenu( GLUT_RIGHT_BUTTON );
    
    return 0;
}

int
cWMain::Idle( void )
{
//    cout << "idle: " << iAnim << endl;
    
    if ( !iAnim ) {
	UseCallBack( WCB_IDLE, 0 );	// turns off idle
    
#ifndef _WIN32
	gettimeofday( &tEnd, NULL );

	elapsed += TValDiff( tStart, tEnd );
	
	fFrameRate = frames/elapsed;
	
	cout << "F: " << frames << " T: " << elapsed
	     << " fps: " << fFrameRate <<endl;
#endif
    }
    
    return 0;
}

int
cWMain::Animate( void )
{
    int ret;
    long dly;
//    struct timeval s,e;

    iAnim = 1;
    
    dly = (long)( .444 * 1000 );
    
    UseCallBack( WCB_IDLE );
#ifndef _WIN32
    gettimeofday( &tStart, NULL );			    // start timer
#endif
    do {
// gettimeofday( &s, NULL );			    // start timer
	ret = ((cVmain*)views[ mw_main ])->Animate();	// do animation
	Display();
// gettimeofday( &e, NULL );			    // start timer
	frames ++;
	iAnim = 0;

// cout << "+" << TValDiff( s, e );
//	usleep( 500 );
    }
    while ( !ret );

    return 0;
}

int
cWMain::stat_message( char *msg )
{
    assert( msg );
    
    ((cVstatus*)views[ mw_status ])->Message( msg );

    return 0;
}
