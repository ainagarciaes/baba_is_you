#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE

#include "MenuScene.h"
#include "InstructionsScene.h"
#include "CreditsScene.h"
#include "LevelScene.h"

// Game is a singleton (a class with a single instance) that represents our whole application
class Game
{

public:
	Game() {}
	
	static Game &instance()
	{
		static Game G;

		return G;
	}
	
	void init();
	bool update(int deltaTime);
	void render();
	
	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);
	
	bool getKey(int key) const;
	bool getSpecialKey(int key) const;
	
	LevelScene getLevelS();

private:
	bool bPlay;                       // Continue to play game?
	MenuScene menu;
	Audio *audiomanager;
	InstructionsScene instr;
	CreditsScene creds;
	LevelScene level;
	bool keys[256], specialKeys[256]; // Store key states so that 
	                                  // we can have access at any time
	int sceneID;
	void initScene();
	void renderScene();
	void updateScene(int deltaTime);
	void nextScene();
};


#endif // _GAME_INCLUDE


