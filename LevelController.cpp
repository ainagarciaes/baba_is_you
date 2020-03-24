#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "LevelController.h"
#include "Game.h"
#include <include/nlohmann/json.hpp>
#include<fstream>

// for convenience
using json = nlohmann::json;

void LevelController::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, int lvl)
{
	idcont = 0;
	nextScene = -1;
	s = shaderProgram;
	level = lvl;
	for (int k = 0; k < 15; k++) {
		for (int w = 0; w < 20; w++) {
			obs_words_positions[k][w] = "empty";
		}
	}

	std::ifstream i("../levels/lvl_"+to_string(lvl)+"_setup.txt");
	json j;
	i >> j;

	// Read map words
	auto mapWords = j["mapWords"];
	for(auto i = 0; i < mapWords.size(); ++i) {
		string name = mapWords[i]["name"];
		int posy = mapWords[i]["posy"];
		int posx = mapWords[i]["posx"];
		string id = mapWords[i]["idw"];
		int wtype = mapWords[i]["wtype"];

		//my code goes here
		Words *mo = new Words(glm::vec2(posx,posy), name, wtype);
		mo->init(tileMapPos, shaderProgram, name);
		obs_words_positions[posy/32][posx/32] = id;
		words[id]=mo;
	}

	// Read map objects
	auto mapObs = j["mapObjects"];
	for(auto i = 0; i < mapObs.size(); ++i) {
		string name = mapObs[i]["name"];
		int posy = mapObs[i]["posy"];
		int posx = mapObs[i]["posx"];
		string id = mapObs[i]["ido"];

		//my code goes here
		MapObject *mo = new MapObject(glm::vec2(posx,posy), name);
		mo->init(tileMapPos, shaderProgram, name);
		obs_words_positions[posy/32][posx/32] = id;
		objects[id] = mo;
		/* init properties */
		playable[name] = false;
		pushable[name]=false; 
		hot[name]=false; 
		melt[name]=false; 
		open[name]=false; 
		close[name]=false; 
		win[name]=false; 
	}
	playable["rock"] = true;

	// load map walls for collisions
	auto walls = j["walls"];
	for(auto i = 0; i < walls.size(); ++i) {
		int posy = walls[i]["posy"];
		int posx = walls[i]["posx"];
		obs_words_positions[posy][posx] = "wall";
	}

	moving = 0;
	isBaba = true;
}

void LevelController::update(int deltaTime)
{
	if (Game::instance().getKey(82)) {
		cout << "restart" << endl;
		this->init(glm::ivec2(0,0), s, level);
	}
	
	movePlayable(deltaTime);
	updateWords(deltaTime);
	processQueries();
	updateNextScene();
	std::map<std::string, MapObject*>::iterator it = objects.begin();
 	while (it != objects.end())
	{
		MapObject *o = it->second;
		string name = o->getName();
		if (!playable[name]) o->update(deltaTime, o->getPosition(), "S");

		bool del = o->getDestroy();
		if (del)
		{
			it = objects.erase(it);
		}
		else {
			++it;
		}
	}

	/* PRINT MAP DEBUG -> DELETE IT ON FINAL VERSION */
	if (Game::instance().getKey(49)) {
		for (int j = 0; j < 15; j++) {
			for (int i = 0; i < 20; i++) {
				cout << obs_words_positions[j][i] << " ";
			}
			cout << endl;
		}
	}
}

void LevelController::updateWords(int deltaTime){	// render objects
	std::map<std::string, Words*>::iterator it2 = words.begin();
 	while (it2 != words.end())
	{	
		Words *o = it2->second;
		glm::vec2 pos = o->getPosition();
		o->update(deltaTime,pos,"nothing");
		it2++;
	}
}
void LevelController::render()
{
	// render objects
	std::map<std::string, MapObject*>::iterator it = objects.begin();
 	while (it != objects.end())
	{
		MapObject *o = it->second;
		o->render();
		++it;
	}

	// render objects
	std::map<std::string, Words*>::iterator it2 = words.begin();
 	while (it2 != words.end())
	{
		Words *o = it2->second;
		o->render();
		it2++;
	}
}

void LevelController::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void LevelController::movePlayable(int deltaTime) {
	bool left = Game::instance().getSpecialKey(GLUT_KEY_LEFT);
	bool right = Game::instance().getSpecialKey(GLUT_KEY_RIGHT);
	bool up = Game::instance().getSpecialKey(GLUT_KEY_UP);
	bool down = Game::instance().getSpecialKey(GLUT_KEY_DOWN);

	if (moving == 0) {
		if (left) { 
			moving = 1; 
			for (int i = 1; i < 19; i++) {
				for (int j = 1; j < 14; j++) { // check map state
					string id = obs_words_positions[j][i];
					// we check that there is not another object at the left of the player and that this object exists
					if (objects.find(id) != objects.end()) {
						MapObject *ob = objects[id]; 
						if (playable[ob->getName()] && moveRecursive(deltaTime, "L", i, j)) {
							glm::ivec2 pos = ob->getPosition();
							pos.x -= 2;
							ob->update(deltaTime, pos, "L");
							obs_words_positions[j][i-1] = obs_words_positions[j][i];
							obs_words_positions[j][i] = "empty";
						}
					}
				}
			}
			movCont = 14;
		} else if (right) {
			moving = 2;
			for (int i = 19; i > 0; i--) {
				for (int j = 1; j < 14; j++) { // check map state
					string id = obs_words_positions[j][i];
					if (objects.find(id) != objects.end()) {
						MapObject *ob = objects[id]; 
						if (playable[ob->getName()] && moveRecursive(deltaTime, "R", i, j)) {
							glm::ivec2 pos = ob->getPosition();
							pos.x += 2;
							ob->update(deltaTime, pos, "R");
							obs_words_positions[j][i+1] = obs_words_positions[j][i];
							obs_words_positions[j][i] = "empty";
						}
					}
				}
			}
			movCont = 14;
		} else if (up) {
			moving = 3;
			for (int j = 1; j < 14; j++) { // check map state
				for (int i = 1; i < 19; i++) {
					string id = obs_words_positions[j][i];
					if (objects.find(id) != objects.end()) {
						MapObject *ob = objects[id]; 
						if (playable[ob->getName()] && moveRecursive(deltaTime, "U", i, j)) {
							glm::ivec2 pos = ob->getPosition();
							pos.y -= 2;
							ob->update(deltaTime, pos, "U");
							obs_words_positions[j-1][i] = obs_words_positions[j][i];
							obs_words_positions[j][i] = "empty";
						}
					}
				}
			}
			movCont = 14;
		} else if (down) {
			moving = 4;
			for (int j = 14; j > 0; j--) { // check map state
				for (int i = 1; i < 19; i++) {
					string id = obs_words_positions[j][i];
					if (objects.find(id) != objects.end()) {
						MapObject *ob = objects[id]; 
						if (playable[ob->getName()] && moveRecursive(deltaTime, "D", i, j)) {
							glm::ivec2 pos = ob->getPosition();
							pos.y += 2;
							ob->update(deltaTime, pos, "D");
							obs_words_positions[j+1][i] = obs_words_positions[j][i];
							obs_words_positions[j][i] = "empty";
						}
					}
				}
			}
			movCont = 14;
		} else {
			std::map<std::string, MapObject*>::iterator it3 = objects.begin();
			for (int j = 14; j > 0; j--) { // check map state
				for (int i = 1; i < 19; i++) {
					string id = obs_words_positions[j][i];
					if (objects.find(id) != objects.end()) {
						MapObject *ob = objects[id]; 
						glm::ivec2 pos = ob->getPosition();
						ob->update(deltaTime, pos, "S");	
					}
				}
			}
		}
	} else {
		// auto move objs
		std::map<std::string, MapObject*>::iterator it = objects.begin();
		while (it != objects.end())
		{
			MapObject *ob = it->second;
			glm::ivec2 pos = ob->getPosition();
			if (pos.x % 32 != 0 || pos.y%32 != 0) {
				if (moving == 1) {
					pos.x -= 2;
					ob->update(deltaTime, pos, "L");	
				} else if (moving == 2) {
					pos.x += 2;
					ob->update(deltaTime, pos, "R");
				} else if (moving == 3) {
					pos.y -= 2;
					ob->update(deltaTime, pos, "U");	
				} else if (moving == 4) {
					pos.y += 2;
					ob->update(deltaTime, pos, "D");
				}
			} 
			it++;
		}

		// automove words
		std::map<std::string, Words*>::iterator it2 = words.begin();
		while (it2 != words.end())
		{
			Words *ob = it2->second;
			glm::ivec2 pos = ob->getPosition();
			if (pos.x % 32 != 0 || pos.y%32 != 0) {
				if (moving == 1) {
					pos.x -= 2;
					ob->update(deltaTime, pos, "L");	
				} else if (moving == 2) {
					pos.x += 2;
					ob->update(deltaTime, pos, "R");
				} else if (moving == 3) {
					pos.y -= 2;
					ob->update(deltaTime, pos, "U");	
				} else if (moving == 4) {
					pos.y += 2;
					ob->update(deltaTime, pos, "D");
				}
			}
			it2++;
		}

		if (movCont == 0) {
			moving = 0;
		}
		movCont -= 1;
	}
}

bool LevelController::moveRecursive(int deltaTime, string direction, int x, int y) {
	// Get the position of the next element in that direction
	if (direction == "L") {
		x--;
	}
	else if (direction == "R") {
		x++;
	}
	else if (direction == "U") {
		y--;
	} 
	else {
		y++;
	}

	if (x < 0 || x > 19 || y < 0 || y > 14) { //out of bounds
		return false;
	}
	string nextPos = obs_words_positions[y][x];
	
	if (nextPos == "empty") {
		return true;
	} else if (nextPos == "wall") {
		return false;
	} else {
		// check if it is an object
		bool ret;
		if (objects.find(nextPos) != objects.end()) {
			MapObject *mo = objects[nextPos];	
			string name = mo->getName();
			if (open[name]) {
				ret = checkClose(x,y);
			}
			if (pushable[mo->getName()]){
				bool movRec = moveRecursive(deltaTime, direction, x, y);
				if(movRec && !ret) {
					glm::vec2 pos = mo->getPosition();
					if (direction == "L") {
						pos.x -= 2;
						x--;
					}
					else if (direction == "R") {
						pos.x += 2;
						x++;
					}
					else if (direction == "U") {
						pos.y -= 2;
						y--;
					} 
					else {
						pos.y += 2;
						y++;
					}
					mo->setPosition(pos);
					obs_words_positions[y][x] = nextPos;
				}
				return movRec;
			}
			if (isWin(x, y)) {
				return false;
			}
		}
		// check if it is a word
		else if (words.find(nextPos) != words.end()) {
			bool movRec = moveRecursive(deltaTime, direction, x, y);
			if(movRec) {
				Words *w = words[nextPos];
				glm::vec2 pos = w->getPosition();
				if (direction == "L") {
					pos.x -= 2;
					x--;
				}
				else if (direction == "R") {
					pos.x += 2;
					x++;
				}
				else if (direction == "U") {
					pos.y -= 2;
					y--;
				} 
				else {
					pos.y += 2;
					y++;
				}
				w->setPosition(pos);
				obs_words_positions[y][x] = nextPos;
			}
			return movRec;
		}	
	}
	return false;
}

void LevelController::processQueries() {
	emptyMaps();
	isBaba = true;
	processLR();
	processUD();
	if (isBaba) {
		playable["baba"] = true;
	}
}

int LevelController::getNextScene() {
	return nextScene;
}

void LevelController::updateNextScene() {

	//check if there is a win condition, if so, set the next scene to whatever it has to
}

bool LevelController::isPlayable(string name) {
	return playable[name];
}

void LevelController::emptyMaps() {
	string mkey = "";
	for(std::map<std::string,bool>::iterator it = playable.begin(); it != playable.end(); ++it) {
		mkey = it->first;
		playable[mkey] = false;
		pushable[mkey]=false; 
		hot[mkey]=false; 
		melt[mkey]=false; 
		open[mkey]=false; 
		close[mkey]=false; 
		win[mkey]=false; 
	}
}

void LevelController::processLR(){
	string val = "";
	
	for (int j = 0; j < 15; j++) { // check map state
		for (int i = 0; i < 18; i++) {
			val = obs_words_positions[j][i];
			if (words.find(val) != words.end()) {
				Words *w1 = words[val]; 
				val = obs_words_positions[j][i+1];
				if (words.find(val) != words.end()) {
					Words *w2 = words[val]; 
					val = obs_words_positions[j][i+2];
					if (words.find(val) != words.end()) {
						Words *w3 = words[val]; 
						executeQuery(w1, w2, w3);
					}
				}
			}
		}
	}
}

void LevelController::processUD(){
	string val = "";
	
	for (int j = 0; j < 13; j++) { // check map state
		for (int i = 0; i < 20; i++) {
			val = obs_words_positions[j][i];
			if (words.find(val) != words.end()) {
				Words *w1 = words[val]; 
				val = obs_words_positions[j+1][i];
				if (words.find(val) != words.end()) {
					Words *w2 = words[val]; 
					val = obs_words_positions[j+2][i];
					if (words.find(val) != words.end()) {
						Words *w3 = words[val]; 
						executeQuery(w1, w2, w3);
					}
				}
			}
		}
	}
}

void LevelController::setProperty(string property, string object, bool value) {
	if (property == "you") {
		playable[object]=value;	
		isBaba = false;
	} else if (property == "push") {
		pushable[object]=value;	
	} else if (property == "open") {
		open[object]=value;	
	} else if (property == "shut") {
		close[object]=value;	
	} else if (property == "hot") {
		hot[object]=value;	
	} else if (property == "melt") {
		melt[object]=value;	
	} else if (property == "win") {
		win[object]=value;
		if (playable[object]) {
			nextScene = level + 3;
		}	
	}
}
//this function simply calls changeConn in words saying in which state the frase is
void LevelController::setConnected(Words *w1,bool con){
	w1->changeConn(con);
}

void LevelController::setObject(string ob1, string ob2){
	std::map<std::string, MapObject*>::iterator it = objects.begin();
 	while (it != objects.end())
	{
		MapObject *o = it->second;
		string name = o->getName();
		if (name == ob1) {
			cout << "changing object type" << endl;
			o->changeTo(ob2);
		}
		it++;
	}	
}

void LevelController::executeQuery(Words *w1, Words *w2, Words *w3){
	//cout << "EXECUTE " << w1->getName() << " " << w2->getName() << " " << w3->getName() << endl;
	// N is P
	int t1 = w1->getWtype();
	string n1 = w1->getName();
	int t2 = w2->getWtype();
	string n2 = w2->getName();
	int t3 = w3->getWtype();
	string n3 = w3->getName();
	if (t1 != 1 || t2 != 2) return;
	if (n2 == "is") {
		setConnected(w1,true);
		setConnected(w2,true);
		setConnected(w3,true);
		if (t3 == 3) {
			setProperty(n3, n1, true);
		} else {
			setObject(n1, n3);
		}
	}

	if (n2 == "make") {
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j <15; j++) {
				string idobj = obs_words_positions[j][i];
				// if elemento es n1 ->
				if(objects.find(idobj) != objects.end()) {
					MapObject *aux = objects[idobj];
					if (aux->getName() == n1) {
						// check animation
						// if animation es una de les de moving -> calcular direccio contraria
						string mov = aux->getMovement();
						bool moving = true;
						int xx = i;
						int yy = j;
						if (mov == "L") {
							xx++;
						} else if (mov == "U") {
							yy--;
						} else if (mov == "D") {
							yy++;
						} else if (mov == "R") {
							xx--;
						} else {
							moving = false;
						}

						// mirar si esta empty, si ho esta:
						if (moving && xx >= 0 && xx < 20 && yy < 15 && yy >= 0) {
							if (obs_words_positions[yy][xx] != "empty") { 
								// posar nova id (mantenir un contador al level controller i anar sumant)
								string id = "o" + idcont;
								idcont++;
								obs_words_positions[yy][xx] = id;
								float x = xx*32;
								float y = yy*32;
								// crear l'objecte, etc...
								MapObject *newObj = new MapObject(glm::vec2(x, y), n3);
								newObj->init(glm::vec2(0,0), s, n3);
								//afegirlo al map d'objectes
								objects[id] = newObj;
							}
						}
					}
				}
			}
		}
	}
}

bool LevelController::checkClose(int x, int y) {
	cout << "check close" << endl;
	bool ret = false;
	string myname = obs_words_positions[y][x];
	string obsname;
	int xaux = x;
	int yaux = y;
	if (x < 19) {
		xaux = x+1;
		obsname = obs_words_positions[y][xaux];
		if (objects.find(obsname) != objects.end()){
			MapObject *m = objects[obsname];
			if (close[m->getName()]) {
				objects[myname]->destroyObj();
				objects[obsname]->destroyObj();
				obs_words_positions[y][xaux] = "empty";
				obs_words_positions[y][x] = "empty";
				ret = true;
			}
		}
	} 
	if (x > 1) {
		xaux = x-1;
		obsname = obs_words_positions[y][xaux];
		if (objects.find(obsname) != objects.end()){
			MapObject *m = objects[obsname];
			if (close[m->getName()]) {
				objects[myname]->destroyObj();
				objects[obsname]->destroyObj();
				obs_words_positions[y][xaux] = "empty";
				obs_words_positions[y][x] = "empty";
				ret = true;
			}
		}
	}
	if (y > 1) {
		yaux = y-1;
		obsname = obs_words_positions[yaux][x];
		if (objects.find(obsname) != objects.end()){
			MapObject *m = objects[obsname];
			if (close[m->getName()]) {
				objects[myname]->destroyObj();
				objects[obsname]->destroyObj();
				obs_words_positions[yaux][x] = "empty";
				obs_words_positions[y][x] = "empty";
				ret = true;
			}
		}		
	}
	if (y < 14) {
		yaux = y+1;
		obsname = obs_words_positions[yaux][x];
		if (objects.find(obsname) != objects.end()){
			MapObject *m = objects[obsname];
			if (close[m->getName()]) {
				objects[myname]->destroyObj();
				objects[obsname]->destroyObj();
				obs_words_positions[yaux][x] = "empty";
				obs_words_positions[y][x] = "empty";
				ret = true;
			}
		}	
	}
	return ret;
}

bool LevelController::isWin(int x, int y){
 	string id = obs_words_positions[y][x];
    MapObject *m = objects[id];
	string name = m->getName();
	bool b = win[name];
	if (b) {
		nextScene = level + 3; 
	}
	return b;
}