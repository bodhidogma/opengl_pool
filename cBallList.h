// File:        cBallList.h
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
//              
// 
// $Revision: 1.3 $

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  1999/11/10 00:21:04  paulmcav
 * misc updates.  added ball(s) class to manage ball movement/ drawing.
 *
 * Revision 1.1  1999/11/08 20:21:40  paulmcav
 * added new ball management classes.
 *
 * 
*/

#ifndef _CBALLLIST_H_
#define _CBALLLIST_H_

#include "cBall.h"

enum bl_balls {
    b_que,
    b_yellow,
    b_blue,
/*    b_red,
    b_purple,
    b_orange,
    b_green,
    b_magenta,
    b_black,
    b_syellow,
    b_sblue,
    b_sred,
    b_spurple,
    b_sorange,
    b_sgreen,
    b_smagenta,
*/    b_count
};

/*
*/

class cBallList
{
private:
    cBall *balls;
    float xMin, xMax, yMin, yMax;	// table dimensions
    
protected:
public:
    cBallList( float x, float y, float w, float h );
    ~cBallList();
    
    int Draw();
    int Move();
    
    int Resize( float x, float y, float w, float h );
    
    int EnableBall( int num );
};

#endif

