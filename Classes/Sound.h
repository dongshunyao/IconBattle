#ifndef __SOUND_H__
#define __SOUND_H__

#include "SimpleAudioEngine.h"
#include <string>
#include <vector>

using namespace CocosDenshion;
using std::string;
using std::vector;

class Sound
{
public:
	// TODO 文件格式请用WAV
	const static string SOUND1;

	static Sound* getInstance();
	void stop() const;
	void play(const string& path) const;

private:
	static Sound* instance;
	SimpleAudioEngine* audio = SimpleAudioEngine::getInstance();
	Sound();
};

#endif
