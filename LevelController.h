#ifndef _LEVEL_CONTROLLER_INCLUDE
#define _LEVEL_CONTROLLER_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include <map>
#include "MapObject.h"
#include "Words.h"

class LevelController
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, int lvl);
	void update(int deltaTime);
	void render();
	
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	int getNextScene();

private:
    void movePlayable(int deltaTime);
	void processQueries();
    bool moveRecursive(int deltaTime, string direction);
	void updateNextScene();
	bool isPlayable(string name);

	bool bJumping;
	glm::ivec2 tileMapDispl, posLevelController;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	// MY VARS
	int nextScene;
	std::map<string, bool> playable; //for each kind of object in the level, sets if it is currently playable
    std::vector<MapObject> objects;
    std::vector<Words> words;
};
#endif // _LEVEL_CONTROLLER_INCLUDE