// File:        glUtil.h
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
//              
// 
// $Revision: 1.4 $

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.3  1999/11/18 01:12:19  paulmcav
 * added help menu again, intro win, got correct fovy
 *
 * Revision 1.2  1999/11/11 20:38:31  paulmcav
 * working on perspective use
 *
 * Revision 1.1  1999/10/25 06:33:21  paulmcav
 * working project with fancy windowing class for GL.
 * Tex maps sorta working, looks sharp though!
 *
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
int glshadebox( GLfloat x, GLfloat y, GLfloat w, GLfloat h, int raised=1 );
int glshadebar( int x, int y, int w, int h, int raised=1 );

GLfloat calcangle( GLfloat size, GLfloat dist );

int glScale( GLfloat scale, GLfloat *list, int start, int step, int cnt );


#endif


