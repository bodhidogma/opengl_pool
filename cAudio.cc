// File:        cAudio.cc
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
// 
// $Revision: 1.1 $
/*
 * $Log: not supported by cvs2svn $
 */

#include "cAudio.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#include <string.h>

#include <iostream.h>

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
    int f1;

    iAudCpid = 0;
    if ( (f1 = open( AUDIO_FILE, O_RDONLY )) == -1 )
	iAudioOk = 0;
    else {
	iAudioOk = 1;

	close( f1 );
	pipe( ph1 );

	if ( !(iAudCpid = fork()) ) {
	    DevAudio();
	    exit(1);
	}
    }
}

cAudio::~cAudio()
{
    if ( iAudCpid )
	kill( iAudCpid, SIGINT );
}

int
cAudio::PlayFile( char *file )
{
    char *buff;
    int len;
    
    if ( iAudioOk ) {

	buff = new char[ strlen(file)+2 ];
	strcpy( buff, file );
	strcat( buff, "\n" );
	
	len = write( ph1[1], buff, strlen( buff ) );
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

