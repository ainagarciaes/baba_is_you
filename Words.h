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
	void update(int deltaTime, const glm::vec2 &pos, string dir);
	void render();
	
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	string getName();
	string getID();
	glm::vec2 getPosition();
	int getWtype();
	bool checkFrase();
	void changeConn(bool a);
	
private:
	glm::ivec2 tileMapDispl, posWords;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
    // my vars
	//LevelScene ls;
	//LevelController lc;
	string wordName;
	long count;
	bool connected; //frase is complete
	int wordType; //1 - noun; 2 - verb; 3 - property
};


#endif // _WORDS_INCLUDE