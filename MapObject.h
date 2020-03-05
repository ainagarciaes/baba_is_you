#ifndef _MAP_OBJECT_INCLUDE
#define _MAP_OBJECT_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include <map>
#include <string>

// MapObject 
class MapObject
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();
	
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	
private:

	glm::ivec2 tileMapDispl, posMapObject;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
    // my vars
    string objectName;
    std::map<string, bool> properties;
};


#endif // _MAP_OBJECT_INCLUDE