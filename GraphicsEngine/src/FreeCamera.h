/*
*
*	Graphics Engine
*	By: Darren Kent
*
*/

#ifndef _FREE_CAMERA_
#define _FREE_CAMERA_

#include "Camera.h"

// Free Camera Class
class FreeCamera : public Camera {
	public:
		FreeCamera();										// Free Camera Constructor

		void PositionCamera();								// Positions The Camera

		void RotateCamAlpha( float amount );				// Rotate Target Alpha Angle
		void RotateCamTheta( float amount );				// Rotate Target Theta Angle
		void SetCameraRadius( float radius );				// Set the Camera's Radius
		void CalculateTargetPosition();						// Calculate Targets Position
	protected:
	private:
};

#endif // _FREE_CAMERA_