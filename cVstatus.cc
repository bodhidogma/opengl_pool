// File:        cVstatus.cc
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
// 
// $Revision: 1.1 $
/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  1999/10/25 06:33:21  paulmcav
 * working project with fancy windowing class for GL.
 * Tex maps sorta working, looks sharp though!
 *
 */

#include "cVstatus.h"
#include "colors.h"
#include "glUtil.h"

#include <iostream.h>
#include <assert.h>
#include <string.h>

enum ws_listobjs {
    ws_outline,
    ws_ballque,
    ws_objcnt
};

// ------------------------------------------------------------------
//  Func: 
//  Desc: 
//
//  Ret:  
// ------------------------------------------------------------------

cVstatus::cVstatus( int x, int y, int w ) :
	glcViewport( x,y, w, V_STATUS_HEIGHT ),
	cMessage(0),
	iBallCnt(0)
{
    // generate display lists
    myLists = glGenLists( ws_objcnt+1 );

    ResetBalls();
//    DrawBallQ();
}

cVstatus::~cVstatus()
{
}

int
cVstatus::Display( void )
{
//    cout << "vstat:disp: "; dump();
    
    // --- init our viewport ---
    SetView();
    
    // --- draw our stuff ---
//    glEnable( GL_COLOR_MATERIAL );
    glDisable( GL_DEPTH_TEST );
    glEnable( GL_CULL_FACE );
    glShadeModel( GL_FLAT );
    
    // draw statusbar outline
    glCallList( myLists + ws_outline );
    
    glShadeModel( GL_SMOOTH );
    glCallList( myLists + ws_ballque );

    if ( cMessage ) {
    	glColor3f( BLUE );
	glputs( 8,8,  cMessage );
    }
    
    return 0;
}

int
cVstatus::Resize( int x, int y, int w, int h )
{
//    if ( x >= 0 ) vX = x;
    if ( y >= 0 ) vY = y;
    if ( w >= 0 ) vW = w;
//    if ( h >= 0 ) vH = h;
    h = V_STATUS_HEIGHT;
    
    // re-generate some lists
    glNewList( myLists + ws_outline, GL_COMPILE );
    {
	glBegin( GL_QUADS );		// Background gray
	{
	    glColor3f( GRAY );
	    glVertex2i( 0, h );		// TL
	    glVertex2i( 0, 0 );		// BL
	    glVertex2i( w, 0 );		// BR
	    glVertex2i( w, h );		// TR
	}
	glEnd();

	glshadebox( 0,0, w, h, 1 );
	glshadebox( 1,1, w-1, h-1, 0 );
	glshadebar( w-(int)(SC_BALL_W*15.4),1, 0, h-2, 1 );
    }
    glEndList();

    DrawBallQ();
    
    return 0;
}

int
cVstatus::SetView( void )
{
    glViewport( vX,vY, vW,vH );
    glScissor( vX,vY, vW,vH );
    
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0.0, (float)vW, 0.0, (float)vH, -10.0, 20.0 );
	
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    
    return 0;
}

int
cVstatus::Message( char *msg )
{
    if ( cMessage )
	delete cMessage;

    cMessage = new char[ strlen( msg ) ];
    assert( cMessage );

    strcpy( cMessage, msg );
    
    Display();

    return 0;
}

int
cVstatus::DrawBallQ( void )
{
    int cnt;
    GLUquadricObj *q = gluNewQuadric();
    GLfloat mat[] = { 50.0 };
    GLfloat pos[] = { 0.5, 0.5, 0.5, 0.0 };


    glNewList( myLists + ws_ballque, GL_COMPILE );
    {
	glEnable( GL_COLOR_MATERIAL );
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
	glMaterialfv( GL_FRONT, GL_SHININESS, mat );
	glLightfv( GL_LIGHT0, GL_POSITION, pos );
    
    	glPushMatrix();
	glLoadIdentity();
	glTranslatef( vW-(SC_BALL_W*14.65), 13, -20.0 );
    	for (cnt = 0; cnt < 15; cnt++ ){
	    if ( iBallList[ cnt ] ) {
    		glColor3f( YELLOW );
		gluQuadricNormals( q, GL_SMOOTH );
		gluSphere( q, SC_BALL_W/2 , 10, 5 );
//	    	glutWireSphere( 10, 10, 5 );
	    }
    	    glTranslatef( SC_BALL_W, 0.0, 0.0 );
    	}
    	glPopMatrix();

	glDisable( GL_COLOR_MATERIAL );
	glDisable( GL_LIGHTING );
	glDisable( GL_LIGHT0 );
    }
    glEndList();
    
    return 0;
}
    

int
cVstatus::ResetBalls( void )
{
    for (iBallCnt = 1; iBallCnt < 16; iBallCnt++ )
	iBallList[ iBallCnt-1 ] = 16-iBallCnt;

    return 0;
}

int
cVstatus::AddBalls( int ballnum )
{
    return 0;
}

