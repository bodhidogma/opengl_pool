// File:        glcWindow.cc
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
// 
// $Revision: 1.2 $
/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  1999/10/29 04:31:21  paulmcav
 * added viewport class to manage glviewports in a window.
 * Also enabled texture mapping class!
 *
 * Revision 1.1  1999/10/25 06:33:21  paulmcav
 * working project with fancy windowing class for GL.
 * Tex maps sorta working, looks sharp though!
 *
 */

#include "glcWindow.h"

#include <string.h>
#include <iostream.h>
#include <assert.h>

// number of windows that have been created ( <= MAX_WINDOWS )
int glcWindow::glWinNum = 0;

// static list of windows that have been created.  Used for call back's
glcWindow *glWinList[ MAX_WINDOWS ];

// ------------------------------------------------------------------
//  Func: glcWindow( parent, x,y, w,h, %, callbacks )
//  Desc: create a child window from a given 'parent'.
//	  set the size info to given values, and look for scaling if '%' flag
//	  is set.
//	  'callbacks' contains WCB_ flags for implementing handlers
//
//  Ret:  n/a
// ------------------------------------------------------------------

glcWindow::glcWindow( glcWindow *parent, float x, float y, float w, float h,
	int pct=0, int cb=0) :
	iNumChildren(0),
	iPctg( pct ),
	wsWidth(w),
	wsHeight(h),
	wsXpos(0),
	wsYpos(0),
	wWidth(w),
	wHeight(h),
	wXpos(0),
	wYpos(0)
{
    // parent does exist?
    assert( parent );
    
    iMyParent = parent->iMyNum;
    icWindow = parent->icWindow;
    
/*    wsWidth = wWidth = w;
    wsHeight = wHeight = h;
    wsXpos = wXpos = x;
    wsYpos = wYpos = y;
    iPctg = pct;
*/    
    rescale();
    
    // create a glut window context
    iMyNum = glutCreateSubWindow( iMyParent,
	    (int)wXpos, (int)wYpos, (int)wWidth, (int)wHeight );

    // attach needed callbacks for window
    glutDisplayFunc( cbDisplay );
    glutReshapeFunc( cbResize );
    
    // do we want any extra call backs?
    if ( cb & WCB_KEYS )
	glutKeyboardFunc( cbKeys );
    if ( cb & WCB_SKEYS )
	glutSpecialFunc( cbSKeys );
    if ( cb & WCB_MOUSECLK )
	glutMouseFunc( cbMouseClk );
    if ( cb & WCB_MOUSEENTER )
	glutEntryFunc( cbMouseEnter );
    
    // store self into window list.
    glWinList[ iMyNum ] = this;
	
    glWinNum++;
    
    // associate self with parent
    parent->newchild( iMyNum );
}

// ------------------------------------------------------------------
//  Func: glcWindow( title, w,h, mode, cb )
//  Desc: create a new decorated window contect
//	  title = window title string
//	  w,h = window width / height
//	  cb = WCB_ flags for attaching desired callbacks
//
//  Ret:  n/a
// ------------------------------------------------------------------

glcWindow::glcWindow( char *title, int w, int h, unsigned int mode, int cb=0 ) :
	iNumChildren(0),
	iPctg(0),
	wsWidth(w),
	wsHeight(h),
	wsXpos(0),
	wsYpos(0),
	wWidth(w),
	wHeight(h),
	wXpos(0),
	wYpos(0),
	iMyParent(0)
{
    glutInitDisplayMode( mode );
    glutInitWindowSize( w, h );
    
/*    wsWidth = wWidth = w;
    wsHeight = wHeight = h;
    wsXpos = wXpos = 0;
    wsYpos = wYpos = 0;
    iPctg = 0;
    iMyParent = 0;
    iNumChildren = 0;
*/
    memset( wChildList, 0, sizeof(int)*MAX_WINDOWS );
    
    iMyNum = glutCreateWindow( title );
    
    glutDisplayFunc( cbDisplay );
    glutReshapeFunc( cbResize );
    
    // do we want any extra call backs?
    if ( cb & WCB_KEYS )
	glutKeyboardFunc( cbKeys );
    if ( cb & WCB_SKEYS )
	glutSpecialFunc( cbSKeys );
    if ( cb & WCB_MOUSECLK )
	glutMouseFunc( cbMouseClk );
    if ( cb & WCB_MOUSEENTER )
	glutEntryFunc( cbMouseEnter );
    
    icWindow = iMyNum;

    if ( !glWinNum ){
	memset( glWinList, 0, MAX_WINDOWS*sizeof(glcWindow*) );
    }

    glWinList[ iMyNum ] = this;
    
    glWinNum++;
}

// ------------------------------------------------------------------
//  Func: ~glcWindow() 
//  Desc: generic destructor
//  TODO: check for and destroy child windows
//  
//  Ret:  n/a
// ------------------------------------------------------------------

glcWindow::~glcWindow()
{
    glWinList[ iMyNum ] = NULL;
    glWinNum--;

    glutDestroyWindow( iMyNum );
}

// ------------------------------------------------------------------
//  Func: cbDisplay()
//  Desc: find window instance, and call implemented callback
//
//  Ret:  n/a
// ------------------------------------------------------------------

void 
glcWindow::cbDisplay( void )
{
    glWinList[ glutGetWindow() ]->Display();
}

// ------------------------------------------------------------------
//  Func: cbResize( w,h )
//  Desc: find window instance, and call implemented callback
// 	  iterate through children, and call their resize also
//
//  Ret:  n/a
// ------------------------------------------------------------------

void
glcWindow::cbResize( int w, int h )
{
    glcWindow *win = glWinList[ glutGetWindow() ];

    // set new window size 
    win->wWidth = (float)w;
    win->wHeight = (float)h;
    
    // call virtual function for implementation specifics
    win->Resize( w, h );
    
    // if window has any children
    if ( win->iNumChildren ) {
    	int cnt;
    	glcWindow *child;
    
	// resize any children
	for ( cnt = 0; cnt < win->iNumChildren; cnt++ ){
    	    child = glWinList[ win->wChildList[cnt] ];
	    
	    child->rescale();		// for child scaling factors
	    
    	    glutSetWindow( child->iMyNum );
	    glutReshapeWindow( (int)child->wWidth, (int)child->wHeight );
	    glutPositionWindow( (int)child->wXpos, (int)child->wYpos );
	}
    }
}

// ------------------------------------------------------------------
//  Func: cb<function>( .. )
//  Desc: associated glut callback functions
//
//  Ret:  n/a
// ------------------------------------------------------------------

void 
glcWindow::cbKeys( unsigned char key, int mx, int my )
{
    glWinList[ glutGetWindow() ]->Keys( key, mx, my );
}

// ------------------------------------------------------------------

void 
glcWindow::cbSKeys( int key, int mx, int my )
{
    glWinList[ glutGetWindow() ]->SKeys( key, mx, my );
}

// ------------------------------------------------------------------

void 
glcWindow::cbMouseClk( int b, int s, int x, int y )
{
    glWinList[ glutGetWindow() ]->MouseClk( b, s, x, y );
}

// ------------------------------------------------------------------

void 
glcWindow::cbMouseEnter( int s )
{
    glWinList[ glutGetWindow() ]->MouseEnter( s );
}

// ------------------------------------------------------------------
//  Func: rescale()
//  Desc: resize window appropriately if scaling info is used
//        NOTE: really only called for child windows
//
//  Ret:  0
// ------------------------------------------------------------------

int
glcWindow::rescale( void )
{
    // if % is used, and window has a parent
    if ( iPctg && iMyParent ) {

	// find parent window (for size info)
    	glcWindow *p = glWinList[ iMyParent ];
	
	// scale appropriately
	if ( wsXpos <= 1 )
	    wXpos = wsXpos * p->wXpos;
	    
	if ( wsYpos <= 1 )
	    wYpos = wsYpos * p->wYpos;

	if ( wsWidth <= 1 )
	    wWidth = wsWidth * p->wWidth;
	
	if ( wsHeight <= 1 )
            wHeight = wsHeight * p->wHeight;
    }
    
    return 0;
}

// ------------------------------------------------------------------
//  Func: Visible( vis )
//  Desc: get / set window visibility
//
//  Ret:  0
// ------------------------------------------------------------------

int
glcWindow::Visible( int iVis )
{
    return 0;
}

// ------------------------------------------------------------------
//  Func: newchild( winnum )
//  Desc: associate winnum as a child of this window
//
//  Ret:  # children attached
// ------------------------------------------------------------------

int
glcWindow::newchild( int winnum )
{
    // only attach limited # of child windows
    if ( iNumChildren < MAX_WINDOWS ) {
	wChildList[ iNumChildren++ ] = winnum;
    }
    
    return  iNumChildren;
}
