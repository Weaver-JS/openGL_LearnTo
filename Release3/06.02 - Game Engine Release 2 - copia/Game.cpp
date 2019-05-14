#include "Game.h"


/**
* Constructor
* Note: It uses an initialization list to set the parameters
* @param windowTitle is the window title
* @param screenWidth is the window width
* @param screenHeight is the window height
*/
Game::Game(std::string windowTitle, int screenWidth, int screenHeight, bool enableLimiterFPS, int maxFPS, bool printFPS) :
	_windowTitle(windowTitle), 
	_screenWidth(screenWidth), 
	_screenHeight(screenHeight),
	_gameState(GameState::INIT), 
	
	_fpsLimiter(enableLimiterFPS, maxFPS, printFPS) {


}

/**
* Destructor
*/
Game::~Game()
{
}

/*
* Game execution
*/
void Game::run() {
		//System initializations
	initSystems();
		//Start the game if all the elements are ready
	gameLoop();
}

/*
* Initializes all the game engine components
*/
void Game::initSystems() {
	win = false;
	lose = false;
	gameLight = 0;
	 lightSource = 1;
	 publicAmbient = 0;
	_drawMode = 1;
	enemyCount = 0;
	actualCamera = 0;
	_camera[0].setCamera(_screenWidth / _screenHeight, 90.0f, 50.0f, 0.1f, 30.0f, 100.0f, glm::vec3(-47.5f, 0.0f, 0.0f));
	_camera[1].setCamera(_screenWidth / _screenHeight, 90.0f, 30.0f, 0.1f, 30.0f, 100.0f, glm::vec3(0.0f, 0.0f, 3.0f));
	_camera[1].setOrtographic();
	_camera[2].setCamera(_screenWidth / _screenHeight, 45.0f, 100.0f, 0.1f, 30.0f, 100.0f, glm::vec3(-20.0f, 0.0f, 0.0f));
	
		//Create an Opengl window using SDL
	//_window.create(_windowTitle, _screenWidth, _screenHeight, 0);	
	
	_window2.create("WINDOW2 TEST", _screenWidth, _screenHeight, 0x2);//0x2

		//Compile and Link shader
	initShaders();
		//Set up the openGL buffers
	_openGLBuffers.initializeBuffers(_colorProgram);

		//Load the current scenario
	//_gameElements.loadGameElements("./resources/scene2D.txt");
	_gameElements.loadGameScene();
	loadGameTextures();

	
	_mainPlayer = Player(_gameElements.getGameElement(PLAYER)._translate, glm::vec3(0.5f, 0.0f, 0.0f),_gameElements);
//	_spawner = Spawner(_gameElements.getGameElement(PLAYER + 1)._translate - _gameElements.getGameElement(PLAYER + 1)._scale, _gameElements.getGameElement(2)._translate + _gameElements.getGameElement(PLAYER + 1)._scale, &_gameElements);
	//loadGameTextures();
}

/*
* Initialize the shaders:
* Compiles, sets the variables between C++ and the Shader program and links the shader program
*/
void Game::initShaders() {
	glActiveTexture(GL_TEXTURE0);
	

		//Compile the shaders
	_colorProgram.addShader(GL_VERTEX_SHADER, "./resources/shaders/vertex-shader.txt");
	_colorProgram.addShader(GL_FRAGMENT_SHADER, "./resources/shaders/fragment-shader.txt");
	_colorProgram.compileShaders();
		//Attributes must be added before linking the code
	_colorProgram.addAttribute("vertexPositionGame");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.addAttribute("vertexNormal");
		//Link the compiled shaders
	_colorProgram.linkShaders();
		//Bind the uniform variables. You must enable shaders before gettting the uniforme variable location
	_colorProgram.use();

	modelMatrixUniform = _colorProgram.getUniformLocation("modelMatrix");
	viewMatrixUniform = _colorProgram.getUniformLocation("viewMatrix");
	projectionMatrixUniform = _colorProgram.getUniformLocation("projectionMatrix");
	_drawModeUniform = _colorProgram.getUniformLocation("drawMode");
	textureLocation = _colorProgram.getUniformLocation("textureData");
	_textureScaleFactorLocation = _colorProgram.getUniformLocation("textureScaleFactor");

	_materialAmbientUniform = _colorProgram.getUniformLocation("material.ambient");
	_materialDiffuseUniform = _colorProgram.getUniformLocation("material.diffuse");
	_materialSpecularUniform = _colorProgram.getUniformLocation("material.specular");
	_materialShininessUniform = _colorProgram.getUniformLocation("material.shininess");

	 _lightingEnabled = _colorProgram.getUniformLocation("lightingEnabled");
	 _isALightSource = _colorProgram.getUniformLocation("isALightSource");
	 _lightPosition = _colorProgram.getUniformLocation("lightPosition");
	 _viewerPosition = _colorProgram.getUniformLocation("viewerPosition");
	 
	 _lightAmbientUniform = _colorProgram.getUniformLocation("lightColor.ambient");
	 _lightDiffuseUniform = _colorProgram.getUniformLocation("lightColor.diffuse");
	 _lightSpecularUniform = _colorProgram.getUniformLocation("lightColor.specular");
	 _lightType = _colorProgram.getUniformLocation("lightColor.type");
	 _lightDirection = _colorProgram.getUniformLocation("lightColor.direction");
	 modelNormalMatrix = _colorProgram.getUniformLocation("modelNormalMatrix");
	// _lightShininessUniform = _colorProgram.getUniformLocation("lightColor.shininess");


	
	_colorProgram.unuse();
}

/*
* Game execution: Gets input events, processes game logic and draws sprites on the screen
*/

void Game::loadGameTextures()
{
	GameObject currentGameObject;

	//Load the game Textures
	for (int i = 0; i < _gameElements.getNumGameElements();i++)
	{
		currentGameObject = _gameElements.getGameElement(i);
		switch (_gameElements.getGameElement(i)._objectType)
		{
		case ENEMY:
		_gameElements.getGameElement(i)._textureFIle = "../06.02 - Game Engine Release 2/resources/textures/NILO.jpg";
		break;

		case mainCharacter:
			_gameElements.getGameElement(i)._textureFIle = "../06.02 - Game Engine Release 2/resources/textures/Stone_moss.jpg";
			break;
		default:
			_gameElements.getGameElement(i)._textureFIle = "../06.02 - Game Engine Release 2/resources/textures/Stone_moss.jpg";
			break;

		}
		if (i == 0)
		{
			_gameElements.getGameElement(i)._textureFIle = "../06.02 - Game Engine Release 2/resources/textures/Nilo's ADVENTURE.jpg";
		}
	
		
		if (i == 1)
		{
			_gameElements.getGameElement(i)._textureFIle = "../06.02 - Game Engine Release 2/resources/textures/galaxy2.jpg";
			_gameElements.getGameElement(i)._textureRepetion = false;
		}
		
		if (i == SCOREOBJECT)
		{
		//	renderScore();
		}
		if (_gameElements.getGameElement(i)._objectType == PURPLE_PYRAMID)
		{
			_gameElements.getGameElement(i)._textureFIle = "../06.02 - Game Engine Release 2/resources/textures/Lava.jpg";
		}
		(_gameElements.getGameElement(i))._textureID = _gameElements.getTextureManager().getTextureID(_gameElements.getGameElement(i)._textureFIle);
	}
}

void Game::gameLoop() {	
	_gameState = GameState::MAIN;
	while (_gameState != GameState::EXIT) {		

		if (_gameState == GameState::MAIN)
		{
			actualCamera = 0;
			_camera[0].setCamera(_screenWidth / _screenHeight, 90.0f, 50.0f, 0.1f, 30.0f, 100.0f, glm::vec3(-47.5f, 0.0f, 0.0f));
			polygonMode = true;
			processInput();
			executeMenuCommands();
			renderMenu();
		}
		else
		{

			//Start synchronization between refresh rate and frame rate
			_fpsLimiter.startSynchronization();
			//Process the input information (keyboard and mouse)
			processInput();
			//Execute the player actions (keyboard and mouse)
			executePlayerCommands();
			//Update the game status
			doPhysics();
			_fpsLimiter.forceSynchronizationAnimation();
			//Draw the objects on the screen
			renderGame();
			//Force synchronization
			_fpsLimiter.forceSynchronization();
		}
	}
}

/*
* Processes input with SDL
*/
void Game::processInput() {
	_inputManager.update();
	//Review https://wiki.libsdl.org/SDL_Event to see the different kind of events
	//Moreover, table show the property affected for each event type
	SDL_Event evnt;
	//Will keep looping until there are no more events to process
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			_inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
			break;
		case SDL_KEYDOWN:
			_inputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.pressKey(evnt.button.button);
			
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.releaseKey(evnt.button.button);
			break;
		default:
			break;
		}
	}

}


/**
* Executes the actions sent by the user by means of the keyboard and mouse
*/
void Game::executePlayerCommands() {
	//loadGameTextures();
	//_gameElements.getGameElement(0)._translate = _camera.getCameraPos()  + glm::vec3(20.0f, 0.0f, 0.0f);
	if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT))
	{
		actualCamera += 1 ;
		actualCamera = actualCamera % CAMERANUM;

		glm::ivec2 mouseCoords = _inputManager.getMouseCoords();
		cout << mouseCoords.x << ", " << mouseCoords.y << endl;

	}
	if (_inputManager.isKeyPressed(SDLK_p))
	{
		lightType += 1;
		lightType = lightType % 2;
	}
	if (_inputManager.isKeyPressed(SDLK_ESCAPE))
	{
		_gameState = GameState::MAIN;
	}

	if (_inputManager.isKeyPressed(SDL_BUTTON_RIGHT))
	{
		if(!win && !lose)
		_mainPlayer.fire();
	}
	if (_inputManager.isKeyPressed(SDLK_t))
	{
		gameLight += 1;
		gameLight = gameLight % 2;
		
		std::cout<<"GameLight :" << gameLight << std::endl;
	}
	if (_inputManager.isKeyPressed(SDLK_r))
	{
		_drawMode += 1;
		_drawMode = _drawMode % 3;
		std::cout <<"DrawMode : " << _drawMode << std::endl;
		if (win || lose)
		{
			_gameElements.restart();
			_mainPlayer.restartScore();
			win = false;
			lose = false;
			//_gameElements.loadGameElements("./resources/scene2D.txt");
			_gameElements.loadGameScene();
			_camera[actualCamera].setPosition(glm::vec3(-47.5f, 0.0f, 0.0f));
		}
	}
	if (_inputManager.isKeyPressed(SDLK_b))
	{
		bothModes = !bothModes;
	}
	if (_inputManager.isKeyPressed(SDLK_f))
	{
		polygonMode = true;
	}
	if (_inputManager.isKeyPressed(SDLK_l))
	{
		polygonMode = false;
	}
	if (_inputManager.isKeyDown (SDLK_w)) {
		
		_camera[actualCamera].moveForward();
	}

	if (_inputManager.isKeyDown(SDLK_a)) {

		_camera[actualCamera].strafeLeft();
	}
	if (_inputManager.isKeyDown(SDLK_s)) {

		_camera[actualCamera].moveBackward();
	}

	if (_inputManager.isKeyDown(SDLK_d)) {
		
		_camera[actualCamera].strafeRight();
	}

	if (_inputManager.isKeyPressed(SDLK_p))
	{
		_camera[actualCamera].setPerspective();
	}
	if (_inputManager.isKeyPressed(SDLK_o))
	{
		_camera[actualCamera].setOrtographic();
	}

	if (_inputManager.isKeyPressed(SDLK_l))
	{
		lightSource += 1;
		lightSource = lightSource % 2;
		std::cout << "LightSource : " << lightSource << std::endl;
	}
	
	if (_inputManager.isKeyDown(SDLK_UP))
	{
		_camera[actualCamera].moveUp();
	}
	if (_inputManager.isKeyDown(SDLK_DOWN))
	{
		_camera[actualCamera].moveDown();
		
	}
	if (_inputManager.isKeyDown(SDLK_RIGHT))
	{
		if (_gameElements.getGameElement(PLAYER)._translate.y >= -2.8f)
		{
			_gameElements.getGameElement(PLAYER)._translate.y -= 0.1f;
			_camera[0].rotateCamera(glm::vec3(0.0f, -0.1f, 0.0f));
		}
		
	}
	if (_inputManager.isKeyDown(SDLK_LEFT))
	{
		if (_gameElements.getGameElement(PLAYER)._translate.y <= 2.8f)
		{
			_gameElements.getGameElement(PLAYER)._translate.y += 0.1f;
			_camera[0].rotateCamera(glm::vec3(0.0f, 0.1f, 0.0f));
		}
	}

	if (_inputManager.isKeyDown(SDLK_PLUS))
	{
		
		publicAmbient += 0.5f;
		
	}
	if (_inputManager.isKeyDown(SDLK_MINUS))
	{

		publicAmbient -= 0.5f;

	}

	_camera[actualCamera].refresh();
}

/*
* Update the game objects based on the physics
*/
void Game::doPhysics() {

	if (actualCamera == CAMERANUM - 1)
		_camera[actualCamera].strafeRight();

	showGameProperties();
	

}
void Game::showGameProperties()
{
	if (!win && !lose)
	{

		_gameElements.spawn();
		loadGameTextures();
		_gameElements.getSpawner().startTimer();
		//_spawner.startTimer();
		_mainPlayer.setPosition(_gameElements.getGameElement(PLAYER)._translate);
		for (int i = PLAYER + 2; i < _gameElements.getNumGameElements();i++)
		{
			calculateCollision(i);
		}
	

	}
	else
	{
		
		if (win)
		{
			renderUI(WINOBJECT);

			/*std::cout << "/*\*\*\*\*\*\*GAME OVER: YOU WIN/*\*\*\*\*\*\*" << std::endl;
			std::cout << "PRESS R TO REPLAY" << std::endl;*/
		}
		if (lose)
		{
			renderUI(LOSEOBJECT);
			/*std::cout << "/*\*\*\*\*\*\*GAME OVER: YOU LOSE/*\*\*\*\*\*\*" << std::endl;
			std::cout << "PRESS R TO REPLAY" << std::endl;*/
		}
		renderUI(RESTARTOBJECT);
	}
	_mainPlayer.getScore() -= 10;
}
void Game::calculateCollision(int id)
{
	enemyCount = 0;
	_gameElements.getGameElement(id).col.updateColliderPosition(_gameElements.getGameElement(id)._translate, _gameElements.getGameElement(id)._scale);
	for (int j = 0; j < _gameElements.getNumGameElements();j++)
	{

		if (_gameElements.getGameElement(j)._objectType == ENEMY)
		{
			enemyCount++;
		}

		if (id != j && j >= PLAYER + 2 && id >= PLAYER + 2)
		{

			if (_gameElements.getGameElement(id)._objectType == PURPLE_PYRAMID && _gameElements.getGameElement(j)._objectType != PURPLE_PYRAMID )
			{

				
				_gameElements.getGameElement(id).col.onCollisionEnter(_gameElements.getGameElement(j).col);

			}
			if (_gameElements.getGameElement(id)._translate.x > 46.0f && _gameElements.getGameElement(id)._objectType == PURPLE_PYRAMID)
			{
				_gameElements.getGameElement(id).col.onCollisionEnter(_gameElements.getGameElement(id).col);
			}
		}
	}

	if (enemyCount <= 0)
	{
		win = true;
	}

	if (enemyCount > 20)
	{
		lose = true;
	}
}

void Game::executeMenuCommands()
{
	if (_inputManager.isKeyPressed(SDLK_t))
	{
		gameLight += 1;
		gameLight = gameLight % 2;
		
	}

if (_inputManager.isKeyPressed(SDLK_ESCAPE))
	{
		_gameState = GameState::EXIT;
	}
if (_inputManager.isKeyPressed(SDLK_r))
{
	_drawMode += 1;
	_drawMode = _drawMode % 3;
	std::cout << gameLight << std::endl;

}

if (_inputManager.isKeyPressed(SDLK_l))
{
	lightSource += 1;
	lightSource = lightSource % 2;
	std::cout << "LightSource : " << lightSource << std::endl;
}

if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT))
{

	if (_inputManager.getMouseCoords().x > 850.0f && _inputManager.getMouseCoords().x < 1050.0f && _inputManager.getMouseCoords().y > 600.0f && _inputManager.getMouseCoords().y < 780.0f)
	{
		_gameState = GameState::PLAY;
	}
	if (_inputManager.getMouseCoords().x > 850.0f && _inputManager.getMouseCoords().x < 1050.0f && _inputManager.getMouseCoords().y > 800.0f && _inputManager.getMouseCoords().y < 980.0f)
	{
		_gameState = GameState::EXIT;
	}
}

}
void Game::renderMenu()
{
	//loadGameTextures();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
		renderGameObjects(actualCamera, 0);
	

	//Unbind the program
	_colorProgram.unuse();

	//Swap the display buffers (displays what was just drawn)


	_window2.swapBuffer();
	glFlush();
}
void Game::renderUI(int id)
{
	modelMatrix = glm::mat4(1.0f);
	GameObject currentRenderedGameElement;

	//Bind the GLSL program. Only one code GLSL can be used at the same time
	_colorProgram.use();
	glActiveTexture(GL_TEXTURE0);
	SDL_Color col;
	std::string _score;
	switch (id)
	{
	case SCOREOBJECT:
		_score = "Score:" + std::to_string(_mainPlayer.getScore());
		col.r = 255;
		col.b = 255;
		col.g = 255;
		break;
	case WINOBJECT:
		_score = "YOU WIN";
		col.r = 0;
		col.b = 255;
		col.g = 0;
		break;

	case LOSEOBJECT:
		_score = "YOU LOSE";
		col.r = 255;
		col.b = 0;
		col.g = 0;
		break;
	case RESTARTOBJECT:
		_score = "Press 'r' to restart ";
		col.r = 255;
		col.b = 255;
		col.g = 255;
		break;
	}
	//For each one of the elements: Each object MUST BE RENDERED based on its position, rotation and scale data
	


	
	
	_gameElements.getGameElement(id)._textureID = _textManager.getTextureID(_score, col);
	currentRenderedGameElement = _gameElements.getGameElement(id);
	//TODO: Compute its model transformation matrix

	//TODO: Pass the matrix as an uniform variable 	


		modelMatrix = glm::translate(modelMatrix, _gameElements.getGameElement(id)._translate);
		modelMatrix = glm::scale(modelMatrix, _gameElements.getGameElement(id)._scale);
	
		

	glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0)));
	glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0)));
	//Texture
	glBindTexture(GL_TEXTURE_2D, currentRenderedGameElement._textureID);

	glUniform1f(textureLocation, 0);
	glUniform1i(_drawModeUniform, _drawMode);

	

	
	//Send data to GPU
	
		
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	_openGLBuffers.sendDataToGPU(_gameElements.getData(currentRenderedGameElement._objectType), _gameElements.getNumVertices(currentRenderedGameElement._objectType));
	glBindTexture(GL_TEXTURE_2D, 0);
}
void Game::gameObjectPhysics(int id)
{

}
/**
* Draw the sprites on the screen
*/
void Game::renderGame()
{
		//Temporal variable
	

		//Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	for (int i = 1; i < _gameElements.getNumGameElements();i++)
	{
		if (i == SCOREOBJECT)
		{
			renderUI(SCOREOBJECT);
		}
		if (lose && i == LOSEOBJECT)
		{
			renderUI(LOSEOBJECT);
			renderUI(RESTARTOBJECT);
		}
		if (win && i == WINOBJECT)
		{
			renderUI(WINOBJECT);
			renderUI(RESTARTOBJECT);
		}
		
		else if ( i != SCOREOBJECT && i != LOSEOBJECT && i != WINOBJECT)
		{
			renderGameObjects(actualCamera, i);
		}
		
		
	}

	//Unbind the program
	_colorProgram.unuse();

	//Swap the display buffers (displays what was just drawn)
	
	
	_window2.swapBuffer();
	glFlush();


}

void Game::renderGameObjects(int actualCm,int id)
{
	modelMatrix = glm::mat4(1.0f);
	material currentMaterial;
	GameObject currentRenderedGameElement;
	
	//Bind the GLSL program. Only one code GLSL can be used at the same time
	_colorProgram.use();
	glActiveTexture(GL_TEXTURE0);

	//For each one of the elements: Each object MUST BE RENDERED based on its position, rotation and scale data
	if (_gameElements.getGameElement(id)._objectType == mainCharacter)
	{
		_gameElements.getGameElement(id)._materialType = CHROME;
	}
	else
	{
		_gameElements.getGameElement(id)._materialType = WHITE_RUBBER;
	}
		currentRenderedGameElement = _gameElements.getGameElement(id);
		
		currentMaterial = _materialManager.getMaterialComponents(currentRenderedGameElement._materialType);
		//TODO: Compute its model transformation matrix

		//TODO: Pass the matrix as an uniform variable 	
	
		/*Model Matrix*/
		modelMatrix = glm::translate(modelMatrix, _gameElements.getGameElement(id)._translate);

	

		if (_gameElements.getGameElement(id)._objectType == PURPLE_PYRAMID)
		{
			modelMatrix = glm::rotate(modelMatrix, glm::radians(currentRenderedGameElement._angle), currentRenderedGameElement._rotation);
			_gameElements.getGameElement(id)._translate += _mainPlayer.getVelocity();
			modelMatrix = glm::scale(modelMatrix, _gameElements.getGameElement(id)._scale);
			_gameElements.getGameElement(id).col.updateColliderPosition(_gameElements.getGameElement(id)._translate, _gameElements.getGameElement(id)._scale);

		}
		else
		{
			
			modelMatrix = glm::scale(modelMatrix, _gameElements.getGameElement(id)._scale);
		}
		 

	/* _material = _colorProgram.getUniformLocation("material");
	 _lightMaterial = _colorProgram.getUniformLocation("lightColor");*/

		
		currentMaterial.ambient += publicAmbient;
		
		glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, glm::value_ptr(_camera[actualCm].getViewMatrix()));
		glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(_camera[actualCm].getProjectionMatrix()));
		//Texture
		glBindTexture(GL_TEXTURE_2D, _gameElements.getGameElement(id)._textureID);

		
		glUniform3fv(_materialAmbientUniform, 1, glm::value_ptr(currentMaterial.ambient));
		glUniform3fv(_materialDiffuseUniform, 1, glm::value_ptr(currentMaterial.diffuse));
		glUniform3fv(_materialSpecularUniform, 1, glm::value_ptr(currentMaterial.specular));
		glUniform1f(_materialShininessUniform, currentMaterial.shininess);

		
		
		 
		//lightPos.z -=90.0f;
		glUniform1i(_lightingEnabled, gameLight);
		
		
		glUniform1i(_isALightSource, lightSource);
		
		

		glUniform3fv(_viewerPosition, 1, glm::value_ptr(_mainPlayer.getPosition()));
		glm::vec3 _lightPos = _camera[actualCamera].getCameraPos();
		if (_gameElements.getGameElement(id)._objectType == ENEMY)
		{
			_lightPos = _gameElements.getGameElement(id)._translate;
		}
		

		
		glUniform3fv(_lightPosition, 1, glm::value_ptr(_lightPos));
		material _light;
		_light.ambient = _materialManager.getMaterialComponents(LIGHT).ambient;
		_light.diffuse = _materialManager.getMaterialComponents(LIGHT).diffuse;
		_light.specular = _materialManager.getMaterialComponents(LIGHT).specular;
		glUniform3fv(_lightAmbientUniform, 1, glm::value_ptr(_light.ambient));
		glUniform3fv(_lightDiffuseUniform, 1, glm::value_ptr(_light.diffuse));
		glUniform3fv(_lightSpecularUniform, 1, glm::value_ptr(_light.specular));
		glUniform1i(_lightType, lightType);
		glUniform3fv(_lightDirection, 1, glm::value_ptr(glm::vec3(0.0f,0.0f, 1.0f)));
		//glUniform1f(_lightShininessUniform, _materialManager.getMaterialComponents(currentRenderedGameElement._materialType).shininess);
		glm::mat4 normalMat = glm::transpose(glm::inverse(modelMatrix));
		glUniform3fv(modelNormalMatrix, 1, glm::value_ptr(normalMat));

		glUniform1f(textureLocation,0);
		glUniform1i(_drawModeUniform, _drawMode);

		if (currentRenderedGameElement._textureRepetion) {
			glUniform2f(_textureScaleFactorLocation, currentRenderedGameElement._scale.x, currentRenderedGameElement._scale.y);
		}
		else {
			glUniform2f(_textureScaleFactorLocation, 1.0f, 1.0f);
		}
		//Send data to GPU
		if (!bothModes)
		{
			if (polygonMode)
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			else
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else
		{
			if (id <= 1)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			else
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
		}
		_openGLBuffers.sendDataToGPU(_gameElements.getData(currentRenderedGameElement._objectType), _gameElements.getNumVertices(currentRenderedGameElement._objectType));
		glBindTexture(GL_TEXTURE_2D, 0);
		if (_gameElements.getGameElement(id).col.isCollision())
		{

			_gameElements.eraseObject(id);
		}
	//	system("cls");
		
		
	

}
