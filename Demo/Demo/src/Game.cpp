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
#include "Draw.h"
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
	mLightAngle = 0;
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

	Texture *tTexture1 = TEXTURE_MGR->LoadTexture( "stone", "data/textures/stone.tga", false );

	Node* tBase = SCENE_MGR->AddNode( "base" );
	Node* tTemple1 = tBase->AddChild( "temple", "data/models/temple.obj", tTexture1 );
}

void Game::GameLogic() {
	double deltaTime = TIME_MGR->GetDeltaTimeSeconds();
	mLightAngle += 1 * (float)deltaTime;
}

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
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glEnable( GL_DEPTH_TEST );

	mCamera->PositionCamera();

	glPushMatrix();
		glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
		DrawSphere3D( cos( mLightAngle ) * 150, sin( mLightAngle ) * 150, 75.0f, 10, 8, 8 );
		GLfloat tLightPosition[] = { cos( mLightAngle ) * 150, sin( mLightAngle ) * 150, 75.0f, 1.0f };
		glLightfv( GL_LIGHT0, GL_POSITION, tLightPosition );
	glPopMatrix();
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );

	glPushMatrix();
		SCENE_MGR->DrawScene();
	glPopMatrix();
}
