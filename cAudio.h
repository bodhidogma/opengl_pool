// File:        cAudio.h
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
//              
// 
// $Revision: 1.4 $

/*
 * $Log: cAudio.h,v $
 * Revision 1.4  1999/12/08 07:05:25  paulmcav
 * added sound / timing support for windos version
 *
 * Revision 1.3  1999/12/08 01:08:16  paulmcav
 * added more stuff!
 *
 * Revision 1.2  1999/12/06 21:19:46  paulmcav
 * updated game to allow collisions between balls
 *
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
#  define HIT_AUDIO	"data/ball_hit.wav"
#  define SUNK_AUDIO	"data/sunk_ball.wav"
#else
#  define BUMPER_AUDIO	"data/bumper.au"
#  define CUE_AUDIO	"data/hit_cue.au"
#  define HIT_AUDIO	"data/ball_hit.au"
#  define SUNK_AUDIO	"data/sunk_ball.au"
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


