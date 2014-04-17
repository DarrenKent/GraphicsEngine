/*
*
*	Graphics Engine Demo
*	By: Darren Kent
*
*/

#include <Windows.h>
#include <fstream>
#include <GL/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <iostream>
#include <sstream>

#include "Debug.h"
#include "Game.h"
#include "Input.h"
#include "TextureManager.h"

Game::Game() : Application() {
	DebugMessage( "Creating Game Instance...", 3 );
	mCamera	= new OrbitalCamera();
	mCamera->SetCameraPos( 0.0f, 0.0f, 0.0f );
	mCamera->SetCameraRadius( 400.0f );
	mCamera->SetCameraTheta( 10.0f );
	mCamera->SetCameraAlpha( 50.0f );
	mCamera->SetTargetPos( 0.0f, 0.0f, 50.0f );
	mCamera->PositionCamera();
}

void Game::Start() {
	DebugMessage( "Starting Up Main Loop..." , 3 );
	while( mActive ) {
		StartFrame();
		GameLogic();
		DrawFrame();
		EndFrame();
	}
}

void Game::InitializeGame() {
	DebugMessage( "Initializing Game...", 3 );

	Texture *tTexture1 = TEXTURE_MGR->LoadTexture( "chrome", "data/textures/chrome.tga", false );
	Texture *tTexture2 = TEXTURE_MGR->LoadTexture( "magma", "data/textures/magma.tga", false );
	Texture *tTexture3 = TEXTURE_MGR->LoadTexture( "brushed", "data/textures/brushed.tga", false );

	Node* tBase = SCENE_MGR->AddNode( "base" );

	Node* tTemple1 = tBase->AddChild( "temple", "data/models/temple.obj", tTexture1 );
	Node* tTemple2 = tBase->AddChild( "temple2", tTemple1->GetModel()->GetModelId(), tTexture2 );
	Node* tTemple3 = tBase->AddChild( "temple3", tTemple1->GetModel()->GetModelId(), tTexture3 );
	tTemple2->SetPosition( 0.0f, 250.0f, 0.0f );
	tTemple3->SetPosition( 0.0f, -250.0f, 0.0f );
}

void Game::GameLogic() {}

void Game::ProcessInput() {
	float tDeltaTime = TIME_MGR->GetDeltaTimeSeconds();

	if ( GetKeyPressed( VK_ESCAPE ) )
		exit(0);

	// Camera Controls
	if ( GetKeyHeld( 'd' ) )
		mCamera->RotateCamAlpha( 50.0f * tDeltaTime );
	if ( GetKeyHeld( 'a' ) )
		mCamera->RotateCamAlpha( -50.0f * tDeltaTime );
	if ( GetKeyHeld( 'w' ) )
		mCamera->RotateCamTheta( 50.0f * tDeltaTime );
	if ( GetKeyHeld( 's' ) )
		mCamera->RotateCamTheta( -50.0f * tDeltaTime );
	if ( GetKeyHeld( 'r' ) ) {
		float tRadius = mCamera->GetCameraRadius() - ( 150.0f * tDeltaTime );
		if ( tRadius < 0.0f )
			tRadius = 0.0f;
		mCamera->SetCameraRadius( tRadius );
	}
	if ( GetKeyHeld( 'f' ) ) {
		float tRadius = mCamera->GetCameraRadius() + ( 150.0f * tDeltaTime );
		mCamera->SetCameraRadius( tRadius );
	}

	if ( GetKeyPressed( 'm' ) ) {
		int tDrawMode = SCENE_MGR->GetDrawMode() + 1;
		if ( tDrawMode > 2 )
			tDrawMode = 0;
		SCENE_MGR->SetDrawMode( tDrawMode );
	}
}

void Game::DrawFrame() {
	ProcessInput();

	DISPLAY_MGR->SetPerspectiveProjection( 30.0f, 2.0f, 1000000.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glEnable( GL_DEPTH_TEST );

	mCamera->PositionCamera();

	glPushMatrix();
		GLfloat tLightPosition[] = { 0.0f, 0.0f, 50.0f, 1.0f };
		glLightfv( GL_LIGHT0, GL_POSITION, tLightPosition );
	glPopMatrix();
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );



	glPushMatrix();
		SCENE_MGR->DrawScene();
	glPopMatrix();
}
