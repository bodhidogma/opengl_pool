// File:        cMenu.cc
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
// 
// $Revision: 1.2 $
/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  1999/10/13 05:22:43  paulmcav
 * template files for future classes
 *
 */

#include "cMenu.h"
#include "common.h"

#define MAX_MENUS	2

// Menu Handles
static int iMenus[ MAX_MENUS ];

// Enum our menu list
enum menu_list {
    m_Main,
    m_Help
};

// Enumerate our Main Menu options
enum main_menu_options {
    mM_New,
    mM_Practice,
    mM_TwoPlayer,
    mM_Help,
    mM_Quit
};

// ------------------------------------------------------------------
//  Func: init_menus() 
//  Desc: init and attach menus to our handles for later use
//
//  Ret:  -
// ------------------------------------------------------------------

void
init_menus( void )
{
    iMenus[ m_Main ] = glutCreateMenu( menuMain );
    glutAddMenuEntry( "New Game", mM_New );
    glutAddMenuEntry( "Practice", mM_Practice);
    glutAddMenuEntry( "2-Player", mM_TwoPlayer );
    glutAddMenuEntry( "Help", mM_Help );
    glutAddMenuEntry( "Quit", mM_Quit );
    glutAttachMenu( GLUT_RIGHT_BUTTON );
}

// ------------------------------------------------------------------
//  Func: menuMain( option ) 
//  Desc: define and manage main menu item selection
//
//  Ret:  -
// ------------------------------------------------------------------

void
menuMain( int option )
{
    switch( option ){
	case mM_New:
	    break;

	case mM_Practice:
	    break;

	case mM_TwoPlayer:
	    break;

	case mM_Help:
	    help ^= 1;
	    if ( help )
		menuHelp( help );
	    else {
		glEnable( GL_DEPTH_TEST );
		glutDisplayFunc( display );
		glutReshapeFunc( reshape );
	    }
	    break;

	case mM_Quit:
	    quit_game();
	    break;
    }
    
}



