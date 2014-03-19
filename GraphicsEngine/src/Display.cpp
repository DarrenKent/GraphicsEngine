/*
*
*	Graphics Engine
*	By: Darren Kent
*
*/

#include <iostream>

#include "Debug.h"
#include "Display.h"
#include "Input.h"


Display::Display() {
	// DEFAULT VALUES
	hRC				= NULL;
	hDC				= NULL;
	hWnd			= NULL;
	mFullscreen		= 0;
	mScreenHeight	= 600;
	mScreenWidth	= 800;
	mScreenDepth	= 32;
	mWinTitle		= L"Simple3DEngine";
	mWinClassName	= L"GLClass";
	mActive			= true;
}

void Display::SetupWindow( LPCWSTR title, int width, int height, int fullscreen, int depth ) {
	DebugMessage( "Setting up Window Paramaters...", 3 );
	mWinTitle		= title;
	mScreenWidth	= width;
	mScreenHeight	= height;
	mScreenDepth	= depth;
	mFullscreen		= fullscreen;
}

bool Display::CreateNewWindow() {
	RegisterWindowClass();

	// Center Window on Display
	int posX = ( GetSystemMetrics(SM_CXSCREEN) / 2 ) - ( mScreenWidth / 2 );
	int posY = ( GetSystemMetrics(SM_CYSCREEN) / 2 ) - ( mScreenHeight / 2 );

	DWORD wndStyle = WS_OVERLAPPEDWINDOW;

	if ( mFullscreen == 1 ){
		DEVMODE fsSettings;
		memset( &fsSettings, 0, sizeof( DEVMODE ) );
		fsSettings.dmSize				= sizeof( DEVMODE );
		fsSettings.dmPelsHeight			= mScreenHeight;
		fsSettings.dmPelsWidth			= mScreenWidth;
		fsSettings.dmBitsPerPel			= mScreenDepth;
		fsSettings.dmDisplayFrequency	= 60;
		fsSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

		long result = ChangeDisplaySettings( &fsSettings, CDS_FULLSCREEN );
		if ( result != DISP_CHANGE_SUCCESSFUL ) {
			DebugMessage( "Error: Could not initialize fullscreen mode.", 1 );
			if ( result == DISP_CHANGE_BADDUALVIEW )
				DebugMessage( "Fullscreen was unsuccessful: System is DualView capable.", 1 );
			if ( result == DISP_CHANGE_BADFLAGS )
				DebugMessage( "Fullscreen was unsuccessful: An invalid set of flags were passed in.", 1 );
			if ( result == DISP_CHANGE_BADMODE )
				DebugMessage( "Fullscreen was unsuccessful: The system does not support Fullscreen.", 1 );
			if ( result == DISP_CHANGE_BADPARAM )
				DebugMessage( "Fullscreen was unsuccessful: An invalid parameter was passed in.", 1 );
			if ( result == DISP_CHANGE_FAILED )
				DebugMessage( "Fullscreen was unsuccessful: The GPU does not support Fullscreen.", 1 );
			if ( result == DISP_CHANGE_NOTUPDATED )
				DebugMessage( "Fullscreen was unsuccessful: Unable to write settings to the registry.", 1 );
			if ( result == DISP_CHANGE_RESTART )
				DebugMessage( "Fullscreen was unsuccessful: Restart Required for changes to take effect.", 1 );
		} else {
			wndStyle	= WS_POPUP;
			posX		= 0;
			posY		= 0;
		}
	}

	DebugMessage( "Creating Window...", 3 );
	hWnd = CreateWindowEx(	NULL, mWinClassName, mWinTitle, wndStyle | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 
							posX, posY, mScreenWidth, mScreenHeight, NULL, NULL, hInstance, NULL );
	if ( !hWnd )
		FatalError( "Could Not Create Window." );

	DebugMessage( "Showing Window...", 3 );

	PIXELFORMATDESCRIPTOR pfd = {
		sizeof( PIXELFORMATDESCRIPTOR ), 1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA, mScreenDepth,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0,
		PFD_MAIN_PLANE, 0, 0, 0, 0
	};

	hDC = GetDC( hWnd );
	if ( !hDC )
		FatalError( "Could not create a GL Device Context." );

	int pixelFormat = ChoosePixelFormat( hDC, &pfd );
	if ( !pixelFormat )
		FatalError( "Pixel Format Invalid." );

	if ( !SetPixelFormat( hDC, pixelFormat, &pfd ) )
		FatalError( "Could not set Pixel Format." );

	hRC = wglCreateContext( hDC );
	if( !hRC )
		FatalError( "Could not create a GL rendering Context." );

	if( !wglMakeCurrent( hDC, hRC ) )
		FatalError( "Could not set Rendering Context" );

	ShowWindow( hWnd, SW_SHOW );
	SetForegroundWindow( hWnd );
	SetFocus( hWnd );
	ResizeGLScene();
	InitializeOpenGL();
	return true;
}

void Display::RegisterWindowClass() {
	DebugMessage( "RegisteringWindowClass...", 3 );
	WNDCLASSEX wClass;

	hInstance			= GetModuleHandle( NULL );

	wClass.cbSize			= sizeof( WNDCLASSEX );
	wClass.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wClass.lpfnWndProc		= MainWProc;
	wClass.cbClsExtra		= 0;
	wClass.cbWndExtra		= 0;
	wClass.hInstance		= hInstance;
	wClass.hIcon			= LoadIcon( NULL, IDI_WINLOGO );
	wClass.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wClass.hbrBackground	= NULL;
	wClass.lpszMenuName		= NULL;
	wClass.lpszClassName	= mWinClassName;
	wClass.hIconSm			= NULL;

	if ( !RegisterClassEx( &wClass ) )
		FatalError( "Failed to Register Window Class." );
}

void Display::InitializeOpenGL() {
	DebugMessage( "Initializing OpenGl...", 3 );
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClearDepth( 1.0f );
	//glDepthFunc( GL_LEQUAL );
	//glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}

void Display::ResizeGLScene() {
	glViewport( 0, 0, mScreenWidth, mScreenHeight );
}

void Display::SetOrthographicProjection() {
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( 0.0, mScreenWidth, 0.0, mScreenHeight, -1.0, 1.0 );
	glMatrixMode( GL_MODELVIEW );
}

void Display::SetPerspectiveProjection( float fov, float zNear, float zFar ) {
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( fov, (double)mScreenWidth / mScreenHeight, zNear, zFar);
	glMatrixMode( GL_MODELVIEW );
}

HDC Display::GetHDC() { 
	return hDC; 
}

void Display::SwapDisplayBuffers() {
	SwapBuffers( hDC );
}

int Display::GetScreenHeight(){
	return mScreenHeight;
}

int Display::GetScreenWidth(){
	return mScreenWidth;
}

int Display::GetFullscreen(){
	return mFullscreen;
}