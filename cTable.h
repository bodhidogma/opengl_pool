// File:        cTable.h
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

#ifndef _CTABLE_H_
#define _CTABLE_H_

#include "cBallList.h"

/*
*/

class cTable
{
private:
    cBallList *lBalls;				// table balls
    float xMin, xMax, yMin, yMax;

protected:
public:
    cTable( float x, float y, float w, float h );
    ~cTable();

    int Draw();
    int Move();

    int Resize( float x, float y, float w, float h );
};

#endif


