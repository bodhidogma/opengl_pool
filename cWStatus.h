// File:        cWStatus.h
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

#ifndef _CWSTATUS_H_
#define _CWSTATUS_H_

#include "glWindow.h"

#define W_STATUS_HEIGHT	26

/*
*/

class cWStatus : public glWindow
{
private:
    GLuint myLists;
    
protected:
    char *cMessage;
    int  iBallList[15];
    int  iBallCnt;
    
public:
    cWStatus( glWindow *p );
    ~cWStatus();
    
    int Display( void );
    int Resize( int w, int h );

    int Message( char *msg );

    int DrawBallQ( void );

    int ResetBalls( void );
    int AddBalls( int ballnum );
	
};

#endif


