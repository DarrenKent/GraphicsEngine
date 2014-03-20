/*
*
*	Graphics Engine
*	By: Darren Kent
*
*/

#include <Windows.h>
#include <fstream>
#include <gl\GL.h>
#include <sstream>

#include "Debug.h"
#include "Model.h"
#include "TextureManager.h"

Model::Model() {
	mColor[0]		= 1.0f; 
	mColor[1]		= 1.0f;
	mColor[2]		= 1.0f;
	mColor[3]		= 1.0f;
	mAmbient[0]		= 1.0f;
	mAmbient[1]		= 1.0f;
	mAmbient[2]		= 1.0f;
	mAmbient[3]		= 1.0f;
	mDiffuse[0]		= 1.0f;
	mDiffuse[1]		= 1.0f;
	mDiffuse[2]		= 1.0f;
	mDiffuse[3]		= 1.0f;
	mSpecular[0]	= 1.0f;
	mSpecular[1]	= 1.0f;
	mSpecular[2]	= 1.0f;
	mSpecular[3]	= 1.0f;
	mShininess		= 0;
	mPolygonCount	= 0;
	mTexture		= NULL;
	mLighted		= true;
	mDepthMask		= true;
	mDrawPriority	= 0;
}

bool Model::LoadModel( std::string filename , GLuint texture ) {
	DebugMessage( "Loading Model: " + filename, 3 );
	mTexture	= texture;
	
	std::string		tLine;
	std::ifstream	tFile(filename);
	
	if ( tFile.is_open() ) {
		while ( tFile.good() ) {
			getline( tFile, tLine );
			std::string			tToken;
			std::istringstream	tStringStream( tLine );

			getline( tStringStream, tToken, ' ' );
			if ( tToken == "v" ) {
				Vertex tVert;
				getline( tStringStream, tToken, ' ' );
				getline( tStringStream, tToken, ' ' );
				tVert.x = (float)atof( tToken.c_str() );
				getline( tStringStream, tToken, ' ' );
				tVert.y = (float)atof( tToken.c_str() );
				getline( tStringStream, tToken, ' ' );
				tVert.z = (float)atof( tToken.c_str() );
				this->mVertices.push_back( tVert );
			} else if ( tToken == "vn" ) {
				Vector tNorm;
				getline( tStringStream, tToken, ' ' );
				tNorm.x = (float)atof( tToken.c_str() );
				getline( tStringStream, tToken, ' ' );
				tNorm.y = (float)atof( tToken.c_str() );
				getline( tStringStream, tToken, ' ' );
				tNorm.z = (float)atof( tToken.c_str() );
				this->mNormals.push_back( tNorm );
			} else if( tToken == "vt" ) {
				Vector tTexCoords;
				getline( tStringStream, tToken, ' ' );
				tTexCoords.x = (float)atof( tToken.c_str() );
				getline( tStringStream, tToken, ' ' );
				tTexCoords.y = (float)atof( tToken.c_str() );
				getline( tStringStream, tToken, ' ' );
				tTexCoords.z = (float)atof( tToken.c_str() );
				this->mTexCoords.push_back( tTexCoords );
			} else if( tToken == "f" ) {
				size_t	tCurrent;
				size_t	tNext;
				Face	tFace;

				getline( tStringStream, tToken, ' ' );
				tCurrent	= 0;
				tNext		= tToken.find_first_of( '/', tCurrent );
				tFace.v1	= (int)atof( tToken.substr( tCurrent, tNext - tCurrent ).c_str() ) - 1;
				tCurrent	= tNext + 1;
				tNext		= tToken.find_first_of( '/', tCurrent );
				tFace.t1	= (int)atof( tToken.substr( tCurrent, tNext - tCurrent).c_str() ) - 1;
				tCurrent	= tNext + 1;
				tNext		= tToken.find_first_of( '/', tCurrent );
				tFace.v1n	= (int)atof( tToken.substr( tCurrent, tNext - tCurrent).c_str() ) - 1;

				getline( tStringStream, tToken, ' ' );
				tCurrent	= 0;
				tNext		= tToken.find_first_of( '/', tCurrent );
				tFace.v2	= (int)atof( tToken.substr( tCurrent, tNext - tCurrent).c_str() ) - 1;
				tCurrent	= tNext + 1;
				tNext		= tToken.find_first_of( '/', tCurrent );
				tFace.t2	= (int)atof( tToken.substr( tCurrent, tNext - tCurrent).c_str() ) - 1;
				tCurrent	= tNext + 1;
				tNext		= tToken.find_first_of( '/', tCurrent );
				tFace.v2n	= (int)atof( tToken.substr( tCurrent, tNext - tCurrent).c_str()) - 1;

				getline( tStringStream, tToken, ' ' );
				tCurrent	= 0;
				tNext		= tToken.find_first_of( '/', tCurrent );
				tFace.v3	= (int)atof( tToken.substr( tCurrent, tNext - tCurrent ).c_str()) - 1;
				tCurrent	= tNext + 1;
				tNext		= tToken.find_first_of( '/', tCurrent );
				tFace.t3	= (int)atof( tToken.substr( tCurrent, tNext - tCurrent).c_str()) - 1;
				tCurrent	= tNext + 1;
				tNext		= tToken.find_first_of( '/', tCurrent );
				tFace.v3n	= (int)atof(tToken.substr( tCurrent, tNext - tCurrent).c_str()) - 1;

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

void Model::StoreModel() {
	mModelId = glGenLists( 1 );
	glNewList( mModelId, GL_COMPILE );
	glPushMatrix();
	glTranslatef( 0.0f, 0.0f, 0.0f );
	glBegin( GL_TRIANGLES );
	for ( unsigned int iFace = 0; iFace < mFaces.size(); ++iFace) {	
		glTexCoord3f( mTexCoords[(int)mFaces[iFace].t1].x, mTexCoords[(int)mFaces[iFace].t1].y, mTexCoords[(int)mFaces[iFace].t1].z );
		glNormal3f( mNormals[(int)mFaces[iFace].v1n].x, mNormals[(int)mFaces[iFace].v1n].y, mNormals[(int)mFaces[iFace].v1n].z );
		glVertex3f( mVertices[(int)mFaces[iFace].v1].x, mVertices[(int)mFaces[iFace].v1].y, mVertices[(int)mFaces[iFace].v1].z );
		glTexCoord3f( mTexCoords[(int)mFaces[iFace].t2].x, mTexCoords[(int)mFaces[iFace].t2].y, mTexCoords[(int)mFaces[iFace].t2].z );
		glNormal3f( mNormals[(int)mFaces[iFace].v2n].x, mNormals[(int)mFaces[iFace].v2n].y, mNormals[(int)mFaces[iFace].v2n].z );
		glVertex3f( mVertices[(int)mFaces[iFace].v2].x, mVertices[(int)mFaces[iFace].v2].y, mVertices[(int)mFaces[iFace].v2].z );
		glTexCoord3f( mTexCoords[(int)mFaces[iFace].t3].x, mTexCoords[(int)mFaces[iFace].t3].y, mTexCoords[(int)mFaces[iFace].t3].z );
		glNormal3f( mNormals[(int)mFaces[iFace].v3n].x, mNormals[(int)mFaces[iFace].v3n].y, mNormals[(int)mFaces[iFace].v3n].z );
		glVertex3f( mVertices[(int)mFaces[iFace].v3].x, mVertices[(int)mFaces[iFace].v3].y, mVertices[(int)mFaces[iFace].v3].z );
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
	
	glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, mAmbient );
	glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, mDiffuse );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, mSpecular );
	glMaterialf( GL_FRONT, GL_SHININESS, mShininess );
	
	glColor4f( mColor[0], mColor[1], mColor[2], mColor[3] );
	if ( mTexture ) {
		glEnable( GL_TEXTURE_2D );
		glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
		glBindTexture( GL_TEXTURE_2D, mTexture );
	}
	glPushMatrix();

	glCallList( mModelId );

	glPopMatrix();

	if ( mTexture )
		glDisable( GL_TEXTURE_2D );
	glDisable( GL_COLOR_MATERIAL );
	glDisable( GL_BLEND );

	if ( mLighted )
		glDisable( GL_LIGHTING );
}

void Model::SetColor( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha )  {
	mColor[0] = red;
	mColor[1] = green;
	mColor[2] = blue;
	mColor[3] = alpha;
}

void Model::SetAmbient( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha )  {
	mAmbient[0] = red;
	mAmbient[1] = green;
	mAmbient[2] = blue;
	mAmbient[3] = alpha;
}

void Model::SetDiffuse( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha )  {
	mDiffuse[0] = red;
	mDiffuse[1] = green;
	mDiffuse[2] = blue;
	mDiffuse[3] = alpha;
}

void Model::SetSpecular( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha )  {
	mSpecular[0] = red;
	mSpecular[1] = green;
	mSpecular[2] = blue;
	mSpecular[3] = alpha;
}

void Model::SetShininess( GLfloat shininess ) {
	mShininess = shininess;
}

int Model::GetPolygonCount() {
	return mPolygonCount;
}

int Model::GetVerticeCount() {
	return mVertices.size();
}

GLuint Model::GetModelId() {
	return mModelId;
}

void Model::SetModelId( GLuint modelId ) {
	mModelId = modelId;
}

GLuint Model::GetTextureId() {
	return mTexture;
}

void Model::SetTextureId( GLuint textureId ) {
	mTexture = textureId;
}

void Model::SetLighted( bool lighted ) {
	mLighted = lighted;
}

bool Model::GetLighted() {
	return mLighted;
}

void Model::SetDepthMask( bool mask ) {
	mDepthMask = mask;
}

bool Model::GetDepthMask() {
	return mDepthMask;
}

void Model::SetDrawPriority( int priority ) {
	mDrawPriority = priority;
}

int Model::GetDrawPriority() {
	return mDrawPriority;
}