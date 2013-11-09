/*
 * SeeHearObj.h
 *
 *  Created on: Nov 30, 2012
 *      Author: user01
 */

#pragma once

#ifndef SEEHEAROBJ_H_
#define SEEHEAROBJ_H_
#include "ofMain.h"
#include <iostream>
#include <fstream>

using namespace std;

static const string DATA_DIR = "data/";
static const string CONTROL_DIR = "control/";
static const string CONTROL_TYPE = ".cntl";
static const string IMAGE_DIR = "images/";
static const string IMAGE_TYPE = ".png";
static const string SOUND_DIR = "sounds/";
static const string SOUND_TYPE = ".wav";
static const int MAX_ALPHA_VALUE = 255;

class SeeHearObj {

public:
	SeeHearObj(int, int);
	~SeeHearObj();
	void startObj();
	int getFrameCount();
	int getAlphaLevel();
	int getZLevelNumber();
	void initialObject();
	void executeDraw();
	void resizeWindowDim();

private:
	ifstream fileStream;
	ifstream controlFile;

	struct controlParms {
		int fadeInFrames;
		int runFrames;
		int fadeOutFrames;

		controlParms() {
			fadeInFrames = 0;
			runFrames = 0;
			fadeOutFrames = 0;
		}
	} cntl;

	ofImage imagePng;
	float alphaInPerFrame;
	float alphaInCurrentAmt;
	float alphaOutPerFrame;
	float alphaOutCurrentAmt;
	float startFadeOut;
	int totalRunFrames;
	float x_pos, y_pos;
	bool soundStarted;
	ofOpenALSoundPlayer soundForImage;
	void loadControlData(string);
	void resetControls();
	int randomNumber(int);
	int frameCount;
	int ZLevelNumber;
};

#endif /* SEEHEAROBJ_H_ */
