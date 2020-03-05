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
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();
	
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	
private:
	glm::ivec2 tileMapDispl, posWords;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
    // my vars
	string wordName;
	int wordType; //1 - noun; 2 - verb; 3 - property
};


#endif // _WORDS_INCLUDE