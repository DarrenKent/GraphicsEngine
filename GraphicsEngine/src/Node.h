/*
*
*	Star Wars: Astromechs
*	By: Darren Kent
*
*/
#ifndef _NODE_
#define _NODE_

#include <map>
#include <string>

#include "Model.h"

class Node{
	public:
		Node(	std::string id );							// Empty Node
		Node(	std::string id, 
				GLuint modelId, 
				GLuint texture );							// Instanced Node
		Node(	std::string id, 
				std::string filename,
				GLuint texture );							// Node with Model Attached

		Model* GetModel();									// Returns a pointer to the Node's model
		void DrawNode();									// Draws the Node and its children
		bool IsVisible();									// Returns if the Node is visible
		void SetVisible( bool visible );					// Sets the Node's Visibility
		void SetColor(	GLfloat red, 
						GLfloat green, 
						GLfloat blue );						// Sets the Object Color
		void SetAmbient(	GLfloat red,
							GLfloat green,
							GLfloat blue );					// Sets the Object's Ambience
		void SetDiffuse(	GLfloat red,
							GLfloat green,
							GLfloat blue );					// Set the Object's Diffuse
		void SetSpecular(	GLfloat red,
							GLfloat green,
							GLfloat blue );					// Set the Object's Specular
		void SetShininess( GLfloat shininess );				// Set the Object's Shininess
		void SetTransparency( GLfloat transparency );		// Sets the transparency of the object
		void SetScale( float scale );						// Sets the scale of the Node
		void SetPosition( float x, float y, float z );		// Sets the position of the Node
		void SetRotation( float y, float p, float r );		// Sets the rotation of the Node
		float GetXPos();									// Gets the x position of the Node
		float GetYPos();									// Gets the y position of the Node
		float GetZPos();									// Gets the z position of the Node
		float GetYaw();										// Gets the yaw rotation of the Node
		float GetPitch();									// Gets the pitch rotation of the Node
		float GetRoll();									// Gets the roll rotation of the Node
	
	protected:
	private:
		std::string mId;									// String Id
		float	mXPos, mYPos, mZPos;						// Node Position
		float	mYaw, mPitch, mRoll;						// Node Rotation
		float	mScale;										// Node Scale
		bool	mVisible;									// Visibility
		Model*	mModel;										// Model
		std::map<std::string, Node*>	mChildren;			// Child Nodes
};

#endif // _NODE_