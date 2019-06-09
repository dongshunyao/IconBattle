#ifndef __SOUND_H__
#define __SOUND_H__

#include "AudioEngine.h"
#include <string>
#include <vector>

using namespace cocos2d::experimental;
using std::string;
using std::vector;

class Sound
{
public:
#pragma region Sound URL
	// TODO 添加音效：点击、三消、粒子特效
	const string clicked = "/sound/clicked.mp3";
#pragma endregion

	static Sound* getInstance();
	void stop() const;
	void play(const string& path);
	bool getStatus() const { return on; }
	void setStatus(const bool status) { on = status; }
	void turnOn() { on = true; }
	void turnOff() { on = false; }

private:
	static Sound* instance;
	int audioId = AudioEngine::INVALID_AUDIO_ID;
	bool on = true;
	Sound();
};

#endif
