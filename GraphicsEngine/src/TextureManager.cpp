/*
*
*	Star Wars: Astromechs
*	By: Darren Kent
*
*/
#include <iostream>
#include <vector>

#include "Debug.h"
#include "TextureManager.h"

TextureManager::TextureManager() {
	mTextureCount = -1;
	glGenTextures( MAX_TEXTURES, mTextureNames );
}

TextureManager::~TextureManager() {}

void TextureManager::SetTextureCount( int count ) {
	mTextureCount = count;
}

GLuint TextureManager::LoadTexture( std::string filename, bool wrap ) {
	if ( mTextureMap[filename] ){
		DebugMessage( "Texture: " + filename + " Already exists. Using previously loaded Texture", 3 );
		return mTextureMap[filename];
	} else {
		DebugMessage( "Loading Image: " + filename, 3 );
		std::string tEnding = filename.substr( filename.find( '.' ) );
		GLuint tTexture = -1;
		if ( tEnding == ".tga" ){
			tTexture = LoadTgaImage( filename, wrap );
		} else if ( tEnding == ".bmp" ) {
			FatalError( "BMP format is not yet Supported." );
		} else if ( tEnding == ".jpg" ) {
			FatalError( "JPG format is not yet Supported." );
		} else if( tEnding == ".png" ) {
			FatalError( "PNG format is not yet Supported." );
		} else {
			FatalError( "Unsupported File Format." );
		}

		if ( tTexture < 0 || tTexture == NULL )
			FatalError( "Could Not Load Image: " + filename );

		mTextureMap[filename] = tTexture;
		return tTexture;
	}
}

GLuint TextureManager::LoadTgaImage( std::string filename, bool wrap ) {
	FILE *tFile;
	fopen_s( &tFile, filename.c_str(), "rb" );
	if ( !tFile )
		return NULL;
	
	TGA_FOOTER tFooter;
	TGA_HEADER tHeader;

	if ( fseek( tFile, 0L - sizeof( tFooter ), SEEK_END ) || fread( &tFooter, sizeof( tFooter ), 1, tFile) != 1 )
		FatalError( "Cannot Read TGA footer" );

	if ( memcmp( tFooter.signature, "TRUEVISION-XFILE.\0", sizeof( tFooter.signature ) ) == 0 )
		DebugMessage( "Using Newer Version TGA", 4 );
	else
		DebugMessage( "Using Older Version TGA", 4 );

	if ( fseek( tFile, 0, SEEK_SET ) || fread( &tHeader,sizeof( tHeader ), 1, tFile ) != 1 )
		FatalError( "Cannot Read TGA header" );

	if ( tHeader.id && fseek( tFile, tHeader.id, SEEK_CUR ) )
		FatalError( "TGA header error" );

	int tWidth		= abs( ( tHeader.widthEnd << 8 ) | tHeader.width );
	int tHeight		= abs( ( tHeader.heightEnd << 8 ) | tHeader.height );
	int tPixelDepth	= abs( tHeader.pixelDepth );
	DebugMessage( "Image Width: " + std::to_string( (long double)tWidth ), 4 );
	DebugMessage( "Image Height: " + std::to_string( (long double)tHeight ), 4 );
	DebugMessage( "Image Depth: " + std::to_string( (long double)tPixelDepth ), 4 );

	int tTextureType;
	if ( tPixelDepth == 24 ) {
		tTextureType = GL_BGR_EXT;
		DebugMessage( "Using GL_BGR_EXT color Mode.", 4 );
	}
	else {
		tTextureType = GL_BGRA_EXT;
		DebugMessage( "Using GL_BGRA_EXT color Mode.", 4 );
	}

	if ( tHeader.imageType == 1 )
		FatalError( "Indexed TGA is not yet supported" );
	if ( tHeader.imageType == 9 || tHeader.imageType == 10 || tHeader.imageType == 11 )
		FatalError( "Compressed TGA is not yet supported" );

	int tMode		= tPixelDepth / 8;
	int tTotalBytes	= tHeight * tWidth * tMode;

	GLubyte *tImageData = (GLubyte*)malloc( tTotalBytes );
	if ( tImageData == NULL )
		FatalError( "TGA memory error. Tried to Allocate " + std::to_string( (long double)tTotalBytes ) + " bytes and failed." );

	int tWidthBytes = tWidth * tMode;
	GLubyte * tData;

	for ( int iRow = 0; iRow < tHeight; ++iRow) {
		tData = tImageData + iRow * tWidthBytes;
		if ( fread( tData, tMode, tWidth, tFile) != tWidth )
			FatalError( "Could not Read TGA Image Data" );
	}

	fclose( tFile );

	mTextureCount += 1;

	glGenTextures( 1, &mTextureNames[mTextureCount] );
	glBindTexture( GL_TEXTURE_2D, mTextureNames[mTextureCount] );

	if( wrap ){
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	} else {
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
	}

	gluBuild2DMipmaps( GL_TEXTURE_2D, 4, tWidth, tHeight, tTextureType, GL_UNSIGNED_BYTE, tImageData );
	//glTexImage2D( GL_TEXTURE_2D, 0, 4, tWidth, tHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, tImageData );

	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

	return mTextureNames[mTextureCount];
}