// File:        colors.h
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
//              
// 
// $Revision: 1.8 $

/*
 * $Log: colors.h,v $
 * Revision 1.8  1999/12/06 09:21:18  paulmcav
 * added windos portability code/utils
 *
 * Revision 1.7  1999/12/06 04:49:24  paulmcav
 * added pooltable model loading / rendering.
 * Cue stick hit now works.  Timing is a bit better
 * Includes timing statistics
 *
 * Revision 1.6  1999/11/20 07:53:57  paulmcav
 * added texmap support, some more menu options, lighting, cleanup, etc.
 *
 * Revision 1.5  1999/11/18 02:02:23  paulmcav
 * added pool table drawing
 *
 * Revision 1.4  1999/11/10 08:19:19  paulmcav
 * added updates to ball management classes
 *
 * Revision 1.3  1999/11/04 02:21:43  paulmcav
 * fixed texmap problem, added colors to out of play balls.
 *
 * Revision 1.2  1999/11/03 17:28:55  paulmcav
 * added some colors for balls
 *
 * Revision 1.1  1999/10/25 06:33:21  paulmcav
 * working project with fancy windowing class for GL.
 * Tex maps sorta working, looks sharp though!
 *
 * 
*/

#ifndef _COLORS_H_
#define _COLORS_H_

#define DEF_WIRE 0 
#define DEF_TEX  1

/*
	list of GLfloating pt color values
*/

// glColor?f( )

#define WHITE	1.0,  1.0,  1.0
#define BLACK   0.0,  0.0,  0.0
#define GRAY	0.75, 0.75, 0.75
#define GRAY44	0.44, 0.44, 0.44
#define GRAY66  0.66, 0.66, 0.66
#define GRAY90	0.90, 0.90, 0.90

#define RED	1.0,  0.0,  0.0
#define ORANGE	1.0,  0.75, 0.0
#define YELLOW	1.0,  1.0,  0.0
#define GREEN	0.0,  1.0,  0.0
#define BLUE	0.0,  0.0,  1.0
#define PURPLE	0.75, 0.0,  1.0

#define FELT	0.0,  0.4,  0.0
#define BUMPER  0.0,  0.6,  0.0
#define WOOD	0.4,  0.2,  0.0

// ball colors
#define BALL0	0.8,  0.8,  0.8		// cue white!
#define BALL1	1.0,  1.0,  0.0		// yellow
#define BALL2	0.2,  0.4,  1.0		// blue
#define BALL3	1.0,  0.0,  0.0		// red
#define BALL4	0.8,  0.2,  0.8		// purple
#define BALL5	1.0,  0.4,  0.0		// orange
#define BALL6	0.2,  0.8,  0.0		// green
#define BALL7	0.8,  0.0,  0.0		// magenta (dark red)
#define BALL8	0.2,  0.2,  0.2		// black
#define BALL9	1.0,  1.0,  0.8		// s - yellow
#define BALL10	0.8,  1.0,  1.0		// s - blue
#define BALL11	1.0,  0.8,  0.8		// s - red
#define BALL12	1.0,  0.8,  1.0		// s - purple
#define BALL13	1.0,  0.8,  0.6		// s - orange
#define BALL14	0.6,  1.0,  0.8		// s - green
#define BALL15	1.0,  0.4,  0.4		// s - magenta

#endif


