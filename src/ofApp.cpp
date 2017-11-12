#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofBackground(0);

    ofSetFrameRate(60);
    

    num.addListener(this, &ofApp::onNumChanged);
    friction.addListener(this, &ofApp::onFrictionChanged);
    
    ofColor minColor = ofColor(0, 0, 0, 0);
    ofColor maxColor = ofColor(255, 255, 255, 255);
    
    // GUI
    gui.setup();
    gui.add(num.setup("particle number", 100000,0, 200000));
    gui.add(size.setup("particle size", 1.0, 0.0, 3.0));
    gui.add(friction.setup("friction", 0.002, 0.0, 0.02));
    gui.add(attraction.setup("attraction", 0.1, 0.0, 1.0));
    gui.add(bgColor.setup("bg color", ofColor(0), minColor, maxColor));
    gui.add(fgColor.setup("fg color", ofColor(255), minColor, maxColor));
    
    // パラメータ読み込み
    gui.loadFromFile("settings.xml");
    
    mesh.setMode(OF_PRIMITIVE_POINTS);
    glPointSize(1.0);
    
    for (int i = 0; i < num; i++) {
        Particle p;
        p.friction = friction;
        p.setup(ofVec2f(ofRandom(ofGetWidth()), ofRandom(ofGetHeight())), ofVec2f(0, 0));
        particles.push_back(p);
    }
    
 
//    
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_NORMALIZE);
    
    leap.open();
    
}
//--------------------------------------------------------------
void ofApp::onFrictionChanged(float &friction){
    for (int i = 0; i < particles.size (); i++) {
        particles[i].friction = friction;
    }
}
//--------------------------------------------------------------
void ofApp::onNumChanged(int &num){

    if (num < particles.size()) {
  
        for (int i = 0; i < particles.size() - num; i++) {
            particles.pop_back();
        }
    }

    if (num > particles.size()) {

        int addNum = num - particles.size();
        for (int i = 0; i < addNum; i++) {
            Particle p;
            p.friction = friction;
            p.setup(ofVec2f(ofRandom(ofGetWidth()), ofRandom(ofGetHeight())), ofVec2f(0, 0));
            particles.push_back(p);
        }
    }
}
//--------------------------------------------------------------
void ofApp::update(){
    
    if(ofGetFrameNum() % 60==0){
        time++;
    }
    if(time<8){
    
    
    simplehands = leap.getSimpleHands();
    if( leap.isFrameNew() && simplehands.size()){
        fingerPos.clear();
        atraction = true;
//        leap.setMappingX(-230, 230, -ofGetWidth()/2, ofGetWidth()/2);
//        leap.setMappingY(90, 490, -ofGetHeight()/2, ofGetHeight()/2);
//        leap.setMappingZ(-150,150,-200,200);
        
        fingerType fingerTypes[] = {INDEX };
        
        for(int i=0;i<simplehands.size(); i++){
            
//                ofPoint mcp = simplehands[i].fingers[ fingerTypes[f] ].mcp;
//                fingerPos.push_back(mcp);
//                
//                
//                ofPoint pip = simplehands[i].fingers[ fingerTypes[f] ].pip;
//                fingerPos.push_back(pip);
//                
//                ofPoint dip = simplehands[i].fingers[ fingerTypes[f] ].dip;
//                fingerPos.push_back(dip);
                
                ofPoint tip = simplehands[i].fingers[ fingerTypes[1] ].tip;
                fingerPos.push_back(tip);

                
                
            
        }
        
    }
    leap.markFrameAsOld();
    
    }else{
        
    }
   
}

//--------------------------------------------------------------
void ofApp::draw(){
    
   

    for (int i = 0; i < particles.size(); i++){

        particles[i].resetForce();

        if( leap.isFrameNew() && simplehands.size()){
            particles[i].addAttractionForce(fingerPos.at(0).x+550,fingerPos.at(0).y+100, ofGetWidth(), attraction);
            
        }
        

        particles[i].update();

        particles[i].throughOfWalls();
    }
    
   

  
    
    
    ofPushMatrix();
    
    ofRotateX(180);
    ofTranslate(0, -ofGetHeight());

    mesh.clear();
    ofSetColor(fgColor);
    glPointSize(size);
    for (int i = 0; i < particles.size(); i++) {
        mesh.addVertex(ofVec3f(particles[i].position.x, particles[i].position.y, 0));
    }
    mesh.draw();
    ofPopMatrix();
    //GUI
    gui.draw();
    
    
//
//    if( leap.isFrameNew() && simplehands.size()){
//        ofPushMatrix();
//        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
//        ofRotateZ(180);
//        ofRotateY(180);
//        ofCircle(fingerPos.at(0).x,fingerPos.at(0).y,20);
//        ofPopMatrix();
//    }

}
//--------------------------------------------------------------

void ofApp::exit(){
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') {
        particles.clear();
        for (int i = 0; i < num; i++) {
            Particle p;
            p.friction = 0.002;
            p.setup(ofVec2f(ofRandom(ofGetWidth()), ofRandom(ofGetHeight())), ofVec2f(0, 0));
            particles.push_back(p);
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
atraction = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
atraction = false;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
