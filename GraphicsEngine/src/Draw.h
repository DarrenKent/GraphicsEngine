/*
*
*	Graphics Engine
*	By: Darren Kent
*
*/

#ifndef _DRAW_
#define _DRAW_

#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <string>

// Basic Drawing methods
void DrawCircle2D( GLfloat x, GLfloat y, GLfloat radius, int slices );
void DrawPartialCircle2D( GLfloat x, GLfloat y, GLfloat radius, float start, float end, int slices );
void DrawCube3D( GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2 );
void DrawRectangle2D( GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2 );
void DrawRectangleOutline2D( GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat thickness );
void DrawSphere3D( GLfloat x, GLfloat y, GLfloat z, GLfloat radius, int slices, int rows );
void DrawTriangle2D( GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3 );
void DrawText2D( const char* text , GLuint fontId, GLfloat x, GLfloat y );

#endif // _DRAW_