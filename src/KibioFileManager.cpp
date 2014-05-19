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


#include "KibioFileManager.h"


KibioFileManager::KibioFileManager():
    _assetsJson(Json::Value(Json::arrayValue))
{
}


KibioFileManager::~KibioFileManager()
{
}


void KibioFileManager::setup()
{
    ofDirectory dir;

    std::size_t numFiles = dir.listDir("assets");

    for(std::size_t i = 0; i < _assets.size(); i++)
    {
    }

    for(std::size_t i = 0; i < numFiles; i++)
    {
        KibioAsset::Type type = (ofRandom(100) > 50 ? KibioAsset::SOUND : KibioAsset::VIDEO);
        KibioAsset ass(dir[i].getAbsolutePath(),type);
        _assets.push_back(ass);
        _assetsJson.append(ass.getJSON());
    }
}

const Json::Value& KibioFileManager::getJSON() const
{
    return _assetsJson;
}
