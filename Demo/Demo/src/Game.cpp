/*
*
*	Graphics Engine Demo
*	By: Darren Kent
*
*/

#include <Windows.h>
#include <fstream>
#include <GL/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <iostream>
#include <sstream>

#include "Debug.h"
#include "Game.h"
#include "Input.h"

float COUNT = 0;

Game::Game() : Application() {

	mCamera	= new OrbitalCamera();
	mCamera->SetCameraPos( 0.0f, 0.0f, 0.0f );
	mCamera->SetCameraRadius( 400.0f );
	mCamera->SetCameraTheta( 10.0f );
	mCamera->SetCameraAlpha( 50.0f );
	mCamera->SetTargetPos( 0.0f, 0.0f, 0.0f );
	mCamera->PositionCamera();
}

void Game::Start() {
	DebugMessage( "Starting Up Main Loop..." , 3 );
	while( mActive ) {
		StartFrame();
		GameLogic();
		DrawFrame();
		EndFrame();
	}
}

void Game::InitializeGame() {
	mModel = new Model();
	mModel->LoadModel("test.obj",NULL);
	mModel->SetColor( 1.0, 0.0, 0.0 );

	glewInit();
	const char* tVertexSource = { 
	"in vec3 vertex;"
	"in vec3 normal;"
	"uniform vec3 light_position;"
	"uniform mat4 Projection;"
	"uniform mat4 View;"
	"uniform mat4 Model;"
	"out vec3 light_vector;"
	"out vec3 normal_vector;"
	"out vec3 halfway_vector;"
	"out vec3 texture_coord;"
	"void main() {"
	"gl_Position = Projectin * View * Model * vec4(vertex,1.0);"
	"vec4 v = View * Model * vec4(vertex,1.0);"
	"vec3 normal1 = normalize(normal);"
	"light_vector = normalize((View*vec4(light_position,1.0)).xyz - v.xyz);"
	"normal_vector = (inverse(transpose(View*MOdel)) * vec4(normal1,0.0)).xyz;"
	"texture_coord = (inverse(transpose(Model)) * vec4(normal1,0.0)).xyz;"
	"halfway_vector = light_vector + normalize(-v.xyz);"
	"}" };
	const char* tFragmentSource = { 
	"in vec3 normal_vector;"
	"in vec3 light_vector;"
	"in vec3 halfway_vector;"
	"in vec3 texture_coord;"
	"uniform samplerCube cubemap;"
	"out vec4 fragColor;"
 
	"void main (void) {"
    "vec3 normal1         = normalize(normal_vector);"
    "vec3 light_vector1   = normalize(light_vector);"
    "vec3 halfway_vector1 = normalize(halfway_vector);"
 
    "vec4 c = texture(cubemap, texture_coord);"
 
    "vec4 emissive_color = vec4(0.0, 1.0, 0.0, 1.0); // green"
    "vec4 ambient_color  = vec4(1.0, 1.0, 1.0, 1.0); // white"
    "vec4 diffuse_color  = vec4(1.0, 1.0, 1.0, 1.0); // white"
    "vec4 specular_color = vec4(0.0, 0.0, 1.0, 1.0); // blue"
 
    "float emissive_contribution = 0.02;"
    "float ambient_contribution  = 0.20;"
    "float diffuse_contribution  = 0.40;"
    "float specular_contribution = 0.38;"
 
    "float d = dot(normal1, light_vector1);"
    "bool facing = d > 0.0;"
 
    "fragColor = emissive_color * emissive_contribution + ambient_color  * ambient_contribution  * c + diffuse_color  * diffuse_contribution  * c * max(d, 0) + (facing ? specular_color * specular_contribution * c * pow(dot(normal1, halfway_vector1), 80.0) : vec4(0.0, 0.0, 0.0, 0.0));"
    "fragColor.a = 1.0;"
	"}"};
	mShaderProgram  = glCreateProgram();
	mVertexShader = glCreateShader( GL_VERTEX_SHADER );
	mFragmentShader = glCreateShader( GL_FRAGMENT_SHADER );

	glShaderSource( mFragmentShader, 1, &tFragmentSource, NULL );
	glShaderSource( mVertexShader, 1, &tVertexSource, NULL );

	glCompileShader( mVertexShader );
	glAttachShader( mShaderProgram, mVertexShader );

	glCompileShader( mFragmentShader );
	glAttachShader( mShaderProgram, mFragmentShader );

	glLinkProgram( mShaderProgram );
}

void Game::GameLogic() {}

void Game::ProcessInput() {
	if ( GetKeyPressed( VK_ESCAPE ) )
		exit(0);
}

void Game::DrawFrame() {
	ProcessInput();

	DISPLAY_MGR->SetPerspectiveProjection( 30.0f, 2.0f, 1000000.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();

	glEnable( GL_DEPTH_TEST );
	mCamera->PositionCamera();

	glUseProgram( mShaderProgram );

	glPushMatrix();
		mModel->DrawModel();
	glPopMatrix();

	glUseProgram(0);
}
