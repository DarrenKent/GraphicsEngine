/*
*
*	Graphics Engine
*	By: Darren Kent
*
*/

#include <iostream>

#include "Debug.h"
#include "Input.h"

bool	KEYS[256];
bool	LIFTED[256];
int		MOUSE_X, MOUSE_Y;
bool	MOUSE_MOVE;

bool GetKeyPressed( char key ){
	key = toupper( key );
	if ( KEYS[key] && !LIFTED[key] ) {
		LIFTED[key] = true;
		return true;
	}
	return false;
}

bool GetKeyHeld( char key ){
	key = toupper( key );
	return KEYS[key];
}

LRESULT CALLBACK MainWProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) {
	switch( uMsg ) {
		case WM_ERASEBKGND:
			return 1;
		case WM_CLOSE:
			DebugMessage( "Exiting Program...", 2 );
			exit(0);
			return 0;
		case WM_KEYDOWN:
			KEYS[wParam] = true;
			return 0;
		case WM_MOUSEMOVE:
			MOUSE_MOVE = true;
			return 0;
		case WM_KEYUP:
			KEYS[wParam] = false;
			LIFTED[wParam] = false;
			return 0;
	}

	POINT tPoint;
	GetCursorPos( &tPoint );
	if ( ScreenToClient( hWnd, &tPoint ) ){
		MOUSE_X = tPoint.x;
		MOUSE_Y = tPoint.y;
		if ( MOUSE_X < 0 )
			MOUSE_X = 0;
		if ( MOUSE_Y < 0 )
			MOUSE_Y = 0;
	}

	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

int GetMouseX() {
	return MOUSE_X;
}

int GetMouseY() {
	return MOUSE_Y;
}

bool GetMouseMove() {
	return MOUSE_MOVE;
}

void SetMouseMove( bool moved ){
	MOUSE_MOVE = false;
}
