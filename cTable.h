// File:        cTable.h
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
//              
// 
// $Revision: 1.4 $

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.3  1999/11/20 07:53:56  paulmcav
 * added texmap support, some more menu options, lighting, cleanup, etc.
 *
 * Revision 1.2  1999/11/19 22:36:57  paulmcav
 * Balls displaying on the table, and more!
 *
 * Revision 1.1  1999/11/10 08:19:19  paulmcav
 * added updates to ball management classes
 *
 * 
*/

#ifndef _CTABLE_H_
#define _CTABLE_H_

#include "cBallList.h"

/*
*/

enum tl_tables {
    tl_solid,
    tl_wire,
    tl_count
};

class cTable
{
private:
    cBallList *lBalls;				// table balls
    float xMin, xMax, yMin, yMax;
    int   iWire, iTex;
    int   dlist;

protected:
    int  make_table( int wire, int lnum );

public:
    cTable( float x, float y, float w, float h );
    ~cTable();

    int Draw( void );
    int Move( void );

    int Resize( float x, float y, float w, float h );
    int SetFlags( int wire, int tex );
};

#endif


