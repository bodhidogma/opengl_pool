// File:        cWMain.cc
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
// 
// $Revision: 1.1 $
/*
 * $Log: not supported by cvs2svn $
 */

#include "cWMain.h"
#include "colors.h"

#include "glUtil.h"
#include "cTexMaps.h"
#include "common.h"

#include "glpng.h"

#include "cWStatus.h"

#include <iostream.h>

extern cTexMaps *texList;

//extern GLuint texName[ tex_cnt+1 ];

// ------------------------------------------------------------------
//  Func: 
//  Desc: 
//
//  Ret:  
// ------------------------------------------------------------------

cWMain::cWMain( char *title, int w, int h, unsigned int mode ) :
	glWindow( title, w, h, mode )
{
    glClearColor( BLACK, 1.0 );
    
    glGenTextures( 1, &texIntro );

    glBindTexture( GL_TEXTURE_2D, texIntro );

//    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
//    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    
    // png is upside down!
    if ( !pngLoad( "data/intro.png", PNG_NOMIPMAP, PNG_SOLID, NULL )) {
	cerr << "Error: couldn't load texture image! " << tex_intro <<  endl;
	exit(1);
    }
}

cWMain::~cWMain()
{
}

int
cWMain::Display( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
    
    glEnable( GL_TEXTURE_2D );
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
//    glBindTexture( GL_TEXTURE_2D, texList->Id( tex_intro ) );
    glBindTexture( GL_TEXTURE_2D, texIntro );
//    texList->Bind( GL_TEXTURE_2D, tex_intro );
    
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
 
    glTranslatef( 100, 100, -20.0 );
    
    glColor3ub( 153, 184, 166 );
    glutWireSphere( 40.1, 20, 16 );
    
//    cout << "Display: " << iMyNum << endl;

    glPopMatrix();
    
    glutSwapBuffers();
    glFlush();
    
    return 0;
}

int
cWMain::Resize( int w, int h )
{
//    cout <<"Resize: "<< iMyNum <<" w: "<< w <<" h: "<< h <<endl;
    
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    
    h -= W_STATUS_HEIGHT;
    
    vX = wXpos;
    vY = wYpos;
    vW = (float)w;
    vH = (float)h;
    
    glViewport( 0,0, w,h );
    glScissor( 0,0, w,h );

    glOrtho( 0.0, vW, 0.0, vH, -20.0, 20.0 );
//    gluPerspective( 60.0, wWidth/wHeight, 1.0, 40.0 );

    glShadeModel( GL_FLAT );
    
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
//    gluLookAt( 0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );
	
    
    return 0;
}

int
cWMain::Keys( unsigned char key, int mx, int my )
{
    return 0;
}


int
cWMain::Intro( void )
{
    glEnable( GL_TEXTURE_2D );
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
//    glBindTexture( GL_TEXTURE_2D, texList->Id( tex_intro ) );
    
    glBegin( GL_QUADS );
    {
	glTexCoord2f( 0.0, 1.0 ); glVertex3f( wXpos+10, wYpos+10, 0.0 );
	glTexCoord2f( 0.0, 0.0 ); glVertex3f( wYpos+10, wHeight-10, 0.0 );
	glTexCoord2f( 1.0, 0.0 ); glVertex3f( wWidth-10, wHeight-10, 0.0 );
	glTexCoord2f( 1.0, 1.0 ); glVertex3f( wWidth-10, wYpos+10, 0.0 );
    }
    glEnd();

    glDisable( GL_TEXTURE_2D );
 
    glutSwapBuffers();
    
    return 0;
}
