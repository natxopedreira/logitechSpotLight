#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    remote.setup();
    ofAddListener(remote.onRemoteData, this, &ofApp::messageFromRemote);
}

//--------------------------------------------------------------
void ofApp::update(){
    remote.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::messageFromRemote(int & msg){

    switch (msg)
    {
    case OF_KEY_INSERT:
        cout << "BOTON GORDO" << endl;
        break;

    case OF_KEY_LEFT:
        cout << "BOTON LEFT" << endl;
        break;
    
    case OF_KEY_RIGHT:
        cout << "BOTON RIGHT" << endl;
        break;

    default:
        break;
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' '){
        remote.vibrate(2,100);
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

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
