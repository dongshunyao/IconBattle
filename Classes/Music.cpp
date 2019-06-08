#include "Music.h"

Music* Music::instance = nullptr;

Music* Music::getInstance()
{
	if (instance == nullptr) instance = new Music;
	return instance;
}

void Music::loading(const vector<string>& path) const
{
	for (const auto& it : path) AudioEngine::preload(it);
}

void Music::stop() const
{
	if (audioId != AudioEngine::INVALID_AUDIO_ID) AudioEngine::stop(audioId);
}

void Music::play(const string& path)
{
	if (audioId == AudioEngine::INVALID_AUDIO_ID)
		audioId = AudioEngine::play2d(
			path, true, static_cast<float>(volume) / 100);
}

void Music::setVolume(const int volume)
{
	if (volume <= 100 && volume >= 0) this->volume = volume;
	else this->volume = 50;
	AudioEngine::setVolume(audioId, static_cast<float>(volume) / 100);
}

void Music::change(const string& path)
{
	AudioEngine::stop(audioId);
	audioId = AudioEngine::play2d(path, true, static_cast<float>(volume) / 100);
}
