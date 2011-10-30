// File:        cTexMaps.cc
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
// 
// $Revision: 1.6 $
/*
 * $Log: cTexMaps.cc,v $
 * Revision 1.6  1999/11/20 07:53:57  paulmcav
 * added texmap support, some more menu options, lighting, cleanup, etc.
 *
 * Revision 1.5  1999/11/10 19:47:18  paulmcav
 * fixed erro message on RH6.0
 *
 * Revision 1.4  1999/11/04 02:21:43  paulmcav
 * fixed texmap problem, added colors to out of play balls.
 *
 * Revision 1.3  1999/11/03 17:28:55  paulmcav
 * added some colors for balls
 *
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

//GLuint texName[ tex_cnt+1 ];
    
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

#ifndef _USE_OLD_IOSTREAMS
using namespace std;
#endif

int
cTexMaps::Init( void )
{
    glBindTexture( GL_TEXTURE_2D, texName[ tex_intro ] );

    if ( !pngLoad( "data/intro.png" , PNG_NOMIPMAP, PNG_SOLID, NULL )) {
	cerr << "Error: couldn't load texture image! "
	    << (int)tex_intro <<  endl;
	exit(1);
    }

    // init texture parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    
    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL );
    glTexGeni( GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );
    glTexGeni( GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );
    
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST );

    return 0;
}

int
cTexMaps::Init2( void )
{
    int cnt;
    char flist[][24] = {
	{ "data/intro.png" },
	{ "data/1.png" },
	{ "data/2.png" },
	{ "data/3.png" },
	{ "data/4.png" },
	{ "data/5.png" },
	{ "data/6.png" },
	{ "data/7.png" },
	{ "data/8.png" },
	{ "data/9.png" },
	{ "data/10.png" },
	{ "data/11.png" },
	{ "data/12.png" },
	{ "data/13.png" },
	{ "data/14.png" },
	{ "data/15.png" }
    };

/*    	glBindTexture( GL_TEXTURE_2D, texName[ 0 ] );
    	if ( !pngLoad( flist[0], PNG_NOMIPMAP, PNG_SOLID, NULL )) {
	    cerr << "Error: couldn't load texture image! "
	    	<< cnt <<  endl;
	    exit(1);
	}
    	glBindTexture( GL_TEXTURE_2D, texName[ 1 ] );
    	if ( !pngLoad( flist[1], PNG_NOMIPMAP, PNG_SOLID, NULL )) {
	    cerr << "Error: couldn't load texture image! "
	    	<< cnt <<  endl;
	    exit(1);
	}
*/	
    // png is upside down!
    for ( cnt=1; cnt< tex_cnt; cnt++ ){
    	glBindTexture( GL_TEXTURE_2D, texName[ cnt ] );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL );
	glTexGeni( GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );
	glTexGeni( GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST );
    
    	if ( !pngLoad( flist[cnt], PNG_NOMIPMAP, PNG_SOLID, NULL )) {
	    cerr << "Error: couldn't load texture image! "
	    	<< cnt <<  endl;
	    exit(1);
	}
    }

    return 0;
}

int
cTexMaps::Bind( GLenum type, tex_list name )
{
    glBindTexture( type, texName[ name ] );

    return texName[ name ];
}

