/*
*
*	Graphics Engine
*	By: Darren Kent
*
*/

#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <math.h>

#include "Camera.h"
#include "Debug.h"

Camera::Camera() {
	DebugMessage( "Initializing Camera...", 3 );
	mCamX		= 0.0f;
	mCamY		= 0.0f;
	mCamZ		= 0.0f;
	mTargetX	= 0.0f;
	mTargetY	= 0.0f;
	mTargetZ	= 0.0f;
	mCamAlpha	= 0.001f;
	mCamTheta	= 0.001f;
	mCamRadius	= 1.0f;
}

void Camera::SetCameraPos( float x, float y, float z ) {
	mCamX = x;
	mCamY = y;
	mCamZ = z;
}

void Camera::SetCameraX( float x ) {
	mCamX = x;
}

void Camera::SetCameraY( float y ) {
	mCamY = y;
}

void Camera::SetCameraZ( float z ) {
	mCamZ = z;
}

void Camera::SetCameraAlpha( float alpha ) {
	mCamAlpha = alpha;
}

void Camera::SetCameraTheta( float theta ) {
	mCamTheta = theta;
}

void Camera::SetTargetPos( float x, float y, float z) {
	mTargetX = x;
	mTargetY = y;
	mTargetZ = z;
}

void Camera::SetTargetX( float x ) {
	mTargetX = x;
}

void Camera::SetTargetY( float y ) {
	mTargetY = y;
}

void Camera::SetTargetZ( float z ) {
	mTargetZ = z;
}

float Camera::GetCameraX() {
	return mCamX;
}

float Camera::GetCameraY() {
	return mCamY;
}

float Camera::GetCameraZ() {
	return mCamZ;
}

float Camera::GetCameraRadius() {
	return mCamRadius;
}

float Camera::GetCameraAlpha() {
	return mCamAlpha;
}

float Camera::GetCameraTheta() {
	return mCamTheta;
}

float Camera::GetTargetX() {
	return mTargetX;
}

float Camera::GetTargetY() {
	return mTargetY;
}

float Camera::GetTargetZ() {
	return mTargetZ;
}