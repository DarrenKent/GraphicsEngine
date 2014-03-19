/*
*
*	Star Wars: Astromechs
*	By: Darren Kent
*
*/
#ifndef _MODEL_
#define _MODEL_

#include <Windows.h>
#include <gl\GL.h>
#include <string>
#include <vector>

// Model Class
class Model {
	public:

		// Structures required for model interpretation.
		struct Vertex {
			float x;
			float y;
			float z;
		};

		struct Face {
			int v1;
			int v2;
			int v3;
			int v1n;
			int v2n;
			int v3n;
			int t1;
			int t2;
			int t3;
		};

		struct Vector {
			float x;
			float y;
			float z;
		};

		Model();											// Model Constructor

		bool LoadModel( std::string file, GLuint texture );	// Load the model from a file
		void StoreModel();									// Stores Model to the Display List
		void DrawModel();									// Draw the model to the screne

		GLuint GetModelId();								// Returns the Model Id
		void SetModelId( GLuint modelId );					// Sets the Model's Id
		GLuint GetTextureId();								// Returns the Model's Texture Id
		void SetTextureId( GLuint textureId );				// Sets the Model's Texture Id

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
		int GetPolygonCount();								// Returns the Amount of Polygons in this Node's model
		int GetVerticeCount();								// Returns the Amount of Vertices in this Node's model

		void SetLighted( bool lighted );					// Sets the Object Lighting
		bool GetLighted();									// Returns the Object Lighting
		void SetDepthMask( bool mask );						// Sets the Object Depth Mask mode
		bool GetDepthMask();								// Returns the Object Depth Mask mode
		void SetDrawPriority( int priority );				// Sets the Objects Draw Priority
		int GetDrawPriority();								// Returns the Objects Draw Priority
		void SetTransparency( float transparency );			// Sets the Objects Transparency
		float GetTransparency();							// Returns the Objects Transparency
		 
	protected:
	private:
		GLuint				mModelId;						// Display List Id
		std::vector<Vertex> mVertices;						// List of all the vertices of the model
		std::vector<Face>	mFaces;							// List of all the faces of the model
		std::vector<Vector> mNormals;						// List of all the normals of the model
		std::vector<Vector> mTexCoords;						// List of all texture coordinates
		int					mPolygonCount;					// Number of faces on the model
		GLuint				mTexture;						// Filename of texture
		GLfloat				mColor[3];						// Color of Model
		GLfloat				mAmbient[3];					// Ambient of Model
		GLfloat				mDiffuse[3];					// Diffuse of Model
		GLfloat				mSpecular[3];					// Specular of Model
		GLfloat				mShininess;						// Shininess of Model
		float				mTransparency;					// Object Transparency
		bool				mLighted;						// Determines if lights effect this object
		bool				mDepthMask;						// Determines if depth mask is on or off
		int					mDrawPriority;					// Drawing Priority
};

#endif // _MODEL_