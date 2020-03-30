#include "Audio.h"
#include <iostream>
Audio::Audio()
{
	soundEngine = createIrrKlangDevice();
	if (!soundEngine){
		std::cout << "ERROR STARTING IRRKLANG" << std::endl;
	} // error starting up the engine
	init();
}


Audio::~Audio()
{
	for (int i = 0; i < NUM_SOUNDS; ++i) {
		sounds[i]->drop();
		sounds[i] = 0;
	}
	soundEngine->drop();
}
 
void Audio::init()
{
	bindAudio("../music/menu.wav", TITLE_MUSIC);
	bindAudio("../music/lvl1.wav", LEVEL1);
	bindAudio("../music/lvl2.wav", LEVEL2);
	bindAudio("../music/lvl3.wav", LEVEL3);
	bindAudio("../music/lvl4.wav", LEVEL4);
	bindAudio("../music/lvl5.wav", LEVEL5);
	bindAudio("../music/instructions.wav", INSTRUCTIONS);
	bindAudio("../music/credits.wav", CREDITS);
	bindAudio("../music/rocketcollides.wav", ROCKET);
	bindAudio("../music/push.wav", PUSH);
	bindAudio("../music/make.wav", MAKE);
	bindAudio("../music/door.wav", DOOR);
	bindAudio("../music/menupress.wav", MENUPRESS);
	bindAudio("../music/winning.wav", WINNING);

}

void Audio::bindAudio(const char * file, int i) {
	std::cout << "BIND AUDIO " << i << std::endl;
	sounds[i] = soundEngine->addSoundSourceFromFile(file);
}

void Audio::play(int i, bool loop) {
	soundEngine->play2D(sounds[i], loop);
}

void Audio::stopAllSounds() {
	soundEngine->stopAllSounds();
}