#include "KibioApp.h"

//------------------------------------------------------------------------------
void KibioApp::exit() {
    server->unregisterWebSocketEvents(this); // not needed
}

//------------------------------------------------------------------------------
void KibioApp::setup() {



    ofSetFrameRate(30);
    ofEnableAlphaBlending();

    ofSetLogLevel(OF_LOG_NOTICE);

    ofxWebSocketServerBasic::Settings settings;

    Zeroconf::Service::TXTRecord txtRecord;

    txtRecord.add("kibio","");
    txtRecord.add("version", "0.1");
    ofxZeroconf::registerService("_http._tcp.", settings.port,txtRecord);
    ofxZeroconf::registerService("_kibio_player._tcp.", settings.port,txtRecord);


    server = ofxWebSocketServerBasic::instance(settings);
    server->registerWebSocketEvents(this);
    server->start();
    
    videoPlayer.loadMovie("assets/0_fingers.mov");
    videoPlayer.setLoopState(OF_LOOP_NORMAL);
    videoPlayer.play();
    
//    ofLaunchBrowser(server.getURL());
    
    lastMessage = "Loaded fingers.mov";
    lastMessageAlpha = 255;
    
    lastIcon = "play";
    lastIconAlpha = 255;
    
    icons["step_backward"] = ofPtr<ofImage>(new ofImage("icons/glyphicons_170_step_backward.png"));
    icons["fast_backward"] = ofPtr<ofImage>(new ofImage("icons/glyphicons_171_fast_backward.png"));
    icons["rewind"] = ofPtr<ofImage>(new ofImage("icons/glyphicons_172_rewind.png"));
    icons["play"] = ofPtr<ofImage>(new ofImage("icons/glyphicons_173_play.png"));
    icons["pause"] = ofPtr<ofImage>(new ofImage("icons/glyphicons_174_pause.png"));
    icons["stop"] = ofPtr<ofImage>(new ofImage("icons/glyphicons_175_stop.png"));
    icons["forward"] = ofPtr<ofImage>(new ofImage("icons/glyphicons_176_forward.png"));
    icons["fast_forward"] = ofPtr<ofImage>(new ofImage("icons/glyphicons_177_fast_forward.png"));
    icons["step_forward"] = ofPtr<ofImage>(new ofImage("icons/glyphicons_178_step_forward.png"));
 
    fileManager.setup();

}

//------------------------------------------------------------------------------
void KibioApp::update() {
    videoPlayer.update();
    
    if(videoPlayer.isFrameNew()) {
        server->broadcast(videoPlayer.getPixelsRef());
    }
        
    lastMessageAlpha = ofClamp(lastMessageAlpha-7,0,255); // dim the message text
    lastIconAlpha    = ofClamp(lastIconAlpha-7,0,255); // dim the message text
    
}

//------------------------------------------------------------------------------
void KibioApp::draw() {
    ofBackground(255);
    ofSetColor(255);
    videoPlayer.draw(0,0,ofGetWidth(),ofGetHeight());
    
    size_t numConnected = server->getNumClientsConnected();
    
    ofSetColor(255,255,0);
    ofFill();
    
    int pad = 5;
    string txt = "Num Connected: " + ofToString(numConnected);
    ofPoint posTop(pad,10+pad);
    ofDrawBitmapStringHighlight(txt,posTop,ofColor(0),ofColor(255));

    ofPoint posBottom(pad,ofGetHeight()-pad);
    ofDrawBitmapStringHighlight(lastMessage,posBottom,ofColor(0,lastMessageAlpha),ofColor(255,lastMessageAlpha));
    
    
    if(icons.find(lastIcon) != icons.end()) {
        ofPtr<ofImage> img = icons[lastIcon];
        
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        
        ofFill();
        ofSetColor(255,255,255,lastIconAlpha);
        
//        img->draw(-img->width / 2, -img->height/2);
        
        
        ofPopMatrix();
        
    } else {
        ofLogError() << "Could not find icon called : " << lastIcon;
    }
    
    
}

//------------------------------------------------------------------------------
void KibioApp::gotMessage(ofMessage msg) {
    lastMessage = msg.message;
    lastMessageAlpha = 255;
}

//------------------------------------------------------------------------------
void KibioApp::onOpenEvent(ofxWebSocketEventArgs& _evtArgs) {
    ofSendMessage("Got open event.");
}

//------------------------------------------------------------------------------
void KibioApp::onCloseEvent(ofxWebSocketEventArgs& _evtArgs) {
    ofSendMessage("Got close event.");
}

//------------------------------------------------------------------------------
void KibioApp::onFrameReceivedEvent(ofxWebSocketFrameEventArgs& _evtArgs) {
    ofSendMessage("Got frame received event.");
    if(_evtArgs.frame.isBinary()) {
        cout << "binary frame=" << endl;
    } else {
        commandInterpreter(_evtArgs);
    }
    
}

//------------------------------------------------------------------------------
void KibioApp::onFrameSentEvent(ofxWebSocketFrameEventArgs& _evtArgs) {
    ofSendMessage("Got frame sent event.");
}

//------------------------------------------------------------------------------
void KibioApp::onErrorEvent(ofxWebSocketEventArgs& _evtArgs) {
    ofSendMessage("Got error event.");
}

//------------------------------------------------------------------------------
void KibioApp::commandInterpreter(ofxWebSocketFrameEventArgs& _evtArgs) {

    string data = _evtArgs.getFrameRef().getText();

    ofxJSONElement json;
    if(json.parse(data)) {
        if(json.isMember("command") && json["command"].isString()) {
            
            string command = json["command"].asString();
            
            cout << "command = " << command << endl;
            
            if(startsWith(command,"video-control")) {
                if(command == "video-control-backward") {
                    
                } else if(command == "video-control-play") {
                    videoPlayer.play();
                } else if(command == "video-control-pause") {
                    videoPlayer.setPaused(!videoPlayer.isPaused());
                } else if(command == "video-control-stop") {
                    videoPlayer.stop();
                } else if(command == "video-control-forward") {

                } else if(command == "video-control-position") {
                    if(json.isMember("data") && json["data"].isDouble()) {
                        videoPlayer.setPosition(json["data"].asDouble());
                    }
                } else {
                    cout << "UNKNOWN COMMAND " << command << endl;
                }
            } else if(startsWith(command,"video-info")) {
                if(command == "video-info-list") {

                    Json::Value value;
                    value["assets"] = fileManager.getJSON();

                    ofxWebSocketFrame frame(value.toStyledString());

                    server->sendFrame(&_evtArgs.getConnectionRef(), frame);
                }


            } else {
                
            }
            
            
            
            /*
             VIDEO_CONTROL_BACKWARD = "video-control-backward";
             VIDEO_CONTROL_PLAY     = "video-control-play";
             VIDEO_CONTROL_PAUSE    = "video-control-pause";
             VIDEO_CONTROL_STOP     = "video-control-stop";
             VIDEO_CONTROL_FORWARD  = "video-control-forward";
             VIDEO_CONTROL_POSITION = "video-control-position";
             */
            
        } else {
            cout << "no command " << endl;
        }
        
    } else {
        cout << "invalid packet json: " << data << endl;
    }
    
    cout << "frame=" << data << endl;
}

//------------------------------------------------------------------------------
bool KibioApp::startsWith(const string& target, const string& prefix) {
    return !target.compare(0, prefix.size(), prefix);
}
