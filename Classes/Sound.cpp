#include "Sound.h"

bool Sound::init()
{
	clickSound = SimpleAudioEngine::getInstance();

	return true;
}

void Sound::generateClickSound() const
{
	//播放一次按键音
	clickSound->playEffect("/musics/clickSound.mp3");
}

