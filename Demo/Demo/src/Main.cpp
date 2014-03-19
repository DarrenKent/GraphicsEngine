/*
*
*	Graphics Engine Demo
*	By: Darren Kent
*
*/

#include <Windows.h>

#include "Debug.h"
#include "Game.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ) {
	SetDebugMode( 4 );
	Game *tDemo = new Game();
	tDemo->Initialize( L"Graphics Engine Demo", 800, 600, 0 );
	tDemo->InitializeGame();
	tDemo->Start();
}