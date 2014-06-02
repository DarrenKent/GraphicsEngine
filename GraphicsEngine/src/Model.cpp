/*
*
*	Graphics Engine
*	By: Darren Kent
*
*/

#include <algorithm>
#include <Windows.h>
#include <fstream>
#include <GL\glew.h>
#include <gl\GL.h>
#include <GL\GLU.h>
#include <sstream>

#include <iostream>

#include "Debug.h"
#include "Model.h"
#include "TextureManager.h"

Model::Model() {
	mPolygonCount	= 0;
	mVertexCount	= 0;
	mTexture		= NULL;
	mLighted		= true;
	mTextureMgr		= new TextureManager();
	mShaderProgram	= NULL;
}

bool Model::LoadModel( std::string filename , Texture *texture ) {
	DebugMessage( "Loading Model: " + filename, 3 );
	mTexture	= texture;
	
	std::string		tLine;
	std::ifstream	tFile( filename );

	std::vector< Vertex > tVertices;
	std::vector< Vector3 > tNormals;
	std::vector< Vector3 > tTexCoordinates;
	std::map< std::string, Material* > tMaterials;
	Material *tMat = new Material();
	
	if ( tFile.is_open() ) {
		while ( tFile.good() ) {
			getline( tFile, tLine );
			std::string			tToken;
			std::istringstream	tStringStream( tLine );
			

			getline( tStringStream, tToken, ' ' );
			if ( tToken == "mtllib" ) {
				getline( tStringStream, tToken, ' ' );
				LoadMaterial( tToken, tMaterials );
			} else if ( tToken == "usemtl" ) {
				getline( tStringStream, tToken, ' ' );
				tMat = new Material();
				tMat = tMaterials[tToken];
			} else if ( tToken == "v" ) {
				Vertex tVert = Vertex();
				getline( tStringStream, tToken, ' ' );
				getline( tStringStream, tToken, ' ' );
				tVert.pos.x = (float)atof( tToken.c_str() );
				getline( tStringStream, tToken, ' ' );
				tVert.pos.y = (float)atof( tToken.c_str() );
				getline( tStringStream, tToken, ' ' );
				tVert.pos.z = (float)atof( tToken.c_str() );
				tVertices.push_back( tVert );
				mVertexCount ++;
			} else if ( tToken == "vn" ) {
				Vector3 tNorm = Vector3();
				getline( tStringStream, tToken, ' ' );
				tNorm.x = (float)atof( tToken.c_str() );
				getline( tStringStream, tToken, ' ' );
				tNorm.y = (float)atof( tToken.c_str() );
				getline( tStringStream, tToken, ' ' );
				tNorm.z = (float)atof( tToken.c_str() );
				tNormals.push_back( tNorm );
			} else if( tToken == "vt" ) {
				Vector3 tTexCoords = Vector3();
				getline( tStringStream, tToken, ' ' );
				tTexCoords.x = (float)atof( tToken.c_str() );
				getline( tStringStream, tToken, ' ' );
				tTexCoords.y = (float)atof( tToken.c_str() );
				getline( tStringStream, tToken, ' ' );
				tTexCoords.z = (float)atof( tToken.c_str() );
				tTexCoordinates.push_back( tTexCoords );
			} else if( tToken == "f" ) {
				size_t	tCurrent;
				size_t	tNext;
				Face	tFace = Face();

				int tVert1, tVert2, tVert3;
				int tTex1, tTex2, tTex3;
				int tNorm1, tNorm2, tNorm3;

				getline( tStringStream, tToken, ' ' );
				tCurrent	= 0;
				tNext		= tToken.find_first_of( '/', tCurrent );
				tVert1		= atoi( tToken.substr( tCurrent, tNext - tCurrent ).c_str() ) - 1;
				tCurrent	= tNext + 1;
				tNext		= tToken.find_first_of( '/', tCurrent );
				tTex1		= atoi( tToken.substr( tCurrent, tNext - tCurrent).c_str() ) - 1;
				tCurrent	= tNext + 1;
				tNext		= tToken.find_first_of( '/', tCurrent );
				tNorm1		= atoi( tToken.substr( tCurrent, tNext - tCurrent).c_str() ) - 1;

				getline( tStringStream, tToken, ' ' );
				tCurrent	= 0;
				tNext		= tToken.find_first_of( '/', tCurrent );
				tVert2		= atoi( tToken.substr( tCurrent, tNext - tCurrent).c_str() ) - 1;
				tCurrent	= tNext + 1;
				tNext		= tToken.find_first_of( '/', tCurrent );
				tTex2		= atoi( tToken.substr( tCurrent, tNext - tCurrent).c_str() ) - 1;
				tCurrent	= tNext + 1;
				tNext		= tToken.find_first_of( '/', tCurrent );
				tNorm2		= atoi( tToken.substr( tCurrent, tNext - tCurrent).c_str()) - 1;

				getline( tStringStream, tToken, ' ' );
				tCurrent	= 0;
				tNext		= tToken.find_first_of( '/', tCurrent );
				tVert3		= atoi( tToken.substr( tCurrent, tNext - tCurrent ).c_str()) - 1;
				tCurrent	= tNext + 1;
				tNext		= tToken.find_first_of( '/', tCurrent );
				tTex3		= atoi( tToken.substr( tCurrent, tNext - tCurrent).c_str()) - 1;
				tCurrent	= tNext + 1;
				tNext		= tToken.find_first_of( '/', tCurrent );
				tNorm3		= atoi(tToken.substr( tCurrent, tNext - tCurrent).c_str()) - 1;

				Vertex tVertex1	= tVertices[tVert1];
				Vertex tVertex2	= tVertices[tVert2];
				Vertex tVertex3	= tVertices[tVert3];
				tVertex1.color		= tMat->diffuse;
				tVertex2.color		= tMat->diffuse;
				tVertex3.color		= tMat->diffuse;
				tVertex1.normal	= tNormals[tNorm1];
				tVertex2.normal	= tNormals[tNorm2];
				tVertex3.normal	= tNormals[tNorm3];
				tVertex1.texCoord	= tTexCoordinates[tTex1];
				tVertex2.texCoord	= tTexCoordinates[tTex2];
				tVertex3.texCoord	= tTexCoordinates[tTex3];

				tFace.mat			= *tMat;
				tFace.v1			= tVertex1;
				tFace.v2			= tVertex2;
				tFace.v3			= tVertex3;

				this->mFaces.push_back( tFace );
				mPolygonCount ++;
			}
		}
		tFile.close();
		StoreModel();
		return true;
	} else
		return false;
}

void Model::LoadMaterial( std::string file, std::map< std::string, Material* > &matList ) {
	DebugMessage( "Loading Material File: " + file, 3 );
	
	std::string		tLine;
	std::ifstream	tFile( "data/models/" + file );
	
	if ( tFile.is_open() ) {
		while ( tFile.good() ) {
			getline( tFile, tLine );
			std::string			tToken;
			std::istringstream	tStringStream( tLine );

			Material *tMaterial = new Material();
			std::string tKey;

			getline( tStringStream, tToken, ' ' );
			if ( tToken == "newmtl" ) {
				getline( tStringStream, tToken, ' ' );
				tKey = tToken;
				
				while ( true ) {
					getline( tFile, tLine );
					std::string			tToken;
					std::istringstream	tStringStream( tLine );
					getline( tStringStream, tToken, ' ' );
					
					tToken.erase( std::remove( tToken.begin(), tToken.end(), ' ' ), tToken.end() );
					tToken.erase( std::remove( tToken.begin(), tToken.end(), '\n' ), tToken.end() );
					tToken.erase( std::remove( tToken.begin(), tToken.end(), '\t' ), tToken.end() );

					if ( tToken == "" ) {
						break;
					} else if ( tToken == "Ns" ) {
						getline( tStringStream, tToken, ' ' );
						tMaterial->shine = (float)atof( tToken.c_str() );
					} else if ( tToken == "d" ) {
						getline( tStringStream, tToken, ' ' );
						tMaterial->transparency = (float)atof( tToken.c_str() );
					} else if ( tToken == "Ka" ) {
						getline( tStringStream, tToken, ' ' );
						tMaterial->ambient.red = (float)atof( tToken.c_str() );
						getline( tStringStream, tToken, ' ' );
						tMaterial->ambient.green = (float)atof( tToken.c_str() );
						getline( tStringStream, tToken, ' ' );
						tMaterial->ambient.blue = (float)atof( tToken.c_str() );
						getline( tStringStream, tToken, ' ' );
						if ( tStringStream.good() )
							tMaterial->ambient.alpha = (float)atof( tToken.c_str() );
					} else if ( tToken == "Kd" ) {
						getline( tStringStream, tToken, ' ' );
						tMaterial->diffuse.red = (float)atof( tToken.c_str() );
						getline( tStringStream, tToken, ' ' );
						tMaterial->diffuse.green = (float)atof( tToken.c_str() );
						getline( tStringStream, tToken, ' ' );
						tMaterial->diffuse.blue = (float)atof( tToken.c_str() );
						getline( tStringStream, tToken, ' ' );
						if ( tStringStream.good() )
							tMaterial->diffuse.alpha = (float)atof( tToken.c_str() );
					} else if ( tToken == "Ks" ) {
						getline( tStringStream, tToken, ' ' );
						tMaterial->specular.red = (float)atof( tToken.c_str() );
						getline( tStringStream, tToken, ' ' );
						tMaterial->specular.green = (float)atof( tToken.c_str() );
						getline( tStringStream, tToken, ' ' );
						tMaterial->specular.blue = (float)atof( tToken.c_str() );
						getline( tStringStream, tToken, ' ' );
						if ( tStringStream.good() )
							tMaterial->specular.alpha = (float)atof( tToken.c_str() );
					} else if ( tToken == "map_Ka" ) {
						getline( tStringStream, tToken, ' ' );
						std::string tTexFile = tToken.substr( tToken.find_last_of( "/\\" ) + 1 );
						tMaterial->texture = mTextureMgr->LoadTexture( tTexFile, std::string("data/textures/" + tTexFile), true );
					}
					
				}
				matList[tKey] = tMaterial;
			}
		}
	} else {
		std::string msg = "Cannot open file: data/models/" + file;
		FatalError( msg );
	}
}

void Model::StoreModel() {
	DebugMessage( "Storing Model to Display List...", 3 );
	mModelId = glGenLists( 1 );
	bool tTextureLoaded = false;
	if ( mTexture )
		tTextureLoaded = true;
	glNewList( mModelId, GL_COMPILE );
		glPushMatrix();
			glTranslatef( 0.0f, 0.0f, 0.0f );

			glBegin( GL_TRIANGLES );
				for ( unsigned int iFace = 0; iFace < mFaces.size(); ++iFace) {	
					Material *tMat = &mFaces[iFace].mat;

					if ( tMat->texture ) {
						glEnable( GL_TEXTURE_2D );
						glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
						glBindTexture( GL_TEXTURE_2D, tMat->texture->GetTextureId() );
						tTextureLoaded = false;
					} else if ( mTexture && !tTextureLoaded ) {
						tTextureLoaded = true;
						glEnable( GL_TEXTURE_2D );
						glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
						glBindTexture( GL_TEXTURE_2D, mTexture->GetTextureId() );
					}

					GLfloat tAmbient[]  = { (GLfloat)tMat->ambient.red, (GLfloat)tMat->ambient.green, (GLfloat)tMat->ambient.blue, tMat->transparency };
					GLfloat tDiffuse[]  = { (GLfloat)tMat->diffuse.red, (GLfloat)tMat->diffuse.green, (GLfloat)tMat->diffuse.blue, tMat->transparency };
					GLfloat tSpecular[] = { (GLfloat)tMat->specular.red, (GLfloat)tMat->specular.green, (GLfloat)tMat->specular.blue, tMat->transparency };

					glMaterialfv( GL_FRONT, GL_AMBIENT, tAmbient );
					glMaterialfv( GL_FRONT, GL_DIFFUSE, tDiffuse );
					glMaterialfv( GL_FRONT, GL_SPECULAR, tSpecular );
					glMaterialf( GL_FRONT, GL_SHININESS, tMat->shine );

					glColor4d( mFaces[iFace].v1.color.red, mFaces[iFace].v1.color.green, mFaces[iFace].v1.color.blue, tMat->transparency );
					glTexCoord3d( mFaces[iFace].v1.texCoord.x, mFaces[iFace].v1.texCoord.y, mFaces[iFace].v1.texCoord.z );
					glNormal3d( mFaces[iFace].v1.normal.x, mFaces[iFace].v1.normal.y, mFaces[iFace].v1.normal.z );
					glVertex3d( mFaces[iFace].v1.pos.x, mFaces[iFace].v1.pos.y, mFaces[iFace].v1.pos.z );

					glColor4d( mFaces[iFace].v2.color.red, mFaces[iFace].v2.color.green, mFaces[iFace].v2.color.blue, tMat->transparency );
					glTexCoord3d( mFaces[iFace].v2.texCoord.x, mFaces[iFace].v2.texCoord.y, mFaces[iFace].v2.texCoord.z );
					glNormal3d( mFaces[iFace].v2.normal.x, mFaces[iFace].v2.normal.y, mFaces[iFace].v2.normal.z );
					glVertex3d( mFaces[iFace].v2.pos.x, mFaces[iFace].v2.pos.y, mFaces[iFace].v2.pos.z );

					glColor4d( mFaces[iFace].v3.color.red, mFaces[iFace].v3.color.green, mFaces[iFace].v3.color.blue, tMat->transparency );
					glTexCoord3d( mFaces[iFace].v3.texCoord.x, mFaces[iFace].v3.texCoord.y, mFaces[iFace].v3.texCoord.z );
					glNormal3d( mFaces[iFace].v3.normal.x, mFaces[iFace].v3.normal.y, mFaces[iFace].v3.normal.z );
					glVertex3d( mFaces[iFace].v3.pos.x, mFaces[iFace].v3.pos.y, mFaces[iFace].v3.pos.z );

					if ( tMat->texture )
						glDisable( GL_TEXTURE_2D );
				}
			glEnd();
		glPopMatrix();
	glEndList();
}

void Model::DrawModel() {
	if ( mLighted )
		glEnable( GL_LIGHTING );
	else
		glDisable( GL_LIGHTING );

	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glEnable( GL_COLOR_MATERIAL );
	glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );

	if ( mTexture ) {
		glEnable( GL_TEXTURE_2D );
		glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
		glBindTexture( GL_TEXTURE_2D, mTexture->GetTextureId() );
	}

	glPushMatrix();
		if ( mShaderProgram )
			glUseProgram( mShaderProgram->GetProgramHandle() );
		glCallList( mModelId );
		if ( mShaderProgram )
			glUseProgram( 0 );
	glPopMatrix();

	glDisable( GL_COLOR_MATERIAL );
	glDisable( GL_BLEND );
	if ( mTexture )
		glDisable( GL_TEXTURE_2D );
}

void Model::SetColor( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha )  {
	Color4 tColor	= Color4();
	tColor.red		= red;
	tColor.green	= green;
	tColor.blue	= blue;
	tColor.alpha	= alpha;

	for ( unsigned int iFace = 0; iFace < mFaces.size(); ++iFace ) {
		mFaces[iFace].v1.color = tColor;
		mFaces[iFace].v2.color = tColor;
		mFaces[iFace].v3.color = tColor;
	}
}

void Model::SetAmbient( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha )  {
	Color4 tColor	= Color4();
	tColor.red		= red;
	tColor.green	= green;
	tColor.blue	= blue;
	tColor.alpha	= alpha;

	for ( unsigned int iFace = 0; iFace < mFaces.size(); ++iFace ) {
		mFaces[iFace].mat.ambient = tColor;
		mFaces[iFace].mat.ambient = tColor;
		mFaces[iFace].mat.ambient = tColor;
	}
}

void Model::SetDiffuse( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha )  {
	Color4 tColor	= Color4();
	tColor.red		= red;
	tColor.green	= green;
	tColor.blue	= blue;
	tColor.alpha	= alpha;

	for ( unsigned int iFace = 0; iFace < mFaces.size(); ++iFace ) {
		mFaces[iFace].mat.diffuse = tColor;
		mFaces[iFace].mat.diffuse = tColor;
		mFaces[iFace].mat.diffuse = tColor;
	}
}

void Model::SetSpecular( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha )  {
	Color4 tColor	= Color4();
	tColor.red		= red;
	tColor.green	= green;
	tColor.blue	= blue;
	tColor.alpha	= alpha;

	for ( unsigned int iFace = 0; iFace < mFaces.size(); ++iFace ) {
		mFaces[iFace].mat.specular = tColor;
		mFaces[iFace].mat.specular = tColor;
		mFaces[iFace].mat.specular = tColor;
	}
}

void Model::SetShininess( GLfloat shininess ) {
	for ( unsigned int iFace = 0; iFace < mFaces.size(); ++iFace ) {
		mFaces[iFace].mat.shine = shininess;
		mFaces[iFace].mat.shine = shininess;
		mFaces[iFace].mat.shine = shininess;
	}
}

int Model::GetPolygonCount() {
	return mPolygonCount;
}

int Model::GetVerticeCount() {
	return mVertexCount;
}

GLuint Model::GetModelId() {
	return mModelId;
}

void Model::SetModelId( GLuint modelId ) {
	mModelId = modelId;
}

Texture* Model::GetTextureId() {
	return mTexture;
}

void Model::SetTextureId( Texture *textureId ) {
	mTexture = textureId;
}

void Model::SetLighted( bool lighted ) {
	mLighted = true;
}

bool Model::GetLighted() {
	return mLighted;
}

void Model::SetShaderProgram( ShaderProgram *shaderProg ) {
	mShaderProgram = shaderProg;
}