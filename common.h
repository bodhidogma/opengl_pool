// File:        common.h
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:		cs630
// Desc:        common header file
//              
// 
// $Revision: 1.2 $

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  1999/10/13 05:22:43  paulmcav
 * template files for future classes
*/

#ifndef _COMMON_H_
#define _COMMON_H_

/*
  Includes common headers, and defines global's / types / etc.

  Header(s) included:

  GL/glut.h : all our GL functionality
  readtex.h : support fuctions from sgi to read bitmap files and such
    cMenu.h : simple menu support functions
    cHelp.h : help screen functions
*/

// library includes
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

// local class / functions
#include "glpool.h"
#include "cMenu.h"
#include "cHelp.h"

// external support functions
#include "readtex.h"

/*
 * Constants / globals
 */
//#ifndef __CH_EXTERNS__
#define __CH_EXTERNS__

static int help = 0;

//#endif

#endif

