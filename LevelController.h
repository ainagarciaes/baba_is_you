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
    bool moveRecursive(int deltaTime, string direction, int x, int y);
	void updateNextScene();
	void emptyMaps();
	bool isPlayable(string name);
	void processLR();
	void processRL();
	void processUD();
	void processDU();
	void setProperty(string property, string object, bool value);

	int moving; // 0 not moving, 1 Left, 2 Right, 3 Up, 4 Down
	TileMap *map;
	// MY VARS
	int nextScene;

	/* Objects with each property */
	std::map<string, bool> playable; //for each kind of object in the level, sets if it is currently playable
	std::map<string, bool> pushable; 
	std::map<string, bool> hot; 
	std::map<string, bool> melt; 
	std::map<string, bool> open; 
	std::map<string, bool> close; 
	std::map<string, bool> win; 

    std::map<string,MapObject*> objects;
    std::map<string,Words*> words;
	bool isBaba;
	int movCont;
	ShaderProgram s;
	int level;
	string obs_words_positions[15][20];
};
#endif // _LEVEL_CONTROLLER_INCLUDE