// File:        cTable.cc
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
// 
// $Revision: 1.6 $
/*
 * $Log: not supported by cvs2svn $
 * Revision 1.5  1999/11/20 07:53:56  paulmcav
 * added texmap support, some more menu options, lighting, cleanup, etc.
 *
 * Revision 1.4  1999/11/19 22:36:57  paulmcav
 * Balls displaying on the table, and more!
 *
 * Revision 1.3  1999/11/18 02:02:23  paulmcav
 * added pool table drawing
 *
 * Revision 1.2  1999/11/10 20:04:49  paulmcav
 * updated project for use with animation
 *
 * Revision 1.1  1999/11/10 08:19:19  paulmcav
 * added updates to ball management classes
 *
 */

// table size: 4'x8' = 48"x96".  Playing area = 44"x88" (92%)

#include "cTable.h"
#include "colors.h"

#include <GL/glut.h>
#include <iostream.h>
#include <assert.h>

cTable::cTable( float x, float y, float w, float h ) :
    lBalls(NULL),
    xMin(x),
    xMax(w),
    yMin(y),
    yMax(h),
    iWire(DEF_WIRE),
    iTex(DEF_TEX),
    StickRotZ(0), StickTrY(0),
    iStick(0)
{
    lBalls = new cBallList( x,y, w*.92,h*.92 );	// put balls on the table!
    assert( lBalls );
    
    dlist = glGenLists( tl_count );

    make_table( 0, dlist );
    make_table( 1, dlist+1 );
    make_stick( dlist+2 );
}

cTable::~cTable()
{
    if ( lBalls )
	delete lBalls;
}

int
cTable::make_table( int wire, int lnum )
{
    int cnt;
    float X,Y,W,H;

    // create table display list
    glNewList( lnum, GL_COMPILE );
    {
	glTranslatef( -(xMax/2), 0, 0 ); 
	glTranslatef( 0, -(yMax/2), 0 ); 
	
	glColor3f( WOOD );
//	if ( wire )
	    glBegin( GL_LINE_LOOP );
//	else 
//	    glBegin( GL_QUADS );
	{
	    glVertex3f( 0, 0, 0 );
	    glVertex3f( xMax, 0, 0 );
	    glVertex3f( xMax, yMax, 0 );
	    glVertex3f( 0, yMax, 0 );
	}
	glEnd();

	glPushMatrix();
	glTranslatef( xMax*.04, yMax*.04, .1 ); 
	
	glColor3f( FELT );
//	if ( wire )
//	    glBegin( GL_LINE_LOOP );
//	else 
	    glBegin( GL_QUADS );
	{
	    glVertex3f( 0, 0, 0 );
	    glVertex3f( xMax*.92, 0, 0 );
	    glVertex3f( xMax*.92, yMax*.92, 0 );
	    glVertex3f( 0, yMax*.92, 0 );
	}
	glEnd();
	glPopMatrix();

	X = xMax*.04;
	Y = yMax*.04;
	W = xMax*.92;
	H = yMax*.92;
	glColor3f( GRAY90 );
	
	glPushMatrix();
        glTranslatef( X/2, Y, 0 );
	
	for ( cnt = 1; cnt < 8; cnt++ ){
	    glTranslatef( 0, H/8, 0 );
	    glutSolidSphere( .3, 5, 3 );
	    glTranslatef( X+W, 0, 0 );
	    glutSolidSphere( .3, 5, 3 );
	    glTranslatef( -X-W, 0, 0 );
	}
	glPopMatrix();
	
	glPushMatrix();
        glTranslatef( X, Y/2, 0 );
	
	for ( cnt = 1; cnt < 4; cnt++ ){
	    glTranslatef( W/4, 0, 0 );
	    glutSolidSphere( .3, 5, 3 );
	    glTranslatef( 0,Y+H, 0 );
	    glutSolidSphere( .3, 5, 3 );
	    glTranslatef( 0,-Y-H, 0 );
	}
	glPopMatrix();
	
    }
    glEndList();

    return 0;
}

int
cTable::make_stick( int lnum )
{
    glNewList( lnum, GL_COMPILE );
    {
	glRotatef( 268, 1, 0, 0 );
	glTranslatef( 0,0, -50 );
	glutSolidCone( .5, 50, 20, 16 );
    }
    glEndList();

    return 0;
}

int
cTable::Draw()
{
    glPushMatrix();
    
    glDisable( GL_LIGHTING );
    glRotatef( -90, 1, 0, 0 );
    glCallList( dlist+iWire );
    
    glTranslatef( xMax*.04, 0, 0 ); 	// l,bottom of playing area
    glTranslatef( 0, yMax*.04, 0 ); 

    glEnable( GL_LIGHTING );
    lBalls->Draw();
    
    
    if ( iStick ) {
	lBalls->MoveToBall( 0 );			// move to que ball

	glRotatef( StickRotZ, 0,0,1 );
	glTranslatef( 0, (.25*StickTrY) + BALL_R, 0 );
	
	glCallList( dlist+tl_stick );
    }
    
    glPopMatrix();

    return 0;
}

int 
cTable::Move()
{
    return (lBalls->Move());
}

int
cTable::Resize( float x, float y, float w, float h )
{
    return 0;
}

int
cTable::SetFlags( int wire, int tex )
{
    iWire = wire;
    iTex = tex;

    lBalls->SetFlags( wire, tex );

    return 0;
}


// ------------------------------------------------------------------
//  Func: 
//  Desc: 
//
//  Ret:  
// ------------------------------------------------------------------


int
cTable::StickRot( int deg )
{
    StickRotZ += deg;
    return 0;
}

int
cTable::StickTr( int dx )
{
    StickTrY += dx;
    return 0;
}

int
cTable::StickToggle( int val )
{
    iStick = val;
    return 0;
}

