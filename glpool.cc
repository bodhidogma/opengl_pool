// File:        glpool.cc
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
// 
// $Revision: 1.5 $
/*
 * $Log: not supported by cvs2svn $
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

#include "glWindow.h"
#include "glUtil.h"
#include "cWStatus.h"
#include "cWMain.h"

#include "cTexMaps.h"


// ------------------------------------------------------------------

// ------------------------------------------------------------------
//  Func: main( argc, argv )
//  Desc: main function
//
//  Ret:  0
// ------------------------------------------------------------------

cWMain	*wMain;
cWStatus *wStatus;
cTexMaps *texList;
    
int
main( int argc, char *argv[] )
{
    
    // init GL stuff
    glutInit( &argc, argv );
    
    // configure GL callabcks for win0
    wMain = new cWMain( "MESH - GLPool v.01",
	    600, 512,
	    GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH
	    );
    assert( wMain );

    glutKeyboardFunc( keypress );
    
    wStatus = new cWStatus( wMain );
    assert( wStatus );
    
    texList = new cTexMaps;
    assert( texList );
    
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
    	wStatus->Message( "Loading please wait ... " );
    
//	sleep(2);
    
   	wStatus->Message( "" );
    
    	glutIdleFunc( NULL );
    }
    else {
//	texList->Init();
    }
    count++;
}

// ------------------------------------------------------------------
//  Func: idle()
//  Desc: idle gl function loop
//
//  Ret:  -
// ------------------------------------------------------------------

void
idle ( void )
{
    glutIdleFunc( NULL );
}

// ------------------------------------------------------------------
//  Func: keypress( key, x,y )
//  Desc: handle normal ascii keypress'
//
//  Ret:  -
// ------------------------------------------------------------------

void
keypress ( unsigned char cKey, int ikX, int ikY )
{
    switch( cKey ){
	case 27:
	case 'q':
	    exit(0);
	    break;

	case 'h':
	    break;
    }

}

// ------------------------------------------------------------------
//  Func: specialkeys( key, x,y )
//  Desc: handle extended type keypresses
//
//  Ret:  -
// ------------------------------------------------------------------

void
specialkeys ( int cKep, int ikX, int ikY )
{
}

// ------------------------------------------------------------------
//  Func: mouseclick( button, state, x, y )
//  Desc: handle a mous button click
//
//  Ret:  -
// ------------------------------------------------------------------

void
mouseclick ( int b, int s, int imX, int imY )
{
}

// ------------------------------------------------------------------
//  Func: quit()
//  Desc: exit application cleanly
//
//  Ret:  -
// ------------------------------------------------------------------

void
quit_game( void )
{
    exit(1);
}
