#ifndef __AUDIO_H__
#define __AUDIO_H__

#include"SimpleAudioEngine.h"
using namespace CocosDenshion;

class Audio
{
public:
	Audio();
	virtual ~Audio();
	bool isPlayBackGroundMusic() { return isPlay; }
	void changeStatu(bool status) { isPlay = status; }
	void getBackGroundMusic();
	void stopBackGroundMusic();
	void resumBackGroundMusic();

private:
	SimpleAudioEngine * audio;
	bool isPlay;
};

#endif // !__AUDIO_H__

