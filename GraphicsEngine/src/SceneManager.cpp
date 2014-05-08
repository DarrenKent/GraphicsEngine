/*
*
*	Graphics Engine
*	By: Darren Kent
*
*/

#include <fstream>
#include <iostream>
#include <math.h>
#include <sstream>

#include "Debug.h"
#include "SceneManager.h"

SceneManager::SceneManager() {
	DebugMessage( "Creating Scene Manager...", 3 );
	DebugMessage( "WARNING: Incorrect Constructor used for SceneManager.", 2 );
	mCurrentFont	= NULL;
	mPolygonTotal	= 0;
	mVerticesTotal	= 0;
	mDrawMode		= 0;
	mShadows		= true;
}

SceneManager::SceneManager( HDC hDC ) {
	DebugMessage( "Creating Scene Manager...", 3 );
	this->hDC = hDC;

	FontHandle* tDefaultFont = new FontHandle( hDC );
	tDefaultFont->LoadFont();
	mCurrentFont	= tDefaultFont;
	mPolygonTotal	= 0;
	mVerticesTotal	= 0;
	mDrawMode		= 0;
	mShadows		= true;
}

Node* SceneManager::AddNode( std::string key ) {
	DebugMessage( "Adding node: " + key, 4 );
	Node* tNode = new Node( key );
	mNodes[key] = tNode;
	return tNode;
}

Node* SceneManager::AddNode( std::string key, std::string filename, Texture *texture ) {
	DebugMessage( "Adding node: " + key, 4 );
	if ( mModels[filename] ) {
		DebugMessage( filename + " Has already been loaded. Using previously loaded model.", 4 );
		Node *tNode = new Node( key, mModels[filename], texture );
		mNodes[key] = tNode;
		return tNode;
	} else {
		Node *tNode = new Node( key, filename, texture );
		mNodes[key] = tNode;
		mPolygonTotal += mNodes[key]->GetModel()->GetPolygonCount();
		mVerticesTotal += mNodes[key]->GetModel()->GetVerticeCount();
		mModels[filename] = tNode->GetModel()->GetModelId();
		return tNode;
	}
}

Node* SceneManager::AddNode( std::string key, GLuint modelId, Texture *texture ) {
	DebugMessage( "Adding node: " + key, 4 );
	Node *tNode = new Node( key, modelId, texture );
	mNodes[key] = tNode;
	return tNode;
}

void SceneManager::ClearScene() {
	std::map<std::string, Node*>::iterator tNode;
	for (tNode = mNodes.begin(); tNode != mNodes.end(); ++tNode) {
		delete &tNode;
	}
	mNodes.clear();
}

void SceneManager::DrawScene(){
	if ( mDrawMode == 0 )
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	else if ( mDrawMode == 1 )
		glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );
	else
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	std::vector<Node*> tTransparentNodes;

	std::map<std::string, Node*>::iterator tNode;
	for (tNode = mNodes.begin(); tNode != mNodes.end(); ++tNode) {
		if ( tNode->second->GetDepthMask() )
			tNode->second->DrawNode();
		else
			tTransparentNodes.push_back(tNode->second);
	}


	glDepthMask( GL_FALSE );
	int tPriority = 0;
	unsigned int tDrawn = 0;
	while ( tDrawn < tTransparentNodes.size() ) {
		for ( unsigned int iNode = 0; iNode < tTransparentNodes.size(); iNode++ ){
			if ( tTransparentNodes[iNode]->GetDrawPriority() == tPriority ) {
				tTransparentNodes[iNode]->DrawNode();
				tDrawn ++;
			}
		}
		tPriority ++;
	}
	glDepthMask( GL_TRUE );
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

void SceneManager::DrawSceneRange( float xPos, float yPos, float zPos, float range ){
	if ( mDrawMode == 0 )
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	else if ( mDrawMode == 1 )
		glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );
	else
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	std::vector<Node*> tTransparentNodes;

	std::map<std::string, Node*>::iterator tNode;
	for (tNode = mNodes.begin(); tNode != mNodes.end(); ++tNode) {
		float tXDiff	= ( tNode->second->GetXPos() - xPos );
		float tYDiff	= ( tNode->second->GetYPos() - yPos );
		float tZDiff	= ( tNode->second->GetZPos() - zPos );
		float tDistance = std::sqrt( std::pow( tXDiff, 2 ) + std::pow( tYDiff, 2 ) + std::pow( tZDiff, 2 ) );
		if ( tDistance <= range ) {
			if ( tNode->second->GetDepthMask() )
				tNode->second->DrawNode();
			else
				tTransparentNodes.push_back( tNode->second );
		}
	}

	glDepthMask( GL_FALSE );
	int tPriority = 0;
	unsigned int tDrawn = 0;
	while ( tDrawn < tTransparentNodes.size() ) {
		for ( unsigned int iNode = 0; iNode < tTransparentNodes.size(); iNode++ ){
			if ( tTransparentNodes[iNode]->GetDrawPriority() == tPriority ) {
				tTransparentNodes[iNode]->DrawNode();
				tDrawn ++;
			}
		}
		tPriority ++;
	}
	glDepthMask( GL_TRUE );
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

Node* SceneManager::GetNode( std::string key ) {
	Node *tNode = mNodes[key];
	if( tNode )
		return tNode;
	else
		FatalError( "Cannot Locate Node: " + key );
	return tNode;
}

void SceneManager::AddFont( std::string key ) {
	FontHandle* tNewFont = new FontHandle( hDC );
	mFonts[key] = tNewFont;
}

void SceneManager::AddFont( std::string key, LPCWSTR fontName, int size ) {
	FontHandle* tNewFont = new FontHandle( hDC, fontName, size );
	mFonts[key] = tNewFont;
}

FontHandle* SceneManager::GetFont( std::string key ) {
	return mFonts[key];
}

void SceneManager::SetFont( std::string key ) {
	mCurrentFont = mFonts[key];
	mCurrentFont->LoadFont();
}

GLuint SceneManager::GetCurrentFontId() {
	if( mCurrentFont ){
		return mCurrentFont->GetDisplayId();
	}
	FatalError( "No Font Loaded." );
	return -1;
}

void SceneManager::CalculatePolygonCount() {
	mPolygonTotal = 0;
	mVerticesTotal = 0;
	std::map<std::string, Node*>::iterator tNode;
	for (tNode = mNodes.begin(); tNode != mNodes.end(); ++tNode) {
		mPolygonTotal += tNode->second->GetPolygonCount();
		mVerticesTotal += tNode->second->GetVerticeCount();
	}
}

int SceneManager::GetTotalPolygons(){
	return mPolygonTotal;
}

int SceneManager::GetTotalVertices(){
	return mVerticesTotal;
}

void SceneManager::SetDrawMode( int mode ) {
	mDrawMode = mode;
}

int SceneManager::GetDrawMode() {
	return mDrawMode;
}