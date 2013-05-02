#pragma once

#include "ofSoundPlayer.h"
#include "ofVideoPlayer.h"

#include "ofFileUtils.h"
#include "ofxMediaTypes.h"

class KibioFileManager {
public:
    KibioFileManager() {
        
    }
    
    void setup() {
        /*
        ofDirectory dir;
        
        int numFiles = dir.listDir("assets");
        
        vector<ofFile> image;
        vector<ofFile> video;
        vector<ofFile> audio;
        
        
        for(unsigned int i = 0; i < numFiles; i++) {
            ofFile file = dir.getFile(i);

            MediaType mediaType = ofxHTTPGetMimeType(ofFilePath::getFileExt(file.getFileName()));
            
            const string& type = mediaType.getType();
            
            if(type == "audio") {
                audio.push_back(file);
            } else if(type == "video") {
                video.push_back(file);
            } else if(type == "image") {
                image.push_back(file);
            } else {
                // unsupported
            }
        }
        
        vector<ofFile>::iterator iter;
        
        cout << "\tAudio==" << endl;
        iter = audio.begin();
        while(iter != audio.end()) {
            
            ofSoundPlayer soundStart;
            soundStart.loadSound((*iter).getAbsolutePath());
            soundStart.play();
            soundStart.setPosition(0.9999999f);
            int ms = soundStart.getPositionMS();
            soundStart.stop();

            cout << (*iter).getFileName() << " ||| duration=" << ms / 1000 << " seconds" << endl;

            ++iter;
        }
        
        cout << "\t==Video==" << endl;
        iter = video.begin();
        while(iter != video.end()) {
            cout << (*iter).getFileName();
            ofVideoPlayer player;
            player.loadMovie((*iter).getAbsolutePath());
            player.play();
            player.setPosition(0.9999999f);
            int ms = player.getDuration();
            player.stop();
            //.getDuration();

            
            
            cout << " ||| duration=" << ms / 1000 << " seconds" << endl;
            
            ++iter;
        }
        
        cout << "\t==Image==" << endl;
        iter = image.begin();
        while(iter != image.end()) {
            cout << (*iter).getFileName() << endl;
            ++iter;
        }
        
    
         */
    }
    
    
    
    
    
    
    // TODO: implement directory watcher
};