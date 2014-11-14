//
//  PredatorController.cpp
//  Emergence03
//
//  Created by Franc Camps-Febrer on 10/29/14.
//
//

#include "Predator.h"
#include "PredatorController.h"

PredatorController::PredatorController(){
    
}

void PredatorController::addPredators(ofPoint p, ofVec3f v){
    for(unsigned int i = 0; i < 5; i++ ) {
        
        ofVec3f rand = ofVec3f(ofRandom(-10, 10), ofRandom(-10, 10), ofRandom(-10, 10));
        p = ofPoint(p.x + rand.x, p.y + rand.y);
        
        Predator pa;
        pa.setup( p, v );
        pa.reset();
        mPredators.push_back( pa );
    }
}

void PredatorController::removePredators(){
    
}

void PredatorController::resetPredators(){
    for( list<Predator>::iterator p = mPredators.begin(); p != mPredators.end(); ++p ){
        p->reset();
    }
}

void PredatorController::update(){
    for( list<Predator>::iterator p = mPredators.begin(); p != mPredators.end();){
        if( p->mIsDead ) {
            p = mPredators.erase(p);
        } else {
            p->update();
            ++p;
        }
    }
}

void PredatorController::applyForce( float zoneRadiusSqrd, float lowThresh, float highThresh ){
    for( list<Predator>::iterator p1 = mPredators.begin(); p1 != mPredators.end(); ++p1 ) {
        
        list<Predator>::iterator p2 = p1;
        
        for( ++p2; p2 != mPredators.end(); ++p2 ) {
            
            ofVec3f dir = p1->pos - p2->pos;
            float distSqrd = dir.lengthSquared();
            
            
            if( distSqrd <= zoneRadiusSqrd ) {	// SEPARATION
                float percent = distSqrd / zoneRadiusSqrd;
                
                if (percent < lowThresh) {
                    float F = ( lowThresh/percent - 1.0f ) * 0.01f;
                    dir = dir.normalize() * F;
                    p1->acc += dir;
                    p2->acc -= dir;
                } else if (percent < highThresh){
                    float threshDelta = highThresh - lowThresh;
                    float adjustedPercent = ( percent - lowThresh )/threshDelta;
                    float F = ( 0.5f - cos( adjustedPercent * M_PI * 2.0f ) * 0.5f + 0.5f ) * 0.01f;
                    p1->acc += p2->vel.normalized() * F;
                    p2->acc += p1->vel.normalized() * F;
                } else {
                    float threshDelta = 1.0f - highThresh;
                    float adjustedPercent = ( percent - highThresh )/threshDelta;
                    float F = ( 1.0 - ( cos( adjustedPercent * M_PI*2.0f ) * -0.5f + 0.5f ) ) * 0.04f;
                    dir = dir.normalized() * F;
                    p1->acc -= dir;
                    p2->acc += dir;
                }
            }
        }
    }
}

void PredatorController::draw(){
    for( list<Predator>::iterator p = mPredators.begin(); p != mPredators.end(); ++p ){
        p->draw();
    }
}