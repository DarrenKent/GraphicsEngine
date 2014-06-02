/*
*
*	Graphics Engine
*	By: Darren Kent
*
*/

#ifndef _GEOMETRY_
#define _GEOMETRY_

#include "Texture.h"

struct Vector3;
struct Vecotr4;
struct Vertex;
struct Face;
struct Material;
struct Color4;

struct Vector3 {
	float x;
	float y;
	float z;

	Vector3() {
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
};

struct Vector4 {
	float x;
	float y;
	float z;
	float w;

	Vector4() {
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;
	}
};

struct Color4 {
	float red;
	float green;
	float blue;
	float alpha;

	Color4() {
		red   = 1.0f;
		green = 1.0f;
		blue  = 1.0f;
		alpha = 1.0f;
	}
};

struct Vertex {
	Vector3 pos;
	Vector3 normal;
	Vector3 texCoord;
	Color4	color;

	Vertex() {
		pos		 = Vector3();
		normal	 = Vector3();
		texCoord = Vector3();
		color	 = Color4();
	}
};

struct Material {
	Color4 ambient;
	Color4 diffuse;
	Color4 specular;
	float shine;
	float transparency;
	bool lighted;
	Texture *texture;

	Material() {
		ambient		 = Color4();
		diffuse		 = Color4();
		specular	 = Color4();
		shine		 = 32.0f;
		transparency = 1.0f;
		lighted		 = true;
		texture		 = NULL;
	}
};

struct Face {
	Vertex v1;
	Vertex v2;
	Vertex v3;
	Material mat;

	Face() {
		v1  = Vertex();
		v2  = Vertex();
		v3  = Vertex();
		mat = Material();
	}
};

#endif // _GEOMETRY_
