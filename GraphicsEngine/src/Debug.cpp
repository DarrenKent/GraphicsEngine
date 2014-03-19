/*
*
*	Graphics Engine
*	By: Darren Kent
*
*/

#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <Windows.h>

#include "Debug.h"
#include "Draw.h"

/*	DEBUG_MODE
*		0 = Disabled (No Console, No Debug Information)
*		1 = GUI (Shows basic GUI Debug info)
*		2 = Minimal (Shows non-Fatal Errors Only)
*		3 = Medium (Shows Warnings and Basic Output)
*		4 = Maximum (Shows All Debug Output. WARNING: Massive Output)
*/
int DEBUG_MODE = 0;

int GetDebugMode(){
	return DEBUG_MODE;
}

void SetDebugMode( int mode ){
	DEBUG_MODE = mode;
}

void CreateConsole() {
	if( !AllocConsole() )
		FatalError( "Unable to Allocate Debug Console" );

	int tControlPanelHandle	= _open_osfhandle( (long)GetStdHandle( STD_OUTPUT_HANDLE ), _O_TEXT );
	FILE *ControlPanel		= _fdopen( tControlPanelHandle, "w" );
	*stdout					= *ControlPanel;
	setvbuf( stdout, NULL, _IONBF, 0 );
}

void DebugStartup() {
	if( DEBUG_MODE == 0 )
		return;
	CreateConsole();

	std::string tModeInfo[] = {		"1 = GUI (Shows basic GUI Debug info)",
									"2 = Minimal (Shows Fatal Errors Only)",
									"3 = Medium (Shows Warnings and Basic Output)",
									"4 = Maximum (Shows All Output. WARNING: Massive Output)" };

	for( int iMode = 0; iMode < DEBUG_MODE; iMode++ )
		std::cout << "Debug Mode Active: " << tModeInfo[iMode] << std::endl;
	std::cout << std::endl;
}

void FatalError( std::string error ) {
	std::cout << "Fatal Error: " << error << std::endl;
	system( "PAUSE" );
	exit(0);
}

void DebugMessage( std::string msg, int level ) {
	if( DEBUG_MODE >= level )
		std::cout << msg << std::endl;
}

void DrawDebugGUI( int fontId, float fps, int polygonCount, int verticeCount, float mouseX, float mouseY ) {
	if( DEBUG_MODE > 0 ) {
		glColor3f( 0.2f, 0.2f, 0.2f );
		DrawRectangle2D( 0.0f, 0.0f, 200.0f, 100.0f );
		glColor3f( 0.4f, 0.4f, 0.4f );
		DrawRectangleOutline2D( 0.0f, 0.0f, 200.0f, 100.0f, 2.0f );	

		glColor3f( 1.0f, 1.0f, 1.0f );
		std::string tFPS = "FPS: " + std::to_string( (long double)fps );
		DrawText( tFPS.c_str(), fontId, 10.0f, 85.0f );
		std::string tPoly = "Polygon Count: " + std::to_string( (long double)polygonCount );
		DrawText( tPoly.c_str(), fontId, 10.0f, 70.0f );
		std::string tVert = "Vertice Count: " + std::to_string( (long double)verticeCount );
		DrawText( tVert.c_str(), fontId, 10.0f, 55.0f );
		std::string tMouseX= "MouseX: " + std::to_string( (long double)mouseX );
		DrawText( tMouseX.c_str(), fontId, 10.0f, 40.0f );
		std::string tMouseY = "MouseY: " + std::to_string( (long double)mouseY );
		DrawText( tMouseY.c_str(), fontId, 10.0f, 25.0f );
		std::string tDMode = "Debug Mode: " + std::to_string( (long double)DEBUG_MODE );
		DrawText( tDMode.c_str(), fontId, 10.0f, 10.0f );
	}
}