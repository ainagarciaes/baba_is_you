#ifndef _WORDS_INCLUDE
#define _WORDS_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include <map>
#include <string>

// Words 
class Words
{

public:
	Words(const glm::vec2 &pos, string name, int wtype);
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, string name);
	void update(int deltaTime);
	void render();
	
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	
	glm::vec2 getPosition();
	int getWtype();
	bool checkFrase();
	
private:
	glm::ivec2 tileMapDispl, posWords;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
    // my vars
	LevelScene ls;
	LevelController lc;
	string wordName;
	int wordType; //1 - noun; 2 - verb; 3 - property
};


#endif // _WORDS_INCLUDE