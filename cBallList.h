// File:        cBallList.h
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

#ifndef _CBALLLIST_H_
#define _CBALLLIST_H_

#include "cBall.h"

/*
*/

class cBallList
{
private:
    cBall *balls;
    
protected:
public:
    cBalllist();
    ~cBallList();
    
    int Draw();
    int Move();
    
    int EnableBall( int num );
};

#endif

