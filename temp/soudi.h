//****************************************************************
// FILE: Proj1.h, the header file for Proj1.c                    *
//                                                               *
// AUTHOR: Soudabeh Maher                                        *
//                                                               *
// USAGE COMMENTS: Link the file with opengl32.lib, glut32.lib,  *
//                 and glu32.lib.                                *
//                                                               *
// LIBRARIES:                                                    *
//                 gl/glut.h -- opengl library                   *
//                 stdio.h   -- standard IO library              *
//                 conio.h   -- console IO library               *
//                                                               *
// FUNCTIONS/METHODS DEFINED:                                    *
//     void init       -- initializes light & background color   *
//     void display    -- displays & rotates the sphere          *
//     void reshape    -- reshapes the object according to width *
//                        & height of the output window          *
//     void SpinSphere -- moves the object forward               *
//     void Back       -- moves the object backward              *
//     void Mouse      -- defines the behavior of mouse clicks   *
//     void Keyboard   -- defines the behvior of differnt keys   *
//     void PlaySound  -- plays sound                            *
//                                                               *
// GLOBAL VARIABLES USED:                                        *
//     static GLint   clockWise   -- for direction of rotation   *          
//     static GLfloat angle       -- angle of rotation           *
//     static GLfloat zaxis       -- position of object on Z-axis*
//     static GLint   maxSizeFlag -- object in max size          *
//                                                               *
// GENERAL COMMENTS:   The first project in opengl               *
//                                                               *
//****************************************************************

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <conio.h>

static GLint   clockWise     = 1;
static GLfloat angle         = 0.0;
static GLfloat zaxis         = 4.0f;
static GLint   maxSizeFlag   = 0;
static int     direction     = 1;
static GLfloat size = 3.0f;
static GLint   subWidth  = 300;
static GLint   subHeight = 300;

//****************************************************************
// Init : initializes the kind and position of the light and the *
//         background color.                                     *
//                                                               *
//****************************************************************

void Init(void);

//****************************************************************
// Display: displays the object on the output window.            *
//          It rotates the object too.                           *
//                                                               *
//****************************************************************

void Display(void);

//****************************************************************
// Reshape: reshapes the object according to the changes in width*
//          and height of the output window.                     *
//                                                               *
//****************************************************************

void Reshape(int  w, int h);

//****************************************************************
// MoveForward: spins and moves the object forward by changing   *
//              its position on z_axis.                          *
//                                                               *
//****************************************************************

void MoveForward(void);

//****************************************************************
// MoveBackward: spins and moves the object backward by changing *
//               its position on z_axis.                         *
//                                                               *
//****************************************************************

void MoveBackward(void);

//****************************************************************
// Mouse: defines the effects of mouse bottons on the movement   *
//        of the object.                                         *
//        right btn  -- rotate twice faster                      * 
//        middle btn -- rotate faster and faster with each btn   *
//                      click                                    *
//        left btn   -- rotate in oposite direction twice faster *
//                                                               *
//****************************************************************

void Mouse(int btn, int state, int x, int y);

void mainMenu(int id);

void CreateSub(void);

void reshape2(int w, int h);

void DisplayInfo(void);

void tick(void);

void output(int x, int y, char *string);

//****************************************************************
// Keyboard: defines the effects of different keys on the        *
//           movement of the object.                             *
//           r or R : repeats the forward motion                 *
//           b or B : repeats the backward motion                *
//           i or I : gives a little menu for the program.       *
//           q or Q : quits the program                          *
//                                                               *
//****************************************************************

void Keyboard(unsigned char key, int x, int y);

//****************************************************************
// BallType struct
//
// float xCo -- x coordinate
// float yCo -- y coordinate
// float zCo -- z coordinate
// float r   -- radius
// float m   -- mass of particle
// float v   -- velocity of particle
// float f   -- force acting on paricle
//
//****************************************************************

struct BallType
{
	float xCo;
	float yCo;
	float zCo;
	float r; 
	float m;
    float v;  
    float f;
};
