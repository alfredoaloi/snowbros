/*
 * SoundBank.h
 *
 *  Created on: 21 ago 2019
 *      Author: franc
 */

#ifndef SOUNDBANK_H_
#define SOUNDBANK_H_

#include <map>
#include <string>
#include <allegro5/allegro_audio.h>

class SoundBank {
	static SoundBank* instance;
	std::map<std::string, ALLEGRO_SAMPLE*> samples;
	bool backgroundPlaying;
protected:
	SoundBank();
	virtual ~SoundBank();
public:
	static SoundBank* getInstance();
	void addSample(std::string, ALLEGRO_SAMPLE*);
	void stopBackgroundMusic();
	void playBackgroundMusic(std::string);
	void playSample(std::string);
	bool isPlaying();
};

#endif /* SOUNDBANK_H_ */
