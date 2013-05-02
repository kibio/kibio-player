#pragma once

#include <string>
#include <vector>

#include "Poco/UUID.h"
#include "Poco/UUIDGenerator.h"

#include "ofPixels.h"

using std::string;
using std::vector;

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
    Type getType() const;
    
    UUID getUUID() const;

    void setDuration(unsigned long long _duration);
    unsigned long long getDuration() const;
    
    void setNumFrames(unsigned long long _numFrames);
    unsigned long long getNumFrames() const;

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