// File:        glpool.cc
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
// 
// $Revision: 1.7 $
/*
 * $Log: not supported by cvs2svn $
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


// ------------------------------------------------------------------

void init ( void );

// ------------------------------------------------------------------
//  Func: main( argc, argv )
//  Desc: main function
//
//  Ret:  0
// ------------------------------------------------------------------

cWMain	 *wMain;
cTexMaps *texList;
    
int
main( int argc, char *argv[] )
{
    // init GL stuff
    glutInit( &argc, argv );
    
    // configure GL callabcks for win0
    wMain = new cWMain( "MESH - GLPool v.01",
	    600, 512,
	    GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH,
	    WCB_KEYS
	    );
    assert( wMain );

    texList = new cTexMaps;
    assert( texList );
    
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
    	glutIdleFunc( NULL );
    }
    else {
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
    if ( texList )
	delete texList;
    if ( wMain )
	delete wMain;

    exit(1);
}
