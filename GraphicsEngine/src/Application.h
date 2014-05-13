/*
*
*	Graphics Engine
*	By: Darren Kent
*
*/

#ifndef _APPLICATION_
#define _APPLICATION_

#include <Windows.h>

#include "Display.h"
#include "SceneManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "TimeManager.h"

// Application Class
class Application {
	public:
		Application();										// Application Constructor

		virtual void Start() = 0;							// Starts Main Loop
		virtual void Initialize(LPCWSTR title, 
								int width, 
								int height, 
								int fullscreen);			// Initializes Application
		void StartFrame();									// Must be done at the beginning of each frame 
		void EndFrame();									// Must be done at the end of each frame
	protected:
		MSG				wMsg;								// Windows Message System
		bool			mActive;							// Status of the Main Loop
		Display			*DISPLAY_MGR;						// Main Display Manager
		SceneManager	*SCENE_MGR;							// Primary Scene Manager
		TimeManager		*TIME_MGR;							// Primary Time Manager
		TextureManager	*TEXTURE_MGR;						// Primary Texture Manager
		ShaderManager	*SHADER_MGR;						// Primary Shader Manager
	private:
};

#endif // _APPLICATION_