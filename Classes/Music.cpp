#include "Music.h"

bool Music::loading()
{   
	backMusic = SimpleAudioEngine::getInstance();

	// TODO: 加载上次运行结束音量、音乐

	//本应该传入上次运行的音乐名
	startMusic("/musics/tryBackgroundMusic.mp3");

	return true;
}

void Music::startMusic(const char* musicFileName) const
{
	//循环播放
	backMusic->playBackgroundMusic(musicFileName, true);
}

void Music::setVolume(const float volume) const
{
	backMusic->setBackgroundMusicVolume(volume);
}

void Music::changeMusic(const char*  newMusicName) const
{
	backMusic->stopBackgroundMusic();
	backMusic->playBackgroundMusic(newMusicName);
}

void Music::stopMusic() const
{
	backMusic->stopBackgroundMusic();
}
