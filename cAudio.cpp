// File:        cAudio.cc
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
// 
// $Revision: 1.5 $
/*
 * $Log: cAudio.cc,v $
 * Revision 1.5  1999/12/08 07:05:25  paulmcav
 * added sound / timing support for windos version
 *
 * Revision 1.4  1999/12/06 09:21:17  paulmcav
 * added windos portability code/utils
 *
 * Revision 1.3  1999/11/24 18:58:48  paulmcav
 * more manipulations for ball movement.
 *
 * Revision 1.2  1999/11/22 22:17:08  paulmcav
 * enabled ball bouncing
 *
 * Revision 1.1  1999/11/20 21:41:30  paulmcav
 * added audio playback support.
 *
 */

#include "cAudio.h"
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#ifdef _WIN32
#  include <windows.h>
#  include <mmsystem.h>
#  include <io.h>
#else
#  include <unistd.h>
#endif
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#include <string.h>

#include <iostream.h>

#ifdef _WIN32
#define fdopen _fdopen
#define open _open
#define read _read
#define write _write
#define close _close
#endif

// ------------------------------------------------------------------
//  Func: 
//  Desc: 
//
//  Ret:  
// ------------------------------------------------------------------

#define AUDIO_FILE	"/dev/audio"

static int ph1[2];		// audio pipe

void DevAudio( void );


cAudio::cAudio()
{
    int f1 = 0;

    iAudCpid = 0;
#ifdef _WIN32
	iAudioOk = 1;
#else
    iAudioOk = 0;
    if ( (f1 = open( AUDIO_FILE, O_WRONLY )) != -1 ) {
	iAudioOk = 1;

	close( f1 );
	pipe( ph1 );

	if ( !(iAudCpid = fork()) ) {
	    DevAudio();
	    exit(1);
	}
    }
#endif
}

cAudio::~cAudio()
{
#ifndef _WIN32
    if ( iAudCpid )
	kill( iAudCpid, SIGINT );
#endif
}

int
cAudio::PlayFile( char *file )
{
    char *buff = NULL;
    int len = 0;
    
    if ( iAudioOk ) {
#ifdef _WIN32
	PlaySound( file, NULL, SND_FILENAME | SND_ASYNC );
#else
	buff = new char[ strlen(file)+2 ];
	strcpy( buff, file );
	strcat( buff, "\n" );
	
	len = write( ph1[1], buff, strlen( buff ) );
#endif
    }

    return iAudioOk;
}

void
DevAudio( void )
{
    FILE *pin;
    char sbuff[4096];
    char buff[1024];
    int  blen;
    int  fin, fout;

    pin = fdopen( ph1[0], "rb" );
    
    while( 1 ) {
	buff[0] = '\0';
	fgets( buff, 1024, pin );
	buff[ strlen(buff)-1 ] = 0;

	if ( (fin = open( buff, O_RDONLY )) != -1 ) {
	    if ( (fout = open( AUDIO_FILE, O_WRONLY )) != -1 ) {

		while( (blen = read( fin, sbuff, 4096 )) )
		    write( fout, sbuff, blen );

		close( fout );
	    }
	    close( fin );
	}
    }
}

