// File:        glWindow.h
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
//              
// 
// $Revision: 1.1 $

/*
 * $Log: not supported by cvs2svn $
 * 
*/

#ifndef _GLWINDOW_H_
#define _GLWINDOW_H_

#define MAX_WINDOWS 32

#define WCB_KEYS	0x01
#define WCB_SKEYS	0x02
#define WCB_MOUSECLK	0x04
#define WCB_MOUSEENTER	0x08

#include <GL/glut.h>

/*
*/

class glWindow
{
private:
static int glWinNum;
    
    int wChildList[ MAX_WINDOWS ];
    int iNumChildren;
    int iPctg;
    
    float wsWidth,
    	  wsHeight,
          wsXpos,
	  wsYpos;

    int rescale( void );
    int newchild( int num );
    
protected:
    float wWidth,
    	  wHeight,
          wXpos,
	  wYpos;

    int iWindow;
    int iMyNum;
    int iMyParent;
    
public:
    glWindow( glWindow *, float x, float y, float w, float h, int pct=0,
	    int cb=0 );
    glWindow( char *title, int w, int h, unsigned int mode, int cb=0 );
    virtual ~glWindow();

static    void cbDisplay( void );
static    void cbResize( int w, int h );
static    void cbKeys( unsigned char key, int x, int y );
static    void cbSKeys( int key, int x, int y );
static    void cbMouseClk( int b, int s, int x, int y );
static    void cbMouseEnter( int s );

    virtual int Display( void ) { return 0; }
    virtual int Resize( int w, int h ) { return 0; }
    virtual int Keys( unsigned char key, int mx, int my ) { return 0; }
    virtual int SKeys( int key, int mx, int my ) { return 0; }
    virtual int MouseClk( int b, int s, int x, int y ) { return 0; }
    virtual int MouseEnter( int s ) { return 0; }

    int iHeight(void) { return (int)wHeight; }
    int iWidth(void) { return (int)wWidth; }
    int iXpos(void) { return (int)wXpos; }
    int iYpos(void) { return (int)wYpos; }
    
    int Visible( int vis );
};

#endif

