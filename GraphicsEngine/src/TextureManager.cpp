/*
*
*	Graphics Engine
*	By: Darren Kent
*
*/

#include <iostream>
#include <vector>

#include "Debug.h"
#include "TextureManager.h"

TextureManager::TextureManager() {}

TextureManager::~TextureManager() {}

Texture* TextureManager::LoadTexture( std::string key, std::string filename, bool wrap ) {
	if ( mTextureMap[key] ){
		DebugMessage( "Texture: " + filename + " Already exists. Using previously loaded Texture", 3 );
		return mTextureMap[key];
	} else {
		DebugMessage( "Loading Image: " + filename, 3 );
		Texture *tTexture = new Texture();
		tTexture->LoadTexture( filename, wrap );
		mTextureMap[key] = tTexture;
		return tTexture;
	}
}

GLuint TextureManager::GetTextureId( std::string key ) {
	return mTextureMap[key]->GetTextureId();
}