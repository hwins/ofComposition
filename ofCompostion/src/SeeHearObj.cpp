/*
 * SeeHearObj.cpp
 *
 *  Created on: Nov 30, 2012
 *      Author: Howard Winston
 */

#include "SeeHearObj.h"

using namespace std;

SeeHearObj::SeeHearObj(int tens, int ones) {

	/**
	 * Load image and sound for image with file names base on numbers
	 * passed to this constructor.
	 */

	string tens_position = static_cast<ostringstream*>( &(ostringstream() << tens) )->str();
	string ones_position = static_cast<ostringstream*>( &(ostringstream() << ones) )->str();

	// parameters to specify how long this should live in frame count, etc.
	loadControlData(tens_position + ones_position);
	alphaInPerFrame = MAX_ALPHA_VALUE / (cntl.fadeInFrames + 1.0); // add 1 to avoid 0 divide
	alphaOutPerFrame = MAX_ALPHA_VALUE / (cntl.fadeOutFrames + 1.0);
	alphaInCurrentAmt = 0.0;
	alphaOutCurrentAmt = 255.0;
	startFadeOut = cntl.fadeInFrames + cntl.runFrames;
	totalRunFrames = (int)(cntl.fadeInFrames + cntl.runFrames + cntl.fadeOutFrames);

	string fileNameString = IMAGE_DIR + tens_position + ones_position + IMAGE_TYPE;

	// validate image file exists prior to load, if not gracefully continue
	string testForExists = DATA_DIR + fileNameString;
	fileStream.open(testForExists.c_str());
	if (!fileStream.good()) {
		cout << "error with " << fileNameString << endl;
	} else {
		imagePng.loadImage(fileNameString);
	}
	fileStream.close();

	fileNameString = SOUND_DIR + tens_position + ones_position + SOUND_TYPE;

	soundStarted = false;

	// validate sound file exists prior to load, if not gracefully continue
	testForExists = DATA_DIR + fileNameString;
	fileStream.open(testForExists.c_str());
	if (!fileStream.good()) {
		cout << "error with " << fileNameString << endl;
	} else {
		soundForImage.loadSound(fileNameString);
		soundForImage.setMultiPlay(true);
	}
	fileStream.close();
}

SeeHearObj::~SeeHearObj() {

	soundForImage.close();
}

void SeeHearObj::startObj() {

	if (frameCount == 0) {
		frameCount = 1;
	}
}

int SeeHearObj::getFrameCount() {

	return frameCount;
}

int SeeHearObj::getAlphaLevel() {

	/**
	 * Works with floats but return an int value for alpha
	 */

	if (alphaInCurrentAmt < 255.0) {
		return (int)(alphaInCurrentAmt += alphaInPerFrame);
	}
	if (frameCount < startFadeOut) {
		return 255;
	}
	if (alphaOutCurrentAmt > 0.0) {
		return (int)(alphaOutCurrentAmt -= alphaOutPerFrame);
	}
	return 0;
}

int SeeHearObj::getZLevelNumber() {

	return ZLevelNumber;
}

void SeeHearObj::initialObject() {

	/**
	 * Establish position and controls for new object
	 */

	this->resetControls();

}

void SeeHearObj::executeDraw() {

	/**
	 * Contains all of the open frameworks draw tasks, when draw loop runs.
	 */

	imagePng.draw(x_pos, y_pos);
	if (frameCount == 1) {
		soundForImage.play();
	}

	// if frame count is beyond what it should run for then reset
	if (frameCount > totalRunFrames) {
		resetControls();
	} else {
		frameCount++;
	}

}

void SeeHearObj::resizeWindowDim() {

	/**
	 * Save new values for next time when calculating a random position.
	 * Adjust non-running images with new positions.
	 */

	if (frameCount < 1) {
		x_pos = (float)this->randomNumber(ofGetWidth() - imagePng.getWidth());
		y_pos = (float)this->randomNumber(ofGetHeight() - imagePng.getHeight());
	}
}

void SeeHearObj::loadControlData(const string fileNumber) {

	/**
	 * Load the control via parse of the respective associated control file data.
	 *
	 * in=000000 - number of frames to fade image in
	 * run=000000 - total number of frames to run once faded in
	 * out=000000 - number of frames to fade image out
	 */

	string controlFileString = DATA_DIR + CONTROL_DIR + fileNumber
			+ CONTROL_TYPE;
	controlFile.open(controlFileString.c_str());
	if (!controlFile.good()) {
		cout << "error with " << controlFileString << endl;
	} else {
		string workLine;
		while (getline(controlFile, workLine)) {
			if (!workLine.empty()) {
				int workSize = workLine.size();
				for (int i = 0; i < workSize; i++) {
					if (workLine.substr(i, (i + 3)) == "in=") {
						this->cntl.fadeInFrames = atoi(workLine.substr((i + 3),
								workLine.length()).c_str());
						continue;
					}
					if (workLine.substr(i, (i + 4)) == "run=") {
						this->cntl.runFrames = atoi(workLine.substr((i + 4),
								workLine.length()).c_str());
						continue;
					}
					if (workLine.substr(i, (i + 4)) == "out=") {
						this->cntl.fadeOutFrames = atoi(workLine.substr((i + 4),
								workLine.length()).c_str());
						continue;
					}
				}
			}
		}
	}
	controlFile.close();
}

void SeeHearObj::resetControls() {


	frameCount = 0;
	alphaInCurrentAmt = 0.0;
	alphaOutCurrentAmt = 255.0;
	imagePng.rotate90(randomNumber(3));
	x_pos = (float)this->randomNumber(ofGetWidth() - imagePng.getWidth());
	y_pos = (float)this->randomNumber(ofGetHeight() - imagePng.getHeight());
	ZLevelNumber = rand();
}

int SeeHearObj::randomNumber(int maxInt) {

	/**
	 * Return a random int between 0 and the maximum int provided
	 */

	int returnInt;
	returnInt = (int)((double)rand() / ((double)RAND_MAX + 1) * maxInt);
	return returnInt;
}
