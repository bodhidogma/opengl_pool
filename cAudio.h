// File:        cAudio.h
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
//              
// 
// $Revision: 1.2 $

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  1999/11/20 21:41:30  paulmcav
 * added audio playback support.
 *
 * 
*/

#ifndef _CAUDIO_H_
#define _CAUDIO_H_

/*
*/

#ifdef _WIN32
#  define BUMPER_AUDIO	"data/bumper.wav"
#  define CUE_AUDIO	"data/hit_cue.wav"
#else
#  define BUMPER_AUDIO	"data/bumper.au"
#  define CUE_AUDIO	"data/hit_cue.au"
#endif

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


