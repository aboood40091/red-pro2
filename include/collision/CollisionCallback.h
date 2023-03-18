#pragma once

#include <math/seadVector.h>

class Actor;
class ActorCollisionCheck;
class BgCollision;

class CollisionCallback
{
public:
    virtual bool ccCallback0(Actor*, ActorCollisionCheck*, const sead::Vector2f&);
    virtual bool ccCallback1(Actor*, ActorCollisionCheck*, const sead::Vector2f&) { return false; }
    virtual bool ccCallback2(Actor*, ActorCollisionCheck*, const sead::Vector2f&);
    virtual void ccCallback3(Actor*, ActorCollisionCheck*, const sead::Vector2f&) { }
    virtual void ccCallback4(Actor*, ActorCollisionCheck*, const sead::Vector2f&) { }
    virtual bool bcCallback0(Actor*, BgCollision*, const sead::Vector2f&);
    virtual bool bcCallback1(Actor*, BgCollision*, const sead::Vector2f&) { return false; }
    virtual bool bcCallback2(Actor*, BgCollision*, const sead::Vector2f&);
    virtual void bcCallback3(Actor*, BgCollision*, const sead::Vector2f&) { }
    virtual void bcCallback4(Actor*, BgCollision*, const sead::Vector2f&) { }
};
static_assert(sizeof(CollisionCallback) == 4);
