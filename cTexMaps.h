// File:        cTexMaps.h
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
//              
// 
// $Revision: 1.2 $

/*
 * $Log: cTexMaps.h,v $
 * Revision 1.2  1999/11/20 07:53:57  paulmcav
 * added texmap support, some more menu options, lighting, cleanup, etc.
 *
 * Revision 1.1  1999/10/25 06:33:21  paulmcav
 * working project with fancy windowing class for GL.
 * Tex maps sorta working, looks sharp though!
 *
 * 
*/

#ifndef _CTEXMAPS_H_
#define _CTEXMAPS_H_

#include <GL/glut.h>

enum tex_list{
    tex_intro,
    tex_b1,
    tex_b2,
    tex_b3,
    tex_b4,
    tex_b5,
    tex_b6,
    tex_b7,
    tex_b8,
    tex_b9,
    tex_b10,
    tex_b11,
    tex_b12,
    tex_b13,
    tex_b14,
    tex_b15,
    tex_cnt
};

/*
*/

class cTexMaps
{
private:
    GLuint texName[ tex_cnt+1 ];

protected:
    
public:
    cTexMaps( void );
    ~cTexMaps();
	
    int Init( void );
    int Init2( void );
    
    int Bind( GLenum type, tex_list name );
};

#endif


