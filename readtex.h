// File:        readtex.h
// Author:      Paul McAvoy <paulmcav@auctomation.com>
// Org:
// Desc:        
//              
// 
// $Revision: 1.1 $

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1.1.1  1999/09/24 15:42:56  paulmcav
 * Imported sources
 *
 * 
*/

#ifndef _READTEX_H_
#define _READTEX_H_

#include <stdio.h> 

/*
 * 
*/

/*
** RGB Image Structure
*/

typedef struct _TK_RGBImageRec {
   GLint sizeX, sizeY;
   GLint components;
   unsigned char *data;
} TK_RGBImageRec;



/******************************************************************************/

typedef struct _rawImageRec {
    unsigned short imagic;
    unsigned short type;
    unsigned short dim;
    unsigned short sizeX, sizeY, sizeZ;
    unsigned long min, max;
    unsigned long wasteBytes;
    char name[80];
    unsigned long colorMap;
    FILE *file;
    unsigned char *tmp, *tmpR, *tmpG, *tmpB, *tmpA;
    unsigned long rleEnd;
    GLuint *rowStart;
    GLint *rowSize;
} rawImageRec;

/******************************************************************************/


void ConvertShort(unsigned short *array, long length);

void ConvertLong(GLuint *array, long length);

rawImageRec *RawImageOpen(const char *fileName);

void RawImageClose(rawImageRec *raw);

void RawImageGetRow(rawImageRec *raw, unsigned char *buf, int y, int z);

void RawImageGetData(rawImageRec *raw, TK_RGBImageRec *final);
    
TK_RGBImageRec *tkRGBImageLoad(const char *fileName);
    
void FreeImage( TK_RGBImageRec *image );
    
GLboolean LoadRGBMipmaps( const char *imageFile, GLint intFormat );
    
GLubyte *LoadRGBImage( const char *imageFile, GLint *width, GLint *height,
                       GLenum *format );
    

#endif


