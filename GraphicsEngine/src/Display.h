/*
*
*	Graphics Engine
*	By: Darren Kent
*
*/

#ifndef _DISPLAY_
#define _DISPLAY_

#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <string>

// Display Class
class Display{
	public:
		Display();											// Display Constructor

		void SetupWindow( LPCWSTR title, 
						  int width,
						  int height, 
						  int fullscreen = 0,
						  int depth = 32 );					// Sets Up the Window with Given Settings
		bool CreateNewWindow();								// Create a New Window
		void RegisterWindowClass();							// Registers Window Class
		void InitializeOpenGL();							// Initialize Open GL
		void ResizeGLScene();								// Change Viewport if resized
		void SetOrthographicProjection();					// Sets projection to Orthographic
		void SetPerspectiveProjection(	float fov,
										float zNear,
										float zFar );		// Sets projection to Perspective

		HDC GetHDC();										// Returns the Device Context
		void SwapDisplayBuffers();							// Swaps the Display Buffers
	
		int GetScreenWidth();								// Returns the Screen Width
		int GetScreenHeight();								// Returns the Screen Height
		int GetFullscreen();								// Returns Fullscreen Status

	protected:
	private:
		HGLRC		hRC;									// OpenGL Rendering Context
		HDC			hDC;									// Device Context
		HWND		hWnd;									// Window Handle
		HINSTANCE	hInstance;								// Application Instance
		int			mFullscreen;							// Fulscreen Mode
		int			mScreenHeight;							// Screen Height
		int			mScreenWidth;							// Screen Width
		int			mScreenDepth;							// Screen Color Depth
		LPCWSTR		mWinClassName;							// Window Class Name
		LPCWSTR		mWinTitle;								// Window Title Bar
		bool		mActive;								// Status of the the Window
};

#endif // _DISPLAY_