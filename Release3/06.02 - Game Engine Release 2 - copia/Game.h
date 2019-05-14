#pragma once


//Third-party libraries
#include <GL/glew.h>			//The OpenGL Extension Wrangler
#define GLM_FORCE_RADIANS
#define CAMERANUM 3

#define SCOREOBJECT 2
#define WINOBJECT SCOREOBJECT + 1
#define LOSEOBJECT WINOBJECT + 1
#define RESTARTOBJECT LOSEOBJECT + 1

#include <glm/glm.hpp>			//OpenGL Mathematics 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "Window.h"
#include "GLSLProgram.h"
#include "FPSLimiter.h"
#include "OpenGLBuffers.h"
#include "Vertex.h"
#include "Geometry.h"
#include "InputManager.h"
#include "Camera.h"
#include "Player.h"
#include "TextManager.h"
#include <string.h>
#include "matManager.h"

//Game has four possible states: INIT (Preparing environment), PLAY (Playing), EXIT (Exit from the game) or MENU (Game menu)
enum class GameState{INIT,MAIN, PLAY, EXIT, MENU};

//This class manages the game execution
class Game {
	public:						
		Game(std::string windowTitle, int screenWidth, int screenHeight, bool enableLimiterFPS, int maxFPS, bool printFPS);	//Constructor
		~Game();					//Destructor
		void run();					//Game execution

	private:
			//Attributes	
		std::string _windowTitle;		//Window Title
		int _screenWidth;				//Screen width in pixels				
		int _screenHeight;			//Screen height in pixels				
		int actualCamera;
		int _drawMode;
		int lightType;
		//int lightType;

		bool polygonMode;
		bool bothModes;
		bool win, lose;
		int countOfEnemies;
		int enemyCount;
		int gameLight;
		int lightSource;
		float publicAmbient;
		GameState _gameState;			//It describes the game state				
	//	Window _window;					//Manage the OpenGL context
		Window _window2;
		GLSLProgram _colorProgram;		//Manage the shader programs
		FPSLimiter _fpsLimiter;			//Manage the synchronization between frame rate and refresh rate
		OpenGLBuffers _openGLBuffers;	//Manage the openGL buffers
		Geometry _gameElements;			//Manage the game elements
		InputManager _inputManager;		//Manage the input devices

		GLuint modelMatrixUniform;
		GLuint viewMatrixUniform;
		GLuint projectionMatrixUniform;
		GLuint textureLocation;
		GLint _textureScaleFactorLocation;
		GLuint _drawModeUniform;

		GLuint _materialAmbientUniform;
		GLuint _materialDiffuseUniform;
		GLuint _materialSpecularUniform;
		GLuint _materialShininessUniform;

		GLuint _lightAmbientUniform;
		GLuint _lightDiffuseUniform;
		GLuint _lightSpecularUniform;
		GLuint _lightShininessUniform;
		GLuint _lightType;
		GLuint _lightDirection;

		GLint _lightingEnabled;
		GLint _isALightSource;
		GLuint _lightPosition;
		GLuint _viewerPosition;
		
		
		
		GLuint modelNormalMatrix;

		 
		Camera _camera[3];
		Player _mainPlayer;
		Spawner _spawner;
		//TextureManager _textureManager;
		TextManager _textManager;
		glm::mat4 modelMatrix;
		matManager _materialManager;
		
		
			//Internal methods
		void initSystems();
		void initShaders();		
		void gameLoop();
		void createPrimitivesToRender();
		void processInput();
		void doPhysics();
		void executePlayerCommands();
		void renderGame();		
		void loadGameTextures();
		void showGameProperties();
		void calculateCollision(int id);
	
		void executeMenuCommands();
		void renderMenu();

		void renderUI(int id);
		void gameObjectPhysics(int id);

		void renderGameObjects(int actualCm,int id);
};

