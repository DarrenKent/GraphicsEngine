/*
*
*	Graphics Engine Demo
*	By: Darren Kent
*
*/

#ifndef _GAME_
#define _GAME_

#include <string>
#include <vector>

#include "Application.h"
#include "Model.h"
#include "OrbitalCamera.h"

// Game Class
class Game : public Application {
	public:
		Game();
	
		void Start();										// Main Loop
		void InitializeGame();								// Initializes the Game
		void ProcessInput();								// Process User Input
		void DrawFrame();									// Draw One Frame
		void GameLogic();									// One Frame of Game Logic
	protected:
	private:
		OrbitalCamera	*mCamera;							// The Camera
};

#endif // _GAME_