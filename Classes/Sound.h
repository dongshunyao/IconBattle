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
	// 单击
	const string click = "/sound/click.mp3";
	// 三消
	const string threeKill = "/sound/3kill.mp3";
	// 四消
	const string fourKill = "/sound/4kill.mp3";
	// 五消
	const string fiveKill = "/sound/5kill.mp3";
	// 爆炸
	const string boom = "/sound/boom.mp3";
	// super生成
	const string superCreate = "/sound/super.mp3";

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
