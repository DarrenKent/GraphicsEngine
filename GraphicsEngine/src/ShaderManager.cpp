/*
*
*	Graphics Engine
*	By: Darren Kent
*
*/

#include <fstream>
#include <GL\glew.h>
#include <sstream>

#include "Debug.h"
#include "ShaderManager.h"

Shader::Shader( std::string filename, int type ) {
	mShader = NULL;
	LoadShader( filename, type );
}

void Shader::LoadShader( std::string filename, int type ) {
	if ( type == VERTEX_SHADER )
		mShader = glCreateShader( GL_VERTEX_SHADER );
	else if ( type == FRAGMENT_SHADER )
		mShader = glCreateShader( GL_FRAGMENT_SHADER );
	else
		FatalError( "Shader type not recognized." );

	DebugMessage( "Loading Shader: " + filename, 3 );
	mType = type;
	mShaderSource = "";

	std::string		tLine;
	std::ifstream	tFile( filename );

	if ( tFile.is_open() ) {
		while ( tFile.good() ) {
			getline( tFile, tLine );
			std::istringstream	tStringStream( tLine );

			mShaderSource += tLine;
		}
	} else {
		FatalError( "Unable to open shader file: " + filename );
	}

	const char * tShader = mShaderSource.c_str();
	glShaderSource( mShader, 1, &tShader, NULL );

	glCompileShader( mShader );

    int tInfoLogSize	= 0;
    int tCharsWritten	= 0;
    char *tInfoLog;

    glGetShaderiv( mShader, GL_INFO_LOG_LENGTH, &tInfoLogSize );
    if (tInfoLogSize > 0)
    {
        tInfoLog = (char *)malloc( tInfoLogSize );
        glGetShaderInfoLog( mShader, tInfoLogSize, &tCharsWritten, tInfoLog);
		std::cout << tInfoLog << std::endl;
        free( tInfoLog );
    }
}

GLenum Shader::GetShaderHandle() {
	return mShader;
}


ShaderProgram::ShaderProgram() {
	mProgram = NULL;
	CreateProgram();
}

void ShaderProgram::CreateProgram() {
	mProgram = glCreateProgram();
}

void ShaderProgram::UseProgram() {
	glUseProgram( mProgram );
}

GLenum ShaderProgram::GetProgramHandle() {
	return mProgram;
}


ShaderManager::ShaderManager() {
	DebugMessage( "Initializing Shader Manager...", 2 );
	glewInit();
}

void ShaderManager::CreateShader( std::string id, std::string filename, int type ) {
	Shader *tShader = new Shader( filename, type );
	mShaders[id] = tShader;
}

void ShaderManager::CreateProgram( std::string id ) {
	ShaderProgram *tProg = new ShaderProgram();
	mPrograms[id] = tProg;
}

void ShaderManager::AttachShader( std::string programId, std::string shaderId ) {
	Shader *tShader			= mShaders[shaderId];
	ShaderProgram *tProgram = mPrograms[programId];
	glAttachShader( tProgram->GetProgramHandle(), tShader->GetShaderHandle() );
	glLinkProgram( mPrograms[programId]->GetProgramHandle() );
}

void ShaderManager::UseProgram( std::string programId ) {
	mPrograms[programId]->UseProgram();
}

void ShaderManager::ClearProgram() {
	glUseProgram( 0 );
}

ShaderProgram* ShaderManager::GetProgram( std::string program ) {
	return mPrograms[program];
}