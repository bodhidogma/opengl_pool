// File:        cTexMaps.h
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
//              
// 
// $Revision: 1.1 $

/*
 * $Log: not supported by cvs2svn $
 * 
*/

#ifndef _CTEXMAPS_H_
#define _CTEXMAPS_H_

#include <GL/glut.h>

enum tex_list{
    tex_intro,
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
    
    int Bind( GLenum type, tex_list name );
};

#endif


