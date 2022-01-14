#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    sound.loadSound("imperial_march.wav"); //Loads a sound file (in bin/data/)
    sound.setLoop(true); // Makes the song loop indefinitely
    sound.setVolume(volume); // Sets the song volume
    ofSetBackgroundColor(36, 32,56); // Sets the Background Color
}

//--------------------------------------------------------------
void ofApp::update(){
    /* The update method is called muliple times per second
    It's in charge of updating variables and the logic of our app */
    ofSoundUpdate(); // Updates all sound players
    if (!pause){
    visualizer.updateAmplitudes(); // Updates Amplitudes for visualizer
    }
    if(replaying){
        tcounter++;
        if(tcounter%60==0){
            seconds++;
            if(seconds%5==0){
                recordIterator++;
                if(recordIterator>recordedKeys.size()){
                    replaying = false;
                }else{
                    char k = recordedKeys[recordIterator-1];
                    if (k!='r' && k!='t'){
                        controls(k);
                    }
                }
            }
        }
    }else{
        recordIterator = 0;
        seconds = 0;
        tcounter = 0;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    /* The update method is called muliple times per second
    It's in charge of drawing all figures and text on screen */
    ofSetColor(256);
    if(!playing){
        ofDrawBitmapString("Press 'p' to play some music!", ofGetWidth()/2 - 50, ofGetHeight()/2);
    }
    if(recording){
        ofDrawBitmapString("**Recording**", 0, 25);// Indicates user if it is recording
    }
    if(replaying){
        ofDrawBitmapString("**Replaying**", 0, 35);
    }
    vector<float> amplitudes = visualizer.getAmplitudes();
    if(mode == '1'){
        drawMode1(amplitudes);
    }else if(mode == '2'){
        drawMode2(amplitudes);
    }else if(mode == '3'){
        drawMode3(amplitudes);
    }else if(mode == '4'){
        drawMode4(amplitudes);
    }
}
void ofApp::drawMode1(vector<float> amplitudes){
        ofFill(); // Drawn Shapes will be filled in with color
        ofSetColor(256); // This resets the color of the "brush" to white
        ofDrawBitmapString("Rectangle Height Visualizer", 0, 15);
        ofSetBackgroundColor(40, 20,56);
        ofSetColor(ofRandom(0, 256), 85, 0);
        int bands = amplitudes.size();
        for(int i = 0; i < bands; i++){
            ofDrawRectangle((ofGetWidth()/64)*i, ofGetHeight(), ofGetWidth()/64,  amplitudes[i]);
        }
}
void ofApp::drawMode2(vector<float> amplitudes){
        ofSetLineWidth(5); // Sets the line width
        ofNoFill(); // Only the outline of shapes will be drawn
        ofSetColor(256); // This resets the color of the "brush" to white
        ofDrawBitmapString("Circle Radius Visualizer", 0, 15);
        ofSetBackgroundColor(20, 20,60);
        int bands = amplitudes.size();
        for(int i=0; i< bands; i++){
            ofSetColor((bands - i)*32 %256,18,144); // Color varies between frequencies
            ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, amplitudes[0]/(i +1));
        }
}

void ofApp::drawMode3(vector<float> amplitudes){
    ofFill();
    ofSetColor(256); // This resets the color of the "brush" to white
    ofDrawBitmapString("Rectangle Width Visualizer", 0, 15);
    // YOUR CODE HERE
    ofSetBackgroundColor(20, 40, 56);
    ofSetColor(ofRandom(0, 256), 25, 0);
    int bands = amplitudes.size();
    for(int i = 0; i < bands; i++){
        ofDrawRectangle(ofGetWidth(), (ofGetHeight()/64)*i, amplitudes[i], ofGetHeight()/64);
    }
}
void ofApp::drawMode4(vector<float> amplitudes){
    ofSetColor(256); // This resets the color of the "brush" to white
    ofDrawBitmapString("Custom Visualizer", 0, 15);
    // YOUR CODE HERE
    ofSetBackgroundColor(ofRandom(0,256), ofRandom(0,256), ofRandom(0,256));
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofSetColor(0);
    ofNoFill();
    ofPushMatrix();
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2); // Translate to the center of the screen
    int bands = amplitudes.size();
    for (int i = 0; i < bands; i++)
    {
        ofScale(1.1, 1.1);
        float time = ofGetElapsedTimef();
        float timeScale = 0.5;
        float noise = ofSignedNoise(time * timeScale) * 20.0;
        ofRotate(noise);
        ofDrawRectangle(0, 0, 50, amplitudes[0]);
    }
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::changeSong(string sng){
    // This method changes the song
    sound.stop();
    sound.loadSound(sng);// Loads a sound file (in bin/data/)
    sound.play();
}

//--------------------------------------------------------------
void ofApp::setVolumeHigh()
{
    // Raises Volume
    if (volume != 1)
    {
        volume = volume + 0.1;
        sound.setVolume(volume);
    }
}

//--------------------------------------------------------------
void ofApp::setVolumeLow()
{
    // Lowers Volume
    if (volume != 0)
    {
        volume = volume - 0.1;
        sound.setVolume(volume);
    }
}
//--------------------------------------------------------------
void ofApp::controls(int key){

    if(recording){ // records key in string
            recordedKeys += key;
        }
        // This method is called automatically when any key is pressed
        switch (key)
        {
        // Controls
        case 'p':
            if(playing){
                sound.stop();
            }else{
                sound.play();
            }
            playing = !playing;
            break;
        case 'a':
            if (pause){
                pause = false;
            }else{
                pause = true;
            }
            break;
        case 'r':
            if(recording){
                recording = false;
            }else{
                recording = true;
            }
            break;
        case '=':
            setVolumeHigh();
            break;
        case '-':
            setVolumeLow();
            break;
        // Songs
        case 'd':
            changeSong("geesebeat.wav");
            break;
        case 'f':
            changeSong("pigeon-coo.wav");
            break;
        case 'g':
            changeSong("rock-song.wav");
            break;
        case 'h':
            changeSong("beat.wav");
            break;
        case 'x':
            changeSong("Looping_Steps.wav");
            break;
        case 'y':
            changeSong("imperial_march.wav");
            break;
        // Options
        case '1':
            mode = '1';
            break;
        case '2':
            mode = '2';
            break;
        case '3':
            mode = '3';
            break;
        case '4':
            mode = '4';
            break;
        case '5':
            char range[] = "1234";
            char result = range[rand()% 4];
            mode = result;
            break;
    }

}
//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if(key == 't' && !replaying){
        replaying = true;
    }else if(key == 't' && replaying){
        replaying = false;
    }
    if(!replaying){
        controls(key);
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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