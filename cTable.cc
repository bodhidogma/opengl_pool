// File:        cTable.cc
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
// 
// $Revision: 1.1 $
/*
 * $Log: not supported by cvs2svn $
 */

#include "cTable.h"

#include <assert.h>

cTable::cTable( float x, float y, float w, float h )
{
    lBalls = new cBallList( x,y, w,h );		// put balls on the table!
    assert( lBalls );
    
}

cTable::~cTable()
{
    if ( lBalls )
	delete lBalls;
}

int
cTable::Draw()
{
    lBalls->Draw();
    return 0;
}

int 
cTable::Move()
{
    lBalls->Move();
    return 0;
}

int
cTable::Resize( float x, float y, float w, float h )
{
    return 0;
}





// ------------------------------------------------------------------
//  Func: 
//  Desc: 
//
//  Ret:  
// ------------------------------------------------------------------


