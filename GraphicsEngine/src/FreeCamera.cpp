/*
*
*	Star Wars: Astromechs
*	By: Darren Kent
*
*/
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <math.h>

#include "FreeCamera.h"

FreeCamera::FreeCamera() : Camera() {}

void FreeCamera::RotateCamAlpha( float amount ) {
	mCamAlpha += amount;
	CalculateTargetPosition();
}

void FreeCamera::RotateCamTheta( float amount ) {
	mCamTheta += amount;
	CalculateTargetPosition();
}

void FreeCamera::SetCameraRadius( float radius ) {
	mCamRadius = radius;
	CalculateTargetPosition();
}

void FreeCamera::CalculateTargetPosition() {
	mTargetX = mCamX + mCamRadius * cos( mCamAlpha ) * cos( mCamTheta );
	mTargetY = mCamY + mCamRadius * sin( mCamAlpha ) * cos( mCamTheta );
	mTargetZ = mCamZ + mCamRadius * sin( mCamTheta );
}

void FreeCamera::PositionCamera() {
	gluLookAt( mCamX, mCamY, mCamZ, mTargetX, mTargetY, mTargetZ, 0.0, 0.0, 1.0 );
}