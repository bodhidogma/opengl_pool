// File:        glWindow.cc
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
// 
// $Revision: 1.1 $
/*
 * $Log: not supported by cvs2svn $
 */

#include "glWindow.h"

#include <string.h>
#include <iostream.h>
#include <assert.h>

int glWindow::glWinNum = 0;

glWindow *glWinList[ MAX_WINDOWS ];

// ------------------------------------------------------------------
//  Func: 
//  Desc: 
//
//  Ret:  
// ------------------------------------------------------------------

// create a child window from a given parent

glWindow::glWindow( glWindow *parent, float x, float y, float w, float h,
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
    assert( parent );
    
    iMyParent = parent->iMyNum;
    iWindow = parent->iWindow;
    
/*    wsWidth = wWidth = w;
    wsHeight = wHeight = h;
    wsXpos = wXpos = x;
    wsYpos = wYpos = y;
    iPctg = pct;
*/    
    rescale();
    
    iMyNum = glutCreateSubWindow( iMyParent,
	    (int)wXpos, (int)wYpos, (int)wWidth, (int)wHeight );

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
    
    glWinList[ iMyNum ] = this;
	
    glWinNum++;
    
    parent->newchild( iMyNum );
}

// create a new top level window with a title bar

glWindow::glWindow( char *title, int w, int h, unsigned int mode, int cb=0 ) :
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
    
    iWindow = iMyNum;

    if ( !glWinNum ){
	memset( glWinList, 0, MAX_WINDOWS*sizeof(glWindow*) );
    }

    glWinList[ iMyNum ] = this;
    
    glWinNum++;
}

glWindow::~glWindow()
{
    glWinList[ iMyNum ] = NULL;
    glWinNum--;

    glutDestroyWindow( iMyNum );
}

void 
glWindow::cbDisplay( void )
{
    glWinList[ glutGetWindow() ]->Display();
}

void
glWindow::cbResize( int w, int h )
{
    glWindow *win = glWinList[ glutGetWindow() ];

//    cout << "cbResize: " << glutGetWindow() << endl;
    
    // set new window size 
    win->wWidth = (float)w;
    win->wHeight = (float)h;
    
    // call virtual function for implementation specifics
    win->Resize( w, h );
    
    // if window has any children
    if ( win->iNumChildren ) {
    	int cnt;
    	glWindow *child;
    
	// resize any children
	for ( cnt = 0; cnt < win->iNumChildren; cnt++ ){
    	    child = glWinList[ win->wChildList[cnt] ];
	    
	    child->rescale();
	    
    	    glutSetWindow( child->iMyNum );
	    glutReshapeWindow( (int)child->wWidth, (int)child->wHeight );
	    glutPositionWindow( (int)child->wXpos, (int)child->wYpos );
	}
    }
}

void 
glWindow::cbKeys( unsigned char key, int mx, int my )
{
    glWinList[ glutGetWindow() ]->Keys( key, mx, my );
}

void 
glWindow::cbSKeys( int key, int mx, int my )
{
    glWinList[ glutGetWindow() ]->SKeys( key, mx, my );
}

void 
glWindow::cbMouseClk( int b, int s, int x, int y )
{
    glWinList[ glutGetWindow() ]->MouseClk( b, s, x, y );
}

void 
glWindow::cbMouseEnter( int s )
{
    glWinList[ glutGetWindow() ]->MouseEnter( s );
}

// should be called as an individual window (ie: it knows about itself)

int
glWindow::rescale( void )
{
//    cout << "rescale: " << iMyNum << " pct: " << iPctg << endl;

    if ( iPctg && iMyParent ) {		// window sizes are some pcg of parent
    	glWindow *p = glWinList[ iMyParent ];
	
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

int
glWindow::Visible( int iVis )
{
    return 0;
}


int
glWindow::newchild( int winnum )
{
    if ( iNumChildren < MAX_WINDOWS ) {
	wChildList[ iNumChildren++ ] = winnum;
    }
    
    return  iNumChildren;
}
