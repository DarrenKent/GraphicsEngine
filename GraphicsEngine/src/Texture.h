/*
*
*	Graphics Engine
*	By: Darren Kent
*
*/

#ifndef _TEXTURE_
#define _TEXTURE_

#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <string>

// Texture Class
class Texture {
	public:
		Texture();											// Constructor
		
		void LoadTexture(	std::string filename,
							bool wrap );					// Loads a texture from a file
		GLuint LoadTgaImage(	std::string filename,
								bool wrap );				// Loads a TGA file
		GLuint LoadBmpImage(	std::string filename,
								bool wrap );				// Loads a BMP file
		GLuint LoadJpgImage(	std::string filename,
								bool wrap );				// Loads a JPG file
		GLuint LoadPngImage(	std::string filename,
								bool wrap );				// Loads a PNG file
		
		float GetImageWidth();								// Returns the Image Width
		float GetImageHeight();								// Returns the Image Height
		bool GetTextureWrap();								// Returns the texture wrap
		GLuint GetTextureId();								// Returns the Texture Id
	protected:
	private:
		std::string	mLabel;									// Texture Label
		GLuint		mTextureId[1];							// Texture Display List Id
		bool		mWrap;									// Texture Wrap
		float		mWidth;									// Texture Width
		float		mHeight;								// Texture Height
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

#endif _TEXUTRE_