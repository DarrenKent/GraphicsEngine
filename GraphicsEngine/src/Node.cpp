/*
*
*	Graphics Engine
*	By: Darren Kent
*
*/

#include <Windows.h>
#include <gl\GL.h>

#include "Debug.h"
#include "Node.h"

Node::Node( std::string id ) {
	mId						= id;
	mXPos = mYPos = mZPos	= 0;
	mYaw = mPitch = mRoll	= .00001f;
	mScale					= 1.0f;
	mVisible				= false;
}

Node::Node( std::string id, GLuint modelId, GLuint texture ) {
	mId						= id;
	mXPos = mYPos = mZPos	= 0;
	mYaw = mPitch = mRoll	= .00001f;
	mScale					= 1.0f;
	mVisible				= true;
	DebugMessage( "Adding Instanced Model Id: " + id, 4 );
	mModel = new Model();
	mModel->SetModelId( modelId );
	mModel->SetTextureId( texture );
}

Node::Node( std::string id, std::string filename, GLuint texture ) {
	mId						= id;
	mXPos = mYPos = mZPos	= 0;
	mYaw = mPitch = mRoll	= .00001f;
	mScale					= 1.0f;
	mVisible				= true;
	DebugMessage( "Adding Model: " + filename, 4 );
	mModel = new Model();
	bool tSuccess = mModel->LoadModel( filename, texture );
	if ( tSuccess ) {
		DebugMessage( "Model Successfully Loaded: " + filename, 4 );
	} else {
		FatalError( "Model Failed to Load: " + filename );
	}
}

Model* Node::GetModel(){
	return mModel;
}

void Node::DrawNode() {
	glPushMatrix();
	glTranslatef( mXPos, mYPos, mZPos );
	glRotatef( mYaw, 0, 0, 1 );
	glRotatef( mPitch, 0, 1, 0 );
	glRotatef( mRoll, 1, 0, 0 );
	glScalef( mScale, mScale, mScale );
	glEnable( GL_NORMALIZE );
	if ( mVisible )
		mModel->DrawModel();
	glDisable( GL_NORMALIZE );

	std::map<std::string, Node*>::iterator tChild;
	for ( tChild = mChildren.begin(); tChild != mChildren.end(); ++tChild) {
		tChild->second->DrawNode();
	}
	glPopMatrix();
}

bool Node::IsVisible() {
	return mVisible;
}

void Node::SetVisible( bool visible ) {
	mVisible = visible;
}

void Node::SetColor( GLfloat red, GLfloat green, GLfloat blue ) {
	mModel->SetColor( red, green, blue );
}

void Node::SetTransparency( GLfloat transparency ) {
	mModel->SetTransparency( transparency );
}

void Node::SetAmbient( GLfloat red, GLfloat green, GLfloat blue ) {
	mModel->SetAmbient( red, green, blue );
}

void Node::SetDiffuse( GLfloat red, GLfloat green, GLfloat blue ) {
	mModel->SetDiffuse( red, green, blue );
}

void Node::SetSpecular( GLfloat red, GLfloat green, GLfloat blue ) {
	mModel->SetSpecular( red, green, blue );
}

void Node::SetShininess( GLfloat shininess ) {
	mModel->SetShininess( shininess );
}

void Node::SetPosition( float x, float y, float z ) {
	mXPos = x;
	mYPos = y;
	mZPos = z;
}

void Node::SetRotation( float y, float p, float r ) {
	mYaw	= y;
	mPitch	= p;
	mRoll	= r;
}

void Node::SetScale( float scale ) {
	mScale = scale;
}

float Node::GetXPos() {
	return mXPos;
}

float Node::GetYPos() {
	return mYPos;
}

float Node::GetZPos() {
	return mZPos;
}

float Node::GetYaw() {
	return mYaw;
}

float Node::GetPitch() {
	return mPitch;
}

float Node::GetRoll() {
	return mRoll;
}