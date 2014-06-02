/*
*
*	Graphics Engine
*	By: Darren Kent
*
*/

#ifndef _SHADER_MANAGER_
#define _SHADER_MANAGER_

#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <iostream>
#include <map>

#define VERTEX_SHADER	0
#define FRAGMENT_SHADER 1

class Shader {
	public:
		Shader( std::string filename, int type );

		void LoadShader( std::string filename, int type );
		void AttachShader( GLenum shaderProgram );
		GLenum GetShaderHandle();
	protected:
	private:
		int				mType;
		std::string		mShaderSource;
		GLenum			mShader;
};

class ShaderProgram {
	public:
		ShaderProgram();

		void CreateProgram();
		void UseProgram();
		GLenum GetProgramHandle();
	protected:
	private:
		GLenum			mProgram;
};

class ShaderManager {
	public:
		ShaderManager();

		void CreateShader( std::string id, std::string filename, int type );
		void CreateProgram( std::string id );
		void AttachShader( std::string programId, std::string shaderId );
		void UseProgram( std::string programId );
		void ClearProgram();
		ShaderProgram* GetProgram( std::string program );
	protected:
	private:
		std::map<std::string, Shader*>			mShaders;
		std::map<std::string, ShaderProgram*>	mPrograms;
};

#endif // _SCENE_MANAGER_