#ifndef __MUSIC_H__
#define __MUSIC_H__

#include "AudioEngine.h"
#include <string>
#include <vector>

using namespace cocos2d::experimental;
using std::string;
using std::vector;

class Music
{
public:
	static Music* getInstance();

	void loading(const vector<string>& path) const;
	void stop() const;
	void play(const string& path);
	void change(const string& path);
	void setVolume(const int volume) const; // 范围0到100
	int getVolume() const;

private:
	static Music* instance;
	int audioId = AudioEngine::INVALID_AUDIO_ID;

	Music() = default;
};

#endif
