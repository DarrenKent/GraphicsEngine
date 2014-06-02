/*
*
*	Graphics Engine
*	By: Darren Kent
*
*/

#ifndef _NODE_
#define _NODE_

#include <map>
#include <string>

#include "Model.h"

// Node Class
class Node{
	public:
		Node(	std::string id );							// Empty Node
		Node(	std::string id, 
				GLuint modelId, 
				Texture *texture );							// Instanced Node
		Node(	std::string id, 
				std::string filename,
				Texture *texture );							// Node with Model Attached

		Model* GetModel();									// Returns a pointer to the Node's model
		void DrawNode();									// Draws the Node and its children
		bool IsVisible();									// Returns if the Node is visible
		void SetVisible( bool visible );					// Sets the Node's Visibility
		void SetColor(	GLfloat red, 
						GLfloat green, 
						GLfloat blue,
						GLfloat alpha );					// Sets the Object Color
		void SetAmbient(	GLfloat red,
							GLfloat green,
							GLfloat blue,
							GLfloat alpha );				// Sets the Object's Ambience
		void SetDiffuse(	GLfloat red,
							GLfloat green,
							GLfloat blue,
							GLfloat alpha );				// Set the Object's Diffuse
		void SetSpecular(	GLfloat red,
							GLfloat green,
							GLfloat blue,
							GLfloat alpha );				// Set the Object's Specular
		void SetShininess( GLfloat shininess );				// Set the Object's Shininess
		void SetScale( float scale );						// Sets the scale of the Node
		void SetPosition( float x, float y, float z );		// Sets the position of the Node
		void SetRotation( float y, float p, float r );		// Sets the rotation of the Node
		float GetXPos();									// Gets the x position of the Node
		float GetYPos();									// Gets the y position of the Node
		float GetZPos();									// Gets the z position of the Node
		float GetYaw();										// Gets the yaw rotation of the Node
		float GetPitch();									// Gets the pitch rotation of the Node
		float GetRoll();									// Gets the roll rotation of the Node
		float GetScale();									// Returns the Scale of the Node
		int GetDrawPriority();								// Returns the Draw Priority
		void SetDrawPriority( int priority );				// Sets the Draw Priority
		bool GetDepthMask();								// Returns the Depth Mask
		void SetDepthMask( bool mask );						// Sets the Depth Mask
		std::string GetId();								// Returns the Node's Id

		Node* AddChild( std::string key );					// Adds a blank Child
		Node* AddChild( std::string key, 
						std::string filename, 
						Texture *texture );					// Adds a child and loads a model
		Node* AddChild( std::string key, 
						GLuint modelId, 
						Texture *texture );					// Adds a child with an instanced model
		Node* GetChild( std::string key );					// Returns a child given a key
		void RemoveChild( std::string key );				// Removes a child from the parent
		void ClearChildren();								// Clears all children	

		int GetVerticeCount();								// Returns the vertice count
		int GetPolygonCount();								// Returns the polygon count
	protected:
	private:
		std::string mId;									// String Id
		float	mXPos, mYPos, mZPos;						// Node Position
		float	mYaw, mPitch, mRoll;						// Node Rotation
		float	mScale;										// Node Scale
		bool	mVisible;									// Visibility
		Model*	mModel;										// Model
		std::map<std::string, Node*>	mChildren;			// Child Nodes
		bool	mDepthMask;									// Use Draw Mask
		int		mDrawPriority;								// Draw Priority
		int		mVerticeCount;								// Total Vertices of all Children
		int		mPolygonCount;								// Total Polygons of all Children
};

#endif // _NODE_