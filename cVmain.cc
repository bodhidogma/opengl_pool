// File:        cVmain.cc
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
// 
// $Revision: 1.21 $
/*
 * $Log: not supported by cvs2svn $
 * Revision 1.20  1999/11/22 22:17:08  paulmcav
 * enabled ball bouncing
 *
 * Revision 1.19  1999/11/20 21:41:30  paulmcav
 * added audio playback support.
 *
 * Revision 1.18  1999/11/20 07:53:57  paulmcav
 * added texmap support, some more menu options, lighting, cleanup, etc.
 *
 * Revision 1.17  1999/11/19 22:36:57  paulmcav
 * Balls displaying on the table, and more!
 *
 * Revision 1.16  1999/11/18 16:27:02  scott
 * Created text for help screen
 *
 * Revision 1.15  1999/11/18 02:02:23  paulmcav
 * added pool table drawing
 *
 * Revision 1.14  1999/11/18 01:12:19  paulmcav
 * added help menu again, intro win, got correct fovy
 *
 * Revision 1.13  1999/11/17 21:05:56  paulmcav
 * added mouse movement support
 *
 * Revision 1.12  1999/11/12 21:05:40  paulmcav
 * more perspective work
 *
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
# include "colors.h"

#include "glpng.h"
#include "cTexMaps.h"
#include "cAudio.h"

#include "glUtil.h"

#include <assert.h>

//#include "pooltable.h"
 
extern cTexMaps *texList;		// external texturemaps list
extern cAudio *audio;
//extern GLuint texName[];

// ------------------------------------------------------------------
//  Func: cVmain( x,y, w,h )
//  Desc: create our main viewport
//
//  Ret:  n/a
// ------------------------------------------------------------------

cVmain::cVmain( int x, int y, int w, int h ) :
	glcViewport( x, y, w, h ),
	iIntroWin(1),
	iHelpWin(0),
	Xdeg(15), Ydeg(0)
{
    GLfloat shiny[] = { 5.0 };			// some light stuff
    
    table = new cTable( 0,0, 48,96 );		// our table (size)
    assert( table );
    
    tmp = 0;
    flg_wire = DEF_WIRE;			// default flags
    flg_tex = DEF_TEX;
    
    fH = VMAIN_HEIGHT;		// viewport height
    
    glMaterialfv( GL_FRONT, GL_SHININESS, shiny );	// light settings
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
    if ( stat )			// get handle to status window
	Vstat = stat;
	
    return 0;
}

// ------------------------------------------------------------------
//  Func: Display()
//  Desc: Manage the display of the main window
//
//  Ret:  0
// ------------------------------------------------------------------

#define LIGHT_POS	0, 0, 1 

int
cVmain::Display( void )
{
    GLfloat pos[] = { LIGHT_POS, 0.0 };
//    cout << "vmain:disp: "; dump();
    
    // --- init our viewport ---
    SetView();
    
    // --- draw our stuff --- 
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_CULL_FACE );		// for texmaps
    glShadeModel( GL_SMOOTH );
    glEnable( GL_COLOR_MATERIAL );

//    glRotatef(tmp, 0, 1.0, 0 );

    if ( iIntroWin ){			// draw the intro screen?
	DoIntro();
    }
    else {
	glPushMatrix();			// save model_view matrix
	
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
	
	glLightfv( GL_LIGHT0, GL_POSITION, pos );

/*	glPushMatrix();
	glTranslatef( LIGHT_POS );
	glutWireSphere(5, 20,16 );
	glPopMatrix();
*/
	glTranslatef( 0,0, (85-abs(Xdeg)) * 3.5);	// zoom with height
	glRotatef( Xdeg, 1, 0, 0 );			// rotate around X
	glRotatef( Ydeg, 0, 1, 0 );			// rotate around Y

        table->Draw();				// draw our table .. etc.
	
	glDisable( GL_LIGHT0 );
	glDisable( GL_LIGHTING );
	
	glPopMatrix();
    }
    if ( iHelpWin ) {				// draw the help window?
        glDisable( GL_DEPTH_TEST );
	DoHelp();
    }
	    
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
    vW = w;	// real window coordinates
    vH = h;

    fW = ( (float)w/(float)h ) * VMAIN_HEIGHT;	// (fake) used Width / height
    
    fovy = calcangle( VMAIN_HEIGHT, VMAIN_DXCNTR );

//    cout << "fovy: " << fovy << endl;
//    cout << "h: " << fH << " w: " << fW << endl;
    
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
//    cout << "fW: " << fW << endl;
//    cout << "vW/vH: " << (float)(w/h) << " tmp: " << tmp << endl;
    
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( fovy, fW/VMAIN_HEIGHT, 50, 1000 );

    glViewport( vX,vY, vW,vH );
    glScissor( vX,vY, vW,vH );

//    glOrtho( -(fW/2), (fW/2), -(fH/2), (fH/2), 1,1000 );
//    cout << "vW: " << vW/2.0 << " vH: " << vH/2.0 << endl;
    
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    
    glTranslatef( 0.0, 0.0, -VMAIN_DXCNTR );
    
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
    GLfloat pos[4];	// 
    GLfloat w,h;

    glPushMatrix();
    
    w = fW / 2;
    h = fH / 2;
    
    // 
    if ( (w * .7) < h ) {
    	pos[2] = w-5;			// W			(x2)
    	pos[3] = (w-5) * .7;		// H : aspect ratio	(y2)
//	pos[3] += (h-pos[3]+10) / 2;
    }
    else {
    	pos[3] = h-5;			// H			(y2)
    	pos[2] = (h-5) * 1.42;		// W : aspect ratio	(x2)
//    	pos[2] += (w-pos[2]+10) / 2;
    }
    pos[0] = -pos[2];		// X1
    pos[1] = -pos[3];		// Y1

    glEnable( GL_TEXTURE_2D );
    
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
    GLfloat pos[4], w,h;

    w = fW/2;
    h = fH/2;
    
    pos[2] = w-10;
    pos[3] = h-10;

    pos[0] = -pos[2];
    pos[1] = -pos[3];
    
    glColor4f( BLACK, 0.65 );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glRectf( pos[0], pos[1], pos[2], pos[3] );
    
    glColor4f( GRAY, 0.20 );
    glRectf( pos[0],pos[1] ,pos[2],pos[3]  );
    
    glDisable( GL_BLEND );

    glshadebox( pos[0],pos[1], pos[2], pos[3], 1 );

    glColor3f( WHITE );
    
//    cout << "x,y: " << (int)pos[0] << "," << pos[3] << endl;

//    help_message( pos[0],pos[3], w*2,h*2 );
    help_message( (int)pos[0],pos[1], pos[2],pos[3] );
    
    return 0;
}
 
int
cVmain::help_message( float x, float y, float w, float h )
{
    x += .5;
    h -= 3.5;

    // test audio file
    audio->PlayFile( "data/ball_hit.au" );
    
    glputs( x, h, "               GLPool v0.1 - MESH GAMING"); h -= 3;
    glputs( x, h, "                      Help Screen" ); h -= 3;
    glputs( x, h, " _____________________________________________________"); h-= 6;
    glputs( x, h, "I. Menu Options:"); h-= 5;
    glputs( x, h, "Depress the RMB to access the menu from anywhere on the"); h-=3;
    glputs( x, h, "intro screen.  Select from the following options:"); h-=4;
    glputs( x, h, "     New Game - Starts a new single player game."); h-=3;
    glputs( x, h, "     Practice - Practice shots with a single ball."); h-=3;
    glputs( x, h, "     2-Player - Starts a new 2-player game."); h-=3;
    glputs( x, h, "     Help     - Enter/Exit the Help Screen."); h-=3;
    glputs( x, h, "     Exit     - Exit the game."); h-=5;
    glputs( x, h, "II. Game Modes:"); h-=5;
    glputs( x, h, "There are 2 modes in GLPool: Movement and Shoot. In");h-=3;
    glputs( x, h, "movement mode (default), depress the LMB while moving");
    h-=3;
    glputs( x, h, "the mouse to tumble around the table.  In shoot mode,");
    h-=3;
    glputs( x, h, "the cue stick is positioned for a shot.  Use the mouse");
    h-=3;
    glputs( x, h, "to simulate the stick action."); h-=6;
    glputs( x, h, "III. Hot Keys:     'h' - Enter/Exit the Help Screen.");
    h-=3;
    glputs( x, h, "                   'q' - Quit the Game."); h-=3;
    glputs( x, h, "                   'm' - Toggle on Movement Mode.");h-=3;
    glputs( x, h, "                   SPACEBAR - Toggle on Shoot Mode.");

    return 0;
}

int
cVmain::Animate( void )
{
    
    iHelpWin = 0;	// turns off these displays
    iIntroWin = 0;
    
//    cout << "mwA" << endl;

    
    return (table->Move()) ;
}

int
cVmain::Wire( int flag )
{
    if ( flag >= 0 )
	flg_wire = flag;
    else
	flg_wire ^= 1;
    
    table->SetFlags( flg_wire, flg_tex );
    return flg_wire;
}

int
cVmain::Texmap( int flag )
{
    if ( flag >= 0 )
	flg_tex = flag;
    else
	flg_tex ^= 1;
    
    table->SetFlags( flg_wire, flg_tex );
    return flg_tex;
}

int
cVmain::Xrot( int deg )
{
    Xdeg += deg;

    if ( Xdeg < VMAIN_MINXD )
        Xdeg = VMAIN_MINXD;
    if ( Xdeg > VMAIN_MAXXD )
        Xdeg = VMAIN_MAXXD;
    
    return 0;
}

int
cVmain::Yrot( int deg )
{
    Ydeg += deg;
    return 0;
}
