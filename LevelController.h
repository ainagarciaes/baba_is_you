#ifndef _LEVEL_CONTROLLER_INCLUDE
#define _LEVEL_CONTROLLER_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include <map>
#include "MapObject.h"
#include "Words.h"
#include "Player.h"

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

	int moving; // 0 not moving, 1 Left, 2 Right, 3 Up, 4 Down
	TileMap *map;
	// MY VARS
	int nextScene;
	std::map<string, bool> playable; //for each kind of object in the level, sets if it is currently playable
    std::map<string,MapObject*> objects;
    std::map<string,Words*> words;
	int movCont;

	string obs_words_positions[15][20];
};
#endif // _LEVEL_CONTROLLER_INCLUDE