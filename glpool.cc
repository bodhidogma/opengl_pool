// File:        glpool.cc
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
// 
// $Revision: 1.15 $
/*
 * $Log: not supported by cvs2svn $
 * Revision 1.14  1999/12/08 01:08:17  paulmcav
 * added more stuff!
 *
 */

#include "glpool.h"

#include <stdlib.h>
#include <iostream.h>
#include <string.h>
#ifndef _WIN32
#  include <unistd.h>
#endif

#include "common.h"

#include "cWMain.h"
#include "cTexMaps.h"
#include "cAudio.h"


// ------------------------------------------------------------------

void init ( void );
void real_exit( void );

// ------------------------------------------------------------------
//  Func: main( argc, argv )
//  Desc: main function
//
//  Ret:  0
// ------------------------------------------------------------------

cWMain	 *wMain;
cTexMaps *texList;
cAudio	 *audio;

GLfloat	fFrameRate = 15.0;
    
int
main( int argc, char *argv[] )
{
    atexit( real_exit );
    
    // init GL stuff
    glutInit( &argc, argv );
    
    // configure GL callabcks for win0
    wMain = new cWMain( "MESH - GLPool v"VERSION,
	    600, 512,
	    GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH,
	    WCB_KEYS | WCB_MOUSECLK | WCB_MOUSEMOVE
	    );
    assert( wMain );

    texList = new cTexMaps;
    assert( texList );
    
    audio = new cAudio();
    assert( audio );
    
    wMain->Init();
    
    glutIdleFunc( init );

    // get it goin'
    glutMainLoop();
    
    return 0;
}

// ------------------------------------------------------------------
//  Func: init()
//  Desc: init our gl application settings
//
//  Ret:  -
// ------------------------------------------------------------------

int count = 0;

void
init ( void )
{
    // we want to draw the window before running init sequence
    if (count) {
    	glutIdleFunc( NULL );	// 2'nd pass. everything else to start
	texList->Init2();
    	wMain->stat_message("Welcome:");
	wMain->Display();
    }
    else {
    	wMain->stat_message("Loading..");
	texList->Init();
    }
    count++;
}

// ------------------------------------------------------------------
//  Func: quit()
//  Desc: exit application cleanly
//
//  Ret:  -
// ------------------------------------------------------------------

void quit_game( void )
{
    exit(1);
}

void real_exit( void )
{
    if ( texList )
	delete texList;
    if ( wMain )
	delete wMain;
    if ( audio )
	delete audio;

}
