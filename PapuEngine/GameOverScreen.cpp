#include "GameOverScreen.h"
#include "ScreenIndices.h"
#include "Game.h"
#include <iostream>


GameOverScreen::GameOverScreen(Window* window) :
	_window(window), btnGameClicked(false)
{
	_screenIndex = SCREEN_INDEX_MENU;
}

void GameOverScreen::initGUI() {

}

GameOverScreen::~GameOverScreen()
{
}

void GameOverScreen::initSystem() {
	_program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
}

void GameOverScreen::build()
{
}

void GameOverScreen::destroy() {
	delete _background;
	delete _button;
}

void GameOverScreen::onExit() {

}

void GameOverScreen::onEntry() {
	initSystem();
	_camera2D.init(_window->getScreenWidth(), _window->getScreenHeight());
	_camera2D.setPosition(glm::vec2(_window->getScreenWidth() / 2.0f, _window->getScreenHeight() / 2.0f));
	_spriteBacth.init();
	_background = new Background("Textures/naves/gam-over.png");
	_button = new Button("Textures/naves/menu_button.png");
	_spriteFont = new SpriteFont("Fonts/arial.ttf", 64);
}

void GameOverScreen::update() {
	_camera2D.update();
	if (_game->_inputManager.isKeyDown(SDL_BUTTON_LEFT)) {
		if (_button->clicked(_game->_inputManager.getMouseCoords()) && !btnGameClicked) {
			btnGameClicked = true;
			std::cout << "Go to menu" << std::endl;
			
			_currentState = ScreenState::CHANGE_NEXT;

		}
	}
	checkInput();
}

void GameOverScreen::draw() {

	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_program.use();
	glActiveTexture(GL_TEXTURE0);

	GLuint pLocation =
		_program.getUniformLocation("P");

	glm::mat4 cameraMatrix = _camera2D.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	GLuint imageLocation = _program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);

	_spriteBacth.begin();

	_background->draw(_spriteBacth);
	_button->draw(_spriteBacth);

	drawText();

	_spriteBacth.end();
	_spriteBacth.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);
	_program.unuse();
}

int GameOverScreen::getNextScreen()const {
	return SCREEN_INDEX_MENU;
}

int GameOverScreen::getPreviousScreen() const {
	return SCREEN_INDEX_MENU;
}

void GameOverScreen::checkInput() {
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		_game->onSDLEvent(evnt);
	}
}

void GameOverScreen::drawText() {

	char buffer[256];

	sprintf_s(buffer, "Game Over");
	_spriteFont->draw(_spriteBacth, buffer, glm::vec2(0, 36),
		glm::vec2(0.5), 0.0f, ColorRGBA(0, 255, 255, 255));

}
