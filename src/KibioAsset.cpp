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


#include "KibioAsset.h"



KibioAsset::KibioAsset(const std::string& filename, Type fileType):
    _filename(filename),
    _fileType(fileType),
    _playlistOccuranceCount(0),
    _playCount(0),
    _width(0),
    _height(0),
    _duration(0),
    _numFrames(0)
{
    _uuid = Poco::UUID(Poco::UUIDGenerator::defaultGenerator().createFromName(Poco::UUID::uri(), _filename));

    _width = (int)ofRandom(320,640);
    _height = (int)ofRandom(320,640);
    _duration = (int)ofRandom(320,32000);
    _numFrames = (int)ofRandom(10,1000);
    _playCount = (int)ofRandom(10,1000);
}


KibioAsset::~KibioAsset()
{
}


string KibioAsset::getFilename() const
{
    return _filename;
}


KibioAsset::Type KibioAsset::getType() const
{
    return _fileType;
}


Poco::UUID KibioAsset::getUUID() const
{
    return _uuid;
}

Poco::URI KibioAsset::getURI() const
{
    return Poco::URI(getFilename());
}


void KibioAsset::setDuration(unsigned long long duration)
{
    _duration = duration;
}


unsigned long long KibioAsset::getDuration() const
{
    return _duration;
}


void KibioAsset::setNumFrames(unsigned long long numFrames)
{
    _numFrames = numFrames;
}


unsigned long long KibioAsset::getNumFrames() const
{
    return _numFrames;
}

//void KibioAsset::addToPlaylist(KibioPlaylistItem* playlistItem);
//
//void KibioAsset::removeFromPlaylist(KibioPlaylistItem* playlistItem)
//
//void KibioAsset::playCountReset();
//
//void KibioAsset::playCountAdd();
//
//void KibioAsset::playCountSubtract();
