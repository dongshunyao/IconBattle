#include "Sound.h"

Sound* Sound::instance = nullptr;

Sound* Sound::getInstance()
{
	if (instance == nullptr) instance = new Sound();
	return instance;
}

void Sound::stop() const
{
	AudioEngine::stop(audioId);
}

void Sound::play(const string& path)
{
	if (on) audioId = AudioEngine::play2d(path, false, 0.8f);
}

Sound::Sound()
{
	AudioEngine::preload(clicked);
}
