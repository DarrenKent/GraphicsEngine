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
	mModel					= NULL;
	mDepthMask				= true;
	mDrawPriority			= 0;
	mPolygonCount			= 0;
	mVerticeCount			= 0;
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
	mDepthMask				= true;
	mDrawPriority			= 0;
	mPolygonCount			= 0;
	mVerticeCount			= 0;
}

Node::Node( std::string id, std::string filename, GLuint texture ) {
	mId						= id;
	mXPos = mYPos = mZPos	= 0;
	mYaw = mPitch = mRoll	= .00001f;
	mScale					= 1.0f;
	mVisible				= true;
	mDepthMask				= true;
	mDrawPriority			= 0;
	mPolygonCount			= 0;
	mVerticeCount			= 0;
	DebugMessage( "Adding Model: " + filename, 4 );
	mModel = new Model();
	bool tSuccess = mModel->LoadModel( filename, texture );
	if ( tSuccess ) {
		mPolygonCount += mModel->GetPolygonCount();
		mVerticeCount += mModel->GetVerticeCount();
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
	if ( mModel && mVisible )
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

void Node::SetColor( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha ) {
	mModel->SetColor( red, green, blue, alpha );
}

void Node::SetAmbient( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha ) {
	mModel->SetAmbient( red, green, blue, alpha );
}

void Node::SetDiffuse( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha ) {
	mModel->SetDiffuse( red, green, blue, alpha );
}

void Node::SetSpecular( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha ) {
	mModel->SetSpecular( red, green, blue, alpha );
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

bool Node::GetDepthMask() {
	return mDepthMask;
}

void Node::SetDepthMask( bool mask ) {
	mDepthMask = mask;
}

void Node::SetDrawPriority( int priority ) {
	mDrawPriority = priority;
}

int Node::GetDrawPriority() {
	return mDrawPriority;
}

Node* Node::AddChild( std::string key ) {
	DebugMessage( "Adding node: " + key, 4 );
	Node* tNode = new Node( key );
	mChildren[key] = tNode;
	return tNode;
}

Node* Node::AddChild( std::string key, std::string filename, GLuint texture ) {
	DebugMessage( "Adding node: " + key, 4 );
	Node *tNode = new Node( key, filename, texture );
	mChildren[key] = tNode;
	mPolygonCount += mChildren[key]->GetPolygonCount();
	mVerticeCount += mChildren[key]->GetVerticeCount();
	return tNode;
}

Node* Node::AddChild( std::string key, GLuint modelId, GLuint texture ) {
	DebugMessage( "Adding node: " + key, 4 );
	Node *tNode = new Node( key, modelId, texture );
	mChildren[key] = tNode;
	return tNode;
}

Node* Node::GetChild( std::string key ) {
	return mChildren[key];
}

void Node::RemoveChild( std::string key ) {
	mChildren.erase( key );
}

void Node::ClearChildren() {
	std::map<std::string, Node*>::iterator tChild;
	for ( tChild = mChildren.begin(); tChild != mChildren.end(); ++tChild) {
		delete &tChild;
	}
}

int Node::GetVerticeCount() {
	return mVerticeCount;
}

int Node::GetPolygonCount() {
	return mPolygonCount;
}

