// File:        glcWindow.h
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
//              
// 
// $Revision: 1.5 $

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.4  1999/11/17 21:05:56  paulmcav
 * added mouse movement support
 *
 * Revision 1.3  1999/11/02 08:47:04  paulmcav
 * added menu / kb callback support; & help window
 *
 * Revision 1.2  1999/10/29 06:50:49  paulmcav
 * added class documentation
 *
 * Revision 1.1  1999/10/29 04:31:21  paulmcav
 * added viewport class to manage glviewports in a window.
 * Also enabled texture mapping class!
 *
 * Revision 1.1  1999/10/25 06:33:21  paulmcav
 * working project with fancy windowing class for GL.
 * Tex maps sorta working, looks sharp though!
 *
 * 
*/

#ifndef _GLCWINDOW_H_
#define _GLCWINDOW_H_

// maximum number of staticly available window instances. (Plenty!)
#define MAX_WINDOWS 32

// call back usage flags
#define WCB_KEYS	0x01
#define WCB_SKEYS	0x02
#define WCB_MOUSECLK	0x04
#define WCB_MOUSEENTER	0x08
#define WCB_MOUSEMOVE	0x10
#define WCB_MENU	0x20
#define WCB_IDLE	0x40
#define WCB_TIMER	0x80

#include <GL/glut.h>

/*
 * glcWindow: generic base class for managing a GL window context.
 * 
 * Requires the implementation of a Display() and Resize() function for the
 * window.  Optional call back methods which can be used are given by the WCB_
 * flags as defined at the top of this file.
 *
 * Vars:
 * glWinNum		number of windows that have been created
 * wChildList		list of child windows this window is parent of.
 * iNumChildren		number of children this window has.
 * iPctg		use the scaling factors when re-sizing window
 * ws<sizes>		scaling sizes (0 >= val) is a % of parent window
 * w<sizes>		actual window sizes
 * icWindow		decorated (parent) window number (maximum size info)
 * iMyNum		instance window number
 * iMyParent		instance parent window number
*/

class glcWindow
{
private:
static int glWinNum;				// number of windows created
    
    int wChildList[ MAX_WINDOWS ];		// list of child wins
    int iNumChildren;
    int iPctg;					// sizes are a pctg of parent
    
    float wsWidth,				// window scaling size info
    	  wsHeight,
          wsXpos,
	  wsYpos;

    int rescale( void );
    int newchild( int num );
    
protected:
    float wWidth,				// actual window sizes
    	  wHeight,
          wXpos,
	  wYpos;

    int icWindow;
    int iMyNum;					// my instance's window #
    int iMyParent;				// my instance's parent #
    
public:
    glcWindow( glcWindow *, float x, float y, float w, float h, int pct=0,
	    int cb=0 );
    glcWindow( char *title, int w, int h, unsigned int mode, int cb=0 );
    virtual ~glcWindow();

    // necessary callback's for interfacing with GLUT
static    void cbDisplay( void );
static    void cbResize( int w, int h );
static    void cbKeys( unsigned char key, int x, int y );
static    void cbSKeys( int key, int x, int y );
static    void cbMouseClk( int b, int s, int x, int y );
static    void cbMouseEnter( int s );
static    void cbMouseMove( int x, int y );
static    void cbMenu( int v );
static    void cbIdle( void );
static    void cbTimer( int v );

    // derived class implementations of call backs.  A per window basis.
    virtual int Display( void ) { return 0; }
    virtual int Resize( int w, int h ) { return 0; }
    virtual int Keys( unsigned char key, int mx, int my ) { return 0; }
    virtual int SKeys( int key, int mx, int my ) { return 0; }
    virtual int MouseClk( int b, int s, int x, int y ) { return 0; }
    virtual int MouseEnter( int s ) { return 0; }
    virtual int MouseMove( int x, int y ) { return 0; }
    virtual int Menu( int v ) { return 0; }
    virtual int Idle( void ) { return 0; }
    virtual int Timer( int v ) { return 0; }

    // return window information
    int iHeight(void) { return (int)wHeight; }
    int iWidth(void) { return (int)wWidth; }
    int iXpos(void) { return (int)wXpos; }
    int iYpos(void) { return (int)wYpos; }
    
    // use callbacks
    int UseCallBack( int cb, int use=1, int opt=0, int opt1=1000 );
    
    // get / set window visibility
    int Visible( int vis );
};

#endif

