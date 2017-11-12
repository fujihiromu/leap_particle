#pragma once

#include "ofMain.h"
#include "ofxLeapMotion2.h"
#include "Particle.hpp"
#include "ofxGui.h"
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void exit();
    
    ofxLeapMotion leap;
    vector <ofxLeapMotionSimpleHand> simplehands;
    
    ofxLeapMotionSimpleHand hands;
    
    vector <ofVec3f> fingerPos;
  

    vector<Particle> particles;

    ofVboMesh mesh;

    bool atraction;
    
    // GUI
    ofxPanel gui;
    ofxIntSlider num;
    ofxFloatSlider size;
    ofxFloatSlider friction;
    ofxFloatSlider attraction;
    ofxColorSlider bgColor;
    ofxColorSlider fgColor;
    
 
    void onNumChanged(int &num);
    void onFrictionChanged(float &friction);
    
    int time;
		
};
