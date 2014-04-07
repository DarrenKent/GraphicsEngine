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

float COUNT = 0;

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

	Texture *tTexture1 = NULL; //TEXTURE_MGR->LoadTexture( "chrome", "data/textures/chrome.tga", false );
	Texture *tTexture2 = NULL; //TEXTURE_MGR->LoadTexture( "magma", "data/textures/magma.tga", false );
	Texture *tTexture3 = NULL; //TEXTURE_MGR->LoadTexture( "brushed", "data/textures/brushed.tga", false );

	Node* tBase = SCENE_MGR->AddNode( "base" );

	Node* tTemple1 = tBase->AddChild( "temple", "data/models/temple.obj", tTexture1 );
	Node* tTemple2 = tBase->AddChild( "temple2", tTemple1->GetModel()->GetModelId(), tTexture2 );
	Node* tTemple3 = tBase->AddChild( "temple3", tTemple1->GetModel()->GetModelId(), tTexture3 );
	tTemple2->SetPosition( 0.0f, 250.0f, 0.0f );
	tTemple3->SetPosition( 0.0f, -250.0f, 0.0f );

	glPushMatrix();
		GLfloat tLightPosition[] = { 0.0f, 0.0f, 75.0f, 1.0f };
		glLightfv( GL_LIGHT0, GL_POSITION, tLightPosition );
	glPopMatrix();

	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
}

void Game::GameLogic() {}

void Game::ProcessInput() {
	float tDeltaTime = TIME_MGR->GetDeltaTimeSeconds();

	if ( GetKeyPressed( VK_ESCAPE ) )
		exit(0);

	// Camera Controls
	if ( GetKeyHeld( 'd' ) )
		mCamera->RotateCamAlpha( 25.0f * tDeltaTime );
	if ( GetKeyHeld( 'a' ) )
		mCamera->RotateCamAlpha( -25.0f * tDeltaTime );
	if ( GetKeyHeld( 'w' ) )
		mCamera->RotateCamTheta( 25.0f * tDeltaTime );
	if ( GetKeyHeld( 's' ) )
		mCamera->RotateCamTheta( -25.0f * tDeltaTime );

	if ( GetKeyHeld( 'j' ) ) {
		float tRotation = SCENE_MGR->GetNode( "base" )->GetYaw();
		SCENE_MGR->GetNode( "base" )->SetRotation( tRotation + 25.0f * tDeltaTime, 0.0f, 0.0f );
	}
}

void Game::DrawFrame() {
	ProcessInput();

	DISPLAY_MGR->SetPerspectiveProjection( 30.0f, 2.0f, 1000000.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();

	glEnable( GL_DEPTH_TEST );
	mCamera->PositionCamera();

	glPushMatrix();
		SCENE_MGR->DrawScene();
	glPopMatrix();
}
