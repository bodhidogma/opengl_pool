// File:        cBallList.h
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
//              
// 
// $Revision: 1.2 $

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  1999/11/08 20:21:40  paulmcav
 * added new ball management classes.
 *
 * 
*/

#ifndef _CBALLLIST_H_
#define _CBALLLIST_H_

#include "cBall.h"

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

