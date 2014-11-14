//
//  predator.h
//  Emergence03
//
//  Created by Franc Camps-Febrer on 10/29/14.
//
//

#ifndef __Emergence03__predator__
#define __Emergence03__predator__

#endif

#pragma once
#include "ofMain.h"

class Predator {
    
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
    bool isHungry;
};