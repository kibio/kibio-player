#pragma once

#include <string>
#include <vector>

#include "Poco/URI.h"
#include "Poco/UUID.h"
#include "Poco/UUIDGenerator.h"

#include "ofPixels.h"
#include "ofxJSONElement.h"

using std::string;
using std::vector;

using Poco::URI;
using Poco::UUID;
using Poco::UUIDGenerator;

class KibioPlaylistItem;

class KibioAsset {
public:
    enum Type {
        VIDEO,
        SOUND
    };
    
    KibioAsset(const string& _filename, Type _fileType);
    virtual ~KibioAsset();
    
    string getFilename() const;
    URI    getURI() const;

    Type getType() const;
    
    UUID getUUID() const;

    void setDuration(unsigned long long _duration);
    unsigned long long getDuration() const;
    
    void setNumFrames(unsigned long long _numFrames);
    unsigned long long getNumFrames() const;

    Json::Value getJSON() const {
        Json::Value json;

        json["UUID"] = getUUID().toString();
        json["URI"]  = getURI().toString();

        json["duration"] = getDuration();
        json["numFrames"] = getNumFrames();

        if(getType() == VIDEO) {
            json["type"] = "VIDEO";
        } else if(getType() == SOUND) {
            json["type"] = "SOUND";
        } else {
            json["type"] = "UNKNOWN";
        }

        json["playCount"] = (int)playCount;

        json["size"]["width"] = width;
        json["size"]["height"] = height;

        return json;
    }


//    void addToPlaylist(KibioPlaylistItem* _playlistItem);
//    void removeFromPlaylist(KibioPlaylistItem* _playlistItem);
//    
//    void playCountReset();
//    void playCountAdd();
//    void playCountSubtract();
    
protected:
        
    Type fileType;
    string filename;
    UUID uuid;
    
    unsigned long playCount;
    unsigned long playlistOccuranceCount;

    float width;
    float height;
    
    unsigned long long duration; // ms
    unsigned long long numFrames;
    
    vector<ofPixels> frameCache;
    
    vector<KibioPlaylistItem*> playlistsItems;

};