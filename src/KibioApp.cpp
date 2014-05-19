// =============================================================================
//
// Copyright (c) 2013 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#include "KibioApp.h"


namespace Kibio {


PlayerApp::PlayerApp()
{
    // Must register for all events before initializing server.
    ofSSLManager::registerAllEvents(this);

    server.getPostRoute()->registerPostEvents(this);
    server.getWebSocketRoute()->registerWebSocketEvents(this);
}


PlayerApp::~PlayerApp()
{
    server.getWebSocketRoute()->unregisterWebSocketEvents(this);
    server.getPostRoute()->unregisterPostEvents(this);

    ofSSLManager::unregisterAllEvents(this);
}


void PlayerApp::setup()
{
    ofSetFrameRate(30);

    ofSetLogLevel(OF_LOG_VERBOSE);

    ofSSLManager::initializeServer(new Poco::Net::Context(Poco::Net::Context::SERVER_USE,
                                                          ofToDataPath("ssl/privateKey.nopassword.pem"),
                                                          ofToDataPath("ssl/selfSignedCertificate.nopassword.pem"),
                                                          ofToDataPath("ssl/cacert.pem")));

    HTTP::BasicJSONRPCServerSettings settings; // TODO: load from file.
    // settings.setUseSSL(true);
    server.setup(settings);

    server.start();
    
    videoPlayer.loadMovie("assets/0_fingers.mov");
    videoPlayer.setLoopState(OF_LOOP_NORMAL);
    videoPlayer.play();
    
    ofLaunchBrowser(server.getURL());

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

//    txtRecord.add("kibio","");
//    txtRecord.add("version", "0.1");
//    ofxZeroconf::registerService("_http._tcp.", settings.port,txtRecord);
//    ofxZeroconf::registerService("_kibio_player._tcp.", settings.port,txtRecord);

}


void PlayerApp::update()
{
    videoPlayer.update();
    
//    if(videoPlayer.isFrameNew())
//    {
//        server->broadcast(videoPlayer.getPixelsRef());
//    }

    lastMessageAlpha = ofClamp(lastMessageAlpha-7,0,255); // dim the message text
    lastIconAlpha    = ofClamp(lastIconAlpha-7,0,255); // dim the message text
    
}


void PlayerApp::draw()
{
    ofBackground(255);
    ofSetColor(255);
    videoPlayer.draw(0,0,ofGetWidth(),ofGetHeight());
    
    std::size_t numConnected = server.getWebSocketRoute()->getNumWebSocketConnections();
    
    ofSetColor(255,255,0);
    ofFill();
    
    int pad = 5;

    string txt = "Num Connected: " + ofToString(numConnected);

    ofPoint posTop(pad,10+pad);

    ofDrawBitmapStringHighlight(txt, posTop, ofColor(0), ofColor(255));

    ofPoint posBottom(pad, ofGetHeight() - pad);
    ofDrawBitmapStringHighlight(lastMessage,
                                posBottom,
                                ofColor(0, lastMessageAlpha),
                                ofColor(255, lastMessageAlpha));
    
    if(icons.find(lastIcon) != icons.end())
    {
        ofPtr<ofImage> img = icons[lastIcon];
        
        ofPushMatrix();
        ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
        
        ofFill();
        ofSetColor(255,255,255,lastIconAlpha);
        
//        img->draw(-img->width / 2, -img->height/2);

        ofPopMatrix();
        
    } else {
        ofLogError() << "Could not find icon called : " << lastIcon;
    }
    
    
}


void PlayerApp::gotMessage(ofMessage msg)
{
    lastMessage = msg.message;
    lastMessageAlpha = 255;
}

bool PlayerApp::onWebSocketOpenEvent(HTTP::WebSocketEventArgs& args)
{
    //    ofLogVerbose("App::onWebSocketOpenEvent") << "Connection opened from: " << args.getConnectionRef().getClientAddress().toString();
    return false; // did not handle it
}


bool PlayerApp::onWebSocketCloseEvent(HTTP::WebSocketEventArgs& args)
{
    //    ofLogVerbose("App::onWebSocketCloseEvent") << "Connection closed from: " << args.getConnectionRef().getClientAddress().toString();
    return false; // did not handle it
}


bool PlayerApp::onWebSocketFrameReceivedEvent(HTTP::WebSocketFrameEventArgs& args)
{
    //    ofLogVerbose("App::onWebSocketFrameReceivedEvent") << "Frame received from: " << args.getConnectionRef().getClientAddress().toString();
    return false; // did not handle it
}


bool PlayerApp::onWebSocketFrameSentEvent(HTTP::WebSocketFrameEventArgs& args)
{
    //    ofLogVerbose("App::onWebSocketFrameSentEvent") << "Frame sent to: " << args.getConnectionRef().getClientAddress().toString();
    return false; // did not handle it
}


bool PlayerApp::onWebSocketErrorEvent(HTTP::WebSocketEventArgs& args)
{
    //    ofLogVerbose("App::onWebSocketErrorEvent") << "Error on: " << args.getConnectionRef().getClientAddress().toString();
    return false; // did not handle it
}


bool PlayerApp::onHTTPPostEvent(HTTP::PostEventArgs& args)
{
    //    ofLogNotice("ofApp::onHTTPPostEvent") << "Data: " << args.getBuffer().getText();
    return false;
}


bool PlayerApp::onHTTPFormEvent(HTTP::PostFormEventArgs& args)
{
    //    ofLogNotice("ofApp::onHTTPFormEvent") << "";
    //    HTTP::Utils::dumpNameValueCollection(args.getForm(), ofGetLogLevel());
    return false;
}


bool PlayerApp::onHTTPUploadEvent(HTTP::PostUploadEventArgs& args)
{
    //    std::string stateString = "";
    //
    //    switch (args.getState())
    //    {
    //        case HTTP::PostUploadEventArgs::UPLOAD_STARTING:
    //            stateString = "STARTING";
    //            break;
    //        case HTTP::PostUploadEventArgs::UPLOAD_PROGRESS:
    //            stateString = "PROGRESS";
    //            break;
    //        case HTTP::PostUploadEventArgs::UPLOAD_FINISHED:
    //            stateString = "FINISHED";
    //            break;
    //    }
    //
    //    ofLogNotice("ofApp::onHTTPUploadEvent") << "";
    //    ofLogNotice("ofApp::onHTTPUploadEvent") << "         state: " << stateString;
    //    ofLogNotice("ofApp::onHTTPUploadEvent") << " formFieldName: " << args.getFormFieldName();
    //    ofLogNotice("ofApp::onHTTPUploadEvent") << "orig. filename: " << args.getOriginalFilename();
    //    ofLogNotice("ofApp::onHTTPUploadEvent") <<  "      filename: " << args.getFilename();
    //    ofLogNotice("ofApp::onHTTPUploadEvent") <<  "      fileType: " << args.getFileType().toString();
    //    ofLogNotice("ofApp::onHTTPUploadEvent") << "# bytes xfer'd: " << args.getNumBytesTransferred();
    return false;
}


void PlayerApp::onSSLServerVerificationError(Poco::Net::VerificationErrorArgs& args)
{
    ofLogVerbose("ofApp::onServerVerificationError") << args.errorMessage();

    // if you want to proceed, you should allow your user to inspect
    // the certificate and set:
    //     args.setIgnoreError(true);
    // if they approve
}


void PlayerApp::onSSLClientVerificationError(Poco::Net::VerificationErrorArgs& args)
{
    ofLogVerbose("ofApp::onClientVerificationError") << args.errorMessage();

    std::stringstream ss;

    ss << "Error: " << args.errorMessage() << " #" << args.errorNumber() << " depth: " << args.errorDepth() << std::endl;

    ss << "Certificate: " << std::endl;

    ss << "Issued By: " << args.certificate().issuerName() << std::endl;
    ss << "Subject Name: " << args.certificate().issuerName() << std::endl;
    ss << "Common Name: " << args.certificate().issuerName() << std::endl;

    Poco::DateTime ldtValidFrom = args.certificate().validFrom();
    Poco::DateTime ldtExpiresOn = args.certificate().expiresOn();

    ss << "Valid From: " << Poco::DateTimeFormatter::format(ldtValidFrom, "%dd %H:%M:%S.%i") << std::endl;
    ss << "Expires On: " << Poco::DateTimeFormatter::format(ldtExpiresOn, "%dd %H:%M:%S.%i") << std::endl;
    
    ofLogVerbose("ofApp::onServerVerificationError") << ss.str();
    
    // if you want to proceed, you should allow your user to inspect
    // the certificate and set:
    //     args.setIgnoreError(true);
    // if they approve
}


void PlayerApp::onSSLPrivateKeyPassphraseRequired(std::string& args)
{
    ofLogVerbose("ofApp::onPrivateKeyPassphraseRequired") << args;
    
    // if you want to proceed, you should allow your user set the
    // the certificate and set:
    args = "password";
}


//void PlayerApp::commandInterpreter(WebSocketFrameEventArgs& _evtArgs)
//{
//    std::string data = _evtArgs.getFrameRef().getText();
//
//    ofxJSONElement json;
//    if(json.parse(data)) {
//        if(json.isMember("command") && json["command"].isString()) {
//            
//            string command = json["command"].asString();
//            
//            cout << "command = " << command << endl;
//            
//            if(startsWith(command,"video-control")) {
//                if(command == "video-control-backward") {
//                    
//                } else if(command == "video-control-play") {
//                    videoPlayer.play();
//                } else if(command == "video-control-pause") {
//                    videoPlayer.setPaused(!videoPlayer.isPaused());
//                } else if(command == "video-control-stop") {
//                    videoPlayer.stop();
//                } else if(command == "video-control-forward") {
//
//                } else if(command == "video-control-position") {
//                    if(json.isMember("data") && json["data"].isDouble()) {
//                        videoPlayer.setPosition(json["data"].asDouble());
//                    }
//                } else {
//                    cout << "UNKNOWN COMMAND " << command << endl;
//                }
//            } else if(startsWith(command,"video-info")) {
//                if(command == "video-info-list") {
//
//                    Json::Value value;
//                    value["assets"] = fileManager.getJSON();
//
//                    WebSocketFrame frame(value.toStyledString());
//
//                    server->sendFrame(&_evtArgs.getConnectionRef(), frame);
//                }
//
//
//            } else {
//                
//            }
//            
//            
//            
//            /*
//             VIDEO_CONTROL_BACKWARD = "video-control-backward";
//             VIDEO_CONTROL_PLAY     = "video-control-play";
//             VIDEO_CONTROL_PAUSE    = "video-control-pause";
//             VIDEO_CONTROL_STOP     = "video-control-stop";
//             VIDEO_CONTROL_FORWARD  = "video-control-forward";
//             VIDEO_CONTROL_POSITION = "video-control-position";
//             */
//            
//        } else {
//            cout << "no command " << endl;
//        }
//        
//    } else {
//        cout << "invalid packet json: " << data << endl;
//    }
//    
//    cout << "frame=" << data << endl;
//}


} // namespace Kibio
