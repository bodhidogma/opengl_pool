// File:        cTable.cc
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
// 
// $Revision: 1.2 $
/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  1999/11/10 08:19:19  paulmcav
 * added updates to ball management classes
 *
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
    return (lBalls->Move());
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


