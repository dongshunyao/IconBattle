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
	if (audioId != AudioEngine::INVALID_AUDIO_ID)
		AudioEngine::stop(audioId);
		//AudioEngine::end();
	
}

void Music::play(const string& path)
{
	if (audioId == AudioEngine::INVALID_AUDIO_ID)
		audioId = AudioEngine::play2d(path, true, 0.5f);
}

void Music::setVolume(const int volume) const
{
	if (volume <= 100 && volume >= 0) AudioEngine::setVolume(audioId, static_cast<float>(volume) / 100);
	else AudioEngine::setVolume(audioId, 0.5f);
}

int Music::getVolume() const
{
	return static_cast<int>(100 * AudioEngine::getVolume(audioId));
}

void Music::change(const string& path)
{
	AudioEngine::stop(audioId);
	audioId = AudioEngine::play2d(path, true);
}
