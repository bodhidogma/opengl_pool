// File:        cVmain.cc
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
 */

#include <iostream.h>

#include "cVmain.h"
#include "colors.h"

#include "glpng.h"
#include "cTexMaps.h"

extern cTexMaps *texList;		// external texturemaps list

// ------------------------------------------------------------------
//  Func: cVmain( x,y, w,h )
//  Desc: create our main viewport
//
//  Ret:  n/a
// ------------------------------------------------------------------

cVmain::cVmain( int x, int y, int w, int h ) :
	glcViewport( x, y, w, h )
{
}

// ------------------------------------------------------------------
//  Func: ~cVmain()
//  Desc: generic desctructor
//
//  Ret:  n/a
// ------------------------------------------------------------------

cVmain::~cVmain()
{
}

// ------------------------------------------------------------------
//  Func: Display()
//  Desc: Manage the display of the main window
//
//  Ret:  0
// ------------------------------------------------------------------

int
cVmain::Display( void )
{
//    cout << "vmain:disp: "; dump();
    
    // --- init our viewport ---
    SetView();
    
    // --- draw our stuff --- 
    glDisable( GL_DEPTH_TEST );
    glDisable( GL_CULL_FACE );		// for texmaps
    glShadeModel( GL_FLAT );

    Intro();
    
    glTranslatef( 100, 100, 0.0 );
    glColor3ub( 153, 184, 166 );
    glutWireSphere( 40.1, 20, 16 );
    
    return 0;
}

// ------------------------------------------------------------------
//  Func: Resize( x,y, w,h )
//  Desc: Take care of stuff that is window size dependent
//
//  Ret:  0
// ------------------------------------------------------------------

int
cVmain::Resize( int x, int y, int w, int h )
{
//    if ( x >= 0 ) vX = x;
//    if ( y >= 0 ) vY = y;
    if ( w >= 0 ) vW = w;
    if ( h >= 0 ) vH = h;
    
    return 0;
}

// ------------------------------------------------------------------
//  Func: SetView()
//  Desc: Setup our viewport projection / size etc.
//
//  Ret:  0
// ------------------------------------------------------------------

int
cVmain::SetView( void )
{
    glViewport( vX,vY, vW,vH );
    glScissor( vX,vY, vW,vH );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0.0, (float)vW, 0.0, (float)vH, -50.0, 50.0 );
    
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    
    return 0;
}

// ------------------------------------------------------------------
//  Func: Intro()
//  Desc: Display our into texture map image scaled to fit viewable area
//
//  Ret:  0
// ------------------------------------------------------------------

int
cVmain::Intro( void )
{
    GLfloat pos[4];

    if ( (vW * .7) < vH ) {
    	pos[2] = vW - 10;		// W
    	pos[3] = (vW-20) * .7;		// H : aspect ratio
	pos[3] += (vH-pos[3]+10) / 2;
    }
    else {
    	pos[3] = vH - 10;		// H
    	pos[2] = (vH-20) * 1.42;	// W : aspect ratio
    	pos[2] += (vW-pos[2]+10) / 2;
    }
    pos[0] = (vW-pos[2]);		// X
    pos[1] = (vH-pos[3]);		// Y
    
    glEnable( GL_TEXTURE_2D );
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
    texList->Bind( GL_TEXTURE_2D, tex_intro );
    
    glBegin( GL_QUADS );
    {
	glTexCoord2f( 0.0, 1.0 );
	glVertex3f( pos[0], pos[1], 0.0 );
	glTexCoord2f( 0.0, 0.0 );
	glVertex3f( pos[0], pos[3], 0.0 );
	glTexCoord2f( 1.0, 0.0 );
	glVertex3f( pos[2], pos[3], 0.0 );
	glTexCoord2f( 1.0, 1.0 );
	glVertex3f( pos[2], pos[1], 0.0 );
    }
    glEnd();
    glDisable( GL_TEXTURE_2D );
    
    return 0;
}
 
