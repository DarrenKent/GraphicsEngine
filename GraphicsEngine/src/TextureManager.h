/*
*
*	Star Wars: Astromechs
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

class TextureManager {
	public:
		TextureManager();									// Texture Manager Constructor
		~TextureManager();									// Texture Manager Deconstructor

		void SetTextureCount( int count );					// Sets the Number of textures

		GLuint LoadTexture(		std::string filename,			
								bool wrap );				// Load a Texture
		GLuint LoadTgaImage(	std::string filename, 
								bool wrap );				// Load TGA Image
	protected:
	private:
		static const int	MAX_TEXTURES = 64;				// Maximum number of textures allowed.
		GLuint				mTextureCount;					// Number of Textures to be loaded.
		GLuint				mTextureNames[MAX_TEXTURES];	// Array of Texture Names
		std::map<std::string, GLuint> mTextureMap;			// Map of all textures keyed by texture name
};

// File Structures

typedef struct{
	char id;												// Id Length
	char colorMap;											// Color Map Type
	char imageType;											// Image Type
	char colorMapOrigin;									// Color Map Origin
	char colorMapOriginEnd;									
	char colorMapLength;									// Color Map Length
	char colorMapLengthEnd;
	char colorMapDepth;										// Depth of Color Map Entries
	char xOffset;											// X Origin of Image
	char xOffsetEnd;
	char yOffset;											// Y Origin of Image
	char yOffsetEnd;
	char width;												// Width of Image
	char widthEnd;
	char height;											// Height of Image
	char heightEnd;
	char pixelDepth;										// Depth of Image
	char imageDescriptor;									// Image Descriptor
} TGA_HEADER;

typedef struct{
	unsigned int	extensionOffset;						// Extension Area Offset
	unsigned int	developerOffset;						// Developer Directory Offset
	char			signature[18];							// TGA Signature
} TGA_FOOTER;

#endif // _TEXTURE_MANAGER_