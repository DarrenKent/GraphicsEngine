/*
*
*	Graphics Engine
*	By: Darren Kent
*
*/

#ifndef _FONT_HANDLE_
#define _FONT_HANDLE_

#include <Windows.h>
#include <gl\GL.h>

// Font Handle Class
class FontHandle {
	public:
		FontHandle( HDC hDC );								// Font Constructor
		FontHandle( HDC hDC, LPCWSTR name, int size );		// Secondary Font Constructor

		void LoadFont();									// Loads all of the font details
		void SetHeight( int height );						// Sets the font height
		void SetWidth( int width );							// Sets the font width
		void SetRotation( int degrees );					// Sets the rotation
		void SetWeight( int weight );						// Sets the font weight
		void SetItalic( bool italic );						// Set italics
		void SetUnderline( bool underline );				// Set underline
		void SetStrikeout( bool strike );					// Set strikeout
		void SetFontName( LPCWSTR name );					// Set font name
		GLuint GetDisplayId();								// Get the Display List Id
	protected:
	private:
		int		mHeight;									// Font size. > 0 = based on Cell height. < 0 = based on Character height.
		int		mWidth;										// Adjustment to width
		int		mRotation;									// Rotation of the font
		int		mWeight;									// Font boldness
		bool	mItalic;									// Italic or not
		bool	mUnderline;									// Underline or not
		bool	mStrikeout;									// Strikeout or not.
		GLuint	mListId;									// Display List Id
		LPCWSTR mFontName;									// Name of font to use
		HDC		hDC;										// Display Controller Handle
};

#endif // _FONT_HANDLE_