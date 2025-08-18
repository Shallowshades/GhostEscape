#ifndef ENEMY_H
#define ENEMY_H

#include "core/actor.h"
#include "player.h"

class Enemy : public Actor {
public:
    virtual void init() override;
    virtual void update(float deltaTime) override;
    void animationTarget(Player* target);
public:
    void setTarget(Player* target) { target_ = target; }
    Player* getTarget() const { return target_; }
private:
    Player* target_ = nullptr;
};

#endif // ENEMY_H