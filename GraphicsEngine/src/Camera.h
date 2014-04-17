/*
*
*	Graphics Engine
*	By: Darren Kent
*
*/

#ifndef _CAMERA_
#define _CAMERA_

// Camera Class
class Camera{
	public:
		Camera();

		void SetCameraPos( float x, float y, float z );		// Sets the camera's position
		void SetCameraX( float x );							// Sets the camera's x position
		void SetCameraY( float y );							// Sets the camera's y position
		void SetCameraZ( float z );							// Sets the camera's z position
		void SetCameraAlpha( float alpha );					// Sets the camera's alpha rotation
		void SetCameraTheta( float theta );					// Sets the camera's theta rotation
		virtual void SetCameraRadius( float radius );		// Sets the camera's radius
		void SetTargetPos( float x, float y, float z );		// Sets the camera's target position
		void SetTargetX( float x );							// Sets the camera's target x position
		void SetTargetY( float y );							// Sets the camera's target y position
		void SetTargetZ( float z );							// Sets the camera's target z position

		float GetCameraX();									// Returns the camera's x position
		float GetCameraY();									// Returns the camera's y position
		float GetCameraZ();									// Returns the camera's z position
		float GetCameraRadius();							// Returns the camera's radius
		float GetCameraAlpha();								// Returns the camera's alpha rotation
		float GetCameraTheta();								// Returns the camera's theta rotation
		float GetTargetX();									// Returns the camera's target x position
		float GetTargetY();									// Returns the camera's target y position
		float GetTargetZ();									// Returns the camera's target z posotion
	protected:
		float mCamX, mCamY, mCamZ;							// Camera Position
		float mTargetX, mTargetY, mTargetZ;					// Camera Target Position
		float mCamAlpha, mCamTheta;							// Camera Angles
		float mCamRadius;									// Radius in which Camera Rotates on.
	private:
};

#endif // _CAMERA_