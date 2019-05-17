#ifndef __MUSIC_H__
#define __MUSIC_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

//USING_NS_CC;
using namespace CocosDenshion;

class Music
{
public:
	bool loading();
	void setVolume(float volume) const;
	void changeMusic(const char* newMusicName) const;
	void stopMusic() const;
	

private:
	
	void startMusic(const char* musicFileName) const;
	SimpleAudioEngine* backMusic = nullptr;

};

#endif

