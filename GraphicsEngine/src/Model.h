/*
*
*	Graphics Engine
*	By: Darren Kent
*
*/

#ifndef _MODEL_
#define _MODEL_

#include <Windows.h>
#include <gl\GL.h>
#include <map>
#include <string>
#include <vector>

#include "Geometry.h"
#include "ShaderManager.h"
#include "TextureManager.h"

// Model Class
class Model {
	public:
		Model();											// Model Constructor

		bool LoadModel( std::string file, 
						Texture *texture );					// Load the model from a file
		void LoadMaterial( std::string file,
						   std::map< std::string, 
									 Material* > &matList );// Load a mtl file
		void StoreModel();									// Stores Model to the Display List
		void DrawModel();									// Draw the model to the screne

		GLuint GetModelId();								// Returns the Model Id
		void SetModelId( GLuint modelId );					// Sets the Model's Id
		Texture *GetTextureId();							// Returns the Model's Texture Id
		void SetTextureId( Texture *texture );				// Sets the Model's Texture Id

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
		int GetPolygonCount();								// Returns the Amount of Polygons in this Node's model
		int GetVerticeCount();								// Returns the Amount of Vertices in this Node's model

		void SetLighted( bool lighted );					// Sets the Object Lighting
		bool GetLighted();									// Get the Object Lighting
		
		void SetShaderProgram( ShaderProgram *shaderProg ); // Sets the model's shader program
	protected:
	private:
		TextureManager		*mTextureMgr;
		GLuint				mModelId;						// Display List Id
		std::vector<Face>	mFaces;							// List of all the faces of the model
		int					mPolygonCount;					// Number of faces on the model
		int					mVertexCount;					// Number of vertices on the model
		Texture				*mTexture;						// Filename of texture
		bool				mLighted;						// Whether the model is lit or not
		ShaderProgram		*mShaderProgram;				// Shader Program
};

#endif // _MODEL_