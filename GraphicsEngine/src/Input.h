/*
*
*	Star Wars: Astromechs
*	By: Darren Kent
*
*/
#ifndef _INPUT_
#define _INPUT_

#include <Windows.h>

bool GetKeyPressed( char key );							// Returns if a key is pressed
bool GetKeyHeld( char key );							// Returns if a key is pressed
int GetMouseX();										// Returns the Mouse X coordinate
int GetMouseY();										// Returns the Mouse Y coordinate
bool GetMouseMove();									// Returns true if the mouse has moved
void SetMouseMove( bool moved );						// Sets the mouse moved flag	

LRESULT CALLBACK MainWProc(	HWND hWnd, 
							UINT uMsg, 
							WPARAM wParam, 
							LPARAM lParam);				// Windows callback

#endif // _INPUT_