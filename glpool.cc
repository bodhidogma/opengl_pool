// File:        glpool.cc
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
// 
// $Revision: 1.11 $
/*
 * $Log: not supported by cvs2svn $
 * Revision 1.10  1999/11/22 22:17:08  paulmcav
 * enabled ball bouncing
 *
 * Revision 1.9  1999/11/20 07:53:57  paulmcav
 * added texmap support, some more menu options, lighting, cleanup, etc.
 *
 * Revision 1.8  1999/11/17 21:05:56  paulmcav
 * added mouse movement support
 *
 * Revision 1.7  1999/11/02 08:47:04  paulmcav
 * added menu / kb callback support; & help window
 *
 * Revision 1.6  1999/10/29 04:31:21  paulmcav
 * added viewport class to manage glviewports in a window.
 * Also enabled texture mapping class!
 *
 * Revision 1.5  1999/10/25 06:33:22  paulmcav
 * working project with fancy windowing class for GL.
 * Tex maps sorta working, looks sharp though!
 *
 * Revision 1.4  1999/10/19 21:14:27  soudi
 * *** empty log message ***
 *
 * Revision 1.3  1999/10/19 08:01:10  paulmcav
 * added multiple viewports, blending and texture maps
 *
 * Revision 1.2  1999/10/13 16:13:11  paulmcav
 * state of project for turn in (proj2a)
 *
 * Revision 1.1  1999/10/13 05:22:43  paulmcav
 * template files for future classes
 *
 */

#include "glpool.h"

#include <stdlib.h>
#include <iostream.h>
#include <string.h>
#include <unistd.h>

#include "common.h"

#include "cWMain.h"
#include "cTexMaps.h"
#include "cAudio.h"


// ------------------------------------------------------------------

void init ( void );
void real_exit( int , void * );

// ------------------------------------------------------------------
//  Func: main( argc, argv )
//  Desc: main function
//
//  Ret:  0
// ------------------------------------------------------------------

cWMain	 *wMain;
cTexMaps *texList;
cAudio	 *audio;
    
int
main( int argc, char *argv[] )
{
    on_exit( real_exit, NULL );
    
    // init GL stuff
    glutInit( &argc, argv );
    
    // configure GL callabcks for win0
    wMain = new cWMain( "MESH - GLPool v.01",
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
    	wMain->stat_message("Ready:");
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

void real_exit( int i, void *ptr )
{
    if ( texList )
	delete texList;
    if ( wMain )
	delete wMain;
    if ( audio )
	delete audio;

}
