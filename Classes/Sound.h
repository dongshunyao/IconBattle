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
	const static string CLICKED;

	static Sound* getInstance();
	void stop() const;
	void play(const string& path) const;
	bool getStatus() const { return on; };
	void turnOn() { on = true; };
	void turnOff() { on = false; };

private:
	static Sound* instance;
	SimpleAudioEngine* audio = SimpleAudioEngine::getInstance();
	bool on = true;
	Sound();
};

#endif
