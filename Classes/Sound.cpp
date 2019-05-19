#include "Sound.h"

// TODO 音效路径常量+预加载
const string Sound::CLICKED = "/sound/clicked.mp3";

Sound* Sound::instance = nullptr;

Sound* Sound::getInstance()
{
	if (instance == nullptr) instance = new Sound();
	return instance;
}

void Sound::stop() const
{
	audio->stopAllEffects();
}

void Sound::play(const string& path) const
{
	if (on) audio->playEffect(path.data());
}

Sound::Sound()
{
	audio->preloadEffect(CLICKED.data());
	audio->setEffectsVolume(0.5f);
}
