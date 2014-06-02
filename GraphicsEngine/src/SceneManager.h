/*
*
*	Graphics Engine
*	By: Darren Kent
*
*/

#ifndef _SCENE_MANAGER_
#define _SCENE_MANAGER_

#include <map>
#include <string>

#include "Font.h"
#include "Node.h"
#include "ShaderManager.h"

// Scene Manager Class
class SceneManager {
	public:
		SceneManager();										// Scene Manager Constructor
		SceneManager( HDC hDC );							// Primary Scene Manager Constructor

		Node* AddNode(   std::string key );					// Adds a blank Node to the Scene
		Node* AddNode(	std::string key, 
						std::string filename,
						Texture *texture );					// Adds a model to the Scene
		Node* AddNode(	std::string key,
						GLuint modelId,
						Texture *texture );					// Adds an instanced model to the Scene
		void ClearScene();									// Removes all Nodes from the Scene
		void RemoveNode( std::string key );					// Removes Node from the Scene

		void DrawScene();									// Draws one frame of the Scene
		void DrawSceneRange(	float xPos,
								float yPos,
								float zPos,
								float range );				// Draws one frame of the Scene in a range of a point
		Node* GetNode( std::string key );					// Retrieves a Node given the key

		void AddFont(	std::string key );					// Adds a default font
		void AddFont(	std::string key, LPCWSTR fontName, 
						int size);							// Adds a font with name and size
		FontHandle* GetFont( std::string key );				// Retrives a font given the key
		void SetFont( std::string key );					// Sets the current font given a key
		GLuint GetCurrentFontId();							// Returns the current font id
		void CalculatePolygonCount();						// Calculates the polygon and vertices
		int GetTotalPolygons();								// Returns the total Polygons being rendered in the scene
		int GetTotalVertices();								// Returns the total Vertices being rendered in the scene
		void SetDrawMode( int mode );						// Sets the Draw Mode
		int GetDrawMode();									// Gets the Draw Mode
	protected:
	private:
		HDC									hDC;			// Display Controller
		std::map<std::string, Node*>		mNodes;			// A list of all Nodes in the scene
		std::map<std::string, GLuint>		mModels;		// A list of all Models loaded into the scene
		std::map<std::string, FontHandle*>	mFonts;			// A list of all fonts in the scene
		FontHandle*							mCurrentFont;	// Current Font being used
		int									mPolygonTotal;	// Total Polygons in the Scene
		int									mVerticesTotal;	// Total Vertices in the Scene
		int									mDrawMode;		// Draw Mode for Polygons 0 = Fill, 1 = Points, 2 = Lines
		bool								mShadows;		// Shadows Disabled or Enabled
};

#endif // _SCENE_MANAGER_