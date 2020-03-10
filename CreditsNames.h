#ifndef _CREDITS_NAMES_INCLUDE
#define _CREDITS_NAMES_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include <map>
#include <string>

// CreditsNames 
class CreditsNames
{

public:
	CreditsNames(const glm::vec2 &pos);
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, int x, int y);
	void update(int deltaTime, const glm::vec2 &pos, string dir);
	void render();
	
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	glm::ivec2 getPosition();
	
private:
	glm::ivec2 tileMapDispl, posCreditsNames;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *tmap;
    // my vars
	
};


#endif // _CREDITS_NAMES_INCLUDE