#include "playApp.h"
#include "ofAppGlutWindow.h"
#include <stdio.h>

//--------------------------------------------------------------
int main(){
	ofAppGlutWindow window; // create a window
	// set width, height, mode (OF_WINDOW or OF_FULLSCREEN)
	ofSetupOpenGL(&window, 1024, 768, OF_WINDOW);
	ofRunApp(new playApp()); // start the app
	return 0;
}
