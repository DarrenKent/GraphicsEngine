/*
*
*	Star Wars: Astromechs
*	By: Darren Kent
*
*/
#ifndef _DEBUG_
#define _DEBUG_

#include <string>

/*	DEBUG_MODE
*		0 = Disabled (No Console, No Debug Information)
*		1 = GUI (Shows basic GUI Debug info)
*		2 = Minimal (Shows non-Fatal Errors Only)
*		3 = Medium (Shows Warnings and Basic Output)
*		4 = Maximum (Shows All Debug Output. WARNING: Massive Output)
*/

int GetDebugMode();											// Returns Debug Mode
void SetDebugMode( int mode );								// Sets the Debug Mode

void CreateConsole();										// Creates a Console to display the Debug Information
void DebugStartup();										// Displays Starting Debug Settings

void FatalError( std::string error );						// Handles a Fatal Error
void DebugMessage( std::string msg, int level );			// Displays a Debug message if the current debug level is >= level
void DrawDebugGUI(	int fontId, 
					float fps, 
					int polygonCount, 
					int verticeCount,
					float mouseX, 
					float mouseY );							// Draws the Debug GUI if active

#endif _DEBUG_