// File:        cBallList.cc
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
// 
// $Revision: 1.1 $
/*
 * $Log: not supported by cvs2svn $
 */

#include "cBallList.h"

#include <assert.h>

// ------------------------------------------------------------------
//  Func: 
//  Desc: 
//
//  Ret:  
// ------------------------------------------------------------------

cBallList::cBallList() :
    balls(0)
{
    balls = new cBall[16];
    assert( balls );
}

cBallList::~cBallList()
{
    if ( balls )
	delete balls;
}

int
cBallList::Draw()
{
    return 0;
}

int
cBallList::Move()
{
    return 0;
}
    
int
cBallList::
