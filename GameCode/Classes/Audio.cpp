#include"Audio.h"

Audio::Audio()
{
	audio = CocosDenshion::SimpleAudioEngine::getInstance();

}

Audio::~Audio()
{
}


void Audio::getBackGroundMusic()
{
	audio->playBackgroundMusic("backMusic.mp3", true);
	isPlay = true;
}

void Audio::stopBackGroundMusic()
{
	audio->pauseBackgroundMusic();
	isPlay = false;
}

void Audio::resumBackGroundMusic()
{
	audio->resumeBackgroundMusic();
	isPlay = true;
}
