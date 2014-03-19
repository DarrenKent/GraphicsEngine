/*
*
*	Graphics Engine
*	By: Darren Kent
*
*/

#include <math.h>
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>

#include "OrbitalCamera.h"

OrbitalCamera::OrbitalCamera() : Camera() {}

void OrbitalCamera::RotateCamAlpha( float amount ) {
	mCamAlpha += amount;
	CalculateCameraPosition();
}

void OrbitalCamera::RotateCamTheta( float amount ) {
	mCamTheta += amount;
	CalculateCameraPosition();
}

void OrbitalCamera::SetCameraRadius( float radius ) {
	mCamRadius = radius;
	CalculateCameraPosition();
}

void OrbitalCamera::CalculateCameraPosition() {
	mCamX = mTargetX + mCamRadius * (float)cos( mCamAlpha * 3.14159 / 180.0 ) * (float)cos( mCamTheta * 3.14159 / 180.0 );
	mCamY = mTargetY + mCamRadius * (float)sin( mCamAlpha * 3.14159 / 180.0 ) * (float)cos( mCamTheta * 3.14159 / 180.0 );
	mCamZ = mTargetZ + mCamRadius * (float)sin( mCamTheta * 3.14159 / 180.0 );
}

void OrbitalCamera::PositionCamera(){
	CalculateCameraPosition();
	gluLookAt( mCamX, mCamY, mCamZ, mTargetX, mTargetY, mTargetZ, 0.0, 0.0, 1.0 );
}