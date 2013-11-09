#pragma once

#include "ofMain.h"
#include "SeeHearObj.h"
#include <vector>
#include <boost/shared_ptr.hpp>

using namespace std;

// max number of files broken down tens and ones position
// example: 1 and 9 for numbers 00,01,02,...19
// 9 and 9 is maximum
static const int TENS_MAX_FILE_NUM = 2;
static const int ONES_MAX_FILE_NUM = 1;

static const int FRAME_RATE = 60;	// if changed must change control files as well
static const int MAX_AT_ONCE = 6;	// to avoid too much chaos

//Miscellaneous constants
static const int F11 = 267;
static const int RANDOM_RED = 0;
static const int RANDOM_BLUE = 1;
static const int RANDOM_GREEN = 2;
static const int RANDOM_COLOR_MOD = 100; // this will control who wildly the color change
static const int MIN_COLOR_VALUE = 2;
static const int MAX_COLOR_VALUE = 250;

class playApp : public ofBaseApp{
public:
	void setup();
	void update();
	void draw();
	void exit();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

private:
	void loadSeeHearObjects();
	int maxObjs;
	int redBackGround;
	int blueBackGround;
	int greenBackGround;
	bool redIncrease;
	bool blueIncrease;
	bool greenIncrease;
	typedef boost::shared_ptr<SeeHearObj> objPtr;
	vector <objPtr> objs;

	// hold draw object's level value with its number
	// the purpose of the Z level is so the same object is
	// not always on top
	struct ObjZLevel {
		int zLevel;
		int objNumber;
		bool operator<(const struct ObjZLevel& other) const {
			return zLevel < other.zLevel;
		}
	};
	priority_queue <ObjZLevel> ZLevelQueue;

};
