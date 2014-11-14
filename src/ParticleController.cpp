//
//  ParticleController.cpp
//  Emergence03
//
//  Created by Franc Camps-Febrer on 10/29/14.
//
//

#include "Predator.h"
#include "PredatorController.h"
#include "Particle.h"
#include "ParticleController.h"

ParticleController::ParticleController(){
    
}

void ParticleController::addParticles(ofPoint p, ofVec3f v){
    for(unsigned int i = 0; i < 5; i++ ) {
        
        ofVec3f rand = ofVec3f(ofRandom(-10, 10), ofRandom(-10, 10), ofRandom(-10, 10));
        p = ofPoint(p.x + rand.x, p.y + rand.y);
        
        Particle pa;
        pa.setup( p, v );
        pa.reset();
        mParticles.push_back( pa );
    }
}

void ParticleController::removeParticles(){
    
}

void ParticleController::resetParticles(){
    for( list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p ){
        p->reset();
    }
}

void ParticleController::update(){
    for( list<Particle>::iterator p = mParticles.begin(); p != mParticles.end();){
        if( p->mIsDead ) {
            p = mParticles.erase(p);
        } else {
            p->update();
            ++p;
        }
    }
}

void ParticleController::applyForce( float zoneRadiusSqrd, float lowThresh, float highThresh ){
    for( list<Particle>::iterator p1 = mParticles.begin(); p1 != mParticles.end(); ++p1 ) {
        
        list<Particle>::iterator p2 = p1;
        
        for( ++p2; p2 != mParticles.end(); ++p2 ) {
           
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

void ParticleController::applyForceToParticles(float zoneRadiusSqrd, list<Predator> mPredators){
    float eatDistSqrd = 10.0f;
    float predatorZoneRadiusSqrd = zoneRadiusSqrd * 3.0f;

    for( list<Particle>::iterator p1 = mParticles.begin(); p1 != mParticles.end(); ++p1 ) {
    
        for( list<Predator>::iterator predator = mPredators.begin(); predator != mPredators.end(); ++predator ) {
            ofVec3f dir = p1->pos - predator->pos;
            float distSqrd = dir.lengthSquared();
            
            if( distSqrd < predatorZoneRadiusSqrd ){
                if( distSqrd > eatDistSqrd ){
                    float F = ( predatorZoneRadiusSqrd/distSqrd - 1.0f ) * 0.1f;
                    p1->fear += F * 0.1f;
                    dir = dir.normalized() * F;
                    p1->acc += dir;
                    predator->acc += dir;
                } else {
                    p1->mIsDead = true;
                    predator->isHungry = false;
                    // predator->mHunger -= p1->mMass;
                }
            }
        }
    }
}

void ParticleController::draw(){
    for( list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p ){
        p->draw();
    }
}