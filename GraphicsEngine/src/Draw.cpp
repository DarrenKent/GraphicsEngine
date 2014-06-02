/*
*
*	Graphics Engine
*	By: Darren Kent
*
*/

#include <math.h>
#include <iostream>

#include "Debug.h"
#include "Draw.h"

void DrawCircle2D( GLfloat x, GLfloat y, GLfloat radius, int slices ) {
	glBegin( GL_TRIANGLE_FAN );
	glVertex2f( x, y );
	for ( int iTri = 0; iTri < slices + 1; iTri++ ) {
		GLfloat tAlpha = (GLfloat)( 2.0 * 3.1415926 * iTri / slices );
		glVertex2f( x+radius * cos( tAlpha ), y + radius * sin( tAlpha ) );
	}
	glEnd();
	
}

void DrawPartialCircle2D( GLfloat x, GLfloat y, GLfloat radius, float start, float end, int slices ) {
	glBegin( GL_TRIANGLE_FAN );
	glVertex2f( x, y );
	for ( int iTri = 0; iTri < slices + 1; iTri++ ) {
		GLfloat tAlpha = (GLfloat)( start + ( ( end - start ) / slices ) * iTri );
		glVertex2f( x+radius * cos( tAlpha ), y + radius * sin( tAlpha ) );
	}
	glEnd();
}

void DrawCube3D( GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2 ) {
	glPushMatrix();
	glEnable( GL_COLOR_MATERIAL );
	glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
	glBegin( GL_QUADS );

	glNormal3f( 0.0f, 1.0f, 0.0f );
	glVertex3f( x1, y1, z1 );
	glVertex3f( x1, y1, z2 );
	glVertex3f( x2, y1, z2 );
	glVertex3f( x2, y1, z1 );

	glNormal3f( 0.0f, 0.0f, 1.0f );
	glVertex3f( x1, y1, z1 );
	glVertex3f( x1, y2, z1 );
	glVertex3f( x2, y2, z1 );
	glVertex3f( x2, y1, z1 );

	glNormal3f( 1.0f, 0.0f, 0.0f );
	glVertex3f( x1, y1, z1 );
	glVertex3f( x1, y1, z2 );
	glVertex3f( x1, y2, z2 );
	glVertex3f( x1, y2, z1 );

	glNormal3f( 0.0f, 0.0f, -1.0f );
	glVertex3f( x1, y1, z2 );
	glVertex3f( x2, y1, z2 );
	glVertex3f( x2, y2, z2 );
	glVertex3f( x1, y2, z2 );

	glNormal3f( -1.0f, 0.0f, 0.0f );
	glVertex3f( x2, y1, z1 );
	glVertex3f( x2, y2, z1 );
	glVertex3f( x2, y2, z2 );
	glVertex3f( x2, y1, z2 );

	glNormal3f( 0.0f, -1.0f, 0.0f );
	glVertex3f( x1, y2, z1 );
	glVertex3f( x1, y2, z2 );
	glVertex3f( x2, y2, z2 );
	glVertex3f( x2, y2, z1 );

	glEnd();
	glDisable( GL_COLOR_MATERIAL );
	glPopMatrix();
}

void DrawRectangle2D( GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2 ) {
	glBegin( GL_QUADS );
	glTexCoord2f( 0.0f, 0.0f );
	glVertex2f( x1, y1 );
	glTexCoord2f( 0.0f, 1.0f );
	glVertex2f( x1, y2 );
	glTexCoord2f( 1.0f, 1.0f );
	glVertex2f( x2, y2 );
	glTexCoord2f( 1.0f, 0.0f );
	glVertex2f( x2, y1 );
	glEnd();
	
}

void DrawRectangleOutline2D( GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat thickness ){
	glLineWidth( thickness );
	glBegin( GL_LINES );
	glVertex2f( x1, y1 );
	glVertex2f( x2, y1 );
	
	glVertex2f( x2, y1 );
	glVertex2f( x2, y2 );

	glVertex2f( x2, y2 );
	glVertex2f( x1, y2 );

	glVertex2f( x1, y2 );
	glVertex2f( x1, y1 );
	glEnd();
	
}

void DrawSphere3D( GLfloat x, GLfloat y, GLfloat z, GLfloat radius, int slices, int rows ) {
	glPushMatrix();
	glEnable( GL_COLOR_MATERIAL );
	glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
	GLUquadricObj* tQuadratic;
	glTranslatef( x, y, z );
	tQuadratic = gluNewQuadric();
	gluQuadricNormals( tQuadratic, GLU_SMOOTH );
	gluQuadricTexture( tQuadratic, GL_TRUE );
	gluSphere( tQuadratic, radius, slices, rows );
	gluDeleteQuadric( tQuadratic );
	glDisable( GL_COLOR_MATERIAL );
	glPopMatrix();
	
}

void DrawTriangle2D( GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3 ) {
	glBegin( GL_TRIANGLES );
		glVertex2f( x1, y1 );
		glVertex2f( x2, y2 );
		glVertex2f( x3, y3 );
	glEnd();
	
}

void DrawText2D( const char* text , GLuint fontId, GLfloat x, GLfloat y ) {
	if( fontId >= 0 ) {
		glPushMatrix();
			glTranslatef( 0.0f, 0.0f, 1.0f );
			glRasterPos2f( x, y );

			char tString[256];		
			va_list tArgs;
			va_start( tArgs, text );
			vsprintf_s( tString, text, tArgs );
			va_end( tArgs );

			glPushAttrib( GL_LIST_BIT );
				glListBase( fontId - 32 );
				glCallLists( strlen( tString ), GL_UNSIGNED_BYTE, tString );
			glPopAttrib();
		glPopMatrix();
	}
	else{
		std::string tText = text;
		std::string msg = "Cannot Draw Text: '" + tText + "'. Font is not loaded.";
		FatalError( msg );
	}	
}