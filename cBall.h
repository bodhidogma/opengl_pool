// File:        cBall.h
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

#ifndef _CBALL_H_
#define _CBALL_H_

/*
*/

class cBall
{
private:
    float pos[3];		// x,y,z
    float vel[3];
    float accel[3];
    float momentum;
    float mass;
    float torque;
    float friction[2];	// static, kinetic
    
protected:
public:
    cBall();
    ~cBall();
    
    int Draw();
    int Move();

};


#endif

