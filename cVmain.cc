// File:        cVmain.cc
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
// 
// $Revision: 1.12 $
/*
 * $Log: not supported by cvs2svn $
 * Revision 1.11  1999/11/12 08:56:35  paulmcav
 * more viewport work
 *
 * Revision 1.10  1999/11/11 20:38:31  paulmcav
 * working on perspective use
 *
 * Revision 1.9  1999/11/10 20:04:49  paulmcav
 * updated project for use with animation
 *
 * Revision 1.8  1999/11/10 08:19:19  paulmcav
 * added updates to ball management classes
 *
 * Revision 1.7  1999/11/10 00:21:04  paulmcav
 * misc updates.  added ball(s) class to manage ball movement/ drawing.
 *
 * Revision 1.6  1999/11/04 02:21:43  paulmcav
 * fixed texmap problem, added colors to out of play balls.
 *
 * Revision 1.5  1999/11/03 17:28:55  paulmcav
 * added some colors for balls
 *
 * Revision 1.4  1999/11/02 09:03:53  paulmcav
 * added a box around help menu
 *
 * Revision 1.3  1999/11/02 08:47:04  paulmcav
 * added menu / kb callback support; & help window
 *
 * Revision 1.2  1999/10/29 07:12:22  paulmcav
 * added some more documentation to the class
 *
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

#include "glUtil.h"

#include <assert.h>

//#include "pooltable.h"

extern cTexMaps *texList;		// external texturemaps list

// ------------------------------------------------------------------
//  Func: cVmain( x,y, w,h )
//  Desc: create our main viewport
//
//  Ret:  n/a
// ------------------------------------------------------------------

cVmain::cVmain( int x, int y, int w, int h ) :
	glcViewport( x, y, w, h ),
	iIntroWin(1),
	iHelpWin(0)
{
    table = new cTable( 100,100, 20,20 );
    assert( table );
    
    tmp = 0;
    flg_wire = 1;
    
    fH = 2.0;
}

// ------------------------------------------------------------------
//  Func: ~cVmain()
//  Desc: generic desctructor
//
//  Ret:  n/a
// ------------------------------------------------------------------

cVmain::~cVmain()
{
    if ( table )
	delete table; 
}

// ------------------------------------------------------------------
//  Func: setstatus( cVstatus *stat )
//  Desc: get a ptr to the status window
//
//  Ret:  n/a
// ------------------------------------------------------------------

int
cVmain::setstatus( cVstatus *stat )
{
    if ( stat )
	Vstat = stat;
	
    return 0;
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
    GLfloat mat[] = { 50.0 };
    GLfloat pos[] = { 0.0, 1.0, 0.0, 0.0 };
    
//    cout << "vmain:disp: "; dump();
    
    // --- init our viewport ---
    SetView();
    
    // --- draw our stuff --- 
//    glDisable( GL_DEPTH_TEST );
    glDisable( GL_CULL_FACE );		// for texmaps
    glShadeModel( GL_SMOOTH );

    glTranslatef( 0.0, 0.0, -2 );
    glRotatef(tmp, 0, 1.0, 0 );


    if ( iIntroWin ){
	DoIntro();
    }
    else {
        table->Draw();
    }
//    if ( iHelpWin )
//	DoHelp();
    
    glColor3f( ORANGE );

	glEnable( GL_COLOR_MATERIAL );
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
	glMaterialfv( GL_FRONT, GL_SHININESS, mat );
	glLightfv( GL_LIGHT0, GL_POSITION, pos );
    
    tmp ++;
    
    if ( flg_wire )
    	glutWireSphere( 1 , 20,16 );
    else 
	glutSolidSphere( 1, 20,16 );
  
	glDisable( GL_COLOR_MATERIAL );
	glDisable( GL_LIGHTING );
	glDisable( GL_LIGHT0 );
    
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
    vW = w;
    vH = h;

    fW = ( (float)w/(float)h ) * 2;
    
    cout << "h: " << fH << " w: " << fW << endl;
    
    
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

//    fovy = calcangle( vH, 100 );
    
//    cout << "vW/vH: " << (float)(w/h) << " tmp: " << tmp << endl;
    
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
//    glOrtho( -1, 1, -1, 1, 1,100 );
    gluPerspective( 60, fW/2, 1, 10 );
    
//    cout << "vW: " << vW/2.0 << " vH: " << vH/2.0 << endl;
    
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    
//    glTranslatef( vW/2.0, vH/2.0, -*1.01.0 );
    
    return 0;
}

// ------------------------------------------------------------------
//  Func: DoIntro()
//  Desc: Display our into texture map image scaled to fit viewable area
//
//  Ret:  0
// ------------------------------------------------------------------

int
cVmain::DoIntro( void )
{
    GLfloat pos[4];

    glPushMatrix();
    
//    glLoadIdentity();
//    glTranslatef( 0, 0, -2.0 );
/*    
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
*/
    pos[0] = -fW/2 ;		// x
    pos[1] = -1.0 ;		// y
    pos[2] = fW/2 ;		// x2
    pos[3] = 1.0 ;		// y2
    
    glEnable( GL_TEXTURE_2D );
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
    texList->Bind( GL_TEXTURE_2D, tex_intro );

    glBegin( GL_QUADS );
    {
	glTexCoord2f( 0.0, 1.0 );
	glVertex3f( pos[0], pos[1], 0.0 );
	glTexCoord2f( 1.0, 1.0 );
	glVertex3f( pos[2], pos[1], 0.0 );
	glTexCoord2f( 1.0, 0.0 );
	glVertex3f( pos[2], pos[3], 0.0 );
	glTexCoord2f( 0.0, 0.0 );
	glVertex3f( pos[0], pos[3], 0.0 );
    }
    glEnd();
    glDisable( GL_TEXTURE_2D );
    
    glPopMatrix();
    
    return 0;
}
 
// ------------------------------------------------------------------
//  Func: DoHelp()
//  Desc: Display our help window
//
//  Ret:  0
// ------------------------------------------------------------------

int
cVmain::DoHelp( void )
{
    GLfloat x,y,w,h;

    x = y = 50.0;
    w = vW -50.0;
    h = vH -50.0;
    
    glColor4f( BLACK, 0.65 );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glRectf( 0.0, 0.0, vW, vH );
    
    glColor4f( GRAY, 0.20 );
    glRectf( x, y, w, h );
    
    glDisable( GL_BLEND );

    glshadebox( (int)x,(int)y, (int)w,(int)h+1, 1 );
//    glshadebox( (int)x+1,(int)y+1, (int)w-1,(int)h-0, 0 );

    glColor3f( WHITE );

    help_message( x,y, w,h );
    
    return 0;
}
 
int
cVmain::help_message( float x, float y, float w, float h )
{
    x += 8;
    h -= 16;
    
    glputs( x, h, "Hi, this is some test message!" ); h -= 16;
    glputs( x, h, "This is a second line..." ); h -= 16;

    return 0;
}

int
cVmain::Animate( void )
{
    iHelpWin = 0;	// turns off these displays
    iIntroWin = 0;
    
    return (table->Move()) ;
}

int
cVmain::Wire( int flag )
{
    if ( flag >= 0 )
	flg_wire = flag;
    else
	flg_wire ^= 1;
    
    return flg_wire;
}

