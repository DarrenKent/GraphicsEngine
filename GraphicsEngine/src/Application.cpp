/*
*
*	Graphics Engine
*	By: Darren Kent
*
*/

#include <iostream>
#include <gl/glew.h>

#include "Application.h"
#include "Debug.h"
#include "Draw.h"
#include "Input.h"

Application::Application() {
	DebugStartup();	
	DebugMessage( "Starting up Application...", 2 );

	mActive		= true;
	DISPLAY_MGR = new Display();
	SHADER_MGR	= new ShaderManager();
	TIME_MGR	= new TimeManager();
	TEXTURE_MGR = new TextureManager();
	TIME_MGR->StartTime();
}

void Application::Initialize( LPCWSTR title, int width, int height, int fullscreen ) {
	DebugMessage( "Initializing Appication...", 3 );
	DISPLAY_MGR->SetupWindow( title, width, height, fullscreen );
	DISPLAY_MGR->CreateNewWindow();
	SCENE_MGR = new SceneManager( DISPLAY_MGR->GetHDC() );
	glewInit();
}

void Application::StartFrame() {
	SetMouseMove( false );
	if ( PeekMessage( &wMsg, NULL, NULL, NULL, PM_REMOVE ) ){
			if( wMsg.message == WM_QUIT )
				mActive = false;

			TranslateMessage( &wMsg );
			DispatchMessage( &wMsg );
	}
	TIME_MGR->TimeFrame();
}

void Application::EndFrame() {
	SHADER_MGR->ClearProgram();

	glDepthMask( GL_FALSE );
	glDisable( GL_LIGHTING );
	DISPLAY_MGR->SetOrthographicProjection();
	glLoadIdentity();

	SCENE_MGR->CalculatePolygonCount();
	DrawDebugGUI(	SCENE_MGR->GetCurrentFontId(),
					(float)TIME_MGR->GetFramesPerSecond(), 
					SCENE_MGR->GetTotalPolygons(), 
					SCENE_MGR->GetTotalVertices(),
					(float)GetMouseX(),
					(float)( DISPLAY_MGR->GetScreenHeight() - GetMouseY() ) );
	glDepthMask( GL_TRUE );

	SwapBuffers( DISPLAY_MGR->GetHDC() );
}