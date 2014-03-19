/*
*
*	Graphics Engine
*	By: Darren Kent
*
*/

#ifndef _ORBITAL_CAMERA_
#define _ORBITAL_CAMERA_

#include "Camera.h"

// Oribital Camera Class
class OrbitalCamera : public Camera {
	public:
		OrbitalCamera();									// Orbital Camera Constructor

		void PositionCamera();								// Positions The Camera

		void RotateCamAlpha( float amount );				// Rotate Camera based on alpha
		void RotateCamTheta( float amount );				// Rotate Camera based on theta
		void SetCameraRadius( float radius );				// Sets the Radius of the Camera
		void CalculateCameraPosition();						// Calculates the Camera's Position
	protected:
	private:
};
#endif // _ORBITAL_CAMERA_