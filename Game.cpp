#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include <iostream>

void Game::init()
{
	bPlay = true;
	sceneID = 0;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	initScene();
}

bool Game::update(int deltaTime)
{
	nextScene();
	updateScene(deltaTime);
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Before rendering the scene, we have to check if we need to change the screen, if we have to, we have to call scene.init() with the next scene ID
	renderScene();
}

void Game::keyPressed(int key)
{
	if(key == 27) // Escape code
		bPlay = false;
	if(key==13) { // This is a test mode of changing between scenes
		sceneID++;
		initScene();
	}
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}

void Game::initScene(){
	if (sceneID == 0) { // menu
		menu.init();
	} else if (sceneID == 1){ // credits
		creds.init(); 
	} else if (sceneID == 2){ // instructions
		instr.init(); 
	} else if (sceneID > 2 && sceneID < 8) {
		level.init(sceneID); 
	}
}
void Game::renderScene(){
	if (sceneID == 0) {
		menu.render();
	} else if (sceneID == 1){ // credits
		creds.render(); 
	} else if (sceneID == 2){ // instructions
		instr.render(); 
	} else if (sceneID > 2 && sceneID < 8) {
		level.render(); 
	}
}

void Game::updateScene(int deltaTime){
	if (sceneID == 0) {
		menu.update(deltaTime);
	} else if (sceneID == 1){ // credits
		creds.update(deltaTime);
	} else if (sceneID == 2){ // instructions
		instr.update(deltaTime);
	} else if (sceneID > 2 && sceneID < 8) {
		level.update(deltaTime);
	}
}

void Game::nextScene(){

}
