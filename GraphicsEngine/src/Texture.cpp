/*
*
*	Graphics Engine
*	By: Darren Kent
*
*/

#include "Debug.h"
#include "Texture.h"

Texture::Texture() {
	mWrap	= false;
	mWidth	= 0;
	mHeight = 0;
	glGenTextures( 1, mTextureId );
}

void Texture::LoadTexture( std::string filename, bool wrap ) {
	DebugMessage( "Loading Image: " + filename, 3 );
	std::string tEnding = filename.substr( filename.find( '.' ) );
	
	GLuint tTexture = -1;
	mWrap = wrap;
	
	if ( tEnding == ".tga" ){
		tTexture = LoadTgaImage( filename, wrap );
	} else if ( tEnding == ".bmp" ) {
		tTexture = LoadBmpImage( filename, wrap );
	} else if ( tEnding == ".jpg" ) {
		tTexture = LoadJpgImage( filename, wrap );
	} else if( tEnding == ".png" ) {
		tTexture = LoadPngImage( filename, wrap );
	} else {
		FatalError( "Unsupported File Format." );
	}

	if ( tTexture < 0 || tTexture == NULL )
		FatalError( "Could Not Load Image: " + filename );
}

GLuint Texture::LoadTgaImage( std::string filename, bool wrap ) {
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

	glGenTextures( 1, &mTextureId[0] );
	glBindTexture( GL_TEXTURE_2D, mTextureId[0] );

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

	mWidth	= (float)tWidth;
	mHeight = (float)mHeight;
	return mTextureId[0];
}

GLuint Texture::LoadBmpImage( std::string filename, bool wrap ) {
	FatalError( "BMP Images currently are not supported." );
	return -1;
}

GLuint Texture::LoadJpgImage( std::string filename, bool wrap ) {
	FatalError( "JPG Images currently are not supported." );
	return -1;
}

GLuint Texture::LoadPngImage( std::string filename, bool wrap ) {
	FatalError( "PNG Images currently are not supported." );
	return -1;
}

float Texture::GetImageWidth() {
	return mWidth;
}

float Texture::GetImageHeight() {
	return mHeight;
}

bool Texture::GetTextureWrap() {
	return mWrap;
}

GLuint Texture::GetTextureId() {
	return mTextureId[0];
}