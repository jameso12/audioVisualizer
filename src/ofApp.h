#pragma once

#include "ofMain.h"
#include "AudioVisualizer.h"
#include <string>

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();

		void drawMode1(vector<float> amplitudes);
		void drawMode2(vector<float> amplitudes);
		void drawMode3(vector<float> amplitudes);
		void drawMode4(vector<float> amplitudes);
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void changeSong(string song);
		void setVolumeHigh();
		void setVolumeLow();
		void controls(int key);
	private:
		ofSoundPlayer sound;
		AudioVisualizer visualizer;
		
		bool playing = false;
		bool pause = false;
		bool recording = false;
		bool replaying = false;
		string recordedKeys;
		int tcounter = 0;
		int seconds;
		unsigned int recordIterator = 0;
		unsigned int recGuard;
		double volume = 0.5;
		char mode = '1';
};
