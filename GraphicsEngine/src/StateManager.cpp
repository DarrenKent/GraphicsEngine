/*
*
*	Graphics Engine
*	By: Darren Kent
*
*/

#include "Debug.h"
#include "Draw.h"
#include "Input.h"
#include "StateManager.h"

StateManager::StateManager() : Application() {
	mCurrentState		= NULL;
	mCurrentStatus		= STATE_PAUSED;

	mDebugKeyPressed	= false;
	mDisplayFPS			= false;
	mFPSKeyPressed		= false;
}

StateManager::~StateManager() {}

void StateManager::SetState( std::string stateId ) {
	if ( mStates[stateId] ) {
		mCurrentState = mStates[stateId];
		mCurrentStatus = STATE_PLAYING;
	} else {
		FatalError( "State " + stateId + " Does Not Exists " );
	}
}

void StateManager::AddState( std::string stateId, State* newState ) {
	mStates[stateId] = newState;
}

void StateManager::DeleteState( std::string stateId ) {
	mStates.erase(stateId);
}

void StateManager::DrawFrame() {
	if ( mCurrentState )
		mCurrentState->DrawFrame();

	glDepthMask( GL_FALSE );
	DISPLAY_MGR->SetOrthographicProjection();
	glLoadIdentity();
	if ( mDisplayFPS ){
		glColor3f( 1.0f, 1.0f, 1.0f );
		std::string tFPS = "FPS: " + std::to_string( (long double)TIME_MGR->GetFramesPerSecond() );
		DrawText( tFPS.c_str(), SCENE_MGR->GetCurrentFontId(), 10.0f, DISPLAY_MGR->GetScreenHeight() - 20.0f );
	}
	
	glDepthMask( GL_TRUE );
}

void StateManager::StateLogic() {
	if ( mCurrentState )
		mCurrentState->GameLogic();
}

void StateManager::ProcessInput() {
	// System Control
	if ( !GetKeyPressed( VK_F12 ) )
		mDebugKeyPressed = false;
	if ( GetKeyPressed( VK_F12 ) && !mDebugKeyPressed ) {
		mDebugKeyPressed = true;
		SetDebugMode( GetDebugMode() + 1 );
		if ( GetDebugMode() > 4 )
			SetDebugMode( 0 );
	}

	if ( !GetKeyPressed( VK_CONTROL ) || !GetKeyPressed( 'f' ) )
		mFPSKeyPressed = false;
	if ( GetKeyPressed( VK_CONTROL ) && GetKeyPressed( 'f' ) && !mFPSKeyPressed ) {
		mFPSKeyPressed = true;
		if ( mDisplayFPS )
			mDisplayFPS = false;
		else
			mDisplayFPS = true;
	}

	if ( mCurrentState )
		mCurrentState->ProcessInput();
}

void StateManager::Start() {
	DebugMessage( "Starting Up Main Loop..." , 3 );
	while( mActive ) {
		StartFrame();
		
		ProcessInput();
		StateLogic();
		DrawFrame();

		EndFrame();
	}
}

Texture* StateManager::LoadTexture( std::string key, std::string filename, bool wrap ) {
	return TEXTURE_MGR->LoadTexture( key, filename, wrap );
}

Display* StateManager::GetDisplay() {
	return DISPLAY_MGR;
}