#pragma once

#include "ofVboMesh.h" 


class KibioWarper : public ofVboMesh  {
public:
    
    struct Settings;
    
    KibioWarper();
    virtual ~KibioWarper();
    
    
    struct Settings {
        int meshResolutionX;
        int meshResolutionY;
    };
    
private:
    Settings settings;
    
    
};