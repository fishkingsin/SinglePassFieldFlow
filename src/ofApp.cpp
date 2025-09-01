#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofDisableArbTex();
	ofEnableAlphaBlending();
	ofSetLogLevel(OF_LOG_VERBOSE);
	
	
	
	shaderA.load("shaders/bufferA");
	shaderDraw.load("shaders/image");
	
	
	
	densityWidth = 1920;
	densityHeight = 1080;
	// process all but the density on 16th resolution
	simulationWidth = densityWidth / 2;
	simulationHeight = densityHeight / 2;
	windowWidth = ofGetWindowWidth();
	windowHeight = ofGetWindowHeight();
	
	fboBufferA.allocate(densityWidth, densityHeight, GL_RGBA32F_ARB);
	fboImage.allocate(densityWidth, densityHeight, GL_RGBA32F_ARB);
	
}

//--------------------------------------------------------------
void ofApp::update(){
	frame += 1 ;
	float dt = 1.0 / max(ofGetFrameRate(), 1.f); // more smooth as 'real' deltaTime.
	
	// apply noiseshader to fbo
	fboBufferA.begin();
	shaderA.begin();
	shaderA.setUniform3f("iResolution", densityWidth, densityHeight, 0);
	shaderA.setUniform1f("texCoordWidthScale", densityWidth);
	shaderA.setUniform1f("texCoordHeightScale", densityHeight);
	shaderA.setUniform1f("iTime", ofGetElapsedTimef());
	shaderA.setUniform1f("iTimeDelta", dt);
	shaderA.setUniform4f("iMouse", ofGetMouseX(), ofGetMouseY(), ofGetMousePressed(), 1.0);
	shaderA.setUniform1i("iFrame", frame);
	shaderA.setUniformTexture("iChannel0", fboBufferA.getTexture() , 1);
	fboImage.draw(0 ,0);
	shaderA.end();
	fboBufferA.end();
	
	fboImage.begin();
	shaderDraw.begin();
	shaderDraw.setUniform3f("iResolution", densityWidth, densityHeight, 0);
	shaderDraw.setUniform1f("texCoordWidthScale", densityWidth);
	shaderDraw.setUniform1f("texCoordHeightScale", densityHeight);
	shaderDraw.setUniform1f("iTime", ofGetElapsedTimef());
	shaderDraw.setUniform1i("iFrame", frame);
	shaderDraw.setUniformTexture("iChannel0", fboBufferA.getTexture() , 1 );
	
	fboBufferA.draw(0, 0);
	shaderDraw.end();
	fboImage.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	fboImage.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
	
	if (showGUI) {
		int width = windowWidth * 0.25;
		int height = windowHeight * 0.25;
		fboBufferA.draw(0, 0, width, height);
	}
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

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
