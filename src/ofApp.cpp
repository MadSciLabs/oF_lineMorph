#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofxSVG _svg;
    vector< ofPath > _paths;
                     
    arrSvgPath.push_back("g_1_oneline.svg");
    arrSvgPath.push_back("g_2_oneline.svg");
    
    for ( auto _p : arrSvgPath ) {
        
        _svg.load(_p);
        _paths = _svg.getPaths();
        //_paths[0].scale(3,3);
        
        arrPaths.push_back(_paths[0].getOutline()[0]);
    }

    ofEnableSmoothing();

    //Conform the drawings
    conformDrawings();

    //Init the correct line
    _polyStart = arrPaths[0];
    
    dIndex = 0;
}

/*
    Drawings need to all have the same number of points. For drawings with less than maximum, we pad the drawing
    with duplicate points. It may make sense to only do it before each move so that we don't have redundant padded
    points
*/
void ofApp::conformDrawings() {
    
    int _maxSize = 0;
    int _curIndex = 0;
    int _diff, _step = 0;

    //Add rest of points
    int _x, _y; // = arrPaths[1].getVertices()[0].y;

    //Get max size
    for ( auto _p : arrPaths )
    {
        if (_p.size() > _maxSize) {
            _maxSize = _p.size();
        }
    }
    
    ofLog() << "Max size : " <<_maxSize;

    //Loop again to pad each Path as needed
    for ( int j=0; j<arrPaths.size(); j++ )
    {
        ofLog() << "Point count : " << arrPaths[j].size();

        //Number of points we need to fill in
        _diff = _maxSize - arrPaths[j].size();
        
        ofLog() << "Diff : " << _diff;
        
        //Spacing of those points to evenly fill in path
        _step = _maxSize / (_diff + 1);
    
        _curIndex = _step;

        //Pad the path as needed
        for (int i=0; i<_diff; i++)
        {
            _x = arrPaths[j].getVertices()[_curIndex].x;
            _y = arrPaths[j].getVertices()[_curIndex].y;

            arrPaths[j].insertVertex(ofPoint(_x,_y), _curIndex);
            _curIndex += _step;
        }
    }


    ofLog() << "Point count 0: " << arrPaths[0].size();
    ofLog() << "Point count 1: " << arrPaths[1].size();
    
}

//--------------------------------------------------------------
void ofApp::update(){

    int _x, _y;
    ofVec2f vC, vT, vD;
    
    ofSetColor(0);
    
    if (START)
    {
        
        for (int i=0; i<_polyStart.getVertices().size(); i++)
        {
            vC = ofVec2f(_polyStart.getVertices()[i].x,_polyStart.getVertices()[i].y);
            vT = ofVec2f(_polyTarget.getVertices()[i].x,_polyTarget.getVertices()[i].y);
            
            vD = .025*(vT - vC);
            vC += vD;

            //If we are close enough, just set to the target node
            if (abs(vD.length()) < .025) {
                vC = vT;
            }

            _polyStart.getVertices()[i].set(vC.x, vC.y);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    //vPaths[0].setStrokeColor(0);
    //vPaths[0].draw();

    //ofTranslate(-500,0);
    //ofScale(4,4);
    
    
    _polyStart.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    START = true;
    
    dIndex++;
    
    if (dIndex % 2 == 1) {

        _polyStart = arrPaths[0];
        _polyTarget = arrPaths[1];

    } else {

        _polyStart = arrPaths[1];
        _polyTarget = arrPaths[0];
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
