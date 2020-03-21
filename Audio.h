#ifndef _AUDIO_INCLUDE
#define _AUDIO_INCLUDE

#include <irrKlang.h>
using namespace irrklang;

#define NUM_SOUNDS 8

enum AUDIOS {
	TITLE_MUSIC, LEVEL1, LEVEL2, LEVEL3, LEVEL4, LEVEL5, CREDITS, INSTRUCTIONS
};

class Audio
{
public:
	Audio();
	~Audio();

	void init();
	void bindAudio(const char* file, int i);
	void play(int i, bool loop);
	void stopAllSounds();

private:
	ISoundEngine* soundEngine;
	ISoundSource *sounds[NUM_SOUNDS];
};

#endif // _AUDIO_INCLUDE

