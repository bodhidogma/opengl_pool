// File:        glUtil.h
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

#ifndef _GLUTIL_H_
#define _GLUTIL_H_

#include <GL/glut.h>

/*
 * list of misc utility functions for using gl
*/


int glputs( GLfloat x, GLfloat y, char *buff );
int glshadebox( int x, int y, int w, int h, int raised=1 );
int glshadebar( int x, int y, int w, int h, int raised=1 );

#endif


