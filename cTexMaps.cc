// File:        cTexMaps.cc
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
// 
// $Revision: 1.3 $
/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  1999/10/29 04:31:21  paulmcav
 * added viewport class to manage glviewports in a window.
 * Also enabled texture mapping class!
 *
 * Revision 1.1  1999/10/25 06:33:21  paulmcav
 * working project with fancy windowing class for GL.
 * Tex maps sorta working, looks sharp though!
 *
 */

#include "cTexMaps.h"
#include "glpng.h"

#include <iostream.h>

//    GLuint texName[ tex_cnt+1 ];
    
// ------------------------------------------------------------------
//  Func: 
//  Desc: 
//
//  Ret:  
// ------------------------------------------------------------------

cTexMaps::cTexMaps( void )
{
    glGenTextures( tex_cnt, texName );
}

cTexMaps::~cTexMaps()
{
}

int
cTexMaps::Init( void )
{
//    cout << "init" << endl;

//    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
//    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    
    glBindTexture( GL_TEXTURE_2D, texName[ tex_intro ] );

    // png is upside down!
    if ( !pngLoad( "data/intro.png", PNG_NOMIPMAP, PNG_SOLID, NULL )) {
	cerr << "Error: couldn't load texture image! " << tex_intro <<  endl;
	exit(1);
    }

    return 0;
}

int
cTexMaps::Bind( GLenum type, tex_list name )
{
    glBindTexture( type, texName[ name ] );

    return texName[ name ];
}

