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
	MapObject(const glm::vec2 &pos, string name);
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, string name);
	void update(int deltaTime, const glm::vec2 &pos, string dir);
	void render();
	
	void changeTo(string objectType);
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	string getName();
	void initSprite(string name);
	glm::ivec2 getPosition();
	
private:
	ShaderProgram sp;
	glm::ivec2 tileMapDispl, posMapObject;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *tmap;
    // my vars
    string objectName;
	string objID;
};


#endif // _MAP_OBJECT_INCLUDE