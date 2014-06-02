/*
*
*	Graphics Engine
*	By: Darren Kent
*
*/

#ifndef _TEXTURE_MANAGER_
#define _TEXTURE_MANAGER_

#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <map>
#include <string>

#include "Texture.h"

// Texture Manager Class
class TextureManager {
	public:
		TextureManager();									// Texture Manager Constructor
		~TextureManager();									// Texture Manager Deconstructor

		Texture* LoadTexture(	std::string key,
								std::string filename,			
								bool wrap );				// Load a Texture
		GLuint GetTextureId( std::string key );				// Returns a Texture Display Id given a key
		Texture* GetTexture( std::string key );				// Returns a Texture Object
	protected:
	private:
		std::map<std::string, Texture*> mTextureMap;		// Map of all textures keyed by texture name
};


#endif // _TEXTURE_MANAGER_