// File:        cTable.cc
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
// 
// $Revision: 1.10 $
/*
 * $Log: cTable.cc,v $
 * Revision 1.10  1999/12/08 01:08:16  paulmcav
 * added more stuff!
 *
 * Revision 1.9  1999/12/06 21:19:46  paulmcav
 * updated game to allow collisions between balls
 *
 * Revision 1.8  1999/12/06 09:21:18  paulmcav
 * added windos portability code/utils
 *
 * Revision 1.7  1999/12/06 04:49:24  paulmcav
 * added pooltable model loading / rendering.
 * Cue stick hit now works.  Timing is a bit better
 * Includes timing statistics
 *
 * Revision 1.6  1999/12/03 21:57:34  paulmcav
 * Added que stick action to game
 *
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

#include <GL/glut.h>
#include <iostream.h>
#include <assert.h>
#include <math.h>
#include <memory.h>

#include "cTable.h"
#include "colors.h"
#include "cAudio.h"
#include "glUtil.h"

#include "glm.h"

#include "cuestick.h"

#define POOL_TABLE	"data/pooltable.obj"
#define STICK_DEF_POS	-.5

extern cAudio *audio;

// ------------------------------------------------------------------
//  Func: cTable( x,y, w,h )
//  Desc: create a table at pos x,y, of w X h width / height
//
//  Ret:  
// ------------------------------------------------------------------

cTable::cTable( GLfloat x, GLfloat y, GLfloat w, GLfloat h ) :
    lBalls(NULL),
    xMin(x),
    xMax(w),
    yMin(y),
    yMax(h),
    iWire(DEF_WIRE),
    iTex(DEF_TEX),
    StickRotZ(0), StickTrY( STICK_DEF_POS ),
    iStick(0)
{
    lBalls = new cBallList( x,y, w*.92,h*.92 );	// put balls on the table!
    assert( lBalls );
    
    dlist = glGenLists( tl_count );

    make_table( 0, dlist );		// solid
    make_table( 1, dlist+1 );		// wire frame
    make_stick( dlist+2 );
}

// ------------------------------------------------------------------
//  Func: ~cTable()
//  Desc: Table destructor
//
//  Ret:  
// ------------------------------------------------------------------

cTable::~cTable()
{
    if ( lBalls )
	delete lBalls;
}

// ------------------------------------------------------------------
//  Func: make_table( wire, lnum )
//  Desc: create wirefram / modeled table display list
//
//  Ret:  
// ------------------------------------------------------------------

int
cTable::make_table( int wire, int lnum )
{
    GLMmodel	*model;
    GLfloat	scale;
    GLfloat 	dims[3];
    int cnt;
    GLfloat X,Y,W,H;

    if ( !wire ) {
	model = glmReadOBJ( POOL_TABLE );
	scale = glmUnitize( model );
	glmScale( model, (xMax+10)*.95 );
	glmDimensions( model, dims );

	pHeight = (dims[2]/2)-(2*BALL_R)+.6;
//cout <<"dx: " << dims[0] << " dy: " << dims[1] << " dz: " << dims[2] << endl;
	
	glmFacetNormals( model );
	glmVertexNormals( model, 90.0 );

	plist = glmList( model, GLM_SMOOTH | GLM_MATERIAL );
    }
    else {
	// create table display list
	glNewList( lnum, GL_COMPILE );
	{
	    glTranslatef( -(xMax/2), 0, 0 ); 
	    glTranslatef( 0, -(yMax/2), 0 ); 
	    
	    glColor3f( WOOD );
	    glBegin( GL_LINE_LOOP );
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
    }

    return 0;
}

// ------------------------------------------------------------------
//  Func: make_stick( lnum )
//  Desc: make cue stick display list lnum
//
//  Ret:  
// ------------------------------------------------------------------

int
cTable::make_stick( int lnum )
{
    GLfloat u[3];
    int cnt;
    
    glInterleavedArrays( CUEFORMAT, 0, (GLvoid*)&CUEMODEL );

    glScale( 10, &CUEMODEL[0], 3, 6, CUEPOLYCNT *3 );
    
    glNewList( lnum, GL_COMPILE );
    {
	glRotatef( 88, 1,0,0 );
	
	glBegin( GL_TRIANGLES );
	for ( cnt=0; cnt < CUEPOLYCNT *3; cnt++ ){
	    memcpy( &u[0], &CUEMODEL[ cnt ], sizeof(GLfloat)*3 );
	    glNormal3fv( u );
	    glArrayElement( cnt );
	}
	glEnd();
    }
    glEndList();

    return 0;
}

// ------------------------------------------------------------------
//  Func: Draw()
//  Desc: Draw table with balls and (possibly) cue stick
//
//  Ret:  
// ------------------------------------------------------------------

int
cTable::Draw( void )
{
    glPushMatrix();
    
    glRotatef( -90, 1, 0, 0 );

    if ( !iWire ) {
    	glEnable( GL_LIGHTING );
	glPushMatrix();
	glTranslatef( 0,0, -pHeight );
		
	glScalef( 1.07, 1,1 );
	glCallList( plist );
	glPopMatrix();

	glTranslatef( -xMax*.46, -yMax*.46, 0 ); 	// l,bottom 
    }
    else {
        glDisable( GL_LIGHTING );
    	glCallList( dlist+iWire );

	glTranslatef( xMax*.04, yMax*.04, 0 ); 	// l,bottom of playing area
    }
    
    glEnable( GL_LIGHTING );
    lBalls->Draw();
    
    if ( iStick ) {
	lBalls->MoveToBall( 0 );			// move to que ball

	glRotatef( StickRotZ, 0,0,1 );
	glTranslatef( 0, StickTrY-BALL_R, 0 );
	
	glEnable( GL_COLOR_MATERIAL );
	
	glCallList( dlist+tl_stick );
    }
    
    glPopMatrix();

    return 0;
}

// ------------------------------------------------------------------
//  Func: Move()
//  Desc: Move things that move on the table (ie: balls)
//
//  Ret:  
// ------------------------------------------------------------------

int 
cTable::Move( void )
{
    return (lBalls->Move());
}

// ------------------------------------------------------------------
//  Func: Resize( x, y, w, h )
//  Desc: 
//
//  Ret:  
// ------------------------------------------------------------------

int
cTable::Resize( GLfloat x, GLfloat y, GLfloat w, GLfloat h )
{
    return 0;
}

// ------------------------------------------------------------------
//  Func: SetFlags( wire, tex )
//  Desc: Set wireframe and texture mapped use flags
//
//  Ret:  
// ------------------------------------------------------------------

int
cTable::SetFlags( int wire, int tex )
{
    iWire = wire;
    iTex = tex;

    lBalls->SetFlags( wire, tex );

    return 0;
}

// ------------------------------------------------------------------
//  Func: StickRot( deg )
//  Desc: Rotate cue stick 'deg' degrees around cue ball
//
//  Ret:  
// ------------------------------------------------------------------

int
cTable::StickRot( int deg )
{
    StickRotZ += deg;
    return 0;
}

// ------------------------------------------------------------------
//  Func: StickTr( dx )
//  Desc: Translate (pull back) stick dx distance.  Check for cue hit
//
//  Ret:  
// ------------------------------------------------------------------

int
cTable::StickTr( int dx )
{
    int iHit = 0;	// hit the ball
    GLfloat x,y,r;

    StickDY = dx * .25;
    
    StickTrY += StickDY;
    
    if ( StickTrY > 0 ) {
	iHit = 1;
	iStick = 0;			// hide stick
	StickTrY = STICK_DEF_POS;

	r = (M_PI/180)*(StickRotZ+90);
	x = cos( r ) * dx;
	y = sin( r ) * dx;

//cout << "ty: " << StickTrY << " dx: " << StickDY << endl;
//cout << "r: " << r << " x: " << x << " y: " << y << endl;

	lBalls->HitBall( 0, x, y );
	audio->PlayFile( CUE_AUDIO );
    }

    return iHit;
}

// ------------------------------------------------------------------
//  Func: StickToggle( val )
//  Desc: Toggle visibility flag of cue stick
//
//  Ret:  
// ------------------------------------------------------------------

int
cTable::StickToggle( int val )
{
    iStick = val;
    return 0;
}

int
cTable::setstatus( cVstatus *stat )
{
    if ( stat ) {
	lBalls->setstatus( stat );
    }
    return 0;
}
    
int
cTable::Reset( void )
{
    lBalls->Reset();

    return 0;
}
