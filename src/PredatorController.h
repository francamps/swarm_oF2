//
//  PredatorController.h
//  Emergence03
//
//  Created by Franc Camps-Febrer on 10/29/14.
//
//

#ifndef __Emergence03__PredatorController__
#define __Emergence03__PredatorController__

#include <stdio.h>

#endif /* defined(__Emergence03__PredatorController__) */

#pragma once
#include "ofMain.h"
#include <list>

class PredatorController {
public:
    PredatorController();
    
    void update();
    void draw();
    
    void addPredators(ofPoint p, ofVec3f mv);
    void removePredators();
    void applyForce(float f, float lowThresh, float highThresh);
    void resetPredators();
    
    std::list<Predator> mPredators;
};