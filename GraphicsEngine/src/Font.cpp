/*
*
*	Star Wars: Astromechs
*	By: Darren Kent
*
*/
#include <iostream>
#include <stdio.h>

#include "Font.h"

FontHandle::FontHandle( HDC hDC ) {
		mHeight		= -12;
		mWidth		= 0;
		mRotation	= 0;
		mWeight		= FW_BOLD;
		mItalic		= false;
		mUnderline	= false;
		mStrikeout	= false;
		mFontName	= L"Courier New";
		this->hDC	= hDC;
		mListId		= -1;
}

FontHandle::FontHandle( HDC hDC, LPCWSTR name, int size ) {
		mHeight		= size;
		mWidth		= 0;
		mRotation	= 0;
		mWeight		= FW_NORMAL;
		mItalic		= false;
		mUnderline	= false;
		mStrikeout	= false;
		mFontName	= name;
		this->hDC	= hDC;
		mListId		= -1;
}

void FontHandle::LoadFont() {
	HFONT tFont;
	HFONT tFinalFont;
	GLuint chars;
	
	chars		= glGenLists( 96 );
	mListId		= chars;
	tFont		= CreateFont(	mHeight, mWidth, mRotation, 0,
								mWeight, mItalic, mUnderline,
								mStrikeout, ANSI_CHARSET,
								OUT_TT_PRECIS, 
								CLIP_DEFAULT_PRECIS,
								ANTIALIASED_QUALITY,
								FF_DONTCARE|DEFAULT_PITCH,
								mFontName );
	tFinalFont	= (HFONT)SelectObject( hDC, tFont );
	wglUseFontBitmaps( hDC, 32, 96, chars );
	SelectObject( hDC, tFinalFont );
	DeleteObject( tFont );
}

void FontHandle::SetHeight( int height ) {
	mHeight = height;
}

void FontHandle::SetWidth( int width ) {
	mWidth = width;
}

void FontHandle::SetRotation( int degrees ) {
	mRotation = degrees;
}

void FontHandle::SetWeight( int weight ) {
	mWeight = weight;
}

void FontHandle::SetItalic( bool italic ) {
	mItalic = italic;
}

void FontHandle::SetUnderline( bool underline ) {
	mUnderline = underline;
}

void FontHandle::SetStrikeout( bool strike ) {
	mStrikeout = strike;
}

void FontHandle::SetFontName( LPCWSTR name ) {
	mFontName = name;
}

GLuint FontHandle::GetDisplayId() {
	return this->mListId;
}