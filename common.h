// File:        common.h
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:		cs630
// Desc:        common header file
//              
// 
// $Revision: 1.5 $

/*
 * $Log: common.h,v $
 * Revision 1.5  1999/12/17 19:36:39  paulmcav
 * added glXWaitGlx command to sync with display under linux
 *
 * Revision 1.4  1999/11/02 08:47:04  paulmcav
 * added menu / kb callback support; & help window
 *
 * Revision 1.3  1999/10/25 06:33:21  paulmcav
 * working project with fancy windowing class for GL.
 * Tex maps sorta working, looks sharp though!
 *
 * Revision 1.2  1999/10/13 16:13:11  paulmcav
 * state of project for turn in (proj2a)
 *
 * Revision 1.1  1999/10/13 05:22:43  paulmcav
 * template files for future classes
*/

#ifndef _COMMON_H_
#define _COMMON_H_

/*
  Includes common headers, and defines global's / types / etc.

  Header(s) included:

  GL/glut.h : all our GL functionality
*/

#define VERSION 	"0.9"
#define _VERSION	0.9

#ifdef _WIN32
#include <windows.h>
#endif

// library includes
#include <GL/glut.h>
#include <assert.h>

// local class / functions
#include "glpool.h"

/*
 * Constants / globals
 */

#endif

