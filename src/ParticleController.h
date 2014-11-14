//
//  ParticleController.h
//  Emergence03
//
//  Created by Franc Camps-Febrer on 10/29/14.
//
//

#ifndef __Emergence03__ParticleController__
#define __Emergence03__ParticleController__

#include <stdio.h>

#endif /* defined(__Emergence02__ParticleController__) */

#pragma once
#include "ofMain.h"
#include <list>

class ParticleController {
public:
    ParticleController();
    
    void update();
    void draw();
    
    void addParticles(ofPoint p, ofVec3f mv);
    void removeParticles();
    void applyForce(float f, float lowThresh, float highThresh);
    void applyForceToParticles(float zoneRadiusSqrd, list<Predator> mPredators);
    void resetParticles();
    
    std::list<Particle> mParticles;
};