
/* **********************************************************************

Author:  Scott L. Emery
Date:    11/2/99
Project: Virtual Billiards

DESCRIPTION:

Test program for a texture-mapped billiards ball
  
*********************************************************************** */

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

GLuint balllist;
GLuint balltexname[1]; 		//Just one texture map for now

/*  Initial operating procedures of program.  Includes display list, background
color, and lighting parameters. */
void init(void) 
{
   GLUquadricObj *q = gluNewQuadric(); 

   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);
  
  //Just generate a single display list for now
   balllist = glGenLists(1);
   glNewList(balllist, GL_COMPILE);
   {
       gluQuadricNormals(q, GL_SMOOTH);
       gluQuadricTexture(q, GL_TRUE);
       gluSphere(q, 1.0, 20, 16);
   }
   glEndlist();
   
   gluDeleteQuadric(q);
   
  //Light source properties on ball
   GLfloat light0_ambience[]= {0.3, 0.3, 0.3, 1.0};
   GLfloat light0_diffuse[]= {0.8, 0.8, 0.8, 1.0};
   GLfloat light0_specular[]= {1.0, 1.0, 1.0, 1.0};
   GLfloat light0_position[]= {2.0, 2.0, 2.0, 1.0};

   glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambience);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
   glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
   glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

  //Texture parameters, coordinate generation, and texture binding
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
 
   glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
   glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
   
   glGenTextures(1, balltexname);
 
   glBindTexture(GL_TEXTURE_2D, balltexname[0]);
   if(!LoadRGBMipmaps("balltex1.rgb", GL_RGB))
   {
       printf("Woops! Error loading texture image.");
       exit(1);
   }
   
  //State capabilities  
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
   glDisable(GL_POLYGON_SMOOTH);
}


/*  The registered GLUT display callback function.  Includes procedures to 
render the scene.  */
void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glPushMatrix();
   glColor3f(0.5, 0.5, 0.5);.
   
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, balltexname[1]);
   glCallList(balllist);

   glDisable(GL_TEXTURE_2D);
   glPopMatrix();
 }


/*  Responsible for handling the resizing of the window.  */
void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective (60.0, 1.0, 1.5, 20.0);
   glMatrixMode (GL_MODELVIEW);
}



/*  Contains routines necessary for initializing the window, display callback,
and running the program.  */
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (70, 50);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutMainLoop();
   return 0;
}
