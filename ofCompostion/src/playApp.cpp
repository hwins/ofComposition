#include "playApp.h"

//--------------------------------------------------------------
void playApp::setup(){

	loadSeeHearObjects();
	maxObjs = objs.size();

	ofSetFrameRate(FRAME_RATE);
	redBackGround = MAX_COLOR_VALUE;
	blueBackGround = MAX_COLOR_VALUE;
	greenBackGround = MAX_COLOR_VALUE;
	redIncrease = true;
	blueIncrease = true;
	greenIncrease = true;
	ofBackground(redBackGround, blueBackGround, greenBackGround);

}

//--------------------------------------------------------------
void playApp::update() {
	// order active objects in their level number order
	for (int i = 0; i < maxObjs; i++) {
		if (objs[i]->getFrameCount() > 0) {
			ObjZLevel ozlPush;
			ozlPush.zLevel = objs[i]->getZLevelNumber();
			ozlPush.objNumber = i;
			ZLevelQueue.push(ozlPush);
		}
	}
}

//--------------------------------------------------------------
void playApp::draw(){

	// choose a random color from red(0), blue(1), or green(2)
	// any number higher (>2) will not adjust color so controlling
	// this pool with a higher number will reduce the color change
	// potential
	int randColor = rand() % RANDOM_COLOR_MOD;
	switch (randColor) {
	case RANDOM_RED:
		if (redIncrease) {
			if (redBackGround > MAX_COLOR_VALUE) {
				redIncrease = false;
				redBackGround--;
			} else {
				redBackGround++;
			}
		} else {
			if (redBackGround < MIN_COLOR_VALUE) {
				redIncrease = true;
				redBackGround++;
			} else {
				redBackGround--;
			}
		}
		break;
	case RANDOM_BLUE:
		if (blueIncrease) {
			if (blueBackGround > MAX_COLOR_VALUE) {
				blueIncrease = false;
				blueBackGround--;
			} else {
				blueBackGround++;
			}
		} else {
			if (blueBackGround < MIN_COLOR_VALUE) {
				blueIncrease = true;
				blueBackGround++;
			} else {
				blueBackGround--;
			}
		}
		break;
	case RANDOM_GREEN:
		if (greenIncrease) {
			if (greenBackGround > MAX_COLOR_VALUE) {
				greenIncrease = false;
				greenBackGround--;
			} else {
				greenBackGround++;
			}
		} else {
			if (greenBackGround < MIN_COLOR_VALUE) {
				greenIncrease = true;
				greenBackGround++;
			} else {
				greenBackGround--;
			}
		}
		break;
	default: // no color change
		break;
	}

	ofBackground(redBackGround, blueBackGround, greenBackGround);

	ofEnableAlphaBlending();
	while (!ZLevelQueue.empty()) {
		ObjZLevel ozlPop = ZLevelQueue.top();
		ofSetColor(255,255,255,objs[ozlPop.objNumber]->getAlphaLevel());
		objs[ozlPop.objNumber]->executeDraw();
		ZLevelQueue.pop();
	}
	ofDisableAlphaBlending();
}

//--------------------------------------------------------------
void playApp::exit() {
	objs.clear();
}

//--------------------------------------------------------------
void playApp::keyPressed(int key){
	// toggle with F11
	if (key == F11) {
		if (ofGetWindowMode() == OF_FULLSCREEN) {
			ofSetFullscreen(False);
		} else {
			ofSetFullscreen(True);
		}
	}
}

//--------------------------------------------------------------
void playApp::keyReleased(int key){

}

//--------------------------------------------------------------
void playApp::mouseMoved(int x, int y){
	/*
	 * select at random an object that has not started (frame
	 * count = 0) and start it. up to the maximum to run at once.
	 */

	int active_count = 0;
	for (int i = 0; i < maxObjs; i++) {
		if (objs[i]->getFrameCount() > 0) {
			active_count++;
		}
	}

	if (active_count < MAX_AT_ONCE) {
		int randInt = (int)((double)rand() / ((double)RAND_MAX + 1) * maxObjs);
		if (objs[randInt]->getFrameCount() == 0) {
			objs[randInt]->startObj();
		}
	}
}

//--------------------------------------------------------------
void playApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void playApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void playApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void playApp::windowResized(int w, int h){

	/**
	 * Pass new window size to all vector objects.
	 */

	for (int i = 0; i < maxObjs; i++) {
		objs[i]->resizeWindowDim();
	}

}

//--------------------------------------------------------------
void playApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void playApp::dragEvent(ofDragInfo dragInfo){

}

void playApp::loadSeeHearObjects() {

	/**
	 * create new See Hear Objects and place in object vector
	 */

	objs.clear();

	// first fill up to the tens value
	for (int i = 0; i < TENS_MAX_FILE_NUM; i++) {
		for (int j = 0; j < 10; j++) {
			objPtr sho(new SeeHearObj(i, j));
			sho->initialObject();
			objs.push_back(sho);
		}
	}
	// now fill the remaining
	int max_ones = ONES_MAX_FILE_NUM + 1;
	for (int j = 0; j < max_ones; j++) {
		objPtr sho(new SeeHearObj(TENS_MAX_FILE_NUM, j));
		sho->initialObject();
		objs.push_back(sho);
	}

}
