// File:        glpool.h
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
//              
// 
// $Revision: 1.2 $

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  1999/10/19 04:19:37  paulmcav
 * start
 *
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
void keypress ( unsigned char key, int x, int y );
void specialkeys ( int key, int x, int y );
void mouseclick ( int b, int s, int mx, int my );

void quit_game( void );
    

#endif


