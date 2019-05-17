#ifndef __SOUND_H__
#define __SOUND_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

class Sound
{
private:
	
	SimpleAudioEngine* clickSound = nullptr;
	//static  Sound* instance;

public:
	bool init();
	//static Sound* getInstance();
	void generateClickSound() const;

};

#endif

