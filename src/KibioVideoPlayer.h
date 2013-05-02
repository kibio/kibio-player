#pragma once

#include "ofVideoPlayer.h"

#include "KibioPlaylist.h"

class KibioVideoPlayer : public ofVideoPlayer {
public:
    KibioVideoPlayer() { }
    virtual ~KibioVideoPlayer() { }
    
    KibioPlaylist playlist;

};
