//
//  particle.h
//  Emergence03
//
//  Created by Franc Camps-Febrer on 10/29/14.
//
//

#ifndef __Emergence03__particle__
#define __Emergence03__particle__

#endif

#pragma once
#include "ofMain.h"

class Particle {
    
public:
//    Particle(ofPoint pos, ofVec3f vel);
    
    void setup(ofPoint pos, ofVec3f vel);
    void reset();
    void update();
    void draw();
    void pullToCenter();
    
    // Position x,y
    ofPoint pos;
    // Velocity x,y
    ofPoint vel;
    // Force x,y?
    ofPoint acc;
    float mass;
    
    float decay;
    
    float radius0;
    float radius;
    
    float seed;
    float noise;
    
    int mAge;
    int mLifespan;
    bool mIsDead;
    float fear;
};