// File:        cWStatus.cc
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
// 
// $Revision: 1.1 $
/*
 * $Log: not supported by cvs2svn $
 */

#include "cWStatus.h"
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

cWStatus::cWStatus( glWindow *p ) :
	glWindow( p, 0,0, 1, W_STATUS_HEIGHT, 1 ),
	cMessage(0),
	iBallCnt(0)
{
    glClearColor( GRAY, 1.0 );

    // generate display lists
    myLists = glGenLists( ws_objcnt+1 );

    ResetBalls();
//    DrawBallQ();
}

cWStatus::~cWStatus()
{
}

int
cWStatus::Display( void )
{
//    cout <<"Display: "<< iMyNum <<" w: "<< wWidth <<" h: "<< wHeight <<endl;
    
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
    
//    glEnable( GL_COLOR_MATERIAL );
    glEnable( GL_CULL_FACE );
    glEnable( GL_DEPTH_TEST );

    glShadeModel( GL_SMOOTH );
    
    // draw statusbar outline
    glCallList( myLists + ws_outline );

/*
    GLfloat mat[] = { 20.0 };
    GLfloat pos[] = { 0.5, 0.5, 0.5, 0.0 };

    glEnable( GL_COLOR_MATERIAL );
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    glMaterialfv( GL_FRONT, GL_SHININESS, mat );
    glLightfv( GL_LIGHT0, GL_POSITION, pos );
*/    
    glCallList( myLists + ws_ballque );
/*    
    glDisable( GL_COLOR_MATERIAL );
    glDisable( GL_LIGHTING );
    glDisable( GL_LIGHT0 );
*/    
    if ( cMessage ) {
    	glColor3f( BLUE );
	glputs( 8,8,  cMessage );
    }
    
    glPopMatrix();
    glutSwapBuffers();
    glFlush();
    
    return 0;
}

int
cWStatus::Resize( int w, int h )
{
//    cout <<"Resize: "<< iMyNum <<" w: "<< w <<" h: "<< h <<endl;
    
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    
    glViewport( 0,0, w,h );
    glScissor( 0,0, w,h );
    
    glOrtho( 0.0, wWidth, 0.0, wHeight, -10.0, 20.0 );

    // re-generate some lists
	    
//    glMatrixMode( GL_MODELVIEW );

    glNewList( myLists + ws_outline, GL_COMPILE );
    {
        glLoadIdentity();
	glshadebox( 0,0, w, h, 1 );
	glshadebox( 1,1, w-1, h-1, 0 );
	glshadebar( w-340,1, 0, h-2, 1 );
    }
    glEndList();

    DrawBallQ();
    
    return 0;
}

int
cWStatus::Message( char *msg )
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
cWStatus::DrawBallQ( void )
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
	glTranslatef( iWidth()-323, 13, -20.0 );
    	for (cnt = 0; cnt < 15; cnt++ ){
	    if ( iBallList[ cnt ] ) {
    		glColor3f( YELLOW );
		gluQuadricNormals( q, GL_SMOOTH );
		gluSphere( q, 12, 10, 5 );
//	    	glutWireSphere( 10, 10, 5 );
	    }
    	    glTranslatef( 22, 0.0, 0.0 );
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
cWStatus::ResetBalls( void )
{
    for (iBallCnt = 1; iBallCnt < 16; iBallCnt++ )
	iBallList[ iBallCnt-1 ] = 16-iBallCnt;

    return 0;
}

int
cWStatus::AddBalls( int ballnum )
{
    return 0;
}

