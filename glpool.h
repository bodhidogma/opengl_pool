// File:        glpool.h
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

#ifndef _GLPOOL_H_
#define _GLPOOL_H_

#include <GL/glut.h>

/*
 * misc functions for support of glpool game
*/

void init ( void );
void idle ( void );
void display ( void );
void reshape ( int w, int h );
void keypress ( unsigned char key, int x, int y );
void specialkeys ( int key, int x, int y );
void mouseclick ( int b, int s, int mx, int my );

int  glputs( GLfloat x, GLfloat y, char *buff );
void quit_game( void );
    

#endif


