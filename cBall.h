// File:        cBall.h
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

#ifndef _CBALL_H_
#define _CBALL_H_

/*
*/

class cBall
{
private:
    GLfloat pos[3];		// x,y,z
    GLfloat vel[3];
    GLfloat accel[3];
    GLfloat momentum;
    GLfloat mass;
    GLfloat torque;
    GLfloat friction[2];	// static, kinetic
    
protected:
public:
    cBall();
    ~cBall();
    
    Draw();
    Move();

};


#endif

