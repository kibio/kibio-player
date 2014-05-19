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


#pragma once


#include <string>
#include <vector>
#include <json/json.h>
#include "Poco/URI.h"
#include "Poco/UUID.h"
#include "Poco/UUIDGenerator.h"
#include "ofPixels.h"


class KibioPlaylistItem;


class KibioAsset
{
public:
    enum Type
    {
        VIDEO,
        SOUND
    };
    
    KibioAsset(const std::string& filename, Type fileType);
    virtual ~KibioAsset();
    
    std::string getFilename() const;

    Poco::URI getURI() const;

    Type getType() const;
    
    Poco::UUID getUUID() const;

    void setDuration(unsigned long long _duration);

    unsigned long long getDuration() const;
    
    void setNumFrames(unsigned long long _numFrames);

    unsigned long long getNumFrames() const;

    Json::Value getJSON() const
    {
        Json::Value json;

        Poco::File file(getFilename());
        
        int fileSize = file.getSize();
        
        json["UUID"] = getUUID().toString();
        json["URI"]  = getURI().toString();
        json["fileName"]  = ofFilePath::getBaseName(getFilename());
        json["fileExtension"] = ofFilePath::getFileExt(getFilename());
        json["fileSize"] = fileSize;
        json["alias"]  = getFilename();
        json["duration"] = getDuration();
        json["numFrames"] = getNumFrames();

        if(getType() == VIDEO)
        {
            json["type"] = "VIDEO";
        }
        else if(getType() == SOUND)
        {
            json["type"] = "SOUND";
        }
        else
        {
            json["type"] = "UNKNOWN";
        }

        json["playCount"] = (int)_playCount;

        json["size"]["width"] = _width;
        json["size"]["height"] = _height;

        json["fileHealth"] = "Perfect";

        return json;
    }


//    void addToPlaylist(KibioPlaylistItem* _playlistItem);
//    void removeFromPlaylist(KibioPlaylistItem* _playlistItem);
//    
//    void playCountReset();
//    void playCountAdd();
//    void playCountSubtract();
    
protected:
    Type _fileType;
    std::string _filename;
    Poco::UUID _uuid;
    std::string _fileExtension;
    
    unsigned long _playCount;
    unsigned long _playlistOccuranceCount;

    float _width;
    float _height;
    
    unsigned long long _duration; // ms
    unsigned long long _numFrames;
    
    std::vector<ofPixels> _frameCache;
    
    std::vector<KibioPlaylistItem*> _playlistsItems;

};