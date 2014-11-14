//
//  Particle.cpp
//  Emergence03
//
//  Created by Franc Camps-Febrer on 10/29/14.
//
//

#include "Particle.h"


//------------------------------------------------------------------
void Particle::setup(ofPoint p, ofVec3f v){
    pos.x = p.x;
    pos.y = p.y;
    pos.z = p.z;
    
    ofVec3f velOffset = ofVec3f(ofRandom(-0.5, .5), ofRandom(-.5, .5), ofRandom(-.5, .5));
    
    vel.x = v.x*.005 + velOffset.x;
    vel.y = v.y*.005 + velOffset.y;
    vel.z = v.z*.005 + velOffset.z;
    
    fear = 0;
}

//------------------------------------------------------------------
void Particle::update() {
    mAge++;
    if (mAge > mLifespan || radius < 0.01){
        mIsDead = true;
    }
    
    float agePer = 1.0f - ( mAge / (float)mLifespan );
    
    vel += acc;
    pos += vel;
    vel *= decay;
    acc.set(0, 0);
    
    pullToCenter();
//    radius = radius*agePer;
    
    float maxSpeed = 10;
    float minSpeed = 1;
    
    float velLengthSqrd = vel.lengthSquared();
    if( velLengthSqrd > maxSpeed*maxSpeed ) {
        vel.normalize();
        vel *= maxSpeed;
    } else if( velLengthSqrd < minSpeed*minSpeed ) {
        vel.normalize();
        vel *= minSpeed;
    }
}

//------------------------------------------------------------------
void Particle::draw() {
    ofSetColor(240, 225, 142, 250);
    ofFill();
    ofDrawSphere(pos.x, pos.y, pos.z, radius);
}

//------------------------------------------------------------------
void Particle::reset() {
    mAge = 0;
    mLifespan = 60000;
    mIsDead = false;
    
    //the unique val allows us to set properties slightly differently for each particle
    // This is used as a seed for other stuff
    seed = ofRandom(-10000, 10000);
    
    // Random velocity to start with limited range
    decay = ofRandom(0.97, 0.98);
    
    radius0 = ofRandom(4, 5);
    radius = radius0;
}

//------------------------------------------------------------------
void Particle::pullToCenter(){
    ofVec3f dirToCenter   = pos - ofPoint(0, 0, 0);
    float distToCenter  = dirToCenter.length();
    float maxDistance   = 300.0f;
    
    if( distToCenter > maxDistance ){
        float pullStrength = 0.0001f;
        vel -= dirToCenter.normalized() * ( ( distToCenter - maxDistance ) * pullStrength );
    }
}