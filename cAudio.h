// File:        cAudio.h
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

#ifndef _CAUDIO_H_
#define _CAUDIO_H_

/*
*/

class cAudio
{
private:
    int iAudioOk;
    int iAudCpid;
    
protected:
public:
    cAudio();
    ~cAudio();

    int PlayFile( char *fname );
};

#endif


