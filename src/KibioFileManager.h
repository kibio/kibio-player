#pragma once

#include "ofSoundPlayer.h"
#include "ofVideoPlayer.h"

#include "ofFileUtils.h"
#include "MediaTypeMap.h"
#include "ofxJSONElement.h"

#include "KibioAsset.h"

class KibioFileManager {
public:
    KibioFileManager() {
        assetsJson = Json::Value(Json::arrayValue);
    }
    
    void setup() {
        ofDirectory dir;
        
        int numFiles = dir.listDir("assets");

        for(int i = 0; i < assets.size(); i++) {

        }

        for(int i = 0; i < numFiles; i++) {
            KibioAsset::Type type = (ofRandom(100) > 50 ? KibioAsset::SOUND : KibioAsset::VIDEO);
            KibioAsset ass(dir[i].getAbsolutePath(),type);
            assets.push_back(ass);
            assetsJson.append(ass.getJSON());
        }

         
    }
    
    Json::Value getJSON() const {
        return assetsJson;
    }

    Json::Value assetsJson;
    vector<KibioAsset> assets;
    
    
    // TODO: implement directory watcher
};