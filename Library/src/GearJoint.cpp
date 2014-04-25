//
//  GearJoint.cpp
//  Stonefish
//
//  Created by Patryk Cieslak on 28/03/2014.
//  Copyright (c) 2014 Patryk Cieslak. All rights reserved.
//

#include "GearJoint.h"

GearJoint::GearJoint(std::string uniqueName, SolidEntity* solidA, SolidEntity* solidB, const btVector3& axisA, const btVector3& axisB, btScalar ratio) : Joint(uniqueName, false)
{
    gearRatio = ratio;
    
    btRigidBody* bodyA = solidA->getRigidBody();
    btRigidBody* bodyB = solidB->getRigidBody();
    btVector3 axisInA = bodyA->getCenterOfMassTransform().getBasis().inverse() * axisA.normalized();
    btVector3 axisInB = bodyB->getCenterOfMassTransform().getBasis().inverse() * axisB.normalized();
    
    btGearConstraint* gear = new btGearConstraint(*bodyA, *bodyB, axisInA, axisInB, gearRatio);
    setConstraint(gear);
}

GearJoint::~GearJoint()
{
}

JointType GearJoint::getType()
{
    return GEAR;
}

btVector3 GearJoint::Render()
{
    btGearConstraint* gear = (btGearConstraint*)getConstraint();
    btVector3 axisA = gear->getRigidBodyA().getCenterOfMassTransform().getBasis() * gear->getAxisA();
    btVector3 axisB = gear->getRigidBodyB().getCenterOfMassTransform().getBasis() * gear->getAxisB();
    btVector3 A = gear->getRigidBodyA().getCenterOfMassPosition();
    btVector3 B = gear->getRigidBodyB().getCenterOfMassPosition();
    btVector3 rA = ((B-A).cross(axisA)).normalized();
    btVector3 rB = ((A-B).cross(axisB)).normalized();
    btVector3 rBp = axisB.cross(rB).normalized();
    btScalar f1 = rBp.dot(axisA);
    btScalar f2 = (B-A).dot(axisA);
    btScalar rAn;
    btScalar rBn;
    
    if(f1 == 0)
    {
        if(axisA.dot(axisB) < 0.001f) // perpendicular
            rBn = (A-B).dot(rBp);
        else
            rBn = (A-B).length()/(gearRatio + btScalar(1.f)) * gearRatio;
    }
    else
        rBn = f2/f1;
    
    rAn = rBn/gearRatio;
    
    glDummyColor();
    //circle A
    glBegin(GL_LINE_STRIP);
    for(int i=0; i<=24; i++)
        glBulletVertex(A + rA.rotate(axisA, i/btScalar(12.) * M_PI) * rAn);
    glEnd();
    //circle B
    glBegin(GL_LINE_STRIP);
    for(int i=0; i<=24; i++)
        glBulletVertex(B + rB.rotate(axisB, i/btScalar(12.) * M_PI) * rBn);
    glEnd();
    
    return B + rBn*rBp;
}

btScalar GearJoint::getRatio()
{
    return gearRatio;
}