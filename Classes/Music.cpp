#include "Music.h"

Music* Music::instance = nullptr;

Music* Music::getInstance()
{
	if (instance == nullptr) instance = new Music;
	return instance;
}

void Music::loading(const vector<string>& path) const
{
	for (const auto& it : path) audio->preloadBackgroundMusic(it.data());
}

void Music::stop() const
{
	audio->stopBackgroundMusic();
}

void Music::play(const string& path) const
{
	// Ñ­»·²¥·Å
	audio->playBackgroundMusic(path.data(), true);
}

void Music::setVolume(const int volume) const
{
	if (volume <= 100 && volume >= 0) audio->setBackgroundMusicVolume(static_cast<float>(volume) / 100);
	else audio->setBackgroundMusicVolume(0.5f);
}

int Music::getVolume() const
{
	return static_cast<int>(100 * audio->getBackgroundMusicVolume());
}

void Music::change(const string& path) const
{
	audio->stopBackgroundMusic();
	audio->playBackgroundMusic(path.data(), true);
}
