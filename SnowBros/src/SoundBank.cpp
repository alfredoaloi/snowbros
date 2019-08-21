/*
 * SoundBank.cpp
 *
 *  Created on: 21 ago 2019
 *      Author: franc
 */

#include "SoundBank.h"

SoundBank* SoundBank::instance = 0;

SoundBank::SoundBank() { backgroundPlaying = false; }

SoundBank::~SoundBank() { }

SoundBank* SoundBank::getInstance()
{
	if(instance == 0)
	{
		instance = new SoundBank();
	}

	return instance;
}

void SoundBank::addSample(std::string key, ALLEGRO_SAMPLE* sample)
{
	samples[key] = sample;
}

void SoundBank::stopBackgroundMusic()
{
	al_stop_samples();
	backgroundPlaying = false;
}

void SoundBank::playBackgroundMusic(std::string key)
{
	if (!backgroundPlaying)
	{
		std::map<std::string, ALLEGRO_SAMPLE*>::iterator it;
		it = samples.find(key);
		al_play_sample(it->second, 1.0, 0.0,1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
		backgroundPlaying = true;
	}
}

void SoundBank::playSample(std::string key)
{
	std::map<std::string, ALLEGRO_SAMPLE*>::iterator it;
	it = samples.find(key);
	al_play_sample(it->second, 1.0, 0.0,1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}
