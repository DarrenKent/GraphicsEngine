/*
*
*	Graphics Engine
*	By: Darren Kent
*
*/

#ifndef _STATE_MANAGER_
#define _STATE_MANAGER_

#include <map>
#include <string>

#include "Application.h"
#include "Display.h"

class StateManager;

// State Class
class State {
	public:
		State();
		~State();

		virtual void DrawFrame()		= 0;				// Draws One frame
		virtual void GameLogic()		= 0;				// Executes One frame of logic
		virtual void ProcessInput()		= 0;				// Process user input
		virtual void InitializeState()	= 0;				// Initialize the State
		StateManager* GetStateManager();					// Returns the State Manager
		Display* GetDisplayManager();						// Returns the Display Manager
		SceneManager* GetSceneManager();					// Returns the Scene Manager
		ShaderManager* GetShaderManager();					// Returns the Shader Manager
		TextureManager* GetTextureManager();				// Returns the Texture Manager
		TimeManager* GetTimeManager();						// Returns the Time Manager
	protected:
		StateManager			*mStateManager;				// Pointer to Primary State Manager
		Display					*mDisplayManager;			// Pointer to Primary Display Manager
		SceneManager			*mSceneManager;				// State Scene Manager
		ShaderManager			*mShaderManager;			// State Shader Manager
		TextureManager			*mTextureManager;			// State Texture Manager
		TimeManager				*mTimeManager;				// State Time Manager
	private:
};

class StateManager : public Application {
	public:
		enum {
			STATE_PAUSED = 0,
			STATE_PLAYING,
			STATE_DELETE
		};													// Status types of the current State

		StateManager();										// Constructor
		~StateManager();									// Deconstructor

		void SetState( std::string stateId );				// Set Current State by Id
		void ChangeState( std::string stateId );			// Change the Current State
		void AddState(	std::string stateId, 
						State* newState );					// Add a state to the state list
		void DeleteState( std::string stateId );			// Delete a state from the state list

		void DrawFrame();									// Draw Current State Frame
		void StateLogic();									// Execute one frame of State Logic
		void ProcessInput();								// Processes the input for the state
		void Start();										// Starts Managers Main Loop

		Texture* LoadTexture( std::string key,
							  std::string filename, 
							  bool wrap );					// Load a Texture

		Display* GetDisplay();								// Returns Display Manager
	protected:
	private:
		State							*mCurrentState;		// Current State
		int								mCurrentStatus;		// Current State Status
		std::map< std::string, State* > mStates;			// State List

		bool							mDisplayFPS;		// Display FPS
		bool							mFPSKeyPressed;		// Determines if the FPS keys are pressed
		bool							mDebugKeyPressed;	// Determines if the Debug key is being pressed
};

#endif // _STATE_MANAGER_