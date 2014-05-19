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


#include "KibioAsset.h"
#include "KibioWarper.h"


class KibioPlaylistItem
{
public:
    KibioPlaylistItem(KibioAsset& asset): _asset(asset)
    {
//        asset.addToPlaylist(this);
    }
    
    virtual ~KibioPlaylistItem()
    {
//        asset.removeFromPlaylist(this);
    }

    KibioAsset& getKibioAssetRef()
    {
        return _asset;
    }
        
private:
    
    KibioWarper::Settings _warperSettings;
    
    KibioAsset& _asset;
    
    Poco::UUID _uuid;
    
    
    /*
     
     // playlist item object
     {
       "playlistId":"12345",
       "playlistItemId":"xyz123",
       "playlistItemAssetId":"qwerty890",
    }

     // playlist object
     
     {
        "playlistName":"my cool playlist",
        "playlistId":"12345",
        "playlistItems" : [ // an array of 
             {
             "playlistId":"12345",
             "playlistItemId":"xyz123",
             "playlistItemAssetId":"qwerty890",
             }

             {
             "playlistId":"12345",
             "playlistItemId":"xyz123",
             "playlistItemAssetId":"qwerty890",
             }

             {
             "playlistId":"12345",
             "playlistItemId":"xyz123",
             "playlistItemAssetId":"qwerty890",
             }
         ]
     }
     
     
     */
    
    


};

class KibioPlaylist
{
public:
    enum RepeatMode
    {
        NONE,
        ONE,
        ALL
    };

    void getNext();
    void getPrevious();
    void getRandom();

    bool isShuffling() const;
    void setIsShuffling(bool isShuffling);
    
    RepeatMode getRepeatMode() const;
    
    void setRepeatMode(RepeatMode repeatMode);
    
    std::size_t getSize() const;

public:
    bool _isShuffling;
    RepeatMode _repeatMode;
    
    std::vector<KibioPlaylistItem> _playlist;

};
