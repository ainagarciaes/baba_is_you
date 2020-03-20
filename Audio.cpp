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
	bindAudio("../music/awesomeness.wav", TITLE_MUSIC);
	bindAudio("../music/rockSlide.wav", LEVEL);
	bindAudio("../music/awesomeness.wav", INSTRUCTIONS);
	bindAudio("../music/awesomeness.wav", CREDITS);
}

void Audio::bindAudio(const char * file, int i) {
	sounds[i] = soundEngine->addSoundSourceFromFile(file);
}

void Audio::play(int i, bool loop) {
	soundEngine->play2D(sounds[i], loop);
}

void Audio::stopAllSounds() {
	soundEngine->stopAllSounds();
}